//
// Created by xuranus on 2/7/19.
//

#ifndef JVM_CLASS_H
#define JVM_CLASS_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include "../../classfile/ClassFile.h"
#include "../Slots.h"
#include "ConstantPool.h"
#include "Field.h"
#include "Method.h"

namespace heap {

    class ClassLoader;
    class ConstantPool;
    class Field;
    class Method;

    static std::map<std::string, std::string> primitiveTypes = {
            { "void",       "V" },
            { "boolean",    "Z" },
            { "byte",       "B" },
            { "short",      "S" },
            { "int",        "I" },
            { "long",       "J" },
            { "char",       "C" },
            { "float",      "F" },
            { "double",     "D" }
    };

    class Class {
    public:
        u2 accessFlags;
        std::string name;//this class name
        std::string superClassName;
        std::string sourceFileName;
        std::vector<std::string> interfacesNames;
        ConstantPool *constantPool;
        std::vector<Field> fields;
        std::vector<Method> methods;

        ClassLoader *classloader; // for referring, do not delete
        Class *superClass;  // for referring, do not delete
        std::vector<Class *> interfaces;  // for referring, do not delete

        u4 instanceSlotCount;
        u4 staticSlotCount;
        runtime::Slots staticVars;

        bool initStarted; // if <clinit> has been executed
        Object *jClass; //java.lang.Class instance of this class

    private:
        friend class ClassLoader;
        explicit Class(classfile::ClassFile* classFile);
        Class(const std::string& primitiveName, ClassLoader* loader, bool array); // for primitive/array class construct
        ~Class();

    public:
        // method used for non array class initialize
        void resolveSuperClass();
        void resolveInterfaces();
        void calculateInstanceFieldSlotsId();
        void calculateStaticFieldSlotsId();
        void allocAndInitializeStaticVars();

        bool accessibleTo(Class *c) const; // if class c can access this class
        std::string packageName() const;  // java/lang/String => java/lang
        std::string getJavaName() const; // java/lang/String => java.lang.String

        // <clinit>
        bool isInitStarted() const;  // if <clinit> invoked
        void markInitStarted();

        void resolveJClass(); // create a java.lang.Class and bind to implement reflection

        //
        Method *getInstanceMethod(const std::string& methodName, const std::string& descriptor) const;
        void setRefVar(const std::string& fieldName, const std::string& fieldDescriptor, Object *ref) ;
        Object *getRefVar(const std::string& fieldName, const std::string& fieldDescriptor) const;
        Method *getMethod(const std::string& name, const std::string& descriptor, bool isStatic) const;
        Field *getField(const std::string& name, const std::string& descriptor, bool isStatic) const; // for string pool usage

        Field *lookUpField(const std::string& name, const std::string& descriptor) const;
        Method *lookUpMethod(const std::string& name, const std::string& descriptor) const;
        Method *lookUpMethodInClass(const std::string& name, const std::string& descriptor) const;
        Method *lookUpMethodInInterfaces(const std::string& name, const std::string& descriptor) const;
        Method *lookUpInterfaceMethod(const std::string& name, const std::string& descriptor) const; //invoker must be interface

        Object *newObject();// non array object instantiation
        Object *newArrayObject(int count); // array object instantiation
        Object *newMultiDimensionArray(const std::vector<int> &counts); // multi-dimension array object instantiation
        Class *arrayClass() const; // example: array class of java/lang/String => [Ljava/lang/String;
        Class *componentClass() const; // component class of array class

        bool isArray() const; // name is [I, [J, ...
        bool isPrimitive() const; // name  is short, int, float...

        // access flags
        bool isInterface() const;
        bool isAbstract() const;
        bool isPublic() const;
        bool isFinal() const;
        bool isSuper() const;
        bool isSynthetic() const;
        bool isAnnotation() const;
        bool isEnum() const;

        bool isSubClassOf(const Class *c) const;
        bool isSuperClassOf(const Class *c) const;
        bool isImplements(const Class *c) const;
        bool isSubInterfacesOf(const Class *interface) const;
        bool isSuperInterfacesOf(const Class *c) const;
        bool isAssignableFrom(const Class *c) const; // weather class s can be cast to this class

        bool isJlObject() const; // is java/lang/Object
        bool isJlCloneable() const; // is java/lang/Cloneable
        bool isJioSerializable() const; // is java/lang/Serializable

        Method *getClinitMethod() const;
        Method *getMainMethod() const;
        Method *getStaticMethod(const std::string& name, const std::string& descriptor) const;

        // for reflection
        std::vector<Method*> getMethods(bool publicOnly);
        std::vector<Field*> getFields(bool publicOnly);
        std::vector<Method*> getConstructors(bool publicOnly);
        Method* getConstructor(const std::string& descriptor) const;


        std::set<heap::Object*> staticFieldObjects() const; // for gc
    };

}

#endif //JVM_CLASS_H
