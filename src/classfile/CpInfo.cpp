//
// Created by XUranus on 2019/1/31.
//

#include "CpInfo.h"
#include <cstdio>
#include <cstdlib>
#include "ClassReader.h"


CpInfo* CpInfo::getConstantInfoByTag(u1 tag,ClassReader& reader,CpInfo** constantPool)
{
    switch(tag) {
        case CONSTANT_Class_tag:return new CONSTANT_Class(tag,reader,constantPool);
        case CONSTANT_Fieldref_tag:return new CONSTANT_Fieldref(tag,reader,constantPool);
        case CONSTANT_Methodref_tag:return new CONSTANT_Methodref(tag,reader,constantPool);
        case CONSTANT_InterfaceMethodref_tag:return new CONSTANT_InterfaceMethodref(tag,reader,constantPool);
        case CONSTANT_String_tag:return new CONSTANT_String(tag,reader,constantPool);
        case CONSTANT_Integer_tag:return new CONSTANT_Integer(tag,reader,constantPool);
        case CONSTANT_Float_tag:return new CONSTANT_Float(tag,reader,constantPool);
        case CONSTANT_Long_tag:return new CONSTANT_Long(tag,reader,constantPool);
        case CONSTANT_Double_tag:return new CONSTANT_Double(tag,reader,constantPool);
        case CONSTANT_NameAndType_tag:return new CONSTANT_NameAndType(tag,reader,constantPool);
        case CONSTANT_Utf8_tag:return new CONSTANT_Utf8(tag,reader,constantPool);
        case CONSTANT_MethodHandle_tag:return new CONSTANT_MethodHandle(tag,reader,constantPool);
        case CONSTANT_MethodType_tag:return new CONSTANT_MethodType(tag,reader,constantPool);
        case CONSTANT_InvokeDynamic_tag:return new CONSTANT_InvokeDynamic(tag,reader,constantPool);
        default: {
            perror("unknown constant tag");
            exit(1);
        }
    }
}

CpInfo::CpInfo(u1 _tag,CpInfo** _constantPool)
{
    tag = _tag;
    constantPool = _constantPool;
}

/************************************** Virtual Method ,Default Invalid ********************************************/
void CpInfo::debug()
{
    printf("%s\n",getCpInfoName().c_str());
}



std::pair<std::string,std::string> CpInfo::getNameAndDescriptor()
{
    printf("method getNameAndDescriptor() not implemented.");
    exit(1);
}

std::string CpInfo::getClassName()
{
    printf("method getClassName() not implemented.");
    exit(1);
}


std::string CpInfo::getClassAndType()
{
    printf("method getClassAndType() not implemented.");
    exit(1);
}

std::string CpInfo::getBootstrapMethodAttr()
{
    printf("method getBootstrapMethodAttr() not implemented.");
    exit(1);
}


std::string CpInfo::getReferenceKind()
{
    printf("method getReferenceKind() not implemented.");
    exit(1);
}

std::string CpInfo::getReference()
{
    printf("method getReference() not implemented.");
    exit(1);
}


std::string CpInfo::getUtf8()
{
    printf("method getUtf8() not implemented.");
    exit(1);
}


std::string CpInfo::getCpInfoName() {
    switch (tag) {
        case 7:return "CONSTANT_Class";
        case 9:return "CONSTANT_Fieldref";
        case 10:return "CONSTANT_Methodref";
        case 11:return "CONSTANT_InterfaceMethodref";
        case 8:return "CONSTANT_String";
        case 3:return "CONSTANT_Integer";
        case 4:return "CONSTANT_Float";
        case 5:return "CONSTANT_Long";
        case 6:return "CONSTANT_Double";
        case 12:return "CONSTANT_NameAndType";
        case 1:return "CONSTANT_Utf8";
        case 15:return "CONSTANT_MethodHandle";
        case 16:return "CONSTANT_MethodType";
        case 18:return "CONSTANT_InvokeDynamic";
        default: {
            printf("no such constant. tag = %d", tag);
            exit(1);
        }
    }
}

/***************************************  CONSTANT_* constructor   **************************************************/

CONSTANT_Class::CONSTANT_Class(u1 tag, ClassReader &reader,CpInfo** constantPool):CpInfo(tag,constantPool)
{
    nameIndex = reader.readU2();
}

CONSTANT_Fieldref::CONSTANT_Fieldref(u1 tag, ClassReader &reader,CpInfo** constantPool):CpInfo(tag,constantPool)
{
    classIndex = reader.readU2();
    classAndTypeIndex = reader.readU2();
}

CONSTANT_Methodref::CONSTANT_Methodref(u1 tag, ClassReader &reader,CpInfo** constantPool):CpInfo(tag,constantPool)
{
    classIndex = reader.readU2();
    nameAndTypeIndex = reader.readU2();
}

CONSTANT_InterfaceMethodref::CONSTANT_InterfaceMethodref(u1 tag, ClassReader &reader,CpInfo** constantPool):CpInfo(tag,constantPool)
{
    classIndex = reader.readU2();
    classAndTypeIndex = reader.readU2();
}

