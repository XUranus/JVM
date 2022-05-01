//
// Created by xuranus on 2/16/19.
//

#ifndef JVM_FIELD_H
#define JVM_FIELD_H

#include <string>
#include "../../classfile/Members.h"
#include "ClassMember.h"
#include "ConstantPool.h"

namespace heap {
    class Class;
    class ClassMember;
    class ConstantPool;

    struct Field : public ClassMember {
        u4 slotId;
        u2 constValueIndex; // read constant from constant pool

        Field(classfile::FieldInfo *fieldInfo, Class *_klass, ConstantPool* constantPool);
        bool isLongOrDouble() const;

        bool isEnum() const;
        bool isVolatile() const;
        bool isTransient() const;
        bool isRef() const;

        Class* type() const;
    };

}

#endif //JVM_FIELD_H
