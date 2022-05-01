//
// Created by XUranus on 2019/1/30.
//

#include "ClassFile.h"
#include <cstdio>
#include <memory>
#include <cassert>
#include <iostream>
#include "../common/Exception.h"

namespace classfile {
    ClassFile::ClassFile(BytesReader& reader) {
        // check magic number
        magic = reader.readU4();
        if(magic != 0xcafebabe) {
            exception::panic("java.lang.ClassFormatError: " + reader.sourceFile());
        }

        minorVersion = reader.readU2();
        majorVersion = reader.readU2();

        // check version(JDK 1.8)
        if(majorVersion < 45 || majorVersion > 52) {
            exception::panic("java.lang.UnSupportedClassVersionError!");
        }

        constantPool = std::make_unique<ConstantsPool>(reader);

        accessFlags = reader.readU2();
        thisClass = reader.readU2();
        superClass = reader.readU2();

        interfaceCount = reader.readU2();
        interfaces = new u2[interfaceCount];
        for(u2 i = 0; i < interfaceCount; i++) {
            interfaces[i] = reader.readU2();
        }

        fieldCount = reader.readU2();
        fields.reserve(fieldCount);
        for(u2 i = 0; i < fieldCount; i++) {
            fields.push_back(std::make_unique<FieldInfo>(reader, constantPool.get()));
        }

        methodCount = reader.readU2();
        methods.reserve(methodCount);
        for(u2 i = 0; i < methodCount; i++) {
            methods.push_back(std::make_unique<MethodInfo>(reader, constantPool.get()));
        }

        attributeCount = reader.readU2();
        attributes.reserve(attributeCount);
        for(u2 i = 0; i < attributeCount; i++) {
            attributes.push_back(std::unique_ptr<AttributeInfo>(AttributeInfo::from(reader, constantPool.get())));
        }

        assert(reader.end());
    }

    std::vector<std::string> ClassFile::accessFlagsNames(u2 accessFlags) {
        std::vector<std::string> ret;
        if (accessFlags & ACC_PUBLIC_FLAG)      ret.emplace_back("ACC_PUBLIC");
        if (accessFlags & ACC_FINAL_FLAG)       ret.emplace_back("ACC_FINAL");
        if (accessFlags & ACC_SUPER_FLAG)       ret.emplace_back("ACC_SUPER");
        if (accessFlags & ACC_INTERFACE_FLAG)   ret.emplace_back("ACC_INTERFACE");
        if (accessFlags & ACC_ABSTRACT_FLAG)    ret.emplace_back("ACC_ABSTRACT");
        if (accessFlags & ACC_SYNTHETIC_FLAG)   ret.emplace_back("ACC_SYNTHETIC");
        if (accessFlags & ACC_ANNOTATION_FLAG)  ret.emplace_back("ACC_ANNOTATION");
        if (accessFlags & ACC_ENUM_FLAG)        ret.emplace_back("ACC_ENUM");
        return ret;
    }

    std::vector<std::string> ClassFile::accessFlagsNames() const {
        return ClassFile::accessFlagsNames(accessFlags);
    }

    std::string ClassFile::className() const {
        return constantPool->className(thisClass);
    }

    std::string ClassFile::superClassName() const {
        if (superClass == 0) {
            return "";
        } else {
            return constantPool->className(superClass);
        }
    }

    std::vector<std::string> ClassFile::interfacesNames() const {
        std::vector<std::string> res;
        for (u2 i = 0; i < interfaceCount; i++) {
            res.push_back(constantPool->className(interfaces[i]));
        }
        return res;
    }

    const std::unique_ptr<MethodInfo>&& ClassFile::mainMethod() const {
        for (u2 i = 0; i < methodCount; i++) {
            if (methods[i]->name() == "main" && methods[i]->descriptor() == "([Ljava/lang/String;)V") {
                return std::move(methods[i]);
            }
        }
        return nullptr;
    }

    std::string ClassFile::sourceFileName() const {
        for (u2 i = 0; i < attributeCount; i++) {
            if (attributes[i]->name() == "SourceFile") {
                u2 sourceFileIndex = ((AttributeSourceFile*)attributes[i].get())->sourceFileIndex;
                return constantPool->utf8(sourceFileIndex);
            }
        }
        //exception::panic("read SourceFile name Error.");
        return "Unknown";
    }


    void ClassFile::dumpClassFile() const {
        if(accessFlags & ACC_PUBLIC_FLAG) {
            std::cout << "public ";
        } else if(accessFlags & ACC_PRIVATE_FLAG) {
            std::cout << "private ";
        }
        std::cout << "class " << className() << std::endl;
        std::cout << "\tminor version: " << minorVersion << std::endl;
        std::cout << "\tmajor version: " << majorVersion << std::endl;
        std::cout << "\tflags: ";
        for(const auto& flag: accessFlagsNames()) {
            std::cout << flag << " ";
        }
        std::cout << std::endl;
        constantPool->dump();
    }


}