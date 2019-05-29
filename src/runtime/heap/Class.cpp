//
// Created by xuranus on 2/7/19.
//

#include "Class.h"
#include "Object.h"
#include "../../util/Console.h"
#include "ClassLoader.h"
#include "StringPool.h"
#include "ObjectPool.h"

Class::Class(ClassFile *classFile) {
    //basic initialize from class file
    accessFlags = classFile->accessFlags;
    name = classFile->getThisClassName();
    superClassName = classFile->getSuperClassName();
    interfacesNames = classFile->getInterfacesNames();
    constantPool = new ConstantPool(this,classFile);


    fields = Field::parseFields(classFile,this);
    methods = Method::parseMethods(classFile,this);

    instanceSlotCount = 0;//init later in link() -> calculateInstanceSlotCount();
    staticSlotCount = 0;//init later in link() -> calculateStaticSlotCount();
    staticVars = nullptr;//init later link() -> initStaticVars();

    superClass = nullptr;//init later in define() -> resolveSuperClass();
    interfaces.clear();//init later in define() -> resolveInterfaces();
    classloader = nullptr;//init later in defineClass()

    jClass = nullptr;
    initStarted = false;//TODO::???!!
}


Class::Class(std::string &arrayClassName):name(arrayClassName)
{
    // for array init use
    accessFlags = ACC_PUBLIC_FLAG;//TODO::
    superClassName = "java/lang/Object";
    interfacesNames.emplace_back("java/lang/Cloneable");
    interfacesNames.emplace_back("java/io/Serializable");
    constantPool= nullptr;
    fields.clear();
    methods.clear();

    instanceSlotCount = 0;
    staticSlotCount = 0;
    staticVars = nullptr;

    superClass = nullptr;
    interfaces.clear();
    classloader = nullptr;
    jClass = nullptr;
    initStarted = true;
}

void Class::debug()
{
    printf("[Debug Class]\n");
    printf("name:%s\n",name.c_str());
    printf("staticVarsCount:%d\n",staticSlotCount);
    printf("instanceSlotsCount:%d\n",instanceSlotCount);
    if(staticVars != nullptr) staticVars->debug();
    printf("\n");
    //TODO::complete it
}

void Class::calculateInstanceFieldSlotsId()
{
    unsigned int slotId = 0;
    if(superClass!= nullptr)
        slotId = superClass->instanceSlotCount;
    for(auto field:fields)
    {
        if(!(field->accessFlags & ACC_STATIC_FLAG)) // field is not static
            field->slotId = slotId;
        slotId++;
        if(field->isLongOrDouble())
            slotId++;
    }
    instanceSlotCount = slotId;
}

void Class::calculateStaticFieldSlotsId()
{
    unsigned int slotId = 0;
    for(auto field:fields)
    {
        if(field->accessFlags & ACC_STATIC_FLAG) // field is static
            field->slotId = slotId;
        slotId++;
        if(field->isLongOrDouble())
            slotId++;
    }
    staticSlotCount = slotId;
}

void Class::initializeStaticVars()
{
    staticVars = new StaticVars(staticSlotCount);
    for(auto field:fields)
    {
        if((field->accessFlags & ACC_STATIC_FLAG) && (field->accessFlags & ACC_FINAL_FLAG))
            initializeStaticFinalVar(field);
    }
}

void Class::initializeStaticFinalVar(Field *field)
{
    auto index = field->constValueIndex;
    auto descriptor = field->descriptor;
    auto slotId = field->slotId;
    if(index > 0) //valid constant pool index
    {
        if(descriptor=="Z" || descriptor=="B" || descriptor=="C" || descriptor=="S" || descriptor=="I") {
            auto val = constantPool->getInt(index);
            staticVars->setInt(slotId, val);
        } else if(descriptor=="J") {
            auto val = constantPool->getLong(index);
            staticVars->setLong(slotId,val);
        } else if(descriptor=="F") {
            auto val = constantPool->getFloat(index);
            staticVars->setFloat(slotId,val);
        } else if(descriptor=="D") {
            auto val = constantPool->getDouble(index);
            staticVars->setDouble(slotId,val);
        } else if(descriptor=="Ljava/lang/Strin") {
            auto localStr = constantPool->getString(index);
            auto jStr = StringPool::getStringPool()->getJString(classloader,localStr);
            staticVars->setRef(slotId,jStr);
        } else {
            Console::printlnError("initializeStaticFinalVar faild,unknown descriptor:"+descriptor);
        }
    }
}

Method* Class::getInstanceMethod(std::string _name, std::string _descriptor) {
    return getMethod(_name,_descriptor, false);
}

Object* Class::getRefVar(std::string fieldName, std::string fieldDescriptor) {
    auto field = getField(fieldName,fieldDescriptor,true);
    return staticVars->getRef(field->slotId);
}

void Class::setRefVar(std::string fieldName, std::string fieldDescriptor, Object *ref)
{
    auto field = getField(fieldName,fieldDescriptor,true);
    staticVars->setRef(field->slotId,ref);
}

