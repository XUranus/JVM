//
// Created by xuranus on 2/7/19.
//


#include "../../native/java/lang/Class.h"
#include <cassert>
#include "Object.h"
#include "../../common/Console.h"
#include "../../common/Exception.h"
#include "ClassLoader.h"
#include "StringPool.h"
#include "ObjectPool.h"

#include "Class.h"

namespace heap {

    Class::~Class() {
        if(classloader) {
            classloader->classMap.erase(name);
        }
        delete constantPool;
        // delete jClass; // todo:: do this in object pool
    }


    // basic initialize from class file
    Class::Class(classfile::ClassFile* classFile):
        name(classFile->className()),
        superClassName(classFile->superClassName()),
        sourceFileName(classFile->sourceFileName()),
        interfacesNames(classFile->interfacesNames()),
        constantPool(new ConstantPool(this, classFile->constantPool.get())),
        staticVars(0) { // init later link() -> initStaticVars();

        accessFlags = classFile->accessFlags;
        fields.reserve(classFile->fieldCount);
        methods.reserve(classFile->methodCount);

        for(int i = 0; i < classFile->fieldCount; i++) {
            fields.emplace_back(classFile->fields[i].get(), this, constantPool);
        }

        for(int i = 0; i < classFile->methodCount; i++) {
            methods.emplace_back(classFile->methods[i].get(), this, constantPool);
        }

        classloader = nullptr;//init later in defineClass()
        superClass = nullptr;//init later in define() -> resolveSuperClass();
        interfaces.resize(classFile->interfaceCount);//init later in define() -> resolveInterfaces();

        instanceSlotCount = 0;//init later in link() -> calculateInstanceSlotCount();
        staticSlotCount = 0;//init later in link() -> calculateStaticSlotCount();

        initStarted = false; // set true after <clinit> invoked
        jClass = nullptr;
    }

    void Class::resolveSuperClass() {
        assert(classloader != nullptr);
        if (name != "java/lang/Object") {
            superClass = classloader->loadClass(superClassName); //recursive load
        }
    }

    void Class::resolveInterfaces() {
        assert(classloader != nullptr);
        for (int i = 0; i < interfacesNames.size(); i++) {
            interfaces[i] = classloader->loadClass(interfacesNames[i]);
        }
    }

    Class::Class(const std::string &className, ClassLoader* loader, bool array): // short, int, float,... or [I, [[B ...
        name(className),
        staticVars(0) {

        constantPool = nullptr; // primitive class or array class has no constants pool
        accessFlags = ACC_PUBLIC_FLAG;
        classloader = loader;

        instanceSlotCount = 0;
        staticSlotCount = 0;

        if(array) { // array class has super class: "java/lang/Object", interface: "java/lang/Cloneable", "java/io/Serializable"
            superClassName = "java/lang/Object";
            superClass = loader->loadClass("java/lang/Object");
            interfacesNames = {"java/lang/Cloneable", "java/io/Serializable"};
            interfaces = {loader->loadClass("java/lang/Cloneable"), loader->loadClass("java/io/Serializable")};
        } else {
            superClass = nullptr; // primitive class has no super class or interfaces
        }

        initStarted = true; // primitive class or array class has no <clinit> method
        jClass = nullptr;
    }


    void Class::calculateInstanceFieldSlotsId() {
        unsigned int slotId = 0;
        if (superClass) {
            slotId = superClass->instanceSlotCount;
        }
        for (Field& field: fields) {
            if (!field.isStatic()) { // field is not static
                field.slotId = slotId;
                slotId++;
                if (field.isLongOrDouble()) {
                    slotId++;
                }
            }
        }
        instanceSlotCount = slotId;
    }

    void Class::calculateStaticFieldSlotsId() {
        unsigned int slotId = 0;
        for (Field& field: fields) {
            if (field.isStatic()) { // field is static
                field.slotId = slotId;
                slotId++;
                if (field.isLongOrDouble()) {
                    slotId++;
                }
            }
        }
        staticSlotCount = slotId;
    }

