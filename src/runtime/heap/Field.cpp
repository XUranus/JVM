//
// Created by xuranus on 2/16/19.
//

#include "Field.h"
#include "Class.h"
#include <iostream>
#include "../../common/Exception.h"

namespace heap {
    Field::Field(classfile::FieldInfo *fieldInfo, Class *_klass, ConstantPool* constantPool):
        ClassMember(fieldInfo->accessFlags,
                    fieldInfo->name(),
                    fieldInfo->descriptor(),
                    _klass) {

        slotId = 0;
        constValueIndex = 0;

        // resolve signature attribute
        classfile::AttributeSignature* signatureAttribute = fieldInfo->signatureAttribute();
        if(signatureAttribute) {
            signature = constantPool->UTF8Value(signatureAttribute->signatureIndex);
        }

        // resolve constant value attribute
        classfile::AttributeConstantValue* attr = fieldInfo->constantValueAttribute();
        if (attr) {
            constValueIndex = attr->constantValueIndex;
        }
    }

    bool Field::isLongOrDouble() const {
        return descriptor == "J" || descriptor == "D";
    }

    bool Field::isEnum() const {return accessFlags & ACC_ENUM_FLAG;}

    bool Field::isVolatile() const {return accessFlags & ACC_VOLATILE_FLAG;}

    bool Field::isTransient() const {return accessFlags & ACC_TRANSIENT_FLAG;}

    bool Field::isRef() const {
        return descriptor[0] == 'L' || descriptor[0] == '[';
    }




    std::string descriptorToClassName(const std::string &descriptor) {
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

    Class *Field::type() const {
        std::string typeClassName = descriptor;
        return klass->classloader->loadClass(descriptorToClassName(typeClassName));
    }

}