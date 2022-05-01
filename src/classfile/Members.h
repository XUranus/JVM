//
// Created by xuranus on 2/12/19.
//

#ifndef JVM_CLASSFILE_MEMBERS_H
#define JVM_CLASSFILE_MEMBERS_H

#include "../basicType.h"
#include "Attributes.h"
#include <vector>
#include "ConstantsPool.h"
/**
 *                          MemberInfo
 *                              |
 *                     ---------------------
 *                    |                    |
 *               FieldInfo              MethodInfo
 */

namespace classfile {

    class AttributeInfo;
    class AttributeConstantValue;
    class AttributeCode;
    class AttributeSignature;

    class MemberInfo {
    public:
        u2 accessFlags;
        u2 nameIndex;
        u2 descriptorIndex;
        u2 attributesCount;
        std::vector<std::unique_ptr<AttributeInfo>> attributes; // [attributesCount]

        ConstantsPool* constantPool; //for referring, do not delete

    public:
        MemberInfo() = default;
        MemberInfo(BytesReader& reader, ConstantsPool* pool);
        virtual ~MemberInfo() = default;
        [[nodiscard]] std::string name() const;
        [[nodiscard]] std::string descriptor() const;
        [[nodiscard]] AttributeConstantValue* constantValueAttribute() const;
        [[nodiscard]] AttributeCode* codeAttribute() const;
        [[nodiscard]] AttributeSignature* signatureAttribute() const;
        [[nodiscard]] virtual std::vector<std::string> accessFlagsNames() const = 0;
    };


    class MethodInfo : public MemberInfo {
    public:
        MethodInfo() = default;
        MethodInfo(BytesReader& reader, ConstantsPool* pool);
        [[nodiscard]] std::vector<std::string> accessFlagsNames() const override ;
        AttributeInfo* getUnparsedAttribute(const std::string& attributeName) const;
    };


    class FieldInfo : public MemberInfo {
    public:
        FieldInfo() = default;
        FieldInfo(BytesReader& reader, ConstantsPool* pool);
        [[nodiscard]] std::vector<std::string> accessFlagsNames() const override;
    };

}

#endif //JVM_CLASSFILE_MEMBERS_H