    void Class::allocAndInitializeStaticVars() {
        staticVars.resize(staticSlotCount);

        for (Field& field: fields) {
            if (field.isStatic() && field.isFinal()) { // static final field need to be initialized now
                u2 index = field.constValueIndex; // index of constant pool
                std::string descriptor = field.descriptor;
                u4 slotId = field.slotId;

                if(index == 0) { //invalid constant pool index
                    continue;
                }

                if (descriptor == "Z" || descriptor == "B" || descriptor == "C" || descriptor == "S" || descriptor == "I") {
                    // bool, byte, char, short, integer are stored as integer in constant pool
                    int val = constantPool->intValue(index);
                    staticVars.setInt(slotId, val);
                } else if (descriptor == "J") { // long
                    long val = constantPool->longValue(index);
                    staticVars.setLong(slotId, val);
                } else if (descriptor == "F") { // float
                    float val = constantPool->floatValue(index);
                    staticVars.setFloat(slotId, val);
                } else if (descriptor == "D") { // double
                    double val = constantPool->doubleValue(index);
                    staticVars.setDouble(slotId, val);
                } else if (descriptor == "Ljava/lang/String;") {
                    std::string localStr = constantPool->stringValue(index);
                    heap::Object* jStr = StringPool::JString(classloader, localStr);
                    staticVars.setRef(slotId, jStr);
                } else {
                    exception::panic("initialize static final field failed, unknown descriptor:" + descriptor);
                }
            }
        }

    }


    Method *Class::getInstanceMethod(const std::string &methodName, const std::string &descriptor) const {
        return getMethod(methodName, descriptor, false);
    }

    Object *Class::getRefVar(const std::string &fieldName, const std::string &fieldDescriptor) const {
        Field* field = getField(fieldName, fieldDescriptor, true);
        return staticVars.refValue(field->slotId);
    }

    void Class::setRefVar(const std::string &fieldName, const std::string &fieldDescriptor, Object *ref)  {
        Field* field = getField(fieldName, fieldDescriptor, true);
        staticVars.setRef(field->slotId, ref);
    }

    // get field in class and its super class
    Field *Class::getField(const std::string &fieldName, const std::string &descriptor, bool isStatic) const {
        for (const Class* c = this; c != nullptr; c = c->superClass) {
            for (const Field& field: c->fields) {
                if (field.isStatic() == isStatic &&
                    (field.name == fieldName) &&
                    (field.descriptor == descriptor)) {
                    return const_cast<Field *>(&field);
                }
            }
        }
        return nullptr;
    }


    Method *Class::getMethod(const std::string &methodName, const std::string &descriptor, bool isStatic) const {
        for (const Class* c = this; c != nullptr; c = c->superClass) {
            for (const Method& method: c->methods) {
                if (((method.isStatic()) == isStatic) &&
                    method.name == methodName &&
                    method.descriptor == descriptor) {
                    return const_cast<Method *>(&method);
                }
            }
        }
        exception::fatal("could not get " + std::string((isStatic ? "static" : "non-static")) + " method:" + methodName + descriptor);
        return nullptr;
    }




    bool Class::accessibleTo(Class *c) const {
        // if class c can access this class
        return isPublic() || (c->packageName() == this->packageName());
    }


    // class: java/lang/String, package name: java/lang
    std::string Class::packageName() const {
        auto index = name.rfind('/');
        if (index != std::string::npos) {
            return name.substr(0, index);
        } else {
            return "";
        }
    }

    bool Class::isInitStarted() const {
        return initStarted;
    }

    void Class::markInitStarted() {
        initStarted = true;
    }


    void Class::resolveJClass() {
        if(!jClass) {
            jClass = classloader->loadClass("java/lang/Class")->newObject();
            //jClass->setRefVar("name", "Ljava/lang/String;", heap::StringPool::JString(classloader, getJavaName()));
            native::java::lang::Class::jClassSetRegister(jClass, this);
        }
    }


    Field *Class::lookUpField(const std::string &fieldName, const std::string &descriptor) const {
        // lookup field in this class fields
        for (const Field& field: fields) {
            if (field.name == fieldName && field.descriptor == descriptor)
                return const_cast<Field *>(&field);
        }
        // lookup field in fields of interfaces
        for (Class* interface: interfaces) {
            Field* field = interface->lookUpField(fieldName, descriptor);
            if (field != nullptr) {
                return field;
            }
        }
        // lookup field in fields of superclass
        if (superClass) {
            return superClass->lookUpField(fieldName, descriptor);
        }
        return nullptr;
    }

    /**
     *  1. lookup method in this or its super class
     *  2. lookup method in its interface,
     *      because interface can also have default implementation for its method since java 8
     */
    Method *Class::lookUpMethod(const std::string &methodName, const std::string &descriptor) const {
        Method* method = this->lookUpMethodInClass(methodName, descriptor);
        if (method == nullptr) {
            method = this->lookUpMethodInInterfaces(methodName, descriptor);
        }
        return method;
    }

