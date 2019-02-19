//
// Created by xuranus on 2/16/19.
//

#ifndef JVM_FIELD_H
#define JVM_FIELD_H

#include <string>
#include "../../classfile/ClassFile.h"
#include "ConstantPool.h"
#include "../Slot.h"
#include "ClassMember.h"

struct Field: public ClassMember {
    unsigned int slotId;
    unsigned int constValueIndex;

    Field(FieldInfo* fieldInfo,Class* classRef);
    static std::vector<Field*> parseFields(ClassFile* classFile,Class* classRef);
    bool isLongOrDouble();
};



#endif //JVM_FIELD_H
