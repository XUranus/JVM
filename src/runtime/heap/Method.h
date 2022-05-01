//
// Created by xuranus on 2/16/19.
//

#ifndef JVM_METHOD_H
#define JVM_METHOD_H

#include <string>
#include <vector>
#include "ExceptionHandler.h"
#include "../../classfile/Members.h"
#include "ClassMember.h"
#include "MethodDescriptorParser.h"

namespace heap {
    class Class;
    class ConstantPool;
    class ClassLoader;
    class ExceptionTable;

    struct LineNumberTableEntry {
        u2 startPC;
        u2 lineNumber;
    };

    struct Method : public ClassMember {
    public:
        u4                                  maxStack;
        u4                                  maxLocals;
        std::vector<u1>                     code;
        std::vector<std::string>            parameterTypeDescriptors;
        std::string                         returnTypeDescriptor;
        u4                                  argSlotCount;
        ExceptionTable*                     exceptionTable;
        std::vector<LineNumberTableEntry>   lineNumberTable;

        std::vector<u1>                     parameterAnnotationData; // TODO::
        std::vector<u1>                     annotationDefaultData; // TODO::


        static Method* ShimMethod; // Shim method

    private:
        void injectCodeAttribute(std::string returnType);

    public:
        Method(classfile::MethodInfo *methodInfo, Class *classRef, heap::ConstantPool* constantPool);
        Method(); // todo:: for shim method
        ~Method();

        int findExceptionHandlerPC(Class* exceptionClass, int pc);
        int lineNumber(int pc);

        [[nodiscard]] bool isConstructor() const;
        [[nodiscard]] bool isClinit() const;
        [[nodiscard]] bool isBridge() const;
        [[nodiscard]] bool isVarargs() const;
        [[nodiscard]] bool isNative() const;
        [[nodiscard]] bool isAbstract() const;
        [[nodiscard]] bool isStrict() const;
        [[nodiscard]] bool isSynchronized() const;

        std::vector<Class*> parameterTypes() const;
        std::vector<Class*> exceptionTypes() const;
        Class* returnType() const;

        std::vector<u1> getParameterAnnotationData() const;
        std::vector<u1> getAnnotationDefaultData() const;

    };
}

#endif //JVM_METHOD_H