    Method *Class::lookUpMethodInClass(const std::string &methodName, const std::string &descriptor) const {
        for (const Class* c = this; c != nullptr; c = c->superClass) {
            for (const Method& method: c->methods) {
                if (method.name == methodName && method.descriptor == descriptor) {
                    return const_cast<Method *>(&method);
                }
            }
        }
        return nullptr;
    }

    /**
     * lookup interface method in a interface
     * 1. lookup method in current class's methods
     * 2. lookup methods in methods of super interfaces
     */
    Method *Class::lookUpInterfaceMethod(const std::string &methodName, const std::string &descriptor) const {
        for (const Method& method: methods) {
            if (method.name == methodName && method.descriptor == descriptor) {
                return const_cast<Method *>(&method);
            }
        }
        return lookUpMethodInInterfaces(name, descriptor);
    }

    Method *Class::lookUpMethodInInterfaces(const std::string &methodName, const std::string &descriptor) const {
        for (const Class* interface: interfaces) {
            for (const Method& method: interface->methods) {
                if (method.name == methodName && method.descriptor == descriptor) {
                    return const_cast<Method *>(&method);
                }
            }
            Method* method = interface->lookUpMethodInInterfaces(methodName, descriptor);
            if (method != nullptr) {
                return method;
            }
        }
        return nullptr;
    }

    Object *Class::newObject() {
        return ObjectPool::createObject(this);
    }

    Object *Class::newArrayObject(int length) {
        assert(isArray());
        return ObjectPool::createObject(this, length);
    }

    Object *Class::newMultiDimensionArray(const std::vector<int> &dimensions) {
        int length = dimensions[0];
        Object* arrayObject = this->newArrayObject(length);

        if (dimensions.size() > 1) {
            Object** objectRefArray = arrayObject->objectRefArray();
            for (int i = 0; i < arrayObject->arrayLength(); i++) {
                std::vector<int> newDimensions;
                for (int j = 1; j < dimensions.size(); j++) {
                    newDimensions.push_back(dimensions[j]);
                }

                objectRefArray[i] = this->componentClass()->newMultiDimensionArray(newDimensions);
            }
        }
        return arrayObject;
    }

    Class *Class::arrayClass() const {
        std::string arrayClassName;
        if (name[0] == '[') { // is array class
            arrayClassName = name; // example: [Ljava/lang/String -> [Ljava/lang/String;
        } if (this->isPrimitive()) { // is primitive type (int, short, bool, ....)
            arrayClassName = primitiveTypes[name]; // example: int -> I
        } else { // is common class {
            arrayClassName = std::string("L") + name + ";"; // example: java/lang/String -> Ljava/lang/String;
        }

        arrayClassName = std::string("[") + arrayClassName;
        return classloader->loadClass(arrayClassName);
    }

    Class *Class::componentClass() const {
        assert(isArray()); // must be array class
        std::string componentTypeDescriptor = name.substr(1); // remove first '['

        std::string componentClassName;
        if(componentTypeDescriptor[0] == '[') { // still array component
            componentClassName = componentTypeDescriptor;
        } else if (componentTypeDescriptor[0] == 'L') { //class ref
            componentClassName = componentTypeDescriptor.substr(1, componentTypeDescriptor.length() - 2);
            // example: Ljava/lang/String => java/lang/String
        } else { // primitive type
            for (auto &ele: primitiveTypes) { // primitive(int double ...) type descriptor
                if (ele.second == componentTypeDescriptor) {
                    componentClassName = ele.first;
                    break;
                }
            }
        }

        assert(!componentClassName.empty());
        return classloader->loadClass(componentClassName);
    }

    bool Class::isArray() const {
        return name[0] == '[';
    }

    bool Class::isPrimitive() const {
        return primitiveTypes.find(name) != primitiveTypes.end();
    }

    // weather class s can be cast to this class
    bool Class::isAssignableFrom(const Class *s) const {
        if (this == s) {
            return true;
        }
        if (!s->isArray()) {
            if (!s->isInterface()) {
                if (!this->isInterface()) {
                    return s->isSubClassOf(this);
                } else {
                    return s->isImplements(this);
                }
            } else {
                if (!this->isInterface()) {
                    return this->isJlObject();
                } else {
                    return this->isSuperInterfacesOf(s);
                }
            }
        } else {
            if (!this->isArray()) {
                if (!this->isInterface()) {
                    return this->isJlObject();
                } else {
                    return this->isJlCloneable() || this->isJioSerializable();
                }
            } else {
                Class* sc = s->componentClass();
                Class* tc = this->componentClass();
                return sc == tc || tc->isAssignableFrom(sc);
            }
        }
    }

