//
// Created by xuranus on 4/6/22.
//

#ifndef JVM_CLASSFILE_CONSTANTS_POOL_H
#define JVM_CLASSFILE_CONSTANTS_POOL_H

#include "../basicType.h"
#include "BytesReader.h"
#include <memory>
#include <vector>

namespace classfile {

    class ConstantsPool;

    class ConstantInfo {
        friend ConstantsPool;

    public:
        u1 tag;

        // if using std::share_ptr<ConstantsPool>, it will take 1 more bytes each constant info
        ConstantsPool* constantsPool;
    public:
        explicit ConstantInfo(u1 _tag, ConstantsPool* _constantsPool);
        virtual ~ConstantInfo() = default;
        static ConstantInfo* fromReader(u1 tag, BytesReader& reader, ConstantsPool* pool);
        virtual std::string verbose() = 0;
    };



    class ConstantUTF8: public ConstantInfo {
    private:
        u2 length;
        std::unique_ptr<u1> bytes; // bytes[length]
    public:
        ConstantUTF8(u1 tag, BytesReader& reader, ConstantsPool* pool);
        [[nodiscard]] std::string utf8() const;
        std::string verbose() override;
    };

    class ConstantInteger: public ConstantInfo {
    private:
        u4 bytes;
    public:
        ConstantInteger(u1 tag, BytesReader& reader, ConstantsPool* pool);
        [[nodiscard]] int intValue() const;
        std::string verbose() override;
    };

    class ConstantFloat: public ConstantInfo {
    private:
        u4 bytes;
    public:
        ConstantFloat(u1 tag, BytesReader& reader, ConstantsPool* pool);
        [[nodiscard]] float floatValue() const;
        std::string verbose() override;
    };

    class ConstantLong: public ConstantInfo {
    private:
        u4 highBytes;
        u4 lowBytes;
    public:
        ConstantLong(u1 tag, BytesReader& reader, ConstantsPool* pool);
        [[nodiscard]] long longValue() const;
        std::string verbose() override;
    };

    class ConstantDouble: public ConstantInfo {
    private:
        u4 highBytes;
        u4 lowBytes;
    public:
        ConstantDouble(u1 tag, BytesReader& reader, ConstantsPool* pool);
        [[nodiscard]] double doubleValue() const;
        std::string verbose() override;
    };

    class ConstantClass: public ConstantInfo {
        friend ConstantsPool;
    private:
        u2 nameIndex;
    public:
        ConstantClass(u1 tag, BytesReader& reader, ConstantsPool* pool);
        [[nodiscard]] std::string className() const;
        std::string verbose() override;
    };

    class ConstantString: public ConstantInfo {
    private:
        u2 stringIndex;
    public:
        ConstantString(u1 tag, BytesReader& reader, ConstantsPool* pool);
        [[nodiscard]] std::string stringValue() const;
        std::string verbose() override;
    };

    class ConstantFieldRef:public ConstantInfo { //MemberRef
    private:
        u2 classIndex;
        u2 classAndTypeIndex;
    public:
        ConstantFieldRef(u1 tag, BytesReader& reader, ConstantsPool* pool);
        std::string className();
        std::pair<std::string,std::string> nameAndDescriptor();
        std::string verbose() override;
    };

    class ConstantMethodRef:public ConstantInfo { //MemberRef
    private:
        u2 classIndex;
        u2 nameAndTypeIndex;
    public:
        ConstantMethodRef(u1 tag, BytesReader& reader, ConstantsPool* pool);
        std::string className();
        std::pair<std::string,std::string> nameAndDescriptor();
        std::string verbose() override;
    };

    class ConstantInterfaceMethodRef:public ConstantInfo { //MemberRef
    private:
        u2 classIndex;
        u2 classAndTypeIndex;
    public:
        ConstantInterfaceMethodRef(u1 tag, BytesReader& reader, ConstantsPool* pool);
        std::string className();
        std::pair<std::string,std::string> nameAndDescriptor();
        std::string verbose() override;
    };

    class ConstantNameAndType:public ConstantInfo {
    private:
        u2 nameIndex;
        u2 descriptorIndex;
    public:
        ConstantNameAndType(u1 tag, BytesReader& reader, ConstantsPool* pool);
        std::pair<std::string, std::string> nameAndDescriptor();
        std::string verbose() override;
    };

    class ConstantMethodHandle:public ConstantInfo {
    private:
        u1 referenceKind;
        u2 referenceIndex;
    public:
        ConstantMethodHandle(u1 tag, BytesReader& reader, ConstantsPool* pool);
        std::string verbose() override;
    };

    class ConstantMethodType:public ConstantInfo {
    private:
        u2 descriptorIndex;
    public:
        ConstantMethodType(u1 tag, BytesReader& reader, ConstantsPool* pool);
        std::string verbose() override;
    };

    class ConstantInvokeDynamic: public ConstantInfo {
    private:
        u2 bootstrapMethodAttrIndex;
        u2 nameAndTypeIndex;
    public:
        ConstantInvokeDynamic(u1 tag, BytesReader& reader, ConstantsPool* pool);
        std::string verbose() override;
    };




    class ConstantsPool {
    public:
        u2 _size{};
        std::vector<std::unique_ptr<ConstantInfo>> constants;

    public:
        ConstantsPool() = default;
        explicit ConstantsPool(BytesReader& reader);

        [[nodiscard]] int size() const;

        [[nodiscard]] std::string utf8(int index) const;
        [[nodiscard]] int intValue(int index) const;
        [[nodiscard]] float floatValue(int index) const;
        [[nodiscard]] long longValue(int index) const;
        [[nodiscard]] double doubleValue(int index) const;
        [[nodiscard]] std::string stringValue(int index) const;
        [[nodiscard]] std::string className(int index) const;
        [[nodiscard]] std::pair<std::string, std::string> nameAndDescriptor(int index) const;
        // <classname, <name, descriptor>
        [[nodiscard]] std::pair<std::string, std::pair<std::string, std::string>> memberRef(int index) const;

        void dump() const;
    };
}


#endif //JVM_CLASSFILE_CONSTANTS_POOL_H
