//
// Created by xuranus on 4/23/22.
//

#ifndef JVM_HEAP_EXCEPTION_HANDLER_H
#define JVM_HEAP_EXCEPTION_HANDLER_H

/**
 *
 * Java Exception can be distinguished as two type: "Checked Exception" and "Unchecked Exception" .
 *
 * "Unchecked Exception" concludes java.lang.RuntimeException, java lang.Error, and their subclasses,
 * while all the other classes are "Checked Exception".
 *
 * All Exception inherit from java.lang.Throwable.
 *
 * Exception can both be threw by Java code or JVM. When a fatal error occurs during runtime, JVM will
 * throw a subclass of java.lang.Error like StackOverFlowError, OutOfMemoryError ,etc, and program won't be
 * able to recover from such Exception. These Exception are usually caused by bugs in code. The throwing
 * Exception procedure is done by corporation of instruction ATHROW and ExceptionTable of methods.
 *
 * Before Java 6, the Java compiler of Oracle uses instruction JSR, JSR_W and RET to implement "finally"
 * clause, and these instructions have been deprecated since Java 6.
 *
 *
 */

#include <vector>
#include "../../classfile/Attributes.h"
#include "ClassLoader.h"
#include "../../basicType.h"

namespace heap {

    class ClassRef;
    class ConstantPool;
    class Class;
    class ClassLoader;


    struct ExceptionHandler {
        u2 startPC{};    // from
        u2 endPC{};      // to
        u2 handlerPC{};  // where to handle
        ClassRef* catchType;  // for referring, do not delete,
                              // nullptr means catch all, this is used to implement 'finally' clause

        ExceptionHandler();
        ExceptionHandler(u2 _startPC, u2 _endPC, u2 _handlerPC, ClassRef* _catchTypeRef);
    };

    class ExceptionTable {
    public:
        std::vector<ExceptionHandler> handlers;

    public:
        ExceptionTable() = default;
        ExceptionTable(ConstantPool* constantPool, classfile::AttributeCode* attributeCode);
        ExceptionHandler* findHandler(Class* klass, int pc);
        std::vector<Class*> exceptionTypes() const;
    };

};


#endif //JVM_HEAP_EXCEPTION_HANDLER_H
