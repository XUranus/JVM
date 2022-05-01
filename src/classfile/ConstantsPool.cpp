//
// Created by xuranus on 4/6/22.
//

#include "ConstantsPool.h"
#include "../common/Exception.h"
#include <cassert>
#include <iostream>

#define DEBUG_MODE
// ConstantInfo
namespace classfile {

    ConstantInfo *ConstantInfo::fromReader(u1 tag, BytesReader &reader, ConstantsPool* pool) {
        switch(tag) {
            case CONSTANT_UTF8:                 return new ConstantUTF8(tag, reader, pool);
            case CONSTANT_Integer:              return new ConstantInteger(tag, reader, pool);
            case CONSTANT_Float:                return new ConstantFloat(tag, reader, pool);
            case CONSTANT_Long:                 return new ConstantLong(tag, reader, pool);
            case CONSTANT_Double:               return new ConstantDouble(tag, reader, pool);
            case CONSTANT_Class:                return new ConstantClass(tag, reader, pool);
            case CONSTANT_String:               return new ConstantString(tag, reader, pool);
            case CONSTANT_FieldRef:             return new ConstantFieldRef(tag, reader, pool);
            case CONSTANT_MethodRef:            return new ConstantMethodRef(tag, reader, pool);
            case CONSTANT_InterfaceMethodRef:   return new ConstantInterfaceMethodRef(tag, reader, pool);
            case CONSTANT_NameAndType:          return new ConstantNameAndType(tag, reader, pool);
            case CONSTANT_MethodHandle:         return new ConstantMethodHandle(tag, reader, pool);
            case CONSTANT_MethodType:           return new ConstantMethodType(tag, reader, pool);
            case CONSTANT_InvokeDynamic:        return new ConstantInvokeDynamic(tag, reader, pool);
            default: {
                exception::panic("unknown constant tag " + std::to_string(tag));
            }
        }
        return nullptr;
    }

    ConstantInfo::ConstantInfo(u1 _tag, ConstantsPool* _constantsPool) {
        tag = _tag;
        constantsPool = _constantsPool;
    }
}


// ConstantInfo Derived Class
namespace classfile {

    ConstantUTF8::ConstantUTF8(u1 tag, BytesReader& reader, ConstantsPool* pool): ConstantInfo(tag, pool){
        length = reader.readU2();
        bytes = std::unique_ptr<u1>(new u1[length]);
        reader.read(bytes.get(), length);
    }

    std::string ConstantUTF8::utf8() const {
        return std::string {(char*)bytes.get(), length};
    }

    std::string ConstantUTF8::verbose() {
        return "Utf8\t\t\t\t\t" + utf8();
    }


    ConstantInteger::ConstantInteger(u1 tag, BytesReader& reader, ConstantsPool* pool): ConstantInfo(tag, pool) {
        bytes = reader.readU4();
    }

    int ConstantInteger::intValue() const {
        return (int)bytes;
    }

    std::string ConstantInteger::verbose() {
        return "Integer\t\t\t\t" + std::to_string(intValue());
    }

    ConstantFloat::ConstantFloat(u1 tag, BytesReader& reader, ConstantsPool* pool): ConstantInfo(tag, pool) {
        bytes = reader.readU4();
    }

    float ConstantFloat::floatValue() const {
        return *(float*)(&bytes);
    }

    std::string ConstantFloat::verbose() {
        return "Float\t\t\t\t" + std::to_string(floatValue());
    }

    ConstantLong::ConstantLong(u1 tag, BytesReader& reader, ConstantsPool* pool): ConstantInfo(tag, pool) {
        highBytes = reader.readU4();
        lowBytes = reader.readU4();
    }

    long ConstantLong::longValue() const {
        return (long)highBytes << 32 | (long)lowBytes;
    }

    std::string ConstantLong::verbose() {
        return "Long\t\t\t\t\t" + std::to_string(longValue());
    }

    ConstantDouble::ConstantDouble(u1 tag, BytesReader& reader, ConstantsPool* pool): ConstantInfo(tag, pool) {
        highBytes = reader.readU4();
        lowBytes = reader.readU4();
    }

    double ConstantDouble::doubleValue() const {
        long t = (long)highBytes << 32 | (long)lowBytes;
        return *(double*)(&t);
    }

    std::string ConstantDouble::verbose() {
        return "Double\t\t\t\t" + std::to_string(doubleValue());
    }

    ConstantClass::ConstantClass(u1 tag, BytesReader& reader, ConstantsPool* pool): ConstantInfo(tag, pool) {
        nameIndex = reader.readU2();
    }

    std::string ConstantClass::className() const {
        return constantsPool->utf8(nameIndex);
    }

    std::string ConstantClass::verbose() {
        return "Class\t\t\t\t\t#" + std::to_string(nameIndex) + "\t\t\t\t// " + className();
    }