    bool Class::isImplements(const Class *interface) const {
        for (const Class* c = this; c != nullptr; c = c->superClass) {
            for (const Class *i: c->interfaces) {
                if (interface == i || i->isSubInterfacesOf(interface)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool Class::isInterface() const { return accessFlags & ACC_INTERFACE_FLAG;}

    bool Class::isAbstract() const {return accessFlags & ACC_ABSTRACT_FLAG;}

    bool Class::isPublic() const { return accessFlags & ACC_PUBLIC_FLAG;}

    bool Class::isFinal() const { return accessFlags & ACC_FINAL_FLAG;}

    bool Class::isSuper() const { return accessFlags & ACC_SUPER_FLAG;}

    bool Class::isSynthetic() const { return accessFlags & ACC_SYNTHETIC_FLAG;}

    bool Class::isAnnotation() const { return accessFlags & ACC_ANNOTATION_FLAG;}

    bool Class::isEnum() const { return accessFlags & ACC_ENUM_FLAG;}

    bool Class::isSubClassOf(const Class *other) const {
        for(const Class* c = superClass; c != nullptr; c = c->superClass) {
            if(c == other) {
                return true;
            }
        }
        return false;
    }

    bool Class::isSuperClassOf(const Class *c) const {
        for (const Class* sup = c->superClass; sup != nullptr; sup = sup->superClass) {
            if (sup == this) {
                return true;
            }
        }
        return false;
    }

    bool Class::isSubInterfacesOf(const Class *interface) const {
        assert(isInterface());
        for (const Class* i: interfaces) {
            if (interface == i || i->isSubInterfacesOf(interface)) {
                return true;
            }
        }
        return false;
    }

    bool Class::isSuperInterfacesOf(const Class *interface) const {
        assert(isInterface());
        return interface->isSubInterfacesOf(this);
    }

    bool Class::isJlObject() const {
        return name == "java/lang/Object";
    }

    bool Class::isJlCloneable() const {
        return name == "java/lang/Cloneable";
    }

    bool Class::isJioSerializable() const {
        return name == "java/lang/Serializable";
    }

    // java/lang/String => java.lang.String
    std::string Class::getJavaName() const {
        std::string javaName = name;
        for (char &c: javaName) {
            if (c == '/') c = '.';
        }
        return javaName;
    }

    Method *Class::getClinitMethod() const {
        return getStaticMethod("<clinit>", "()V");
    }

    Method *Class::getMainMethod() const {
        return getStaticMethod("main", "([Ljava/lang/String;)V");
    }

    Method *Class::getStaticMethod(const std::string &methodName, const std::string &descriptor) const {
        for (const Method& method: methods) {
            if (method.isStatic()
                && method.name == methodName && method.descriptor == descriptor) {
                return const_cast<Method *>(&method);
            }
        }
        return nullptr;
    }

    std::vector<Method *> Class::getMethods(bool publicOnly) {
        std::vector<Method*> res;
        for(Method& method: methods) {
            if(!method.isClinit() && !method.isConstructor()) {
                if(!publicOnly || method.isPublic()) {
                    res.push_back(&method);
                }
            }
        }
        return res;
    }

    std::vector<Method *> Class::getConstructors(bool publicOnly) {
        std::vector<Method*> res;
        for(Method& method: methods) {
            if(method.isConstructor()) {
                if(!publicOnly || method.isPublic()) {
                    res.push_back(&method);
                }
            }
        }
        return res;
    }

    std::vector<Field *> Class::getFields(bool publicOnly) {
        std::vector<Field*> res;
        for(Field& field: fields) {
            if(!publicOnly || field.isPublic()) {
                res.push_back(&field);
            }
        }
        return res;
    }


    Method *Class::getConstructor(const std::string &descriptor) const {
        return getInstanceMethod("<init>", descriptor);
    }

    std::set<heap::Object *> Class::staticFieldObjects() const {
        std::set<Object*> res;
        for(auto& field: fields) {
            if(field.isStatic() && field.isRef()) {
                heap::Object* object = staticVars.refValue(field.slotId);
                assert(object == nullptr || (object < ObjectPool::pool + ObjectPool::capacity && object > ObjectPool::pool));
                res.insert(object);
            }
        }
        return res;
    }
}