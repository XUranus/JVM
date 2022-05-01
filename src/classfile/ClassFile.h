//
// Created by XUranus on 2019/1/30.
//

#ifndef JVM_CLASSFILE_H
#define JVM_CLASSFILE_H

#include "Members.h"
#include "ConstantsPool.h"
#include "BytesReader.h"
#include "Attributes.h"
#include <vector>
#include <memory>


namespace classfile {

    class FieldInfo;
    class MethodInfo;
    class AttributeInfo;

    class ClassFile {
    public:
        u4 magic;
        u2 minorVersion;
        u2 majorVersion;

        std::shared_ptr<ConstantsPool> constantPool;

        u2 accessFlags;
        u2 thisClass;
        u2 superClass;

        u2 interfaceCount;
        u2* interfaces;// [interfaceCount];

        u2 fieldCount;
        std::vector<std::unique_ptr<FieldInfo>> fields; // [fieldsCount]

        u2 methodCount;
        std::vector<std::unique_ptr<MethodInfo>> methods; // [methodsCount - 1];

        u2 attributeCount;
        std::vector<std::unique_ptr<AttributeInfo>> attributes; // [attributeCount];

    public:
        explicit ClassFile(BytesReader&);

        [[nodiscard]] std::vector<std::string> accessFlagsNames() const;
        static std::vector<std::string> accessFlagsNames(u2 accessFlags);
        [[nodiscard]] std::string className() const;
        [[nodiscard]] std::string superClassName() const;
        [[nodiscard]] std::vector<std::string> interfacesNames() const;
        [[nodiscard]] const std::unique_ptr<MethodInfo>&& mainMethod() const;
        [[nodiscard]] std::string sourceFileName() const;
        void dumpClassFile() const; // javap verbose tool, to print detail
    };

}


#endif //JVM_CLASSFILE_H