bool Class::accessibleTo(Class *c)
{
    return (accessFlags & ACC_PUBLIC_FLAG) || (c->getPackageName()==getPackageName());
}


std::string Class::getPackageName()
{
    auto index = name.rfind('/');
    if(index!=std::string::npos)
        return name.substr(0,index);
    return "";
}

Method* Class::getMethod(std::string _name, std::string _descriptor, bool isStatic)
{
    for(auto c = this;c != nullptr;c = c->superClass)
    {
        for(auto method:c->methods)
        {
            if(((method->accessFlags & ACC_STATIC_FLAG)==isStatic) && (method->name == _name) && (method->descriptor==_descriptor))
                return method;
        }
    }
    Console::printlnWarning("could not get "+std::string((isStatic?"static":"unstatic"))+" method:"+_name+_descriptor);
    return nullptr;
}

Field* Class::getField(std::string _name, std::string descriptor, bool isStatic)
{
    for(auto c = this;c != nullptr;c = c->superClass)
    {
        for(auto field:c->fields)
        {
            if(((field->accessFlags & ACC_STATIC_FLAG)==isStatic) && (field->name == _name) && (field->descriptor==descriptor))
                return field;
        }
    }
    Console::printlnWarning("could not get "+std::string((isStatic?"static":"unstatic"))+" field:"+_name+descriptor);
    return nullptr;
}

Field* Class::lookUpField(std::string _name, std::string descriptor)
{
    for(auto field:fields)
    {
        if (field->name == _name && field->descriptor == descriptor)
            return field;
    }
    for(auto interface:interfaces)
    {
        auto field = interface->lookUpField(_name,descriptor);
        if(field!=nullptr)
            return field;
    }
    if(superClass!=nullptr)
        return superClass->lookUpField(_name,descriptor);
    return nullptr;
}

Method* Class::lookUpMethod(std::string _name, std::string descriptor)
{
    auto method = lookUpMethodInClass(_name,descriptor);
    if(method== nullptr)
        method = lookUpMethodInInterfaces(_name,descriptor);
    return method;
}

Method* Class::lookUpMethodInClass(std::string _name, std::string descriptor)
{
    //Console::printlnWarning("lookUpMethodInClass("+_name+","+descriptor+") className="+name);
    for(auto c = this;c != nullptr;c = c->superClass)
    {
        for(auto m:c->methods)
        {
            //Console::printlnWarning("["+m->name+","+m->descriptor+"]");
            if(m->name == _name && m->descriptor == descriptor)
                return m;
        }
    }
    //Console::printlnWarning("null returned");
    return nullptr;
}

Method* Class::lookUpMethodInInterfaces(std::string _name, std::string descriptor)
{
    for(auto iface:interfaces)
    {
        for(auto m:iface->methods)
        {
            if(m->name == _name && m->descriptor == descriptor)
                return m;
        }
        auto m = iface->lookUpMethodInInterfaces(_name,descriptor);
        if(m != nullptr)
            return m;
    }
    return nullptr;
}

Method* Class::lookUpInterfaceMethod(std::string _name, std::string descriptor)
{
    for(auto m:methods)
    {
        if(m->name == _name && m->descriptor == descriptor)
            return m;
    }
    return lookUpMethodInInterfaces(_name,descriptor);
}

Object* Class::newObject()
{
    auto obj = new Object(this);
    ObjectPool::getObjectPool()->add(obj);
    return obj;
}

Object* Class::newArrayObject(unsigned int count)
{
    if(!isArray())
    {
        Console::printlnError("initialize failed, not array:"+name);
        exit(1);
    }
    auto obj = new Object(this,count);
    ObjectPool::getObjectPool()->add(obj);
    return obj;
}

Object* Class::newMultiDimensionArray(std::vector<int32>& counts)
{
    auto count = (unsigned int)counts[0];
    auto arr = newArrayObject(count);

    if(counts.size() > 1)
    {
        auto refs = arr->refs();
        for(auto i=0;i<arr->dataCount;i++)
        {
            std::vector<int32> newCounts;
            for(auto j=1;j<counts.size();j++)
                newCounts.push_back(counts[j]);
            refs[i] = componentClass()->newMultiDimensionArray(newCounts);
        }
    }
    return nullptr;
}

std::string Class::toDescriptor(std::string& className)
{
    std::map<std::string,std::string> primitiveTypes;
    primitiveTypes["void"] = "V";
    primitiveTypes["boolean"] = "Z";
    primitiveTypes["byte"] = "B";
    primitiveTypes["short"] = "S";
    primitiveTypes["int"] = "I";
    primitiveTypes["long"] = "J";
    primitiveTypes["char"] = "C";
    primitiveTypes["float"] = "F";
    primitiveTypes["double"] = "D";

    if(className[0]=='[')
        return className;
    if(primitiveTypes.find(className)!=primitiveTypes.end())
        return primitiveTypes[className];
    return "L"+className+";";
}

