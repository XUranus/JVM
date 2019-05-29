//
// Created by XUranus on 2019/1/31.
//

#ifndef JVM_CPINFO_H
#define JVM_CPINFO_H

#include "basicType.h"
#include <iostream>
#include <string>


#define CONSTANT_Class_tag 7
#define CONSTANT_Fieldref_tag 9
#define CONSTANT_Methodref_tag 10
#define CONSTANT_InterfaceMethodref_tag 11
#define CONSTANT_String_tag 8
#define CONSTANT_Integer_tag 3
#define CONSTANT_Float_tag 4
#define CONSTANT_Long_tag 5
#define CONSTANT_Double_tag 6
#define CONSTANT_NameAndType_tag 12
#define CONSTANT_Utf8_tag 1
#define CONSTANT_MethodHandle_tag 15
#define CONSTANT_MethodType_tag 16
#define CONSTANT_InvokeDynamic_tag 18

struct ClassReader;

struct CpInfo {
    u1 tag;
    CpInfo** constantPool;

    static CpInfo* getConstantInfoByTag(u1 tag,ClassReader& reader,CpInfo** constantPool);
    CpInfo(u1 tag,CpInfo** constantPool);

    virtual std::string getCpInfoName();
    virtual void debug();

    //MemberRef interface
    virtual std::string getClassName();
    virtual std::pair<std::string,std::string> getNameAndDescriptor();


    virtual std::string getClassAndType();
    virtual std::string getBootstrapMethodAttr();
    virtual std::string getReferenceKind();
    virtual std::string getReference();
    virtual std::string getUtf8();
};


struct CONSTANT_Utf8:public CpInfo {
    u2 length;
    u1 *bytes;//bytes[length]

    CONSTANT_Utf8(u1 tag,ClassReader& reader,CpInfo** constantPool);
    std::string getUtf8();
    void debug();
};

struct CONSTANT_Integer:public CpInfo {
    u4 bytes;
    CONSTANT_Integer(u1 tag,ClassReader& reader,CpInfo** constantPool);
    int getIntValue();
};

struct CONSTANT_Float:public CpInfo {
    u4 bytes;
    CONSTANT_Float(u1 tag,ClassReader& reader,CpInfo** constantPool);
    float getFloatValue();
};

struct CONSTANT_Long:public CpInfo {
    u4 highBytes;
    u4 lowBytes;
    CONSTANT_Long(u1 tag,ClassReader& reader,CpInfo** constantPool);
    long getLongValue();
};

struct CONSTANT_Double:public CpInfo {
    u4 highBytes;
    u4 lowBytes;
    CONSTANT_Double(u1 tag,ClassReader& reader,CpInfo** constantPool);
    double getDoubleValue();
};

struct CONSTANT_Class:public CpInfo {
    u2 nameIndex;
    CONSTANT_Class(u1 tag,ClassReader& reader,CpInfo** constantPool);

    std::string getClassName();
};

struct CONSTANT_String:public CpInfo {
    u2 stringIndex;
    CONSTANT_String(u1 tag,ClassReader& reader,CpInfo** constantPool);
    std::string getStringValue();
};

struct CONSTANT_Fieldref:public CpInfo { //MemberRef
    u2 classIndex;
    u2 classAndTypeIndex;

    CONSTANT_Fieldref(u1 tag,ClassReader& reader,CpInfo** constantPool);
    std::string getClassName();
    std::pair<std::string,std::string> getNameAndDescriptor();
};

struct CONSTANT_Methodref:public CpInfo { //MemberRef
    u2 classIndex;
    u2 nameAndTypeIndex;

    CONSTANT_Methodref(u1 tag,ClassReader& reader,CpInfo** constantPool);
    std::string getClassName();
    std::pair<std::string,std::string> getNameAndDescriptor();
};

struct CONSTANT_InterfaceMethodref:public CpInfo { //MemberRef
    u2 classIndex;
    u2 classAndTypeIndex;

    CONSTANT_InterfaceMethodref(u1 tag,ClassReader& reader,CpInfo** constantPool);
    std::string getClassName();
    std::pair<std::string,std::string> getNameAndDescriptor();
};

struct CONSTANT_NameAndType:public CpInfo {
    u2 nameIndex;
    u2 descriptorIndex;
    CONSTANT_NameAndType(u1 tag,ClassReader& reader,CpInfo** constantPool);
    std::pair<std::string,std::string> getNameAndType();
};

struct CONSTANT_MethodHandle:public CpInfo {
    u1 referenceKind;
    u2 referenceIndex;
    CONSTANT_MethodHandle(u1 tag,ClassReader& reader,CpInfo** constantPool);
};

struct CONSTANT_MethodType:public CpInfo {
    u2 descriptorIndex;
    CONSTANT_MethodType(u1 tag,ClassReader& reader,CpInfo** constantPool);
};

struct CONSTANT_InvokeDynamic:public CpInfo {
    u2 bootstrapMethodAttrIndex;
    u2 nameAndTypeIndex;
    CONSTANT_InvokeDynamic(u1 tag,ClassReader& reader,CpInfo** constantPool);
};


#endif //JVM_CPINFO_H
