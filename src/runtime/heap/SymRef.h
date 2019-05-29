//
// Created by xuranus on 2/11/19.
//

#ifndef JVM_SYMREF_H
#define JVM_SYMREF_H

#include "Class.h"

struct SymRef {
    ConstantPool* constantPool;
    std::string className;
    Class* _class;

    SymRef();
    void resolveClassRef();
    Class* resolvedClass();
};

struct ClassRef: public SymRef {
    ClassRef(ConstantPool* cp,CONSTANT_Class* classInfo);
};

struct MemberRef: public SymRef {
    std::string name;
    std::string descriptor;

    MemberRef(CpInfo* contantMemberRef);//three types of constant:FieldRef MethodRef InterfacesMethodRef,corresponding to the following three sub class
};

struct FieldRef:public MemberRef {
    Field* field;

    FieldRef(ConstantPool* cp,CONSTANT_Fieldref *constantFieldrefInfo);
    void resolveFieldRef();
    Field* resolvedField();
};

struct MethodRef: public MemberRef {
    Method* method;

    MethodRef(ConstantPool* cp,CONSTANT_Methodref* constantMethodRefInfo);
    void resolveMethodRef();
    Method* resolvedMethod();
};

struct InterfaceMemberRef: public MemberRef {
    Method* method;

    InterfaceMemberRef(ConstantPool* cp,CONSTANT_InterfaceMethodref* constantInterfaceMethodRefInfo);
    void resolveInterfaceMethodRef();
    Method* resolvedInterfaceMethod();
};


#endif //JVM_SYMREF_H
