//
// Created by XUranus on 2019/1/31.
//

#include "ClassReader.h"
#include "ClassFile.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "../util/Console.h"

ClassReader::ClassReader(const std::string filename)
{
    auto res = readAllBytes(filename);
    data = res.first;
    data_size = res.second;
    offset = 0;

    if(data== nullptr)
    {
        Console::printlnError("class file open failed:"+filename);
        exit(1);
    }
}

ClassReader::ClassReader(byte *d, long size)
{
    data = d;
    data_size = size;
    offset = 0;
}

u1 ClassReader::readU1()
{
    if(offset>=data_size)
    {
        Console::printlnError("class data read out of boundary");
        exit(1);
    }
    u1 ret = data[offset];
    offset++;
    return ret;
}

u2 ClassReader::readU2()
{
    if(offset+1>=data_size)
    {
        Console::printlnError("class data read out of boundary");
        exit(1);
    }
    u2 ret = ((u2)data[offset]<<8) + data[offset+1];
    offset+=2;
    return ret;
}

u4 ClassReader::readU4()
{
    if(offset+3>=data_size)
    {
        Console::printlnError("class data read out of boundary");
        exit(1);
    }
    u4 ret = ((u4)data[offset]<<24) + ((u4)data[offset+1]<<16) + ((u4)data[offset+2]<<8) + data[offset+3];
    offset+=4;
    return ret;
}

u1* ClassReader::readBytes(int n) {
    u1* bytes = new u1[n];
    for(int i=0;i<n;i++)
    {
        bytes[i] = readU1();
    }
    return bytes;
}

ClassReader::~ClassReader()
{
    delete data;
}

void ClassReader::printAllHexBytes()
{
    for(long i=0;i<data_size;i++) {
        printf("%02x ",data[i]);
        if((i+1)%20 == 0) printf("\n");
    }
    printf("\n");
}

FieldInfo* ClassReader::readFieldInfo(CpInfo** constantPool)
{
    auto fieldInfo = new FieldInfo();
    fieldInfo->constantPool = constantPool;
    fieldInfo->accessFlags = readU2();
    fieldInfo->nameIndex = readU2();
    fieldInfo->descriptorIndex = readU2();
    fieldInfo->attributesCount = readU2();
    fieldInfo->attributes = new AttributeInfo*[fieldInfo->attributesCount];
    for(u2 i=0;i<fieldInfo->attributesCount;i++)
        fieldInfo->attributes[i] = readAttributeInfo(constantPool);
    return fieldInfo;
}

MethodInfo* ClassReader::readMethodInfo(CpInfo **constantPool)
{
    auto methodInfo = new MethodInfo();
    methodInfo->constantPool = constantPool;
    methodInfo->accessFlags = readU2();
    methodInfo->nameIndex = readU2();
    methodInfo->descriptorIndex = readU2();
    methodInfo->attributesCount = readU2();
    methodInfo->attributes = new AttributeInfo*[methodInfo->attributesCount];
    for(u2 i=0;i<methodInfo->attributesCount;i++)
        methodInfo->attributes[i] = readAttributeInfo(constantPool);
    return methodInfo;
}

