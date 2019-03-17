//
// Created by xuranus on 2/16/19.
//

#ifndef JVM_METHOD_H
#define JVM_METHOD_H


#include <string>
#include <vector>
#include "../../classfile/ClassFile.h"
#include "ClassMember.h"
#include <id3/sized_types.h>

struct MethodDescriptor {
    std::vector<std::string> parameterTypes;
    std::string returnType;

    void addParameterType(std::string type);
};

struct MethodDescriptorParser {
    std::string raw;
    unsigned long offset;
    MethodDescriptor* parsed;

    MethodDescriptor* parse(std::string& descriptor);//the builder design pattern
    void startParams();
    void endParams();
    void finish();
    void causeError(int code);
    uint8 readUint8();
    void unreadUint8();
    void parseParamTypes();
    void parseReturnType();
    std::string parseFieldType();
    std::string parseObjectType();
    std::string parseArrayType();
};

struct Method: public ClassMember {


    unsigned int maxStack;
    unsigned int maxLocals;
    std::vector<byte> code;
    unsigned int argSlotCount;

    Method(MethodInfo* methodInfo,Class* classRef);
    static std::vector<Method*> parseMethods(ClassFile* classFile,Class* classRef);
    static void interpret(Method* method,bool logTag,std::vector<std::string> args);
    void injectCodeAttribute(std::string returnType);
    void debug();
};


#endif //JVM_METHOD_H
