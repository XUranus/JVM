//
// Created by xuranus on 2/12/19.
//

#include "MemberInfo.h"
#include "ClassFile.h"

MemberInfo::MemberInfo() {
    accessFlags = 0;
    nameIndex = 0;
    descriptorIndex = 0;
    attributesCount = 0;

    attributes = nullptr;
    constantPool = nullptr;
}

std::string MemberInfo::getDescriptorName()
{
    if(constantPool!= nullptr)
        return constantPool[descriptorIndex]->getUtf8();
    else {
        printf("constant pool ptr not initialized.");
        exit(1);
    }
}

std::string MemberInfo::getName()
{
    if(constantPool!= nullptr)
        return constantPool[nameIndex]->getUtf8();
    else {
        printf("constant pool ptr not initialized.");
        exit(1);
    }
}

void MemberInfo::debug()
{
    //TODO:implment it
    printf("[Debug MemberInfo]\n");
    printf("name: %s\n",getName().c_str(),getDescriptorName().c_str());
    printf("descriptor: %s\n",getDescriptorName().c_str());
    printf("accessFlags: ");
    for(const auto &af:getAccessFlagsNames())
    {
        printf("%s,",af.c_str());
    }
    printf("\nattributeCount:%d\n",attributesCount);
    for(auto i=0;i<attributesCount;i++) printf("attributeNameIndex: %u\n",attributes[i]->attributeNameAndIndex);

    printf("\n");

    for(u2 i=0;i<attributesCount;i++)
        attributes[i]->debug();
    printf("\n");
}


Attribute_Code* MemberInfo::getCodeAttribute() {
    for (int i=0;i<attributesCount;i++)
    {
        if(attributes[i]->getAttributeName()=="Code")
            return (Attribute_Code*)attributes[i];
    }
    return nullptr;
}

Attribute_ConstantValue* MemberInfo::getConstantValueAttribute()
{
    for (int i=0;i<attributesCount;i++)
    {
        if(attributes[i]->getAttributeName()=="ConstantValue")
            return (Attribute_ConstantValue*)attributes[i];
    }
    return nullptr;
}


// override zone

MethodInfo::MethodInfo():MemberInfo() {}

FieldInfo::FieldInfo():MemberInfo() {}

std::vector<std::string> MethodInfo::getAccessFlagsNames()
{
    std::vector<std::string> ret;
    if(accessFlags&ACC_PUBLIC_FLAG) ret.emplace_back("ACC_PUBLIC");
    if(accessFlags&ACC_PRIVATE_FLAG) ret.emplace_back("ACC_PRIVATE");
    if(accessFlags&ACC_PROTECTED_FLAG) ret.emplace_back("ACC_PROTECTED");
    if(accessFlags&ACC_STATIC_FLAG) ret.emplace_back("ACC_STATIC");
    if(accessFlags&ACC_FINAL_FLAG) ret.emplace_back("ACC_FINAL");
    if(accessFlags&ACC_SYNCHRONIZED_FLAG) ret.emplace_back("ACC_SYNCHRONIZED");
    if(accessFlags&ACC_BRIDGE_FLAG) ret.emplace_back("ACC_BRIDGE");
    if(accessFlags&ACC_VARARGS_FLAG) ret.emplace_back("ACC_VARARGS");
    if(accessFlags&ACC_NATIVE_FLAG) ret.emplace_back("ACC_NATIVE");
    if(accessFlags&ACC_ABSTRACT_FLAG) ret.emplace_back("ACC_ABSTRACT");
    if(accessFlags&ACC_STRICT_FLAG) ret.emplace_back("ACC_STRICT");
    if(accessFlags&ACC_SYNTHETIC_FLAG) ret.emplace_back("ACC_SYNTHETIC");
    return ret;
}

std::vector<std::string> FieldInfo::getAccessFlagsNames()
{
    std::vector<std::string> ret;
    if(accessFlags&ACC_PUBLIC_FLAG) ret.emplace_back("ACC_PUBLIC");
    if(accessFlags&ACC_PRIVATE_FLAG) ret.emplace_back("ACC_PRIVATE");
    if(accessFlags&ACC_PROTECTED_FLAG) ret.emplace_back("ACC_PROTECTED");
    if(accessFlags&ACC_STATIC_FLAG) ret.emplace_back("ACC_STATIC");
    if(accessFlags&ACC_FINAL_FLAG) ret.emplace_back("ACC_FINAL");
    if(accessFlags&ACC_VOLATILE_FLAG) ret.emplace_back("ACC_VOLATILE");
    if(accessFlags&ACC_TRANSIENT_FLAG) ret.emplace_back("ACC_TRANSIENT");
    if(accessFlags&ACC_SYNTHETIC_FLAG) ret.emplace_back("ACC_SYNTHETIC");
    if(accessFlags&ACC_ENUM_FLAG) ret.emplace_back("ACC_ENUM");
    return ret;
}