AttributeInfo* ClassReader::readAttributeInfo(CpInfo **_constantPool)
{
    u2 _attributeNameAndIndex = readU2();
    std::string attrName = _constantPool[_attributeNameAndIndex]->getUtf8();
    u4 _attributeLength = readU4();

    if(attrName=="ConstantValue") return new Attribute_ConstantValue(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="Code") return new Attribute_Code(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="Exceptions") return new Attribute_Exceptions(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="SourceFile") return new Attribute_SourceFile(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="LineNumberTable") return new Attribute_LineNumberTable(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="LocalVariableTable") return new Attribute_LocalVariableTable(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="InnerClasses") return new Attribute_InnerClasses(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="Synthetic") return new Attribute_Synthetic(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="Deprecated") return new Attribute_Deprecated(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="EnclosingMethod") return new Attribute_EnclosingMethod(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="Signature") return new Attribute_Signature(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="SourceDebugExtension") return new Attribute_SourceDebugExtension(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="LocalVariableTypeTable") return new Attribute_LocalVariableTypeTable(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="RuntimeVisibleAnnotations") return new Attribute_RuntimeVisibleAnnotations(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="RuntimeInvisibleAnnotations") return new Attribute_RuntimeInvisibleAnnotations(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="RuntimeVisibleParamaterAnnotations") return new Attribute_RuntimeVisibleParamaterAnnotations(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="RuntimeInvisibleParamaterAnnotations") return new Attribute_RuntimeInvisibleParamaterAnnotations(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="AnnotationDefault") return new Attribute_AnnotationDefault(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="StackMapTable") return new Attribute_StackMapTable(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="BootstrapMethods") return new Attribute_BootstrapMethods(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="RuntimeVisibleTypeAnnotations") return new Attribute_RuntimeVisibleTypeAnnotations(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="RuntimeInvisibleTypeAnnotations") return new Attribute_RuntimeInvisibleTypeAnnotations(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else if(attrName=="MethodParameters") return new Attribute_MethodParameters(_attributeNameAndIndex,_attributeLength,_constantPool,*this);
    else {
        printf("no such attribute,attrName = %s\n",attrName.c_str());
        exit(1);
    }
}


std::pair<byte*,int> ClassReader::readAllBytes(std::string filename)
{
    //Console::printlnInfo("ClassReader::readAllBytes():"+filename);
    FILE *fp = fopen(filename.c_str(),"rb+");//read as binary
    if(fp == nullptr) //not exist
    {
        //printf("%s not exist\n",filename.c_str());
        return std::make_pair(nullptr,0);
    }
    fseek(fp,0L,SEEK_END);
    long file_size = ftell(fp);//get file size
    if(file_size == 1L)
    {
        printf("get file size error");
        return std::make_pair(nullptr,-1);
    }

    byte* data = new u1[file_size+1];//build buffer size equals to file size

    //start read file
    rewind(fp);
    int rc = 0;//read count
    rc =(int)fread(data, sizeof(unsigned char),file_size+1,fp);
    if(rc != file_size)
    {
        printf("read file size and buffer size mismatch");
        delete[] data;
        return std::make_pair(nullptr,-1);
    }
    fclose(fp);

    return std::make_pair(data,file_size);
}

ClassFile* ClassReader::parseClassFile()
{
    //printf("parseClassFile()\n");
    auto *classfile = new ClassFile();
    classfile->magic = readU4();
    classfile->minorVersion = readU2();
    classfile->majorVersion = readU2();
    classfile->constantPoolCount = readU2();

    classfile->constantPool = new CpInfo*[classfile->constantPoolCount];
    for(u2 i=0;i<classfile->constantPoolCount;i++)
    {
        classfile->constantPool[i] = nullptr;
    }

    for(u2 i=1;i<classfile->constantPoolCount;i++)
    {
        u1 tag = readU1();
        auto cpInfo = CpInfo::getConstantInfoByTag(tag,*this,classfile->constantPool);
        classfile->constantPool[i] = cpInfo;
        if(tag == 5 || tag == 6) i++;
    }


    classfile->accessFlags = readU2();
    classfile->thisClass = readU2();
    classfile->superClass = readU2();

    classfile->interfaceCount = readU2();
    classfile->interfaces = new u2[classfile->interfaceCount];
    for(u2 i=0;i<classfile->interfaceCount;i++) {
        classfile->interfaces[i] = readU2();
    }

    classfile->fieldsCount = readU2();
    classfile->fields = new FieldInfo*[classfile->fieldsCount];
    for(u2 i=0;i<classfile->fieldsCount;i++)
    {
        classfile->fields[i] = readFieldInfo(classfile->constantPool);
    }


    classfile->methodsCount = readU2();
    classfile->methods = new MethodInfo*[classfile->methodsCount];
    for(u2 i=0;i<classfile->methodsCount;i++)
    {
        classfile->methods[i] = readMethodInfo(classfile->constantPool);
    }

    classfile->attributeCount = readU2();
    classfile->attributes = new AttributeInfo*[classfile->attributeCount];
    for(u2 i=0;i<classfile->attributeCount;i++)
    {
        classfile->attributes[i] = readAttributeInfo(classfile->constantPool);
    }

    return classfile;
}

