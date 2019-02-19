//
// Created by xuranus on 2/12/19.
//

#ifndef JVM_MEMBERINFO_H
#define JVM_MEMBERINFO_H

#include "basicType.h"
#include "CpInfo.h"
#include "AttributeInfo.h"
#include <vector>

/*
 * MemberInfo is the super class of MethodInfo and FieldInfo
 */

struct MemberInfo {
    u2 accessFlags;
    u2 nameIndex;
    u2 descriptorIndex;
    u2 attributesCount;
    AttributeInfo **attributes;//[attributesCount]

    CpInfo** constantPool;

    MemberInfo();
    std::string getName();
    std::string getDescriptorName();
    Attribute_ConstantValue* getConstantValueAttribute();
    Attribute_Code* getCodeAttribute();

    virtual std::vector<std::string> getAccessFlagsNames()=0;
    virtual void debug();
};


struct MethodInfo: public MemberInfo {
    MethodInfo();
    std::vector<std::string> getAccessFlagsNames() override;
};


struct FieldInfo: public MemberInfo {
    FieldInfo();
    std::vector<std::string> getAccessFlagsNames() override;
};

#endif //JVM_MEMBERINFO_H
