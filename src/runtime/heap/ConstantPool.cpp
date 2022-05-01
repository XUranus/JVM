//
// Created by xuranus on 2/11/19.
//

#include "ConstantPool.h"
#include "SymRef.h"
#include <cstring>

namespace heap {

    ConstantPool::ConstantPool(Class* classRef,
                               classfile::ConstantsPool* constantsPool):
        size(constantsPool->size()),
        slots(constantsPool->size()) {
        klass = classRef;
        constantType = new ConstantType[size];
        ptrs = new void*[size];
        memset(constantType, ConstantType::NoneType, sizeof(ConstantType) * size);

        for (int i = 0; i < size; i++) {
            if(!constantsPool->constants[i]) {
                continue;
            }
            int tag = constantsPool->constants[i]->tag;
            switch (tag) {
                case CONSTANT_Integer: {
                    setInt(i, constantsPool->intValue(i));
                    break;
                }
                case CONSTANT_Long: {
                    setLong(i, constantsPool->longValue(i));
                    i++;
                    break;
                }
                case CONSTANT_Float: {
                    setFloat(i, constantsPool->floatValue(i));
                    break;
                }
                case CONSTANT_Double: {
                    setDouble(i, constantsPool->doubleValue(i));
                    i++;
                    break;
                }
                case CONSTANT_String: {
                    setString(i, constantsPool->stringValue(i));
                    break;
                }
                case CONSTANT_UTF8: {
                    setUTF8(i, constantsPool->utf8(i));
                    break;
                }
                case CONSTANT_Class: {
                    setClassRef(i, new ClassRef(this, constantsPool->className(i)));
                    break;
                }
                case CONSTANT_FieldRef: {
                    auto res = constantsPool->memberRef(i);
                    setFieldRef(i, new FieldRef(this, res.first, res.second));
                    break;
                }
                case CONSTANT_MethodRef: {
                    auto res = constantsPool->memberRef(i);
                    setMethodRef(i, new MethodRef(this, res.first, res.second));
                    break;
                }
                case CONSTANT_InterfaceMethodRef: {
                    auto res = constantsPool->memberRef(i);
                    setInterfaceMemberRef(i, new InterfaceMemberRef(this, res.first, res.second));
                    break;
                }
                default: {
                    // todo:: implement
                    //ConstantInvokeDynamic
                    //ConstantMethodHandle
                    //ConstantMethodType
                }
            }
        }
    }

    ConstantPool::~ConstantPool() {
        for(int i = 0; i < size; i++) {
            if(constantType[i] == ConstantType::StringType) {
                delete (std::string*)(ptrs[i]);
            } else if(constantType[i] == ConstantType::ClassRefType) {
                delete (ClassRef*)(ptrs[i]);
            } else if(constantType[i] == ConstantType::MethodRefType) {
                delete (MethodRef*)(ptrs[i]);
            } else if(constantType[i] == ConstantType::FieldRefType) {
                delete (FieldRef*)(ptrs[i]);
            } else if(constantType[i] == ConstantType::InterfaceMemberRefType) {
                delete (InterfaceMemberRef*)(ptrs[i]);
            }
        }
        delete[] ptrs;
        delete[] constantType;
    }


    void ConstantPool::setInt(unsigned int index, int v) {
        slots.setInt(index, v);
        constantType[index] = ConstantType::IntType;
    }

    int ConstantPool::intValue(unsigned int index) const {
        return slots.intValue(index);
    }

    void ConstantPool::setLong(unsigned int index, long v) {
        slots.setLong(index, v);
        constantType[index] = ConstantType::LongType;
    }

    long ConstantPool::longValue(unsigned int index) const {
        return slots.longValue(index);
    }

    void ConstantPool::setFloat(unsigned int index, float v) {
        slots.setFloat(index, v);
        constantType[index] = ConstantType::FloatType;
    }

    float ConstantPool::floatValue(unsigned int index) const {
        return slots.floatValue(index);
    }

    void ConstantPool::setDouble(unsigned int index, double v) {
        slots.setDouble(index, v);
        constantType[index] = ConstantType::DoubleType;
    }

    double ConstantPool::doubleValue(unsigned int index) const {
        return slots.doubleValue(index);
    }

    void ConstantPool::setString(unsigned int index, const std::string &str) {
        ptrs[index] = new std::string(str);
        constantType[index] = ConstantType::StringType;
    }

    std::string ConstantPool::stringValue(unsigned int index) const {
        return *(std::string*)ptrs[index];
    }

    void ConstantPool::setClassRef(unsigned int index, class ClassRef *ref) {
        ptrs[index] = ref;
        constantType[index] = ConstantType::ClassRefType;
    }

    class ClassRef *ConstantPool::classRefValue(unsigned int index) const {
        return (ClassRef*)ptrs[index];
    }

    void ConstantPool::setFieldRef(unsigned int index, class FieldRef *ref) {
        ptrs[index] = ref;
        constantType[index] = ConstantType::FieldRefType;
    }

    class FieldRef *ConstantPool::fieldRefValue(unsigned int index) const {
        return (FieldRef*)ptrs[index];
    }

    void ConstantPool::setMethodRef(unsigned int index, class MethodRef *ref) {
        ptrs[index] = ref;
        constantType[index] = ConstantType::MethodRefType;
    }

    class MethodRef *ConstantPool::methodRefValue(unsigned int index) const {
        return (MethodRef*)ptrs[index];
    }

    void ConstantPool::setInterfaceMemberRef(unsigned int index, class InterfaceMemberRef *ref) {
        ptrs[index] = ref;
        constantType[index] = ConstantType::InterfaceMemberRefType;
    }

    class InterfaceMemberRef *ConstantPool::interfaceMemberRefValue(unsigned int index) const {
        return (InterfaceMemberRef*)ptrs[index];
    }

    void ConstantPool::setUTF8(unsigned int index, const std::string &str) {
        ptrs[index] = new std::string(str);
        constantType[index] = ConstantType::UTF8Type;
    }

    std::string ConstantPool::UTF8Value(unsigned int index) const {
        return *(std::string*)ptrs[index];
    }


    ConstantType ConstantPool::type(unsigned int index) const {
        return constantType[index];
    }

    void ConstantPool::dump() const {
        for(int i = 0; i < size; i++) {
            std::cout << "[" << i << "]";
            switch (constantType[i]) {
                case ConstantType::IntType: { std::cout << "(int)" << intValue(i); break;}
                case ConstantType::LongType: { std::cout << "(long)" << longValue(i); break;}
                case ConstantType::FloatType: { std::cout << "(float)" << floatValue(i); break;}
                case ConstantType::DoubleType: { std::cout << "(double)" << doubleValue(i); break;}
                case ConstantType::ClassRefType: { std::cout << "(classRef)" << classRefValue(i); break;}
                case ConstantType::FieldRefType: { std::cout << "(fieldRef)" << fieldRefValue(i); break;}
                case ConstantType::MethodRefType: { std::cout << "(methodRef)" << methodRefValue(i); break;}
                case ConstantType::InterfaceMemberRefType: { std::cout << "(interfaceMemberRef)" << interfaceMemberRefValue(i); break;}
                case ConstantType::UTF8Type: { std::cout << "(UTF8)" << UTF8Value(i); break;}
                case ConstantType::StringType: { std::cout << "(string)" << stringValue(i); break;}
                case ConstantType::NoneType: { std::cout << "(None)"; break;}
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }

}