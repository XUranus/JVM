#pragma once

#include <string>
#include <vector>
#include <memory>
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
        std::unique_ptr<ExceptionTable>     exceptionTable;
        std::vector<LineNumberTableEntry>   lineNumberTable;

        std::vector<u1>                     parameterAnnotationData; // TODO::
        std::vector<u1>                     annotationDefaultData; // TODO::

        static std::unique_ptr<Method> ShimMethod; // Shim method

    private:
        void injectCodeAttribute(std::string returnType);

    public:
        Method(classfile::MethodInfo *methodInfo, Class *classRef, heap::ConstantPool* constantPool);
        Method(); // todo:: for shim method
        ~Method();

        // Method is movable but not copyable (due to unique_ptr<ExceptionTable>)
        Method(Method&&) noexcept = default;
        Method& operator=(Method&&) noexcept = default;

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
