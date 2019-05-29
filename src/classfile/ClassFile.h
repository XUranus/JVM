//
// Created by XUranus on 2019/1/30.
//

#ifndef JVM_CLASSFILE_H
#define JVM_CLASSFILE_H

#include "basicType.h"
#include <cstdint>
#include <iostream>
#include "CpInfo.h"
#include "MemberInfo.h"
#include "AttributeInfo.h"
#include <vector>


struct ClassFile {
    u4 magic;
    u2 minorVersion;
    u2 majorVersion;
    u2 constantPoolCount;
    CpInfo** constantPool;//[constantPoolCount-1];
    u2 accessFlags;
    u2 thisClass;
    u2 superClass;
    u2 interfaceCount;
    u2 *interfaces;//[interfaceCount];
    u2 fieldsCount;
    FieldInfo** fields;//[fieldsCount]
    u2 methodsCount;
    MethodInfo** methods;//[methodsCount-1];
    u2 attributeCount;
    AttributeInfo** attributes;//[attributeCount];

    ClassFile(){}
    ~ClassFile();
    void debug();
    std::vector<std::string> getAccessFlagsNames();
    static std::vector<std::string> getAccessFlagsNames(u2 accessFlags);
    std::string getThisClassName();
    std::string getSuperClassName();
    std::string getInterfaceName(u2 index);
    std::vector<std::string> getInterfacesNames();
    MethodInfo* getMainMethod();
    std::string getSourceFileName();
    void verbose();//javap verbose tool


};


#endif //JVM_CLASSFILE_H