    ConstantString::ConstantString(u1 tag, BytesReader& reader, ConstantsPool* pool): ConstantInfo(tag, pool) {
        stringIndex = reader.readU2();
    }

    std::string ConstantString::stringValue() const {
        return constantsPool->utf8(stringIndex);
    }

    std::string ConstantString::verbose() {
        return "String\t\t\t\t\t#" + std::to_string(stringIndex) + "\t\t\t\t// " + stringValue();
    }


    ConstantFieldRef::ConstantFieldRef(u1 tag, BytesReader& reader, ConstantsPool* pool): ConstantInfo(tag, pool) {
        classIndex = reader.readU2();
        classAndTypeIndex = reader.readU2();

    }

    std::string ConstantFieldRef::className() {
        return constantsPool->className(classIndex);
    }

    std::pair<std::string, std::string> ConstantFieldRef::nameAndDescriptor() {
        return constantsPool->nameAndDescriptor(classAndTypeIndex);
    }

    std::string ConstantFieldRef::verbose() {
        auto pair = nameAndDescriptor();
        return "FieldRef\t\t\t\t#" + std::to_string(classIndex) + ".#" + std::to_string(classAndTypeIndex)
        + "\t\t\t// " + className() + "." + pair.first + ":" + pair.second;
    }

    ConstantMethodRef::ConstantMethodRef(u1 tag, BytesReader& reader, ConstantsPool* pool): ConstantInfo(tag, pool) {
        classIndex = reader.readU2();
        nameAndTypeIndex = reader.readU2();
    }

    std::string ConstantMethodRef::className() {
        return constantsPool->className(classIndex);
    }

    std::pair<std::string, std::string> ConstantMethodRef::nameAndDescriptor() {
        return constantsPool->nameAndDescriptor(nameAndTypeIndex);
    }

    std::string ConstantMethodRef::verbose() {
        auto pair = nameAndDescriptor();
        return "MethodRef\t\t\t\t#" + std::to_string(classIndex) + ".#" + std::to_string(nameAndTypeIndex)
              + "\t\t\t// " + className() + "." + pair.first + ":" + pair.second;
    };

    ConstantInterfaceMethodRef::ConstantInterfaceMethodRef(u1 tag, BytesReader& reader, ConstantsPool* pool): ConstantInfo(tag, pool) {
        classIndex = reader.readU2();
        classAndTypeIndex = reader.readU2();

    }

    std::string ConstantInterfaceMethodRef::className() {
        return constantsPool->className(classIndex);
    }

    std::pair<std::string,std::string> ConstantInterfaceMethodRef::nameAndDescriptor() {
        return constantsPool->nameAndDescriptor(classAndTypeIndex);
    }

    std::string ConstantInterfaceMethodRef::verbose() {
        auto pair = nameAndDescriptor();
        return "InterfaceMethodRef\t#" + std::to_string(classIndex) + ".#" + std::to_string(classAndTypeIndex)
               + "\t\t\t\t// " + className() + "." + pair.first + ":" + pair.second;
    }

    ConstantNameAndType::ConstantNameAndType(u1 tag, BytesReader& reader, ConstantsPool* pool): ConstantInfo(tag, pool) {
        nameIndex = reader.readU2();
        descriptorIndex = reader.readU2();

    }

    std::pair<std::string, std::string> ConstantNameAndType::nameAndDescriptor() {
        std::string name = constantsPool->utf8(nameIndex);
        std::string type = constantsPool->utf8(descriptorIndex);
        return std::make_pair(name,type);
    }

    std::string ConstantNameAndType::verbose() {
        auto pair = nameAndDescriptor();
        return "NameAndType\t\t\t#" + std::to_string(nameIndex) + ".#" + std::to_string(descriptorIndex)
               + "\t\t\t// " + pair.first + ":" + pair.second;
    }



    ConstantMethodHandle::ConstantMethodHandle(u1 tag, BytesReader& reader, ConstantsPool* pool): ConstantInfo(tag, pool) {
        referenceKind = reader.readU1();
        referenceIndex = reader.readU2();

    }

    std::string ConstantMethodHandle::verbose() {
        return "MethodHandle\t\t\t\t#" + std::to_string(referenceIndex) + ".#" + std::to_string(referenceIndex);
    }

    ConstantMethodType::ConstantMethodType(u1 tag, BytesReader& reader, ConstantsPool* pool): ConstantInfo(tag, pool) {
        descriptorIndex = reader.readU2();

    }

    std::string ConstantMethodType::verbose() {
        return "MethodType\t\t\t\t#" + std::to_string(descriptorIndex);
    }

