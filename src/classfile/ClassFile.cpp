//
// Created by XUranus on 2019/1/30.
//

#include "ClassFile.h"
#include <cstdio>
#include "../util/Console.h"
using namespace std;

ClassFile::ClassFile() {
    magic = 0;
    minorVersion = 0;
    majorVersion = 0;
    constantPoolCount = 0;
    constantPool = nullptr;//[constantPoolCount-1];
    accessFlags = 0;
    thisClass = 0;
    superClass = 0;
    interfaceCount = 0;
    interfaces = nullptr;//[interfaceCount];//
    fieldsCount = 0;
    fields = nullptr;//[fieldsCount]
    methodsCount = 0;
    methods = nullptr;//[methodsCount-1];
    attributeCount = 0;
    attributes = 0;//[attributeCount];
}

ClassFile::~ClassFile() {
    /*
    CpInfo** constantPool;//[constantPoolCount-1];
    u2 *interfaces;//[interfaceCount];
    FieldInfo** fields;//[fieldsCount]
    MethodInfo** methods;//[methodsCount-1];
    AttributeInfo** attributes;//[attributeCount];
    */
    //some of them are nullptr, free to delete all ptr
    for(int i = 0; i < constantPoolCount; i++) {
        delete constantPool[i];
    }
    for(int i = 0; i < fieldsCount; i++) {
        delete fields[i];
    }
    for(int i = 0; i < methodsCount; i++) {
        delete methods[i];
    }
    for(int i = 0; i < attributeCount; i++) {
        delete attributes[i];
    }
    delete[] constantPool;
    delete[] interfaces;
    delete[] fields;
    delete[] methods;
    delete[] attributes;
}

void ClassFile::debug()
{
    printf("magic: %02lx\n",magic);
    printf("minorVersion: %02x\n",minorVersion);
    printf("majorVersion: %02x\n",majorVersion);
    printf("constantPoolCount: %02x\n",constantPoolCount);

    for(u2 i=0;i<constantPoolCount;i++)
    {
        if(constantPool[i]!= nullptr)
        {
            printf("#%u\t = ",i);
            constantPool[i]->debug();
        } else
            printf("#%u\t = nullptr\n",i);
    }

    printf("accessFlags: %02x ",accessFlags);
    for(const auto &af :getAccessFlagsNames())
    {
        printf("%s, ",af.c_str());
    }
    printf("\n");

    printf("thisClass: %s\n",getThisClassName().c_str());
    printf("superClass: %s\n",getSuperClassName().c_str());
    printf("interfaceCount: 0x%04x\n",interfaceCount);
    for(u2 i=0;i<interfaceCount;i++)
    {
        printf("interface[i]: %s\n",getInterfaceName(interfaces[i]).c_str());
    }

    printf("fieldsCount: 0x%04x\n",fieldsCount);
    for(u2 i=0;i<fieldsCount;i++)
    {
        fields[i]->debug();
    }

    printf("\n");
    printf("methodCount: 0x%04x\n\n",methodsCount);
    for(u2 i=0;i<methodsCount;i++)
    {
        printf("[%u] ",i);
        methods[i]->debug();
        printf("\n");
    }

    printf("attrbutesCount: 0x%04x\n",attributeCount);
    for(u2 i=0;i<attributeCount;i++)
    {
        attributes[i]->debug();
    }

}

std::vector<std::string> ClassFile::getAccessFlagsNames(u2 accessFlags)
{
    std::vector<std::string> ret;
    if(accessFlags&ACC_PUBLIC_FLAG) ret.emplace_back("ACC_PUBLIC");
    if(accessFlags&ACC_FINAL_FLAG) ret.emplace_back("ACC_FINAL");
    if(accessFlags&ACC_SUPER_FLAG) ret.emplace_back("ACC_SUPER");
    if(accessFlags&ACC_INTERFACE_FLAG) ret.emplace_back("ACC_INTERFACE");
    if(accessFlags&ACC_ABSTRACT_FLAG) ret.emplace_back("ACC_ABSTRACT");
    if(accessFlags&ACC_SYNTHETIC_FLAG) ret.emplace_back("ACC_SYNTHETIC");
    if(accessFlags&ACC_ANNOTATION_FLAG) ret.emplace_back("ACC_ANNOTATION");
    if(accessFlags&ACC_ENUM_FLAG) ret.emplace_back("ACC_ENUM");
    return ret;
}

std::vector<std::string> ClassFile::getAccessFlagsNames()
{
   return getAccessFlagsNames(accessFlags);
}

std::string ClassFile::getSuperClassName()
{
    if(superClass==0)
        return "";
    else
        return constantPool[superClass]->getClassName();
}

std::string ClassFile::getThisClassName()
{
    return constantPool[thisClass]->getClassName();
}

std::string ClassFile::getInterfaceName(u2 index)
{
    return ((CONSTANT_Class*)constantPool[index])->getClassName();
}


std::vector<std::string> ClassFile::getInterfacesNames()
{
    std::vector<std::string> ret;
    for(u2 i=0;i<interfaceCount;i++)
    {
        ret.push_back(getInterfaceName(interfaces[i]));
    }
    return ret;
}

MethodInfo* ClassFile::getMainMethod()
{
    for(auto i=0;i<methodsCount;i++)
    {
        if(methods[i]->getName()=="main" && methods[i]->getDescriptorName()=="([Ljava/lang/String;)V")
            return methods[i];
    }
    return nullptr;
}

std::string ClassFile::getSourceFileName()
{
    for(auto i=0;i<attributeCount;i++)
    {
        if(attributes[i]->getAttributeName()=="SourceFile")
            return constantPool[attributes[i]->attributeNameAndIndex]->getUtf8();
    }
    Console::printlnError("read SourceFile name Error.");
    exit(1);
}

void ClassFile::verbose() {
    debug();//todo::fix latter
}