CONSTANT_String::CONSTANT_String(u1 tag, ClassReader &reader,CpInfo** constantPool):CpInfo(tag,constantPool)
{
    stringIndex = reader.readU2();
}

CONSTANT_Integer::CONSTANT_Integer(u1 tag, ClassReader &reader,CpInfo** constantPool):CpInfo(tag,constantPool)
{
    bytes = reader.readU4();
}

CONSTANT_Float::CONSTANT_Float(u1 tag, ClassReader &reader,CpInfo** constantPool):CpInfo(tag,constantPool)
{
    bytes = reader.readU4();
}

CONSTANT_Long::CONSTANT_Long(u1 tag, ClassReader &reader,CpInfo** constantPool):CpInfo(tag,constantPool)
{
    highBytes = reader.readU4();
    lowBytes = reader.readU4();
}

CONSTANT_Double::CONSTANT_Double(u1 tag, ClassReader &reader,CpInfo** constantPool):CpInfo(tag,constantPool)
{
    highBytes = reader.readU4();
    lowBytes = reader.readU4();
}

CONSTANT_NameAndType::CONSTANT_NameAndType(u1 tag, ClassReader &reader,CpInfo** constantPool):CpInfo(tag,constantPool)
{
    nameIndex = reader.readU2();
    descriptorIndex = reader.readU2();
}

CONSTANT_Utf8::CONSTANT_Utf8(u1 tag, ClassReader &reader,CpInfo** constantPool):CpInfo(tag,constantPool)
{
    length = reader.readU2();
    bytes = reader.readBytes(length);
}

CONSTANT_MethodHandle::CONSTANT_MethodHandle(u1 tag, ClassReader &reader,CpInfo** constantPool):CpInfo(tag,constantPool)
{
    referenceKind = reader.readU1();
    referenceIndex = reader.readU2();
}

CONSTANT_MethodType::CONSTANT_MethodType(u1 tag, ClassReader &reader,CpInfo** constantPool):CpInfo(tag,constantPool)
{
    classIndex = reader.readU2();
    classAndTypeIndex = reader.readU2();
}

CONSTANT_InvokeDynamic::CONSTANT_InvokeDynamic(u1 tag, ClassReader &reader,CpInfo** constantPool):CpInfo(tag,constantPool)
{
    bootstrapMethodAttrIndex = reader.readU2();
    nameAndTypeIndex = reader.readU2();
}

/***********************************  Non contruction methods  *****************************************************/

int CONSTANT_Integer::getIntValue()
{
    return (int)bytes;
}

float CONSTANT_Float::getFloatValue()
{
    return *(float*)(&bytes);
}

long CONSTANT_Long::getLongValue()
{
    return (long)highBytes << 32 | (long)lowBytes;
}

double CONSTANT_Double::getDoubleValue()
{
    long t = (long)highBytes << 32 | (long)lowBytes;
    return *(double *)(&t);
}

std::string CONSTANT_String::getStringValue()
{
    return constantPool[stringIndex]->getUtf8();
}

std::pair<std::string,std::string> CONSTANT_NameAndType::getNameAndType()
{
    std::string name = constantPool[nameIndex]->getUtf8();
    std::string type = constantPool[descriptorIndex]->getUtf8();
    return std::make_pair(name,type);
}


/************************************  Partial implemented Virtual Method  *****************************************/

std::string CONSTANT_Utf8::getUtf8() {
    std::string ret;
    for(int i=0;i<length;i++) {
        ret.push_back(char(bytes[i]));
    }
    return ret;
}

void CONSTANT_Utf8::debug() {
    printf("%s %s\n",getCpInfoName().c_str(),getUtf8().c_str());
}

std::string CONSTANT_Class::getClassName() {
    return constantPool[nameIndex]->getUtf8();
}


//implement memberRef interface

std::string CONSTANT_Fieldref::getClassName()
{
    return ((CONSTANT_Class*)constantPool[classIndex])->getClassName();
}

std::pair<std::string,std::string> CONSTANT_Fieldref::getNameAndDescriptor()
{
    return ((CONSTANT_NameAndType*)constantPool[classAndTypeIndex])->getNameAndType();
}

std::string CONSTANT_Methodref::getClassName()
{
    return ((CONSTANT_Class*)constantPool[classIndex])->getClassName();
}

std::pair<std::string,std::string> CONSTANT_Methodref::getNameAndDescriptor()
{
    return ((CONSTANT_NameAndType*)constantPool[nameAndTypeIndex])->getNameAndType();
}

std::string CONSTANT_InterfaceMethodref::getClassName()
{
    return ((CONSTANT_Class*)constantPool[classIndex])->getClassName();
}

std::pair<std::string,std::string> CONSTANT_InterfaceMethodref::getNameAndDescriptor()
{
    return ((CONSTANT_NameAndType*)constantPool[classAndTypeIndex])->getNameAndType();
}
