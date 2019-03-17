//
// Created by xuranus on 2/7/19.
//

#ifndef JVM_CLASS_H
#define JVM_CLASS_H

#include <iostream>
#include <vector>
#include <string>
#include "../../classfile/ClassFile.h"
#include "ConstantPool.h"
#include "../Slot.h"
#include "Field.h"
#include "Method.h"

struct ClassLoader;
typedef Slots StaticVars;



struct Class {
    u2 accessFlags;
    std::string name;//this class name
    std::string superClassName;
    std::vector<std::string> interfacesNames;
    ConstantPool* constantPool;
    std::vector<Field*> fields;
    std::vector<Method*> methods;
    ClassLoader* classloader;
    Class* superClass;
    std::vector<Class*> interfaces;
    unsigned int instanceSlotCount;
    unsigned int staticSlotCount;
    StaticVars* staticVars;
    Object* jClass;//java.lang.Class instance
    bool initStarted;

    Class() = default;
    explicit Class(ClassFile* classFile);
    explicit Class(std::string& arrayClassName);//for array construct
    //~Class();//TODO::implement it
    void debug();

    void calculateInstanceFieldSlotsId();
    void calculateStaticFieldSlotsId();
    void initializeStaticVars();
    void initializeStaticFinalVar(Field* field);


    bool accessibleTo(Class* c);
    std::string getPackageName();

    Method* getInstanceMethod(std::string _name,std::string _descriptor);
    void setRefVar(std::string fieldName,std::string fieldDescriptor,Object* ref);
    Object* getRefVar(std::string fieldName,std::string fieldDescriptor);
    Method* getMethod(std::string name,std::string _descriptor,bool isStatic);
    Field* getField(std::string name,std::string descriptor,bool isStatic);
    Field* lookUpField(std::string name,std::string descriptor);
    Method* lookUpMethod(std::string name,std::string descriptor);
    Method* lookUpMethodInClass(std::string name,std::string descriptor);
    Method* lookUpMethodInInterfaces(std::string name,std::string descriptor);
    Method* lookUpInterfaceMethod(std::string name,std::string descriptor);//invoker must be interface
    Object* newObject();//instantiation
    Object* newArrayObject(unsigned int count);
    Object* newMultiDimensionArray(std::vector<int32>& counts);

    static std::string toDescriptor(std::string& className);
    static std::string getArrayClassName(std::string& className);
    static std::string descriptorToClassName(std::string& descriptor);
    static std::string getComponentClassName(std::string& className);
    Class* arrayClass();
    Class* componentClass();

    bool isArray();
    bool isPrimitive();
    bool isAssignableFrom(Class* c);
    bool isSubClassOf(Class* c);
    bool isSuperClassOf(Class* c);
    bool isImplements(Class* c);
    bool isSubInterfacesOf(Class* iface);
    bool isJlObject();
    bool isSuperInterfacesOf(Class* c);
    bool isJlCloneable();
    bool isJioSerializable();

    std::string getJavaName();

    Method* getClinitMethod();
    Method* getMainMethod();
    Method* getStaticMethod(std::string name,std::string descriptor);
};


#endif //JVM_CLASS_H