    ConstantInvokeDynamic::ConstantInvokeDynamic(u1 tag, BytesReader& reader, ConstantsPool* pool): ConstantInfo(tag, pool) {
        bootstrapMethodAttrIndex = reader.readU2();
        nameAndTypeIndex = reader.readU2();

    }

    std::string ConstantInvokeDynamic::verbose() {
        return "InvokeDynamic\t\t\t\t#" + std::to_string(bootstrapMethodAttrIndex) + ".#" + std::to_string(nameAndTypeIndex);
    }



}


/**
 * ConstantsPool
 */
namespace classfile {

    ConstantsPool::ConstantsPool(BytesReader &reader) {
        _size = reader.readU2();
        constants.reserve(_size);
        constants.push_back(nullptr);
        for(u2 i = 1; i < _size; i++) {
            int tag = reader.readU1();
            constants.push_back(std::unique_ptr<ConstantInfo>(ConstantInfo::fromReader(tag, reader, this)));
            if(tag == CONSTANT_Long || tag == CONSTANT_Double) {
                i++;
                constants.push_back(nullptr);
            }
        }
    }

    int ConstantsPool::size() const {
        return _size;
    }


    std::string ConstantsPool::utf8(int index) const {
#ifdef DEBUG_MODE
        assert(constants[index]->tag == CONSTANT_UTF8);
#endif
        return ((ConstantUTF8*)constants[index].get())->utf8();
    }

    int ConstantsPool::intValue(int index) const {
#ifdef DEBUG_MODE
        assert(constants[index]->tag == CONSTANT_Integer);
#endif
        return ((ConstantInteger*)constants[index].get())->intValue();
    }

    float ConstantsPool::floatValue(int index) const {
#ifdef DEBUG_MODE
        assert(constants[index]->tag == CONSTANT_Float);
#endif
        return ((ConstantFloat*)constants[index].get())->floatValue();
    }

    double ConstantsPool::doubleValue(int index) const {
#ifdef DEBUG_MODE
        assert(constants[index]->tag == CONSTANT_Double);
#endif
        return ((ConstantDouble*)constants[index].get())->doubleValue();
    }

    std::string ConstantsPool::stringValue(int index) const {
#ifdef DEBUG_MODE
        assert(constants[index]->tag == CONSTANT_String);
#endif
        return ((ConstantString*)constants[index].get())->stringValue();
    }

    long ConstantsPool::longValue(int index) const {
#ifdef DEBUG_MODE
        assert(constants[index]->tag == CONSTANT_Long);
#endif
        return ((ConstantLong*)constants[index].get())->longValue();
    }

    std::string ConstantsPool::className(int index) const {
#ifdef DEBUG_MODE
        assert(constants[index]->tag == CONSTANT_Class);
#endif
        return ((ConstantClass*)constants[index].get())->className();
    }

    std::pair<std::string, std::string> ConstantsPool::nameAndDescriptor(int index) const {
#ifdef DEBUG_MODE
        assert(constants[index]->tag == CONSTANT_NameAndType);
#endif
        return ((ConstantNameAndType*)constants[index].get())->nameAndDescriptor();
    }

    std::pair<std::string, std::pair<std::string, std::string>> ConstantsPool::memberRef(int index) const {
        int tag = constants[index]->tag;
#ifdef DEBUG_MODE
        assert(tag == CONSTANT_FieldRef
            || tag == CONSTANT_MethodRef
            || tag == CONSTANT_InterfaceMethodRef);
#endif
        if(tag == CONSTANT_MethodRef) {
            auto className = ((ConstantMethodRef *) constants[index].get())->className();
            auto nameAndDescriptor = ((ConstantMethodRef *) constants[index].get())->nameAndDescriptor();
            return std::make_pair(className, nameAndDescriptor);
        } else if(tag == CONSTANT_FieldRef) {
            auto className = ((ConstantFieldRef *) constants[index].get())->className();
            auto nameAndDescriptor = ((ConstantFieldRef *) constants[index].get())->nameAndDescriptor();
            return std::make_pair(className, nameAndDescriptor);
        } else if(tag == CONSTANT_InterfaceMethodRef) {
            auto className = ((ConstantInterfaceMethodRef *) constants[index].get())->className();
            auto nameAndDescriptor = ((ConstantInterfaceMethodRef *) constants[index].get())->nameAndDescriptor();
            return std::make_pair(className, nameAndDescriptor);
        }
        exception::panic("no such member ref tag: " + std::to_string(tag));
        exit(1);
    }

    void ConstantsPool::dump() const {
        std::cout << "Constant pool:" << std::endl;
        for(int i = 1; i < _size; i++) {
            if(constants[i] == nullptr) continue;
            int tag = constants[i]->tag;
            std::cout << "\t#" << i << " = " << constants[i]->verbose() << std::endl;
            if(tag == CONSTANT_Long || tag == CONSTANT_Double) i++;
        }
    }

}