std::string Class::getArrayClassName(std::string& className)
{
    return "["+toDescriptor(className);
}

Class* Class::arrayClass()
{
    auto arrayClassName = getArrayClassName(name);
    return classloader->loadClass(arrayClassName);
}

std::string Class::descriptorToClassName(std::string& descriptor)
{
    std::map<std::string,std::string> primitiveTypes;
    primitiveTypes["void"] = "V";
    primitiveTypes["boolean"] = "Z";
    primitiveTypes["byte"] = "B";
    primitiveTypes["short"] = "S";
    primitiveTypes["int"] = "I";
    primitiveTypes["long"] = "J";
    primitiveTypes["char"] = "C";
    primitiveTypes["float"] = "F";
    primitiveTypes["double"] = "D";

    if(descriptor[0]=='[') //array
        return descriptor;
    if(descriptor[0]=='L')//object
        return descriptor.substr(1,descriptor.length()-1);//remove L ;
    for(auto& ele:primitiveTypes)//primitive(int double ...) type descriptor
    {
        if(ele.second==descriptor)
            return ele.first;
    }
    Console::printlnError("invalid descriptor:"+descriptor);
    exit(1);
}


std::string Class::getComponentClassName(std::string& className)
{
    if(className[0]=='[') //is array
    {
        auto componentTypeDescriptor = className.substr(1, className.length());
        return descriptorToClassName(componentTypeDescriptor);
    }
    Console::printlnError("not array:"+className);
    exit(1);
}

Class* Class::componentClass()
{
    auto componentClassName = getComponentClassName(name);
    return classloader->loadClass(componentClassName);
}

bool Class::isArray()
{
    return name[0]=='[';
}

bool Class::isPrimitive() {
    std::map<std::string,std::string> primitiveTypes;
    primitiveTypes["void"] = "V";
    primitiveTypes["boolean"] = "Z";
    primitiveTypes["byte"] = "B";
    primitiveTypes["short"] = "S";
    primitiveTypes["int"] = "I";
    primitiveTypes["long"] = "J";
    primitiveTypes["char"] = "C";
    primitiveTypes["float"] = "F";
    primitiveTypes["double"] = "D";
    return primitiveTypes.find(name)==primitiveTypes.end();
}

bool Class::isAssignableFrom(Class *s)
{
    if(this==s)
        return true;
    if(!s->isArray()) {
        if(!(s->accessFlags & ACC_INTERFACE_FLAG))
        {
            if(!(accessFlags & ACC_INTERFACE_FLAG))
                return s->isSubClassOf(this);
            else
                return s->isImplements(this);
        } else {
            if(!(accessFlags & ACC_INTERFACE_FLAG))
                return isJlObject();
            else
                return isSuperInterfacesOf(s);
        }
    } else {
        if(!isArray())
        {
            if(!(accessFlags & ACC_INTERFACE_FLAG))
                return isJlObject();
            else
                return isJlCloneable() || isJioSerializable();
        } else {
            auto sc = s->componentClass();
            auto tc = componentClass();
            return sc==tc || tc->isAssignableFrom(sc);
        }
    }
    return false;
}

bool Class::isImplements(Class *iface)
{
    for(auto c=this;c!= nullptr;c = c->superClass)
        for(auto i:c->interfaces)
            if(iface==i || i->isSubInterfacesOf(iface))
                return true;
    return false;
}

bool Class::isSubClassOf(Class *c)
{
    auto spc = superClass;
    while (spc!= nullptr)
    {
        if(spc==c)
            return true;
        else
            spc = spc->superClass;
    }
    return false;
}

bool Class::isSuperClassOf(Class *c)
{
    for(auto sup = c->superClass;sup != nullptr; sup = sup->superClass)
    {
        if(sup == this)
            return true;
    }
    return false;
}

bool Class::isSubInterfacesOf(Class *iface)
{
    for(auto i:interfaces)
        if(iface==i || i->isSubInterfacesOf(iface))
            return true;
    return false;
}

bool Class::isSuperInterfacesOf(Class *iface)
{
    return iface->isSubInterfacesOf(this);
}

bool Class::isJlObject()
{
    return name == "java/lang/Object";
}

bool Class::isJlCloneable()
{
    return name == "java/lang/Cloneable";
}

bool Class::isJioSerializable()
{
    return name == "java/lang/Serializable";
}


std::string Class::getJavaName()
{
    std::string javaName = name;
    for(auto& c:javaName) {
        if(c=='/') c = '.';
    }
    return javaName;
}

Method* Class::getClinitMethod()
{
    return getStaticMethod("<clinit>","()V");
}

Method* Class::getMainMethod()
{
    return getStaticMethod("main","([Ljava/lang/String;)V");
}

Method* Class::getStaticMethod(std::string _name, std::string descriptor)
{
    for(auto method:methods)
    {
        if((method->name==_name && method->descriptor==descriptor && method->accessFlags & ACC_STATIC_FLAG))
            return method;
    }
    return nullptr;
}