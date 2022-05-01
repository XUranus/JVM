//
// Created by xuranus on 2/16/19.
//

#include "Method.h"
#include "../thread/Thread.h"
#include "../../instruction/instruction.h"
#include "../../common//Exception.h"
#include "ClassLoader.h"
#include "StringPool.h"
#include "ObjectPool.h"
#include <cassert>

namespace heap {

    Method::Method(classfile::MethodInfo *methodInfo, Class *classRef, ConstantPool* constantPool):
        ClassMember(methodInfo->accessFlags,
                    methodInfo->name(),
                    methodInfo->descriptor(),
                    classRef) {

        // resolve signature attribute
        classfile::AttributeSignature* signatureAttribute = methodInfo->signatureAttribute();
        if(signatureAttribute) {
            signature = constantPool->UTF8Value(signatureAttribute->signatureIndex);
        }

        exceptionTable = nullptr;

        // resolve code attribute
        classfile::AttributeCode* codeAttribute = methodInfo->codeAttribute();
        if (codeAttribute) {
            maxLocals = codeAttribute->maxLocals;
            maxStack = codeAttribute->maxStacks;

            // todo::optimize
            code = std::vector<u1>(codeAttribute->codeLength);
            for (int i = 0; i < codeAttribute->codeLength; i++) {
                code[i] = codeAttribute->codes[i];
            }

            // copy ExceptionTable attribute
            exceptionTable = new ExceptionTable(constantPool, codeAttribute);

            // copy LineNumberTable attribute
            auto lineNumberTableAttribute = codeAttribute->attributeLineNumberTable();
            for(int i = 0; i < lineNumberTableAttribute->lineNumberTableLength; i++) {
                lineNumberTable.push_back(LineNumberTableEntry{
                    lineNumberTableAttribute->lineNumberTable[i].startPC,
                    lineNumberTableAttribute->lineNumberTable[i].lineNumber,
                });
            }

            // copy Annotation attribute
            auto* runtimeVisibleAnnotations =
                    (classfile::AttributeRuntimeVisibleAnnotations*)methodInfo->getUnparsedAttribute("RuntimeVisibleAnnotations");
            auto* runtimeVisibleParameterAnnotations =
                    (classfile::AttributeRuntimeVisibleParameterAnnotations*)methodInfo->getUnparsedAttribute("RuntimeVisibleParameterAnnotations");
            auto* annotationDefault =
                    (classfile::AttributeAnnotationDefault*)methodInfo->getUnparsedAttribute("AnnotationDefault");

            // TODO:: do translate
//            annotationData = runtimeVisibleAnnotations;
//            parameterAnnotationData = runtimeVisibleParameterAnnotations;
//            annotationDefaultData = annotationDefault;

        } else {
            maxLocals = 0;
            maxStack = 0;
        }

        //calculate args slots
        argSlotCount = 0;
        MethodDescriptorParser parser(descriptor);
        std::pair<std::vector<std::string>, std::string> result = parser.parse();
        parameterTypeDescriptors = result.first;
        returnTypeDescriptor = result.second;

        for (const std::string &parameterDescriptor: parameterTypeDescriptors) {
            argSlotCount++;
            if (parameterDescriptor == "J" || parameterDescriptor == "D") {//double or long
                argSlotCount++;
            }
        }

        if (!isStatic()) { // non-static method
            argSlotCount++; // nonstatic method has "this" ref parameter implicitly
        }

        // inject code for native method
        if (isNative()) {
            injectCodeAttribute(returnTypeDescriptor);
        }
    }

    Method::~Method() {
        delete exceptionTable;
    }

    // inject code for native method
    void Method::injectCodeAttribute(std::string returnType) {
        maxStack = 4;
        maxLocals = argSlotCount;
        if (returnType[0] == 'V') {
            code = {0xfe, 0xb1}; // invokenative return
        } else if (returnType[0] == 'D') {
            code = {0xfe, 0xaf}; // invokenative dreturn
        } else if (returnType[0] == 'F') {
            code = {0xfe, 0xae}; // invokenative freturn
        } else if (returnType[0] == 'J') {
            code = {0xfe, 0xad}; // invokenative lreturn
        } else if (returnType[0] == 'L' || returnType[0] == '[') {
            code = {0xfe, 0xb0}; // invokenative areturn
        } else {
            code = {0xfe, 0xac}; // invokenative iretyrb
        }
    }

    int Method::findExceptionHandlerPC(Class *exceptionClass, int pc) {
        ExceptionHandler* handler = exceptionTable->findHandler(exceptionClass, pc);
        if(handler == nullptr) {
            return -1;
        } else {
            return handler->handlerPC;
        }
    }

    int Method::lineNumber(int pc) {
        if(isNative()) {
            return -2;
        } else if(lineNumberTable.empty()) {
            return -1;
        } else {
            for(auto it = lineNumberTable.rbegin(); it != lineNumberTable.rend(); it++) {
                if(pc >= it->startPC) {
                    return it->lineNumber;
                }
            }
        }
        return -1;
    }


    bool Method::isConstructor() const { return !isStatic() && name == "<init>"; }

    bool Method::isClinit() const {return isStatic() && name == "<clinit>"; }

    bool Method::isBridge() const { return accessFlags & ACC_BRIDGE_FLAG; }

    bool Method::isVarargs() const { return accessFlags & ACC_VARARGS_FLAG; }

    bool Method::isNative() const { return accessFlags & ACC_NATIVE_FLAG; }

    bool Method::isAbstract() const { return accessFlags & ACC_ABSTRACT_FLAG; }

    bool Method::isStrict() const { return accessFlags & ACC_STRICT_FLAG; }

    bool Method::isSynchronized() const { return accessFlags & ACC_SYNCHRONIZED_FLAG; }




    std::string _descriptorToClassName(const std::string &descriptor) {
        if(descriptor[0] == '[') {
            return descriptor;
        } else if(descriptor[0] == 'L') {
            return descriptor.substr(1, descriptor.length() - 2);
        }
        for(auto& pair: primitiveTypes) {
            if(pair.second == descriptor) {
                return pair.first;
            }
        }
        exception::panic("invalid descriptor: " + descriptor);
        return "";
    }


    std::vector<Class *> Method::parameterTypes() const {
        std::vector<Class*> res;
        for(const std::string& paramDescriptor: parameterTypeDescriptors) {
            std::string paramClassName = _descriptorToClassName(paramDescriptor);
            res.emplace_back(klass->classloader->loadClass(paramClassName));
        }
        return res;
    }

    std::vector<Class *> Method::exceptionTypes() const {
        return exceptionTable->exceptionTypes();
    }

    Class *Method::returnType() const {
        std::string returnClassName = _descriptorToClassName(returnTypeDescriptor);
        return klass->classloader->loadClass(returnClassName);
    }


    std::vector<u1> Method::getAnnotationDefaultData() const {
        return annotationDefaultData;
    }

    std::vector<u1> Method::getParameterAnnotationData() const {
        return parameterAnnotationData;
    }

    Method::Method():
    ClassMember(ACC_STATIC_FLAG, "<return>", "()V", nullptr) {
        maxStack = 0;
        maxLocals = 0;
        code = {0xb1};
        argSlotCount = 0;
        klass = nullptr;
        exceptionTable = new ExceptionTable;
    } // todo:: shim method

    Method* Method::ShimMethod = new Method;
}