//
// Created by xuranus on 2/11/19.
//

#ifndef JVM_HEAP_SYM_REF_H
#define JVM_HEAP_SYM_REF_H

#include "Class.h"
#include "ConstantPool.h"
/**
 *  when classfile::ConstantPool is converted to heap::ConstantPool, ref constants need be parsed as SymRef*
 *
 *                            SymRef
 *                              |
 *               --------------------------------
 *              |                               |
 *          ClassRef                        MemberRef
 *                                              |
 *                                    ----------------------------
 *                                   |          |                |
 *                               FieldRef    MethodRef   InterfaceMemberRef
 *
 * example:
 *  Java Code:
 *
 *     class Student {
 *          private String studentName;
 *          public String getName() {...};
 *     }
 *
 *  Native JVM Heap Data Structure;
 *     field {
 *          accessFlag: ACC_PRIVATE
 *          className:  "Student"
 *          class:      (cache ptr to class 'Student')
 *          name:       "studentName"
 *          descriptor: "Ljava/lang/String;"
 *          Field:      (cache ptr to resolved field)
 *     }
 *
 *     Method {
 *          accessFlag: ACC_PUBLIC
 *          className:  "Student"
 *          class:      (cache ptr to class 'Student')
 *          name:       "getName"
 *          descriptor: "()Ljava/lang/String;"
 *          Method:     (cache ptr to resolved method)
 *     }
 */

namespace heap {

    class ConstantPool;
    class Class;
    class Field;
    class Method;

    class SymRef {
    protected:
        std::string className;  // the class it belongs to
        ConstantPool *constantPool; // for referring

        Class *klass; // for referring, cache ptr of the class it belongs to, init later -> resolveClassRef()

    public:
        SymRef(ConstantPool* _constantPool, const std::string& _className);
        virtual ~SymRef() = default;
        void resolveClassRef();
        Class *resolvedClass();
    };

    // from CONSTANT_Class
    class ClassRef : public SymRef {
    public:
        ClassRef(ConstantPool *_constantPool, const std::string& _classname);
    };

    class MemberRef : public SymRef {
    public:
        std::string name;
        std::string descriptor;
    public:
        MemberRef(const std::string &_className, const std::pair<std::string, std::string> &nameAndDescriptor, ConstantPool *_constantPool);
        //three types of constant: FieldRef MethodRef InterfacesMethodRef, corresponding to the following three subclass
    };

    // from CONSTANT_FieldRef
    class FieldRef : public MemberRef {
    private:
        Field *field; // cache resolved field
    public:
        FieldRef(ConstantPool *_constantPool, const std::string& _className, const std::pair<std::string, std::string>& nameAndDescriptor);
        void resolveFieldRef();
        Field *resolvedField();
    };

    // from CONSTANT_MethodRef
    class MethodRef : public MemberRef {
    private:
        Method *method; // cache resolved method
    public:
        MethodRef(ConstantPool *_constantPool, const std::string& _className, const std::pair<std::string, std::string>& nameAndDescriptor);
        void resolveMethodRef();
        Method *resolvedMethod();
    };

    // from CONSTANT_InterfaceMethodRef
    class InterfaceMemberRef : public MemberRef {
    private:
        Method *method; // cache resolved method
    public:
        InterfaceMemberRef(ConstantPool *_constantPool, const std::string& _className, const std::pair<std::string, std::string>& nameAndDescriptor);
        void resolveInterfaceMethodRef();
        Method *resolvedInterfaceMethod();
    };

}

#endif //JVM_HEAP_SYM_REF_H
