//
// Created by xuranus on 2/12/19.
//

#include "Members.h"
#include "../common/Exception.h"
#include <memory>

namespace classfile {

    MemberInfo::MemberInfo(BytesReader &reader, ConstantsPool* pool) {
        constantPool = pool;
        accessFlags = reader.readU2();
        nameIndex = reader.readU2();
        descriptorIndex = reader.readU2();
        attributesCount = reader.readU2();

        attributes.reserve(attributesCount);
        for(u2 i = 0; i < attributesCount; i++) {
            attributes.push_back(std::unique_ptr<AttributeInfo>(AttributeInfo::from(reader, pool)));
        }
    }

    std::string MemberInfo::name() const {
        if (constantPool != nullptr) {
            return constantPool->utf8(nameIndex);
        } else {
            exception::panic("constant pool not initialized.");
            return "";
        }
    }

    std::string MemberInfo::descriptor() const {
        if (constantPool != nullptr) {
            return constantPool->utf8(descriptorIndex);
        } else {
            exception::panic("constant pool not initialized.");
            return "";
        }
    }

    AttributeConstantValue* MemberInfo::constantValueAttribute() const {
        for (u2 i = 0; i < attributesCount; i++) {
            if (attributes[i]->name() == "ConstantValue") {
                return (AttributeConstantValue*) attributes[i].get();
            }
        }
        return nullptr;
    }

    AttributeCode *MemberInfo::codeAttribute() const {
        for (u2 i = 0; i < attributesCount; i++) {
            if (attributes[i]->name() == "Code") {
                return (AttributeCode*)attributes[i].get();
            }
        }
        return nullptr;
    }

    AttributeSignature *MemberInfo::signatureAttribute() const {
        for (u2 i = 0; i < attributesCount; i++) {
            if (attributes[i]->name() == "Signature") {
                return (AttributeSignature*)attributes[i].get();
            }
        }
        return nullptr;
    }

    MethodInfo::MethodInfo(BytesReader& reader, ConstantsPool* pool):MemberInfo(reader, pool) {}

    AttributeInfo* MethodInfo::getUnparsedAttribute(const std::string& attributeName) const {
        for(auto& attribute: attributes) {
            if(attribute->name() == attributeName) {
                return attribute.get();
            }
        }
        return nullptr;
    }



    FieldInfo::FieldInfo(BytesReader& reader, ConstantsPool* pool):MemberInfo(reader, pool) {}

    std::vector<std::string> MethodInfo::accessFlagsNames() const {
        std::vector<std::string> ret;
        if (accessFlags & ACC_PUBLIC_FLAG)          ret.emplace_back("ACC_PUBLIC");
        if (accessFlags & ACC_PRIVATE_FLAG)         ret.emplace_back("ACC_PRIVATE");
        if (accessFlags & ACC_PROTECTED_FLAG)       ret.emplace_back("ACC_PROTECTED");
        if (accessFlags & ACC_STATIC_FLAG)          ret.emplace_back("ACC_STATIC");
        if (accessFlags & ACC_FINAL_FLAG)           ret.emplace_back("ACC_FINAL");
        if (accessFlags & ACC_SYNCHRONIZED_FLAG)    ret.emplace_back("ACC_SYNCHRONIZED");
        if (accessFlags & ACC_BRIDGE_FLAG)          ret.emplace_back("ACC_BRIDGE");
        if (accessFlags & ACC_VARARGS_FLAG)         ret.emplace_back("ACC_VARARGS");
        if (accessFlags & ACC_NATIVE_FLAG)          ret.emplace_back("ACC_NATIVE");
        if (accessFlags & ACC_ABSTRACT_FLAG)        ret.emplace_back("ACC_ABSTRACT");
        if (accessFlags & ACC_STRICT_FLAG)          ret.emplace_back("ACC_STRICT");
        if (accessFlags & ACC_SYNTHETIC_FLAG)       ret.emplace_back("ACC_SYNTHETIC");
        return ret;
    }

    std::vector<std::string> FieldInfo::accessFlagsNames() const {
        std::vector<std::string> ret;
        if (accessFlags & ACC_PUBLIC_FLAG)          ret.emplace_back("ACC_PUBLIC");
        if (accessFlags & ACC_PRIVATE_FLAG)         ret.emplace_back("ACC_PRIVATE");
        if (accessFlags & ACC_PROTECTED_FLAG)       ret.emplace_back("ACC_PROTECTED");
        if (accessFlags & ACC_STATIC_FLAG)          ret.emplace_back("ACC_STATIC");
        if (accessFlags & ACC_FINAL_FLAG)           ret.emplace_back("ACC_FINAL");
        if (accessFlags & ACC_VOLATILE_FLAG)        ret.emplace_back("ACC_VOLATILE");
        if (accessFlags & ACC_TRANSIENT_FLAG)       ret.emplace_back("ACC_TRANSIENT");
        if (accessFlags & ACC_SYNTHETIC_FLAG)       ret.emplace_back("ACC_SYNTHETIC");
        if (accessFlags & ACC_ENUM_FLAG)            ret.emplace_back("ACC_ENUM");
        return ret;
    }

}