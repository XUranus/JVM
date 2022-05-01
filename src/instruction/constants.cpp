//
// Created by xuranus on 2/5/19.
//

//#define DEBUG_MODE 1



#include "constants.h"
#include "../common/Exception.h"
#include "../runtime/thread/Frame.h"
#include "../runtime/heap/StringPool.h"
#include "../runtime/heap/SymRef.h"

namespace instruction {

    void nop::execute(runtime::Frame* frame) {
        /** do nothing **/
    }

    void aconst_null::execute(runtime::Frame* frame) {
        frame->operandStack.pushRef(nullptr);
    }

    void iconst_m1::execute(runtime::Frame* frame) {
        frame->operandStack.pushInt(-1);
    }

    void iconst_0::execute(runtime::Frame* frame) {
        frame->operandStack.pushInt(0);
    }

    void iconst_1::execute(runtime::Frame* frame) {
        frame->operandStack.pushInt(1);
    }

    void iconst_2::execute(runtime::Frame* frame) {
        frame->operandStack.pushInt(2);
    }

    void iconst_3::execute(runtime::Frame* frame) {
        frame->operandStack.pushInt(3);
    }

    void iconst_4::execute(runtime::Frame* frame) {
        frame->operandStack.pushInt(4);
    }

    void iconst_5::execute(runtime::Frame* frame) {
        frame->operandStack.pushInt(5);
    }

    void lconst_0::execute(runtime::Frame* frame) {
        frame->operandStack.pushLong(0);
    }

    void lconst_1::execute(runtime::Frame* frame) {
        frame->operandStack.pushLong(1);
    }

    void fconst_0::execute(runtime::Frame* frame) {
        frame->operandStack.pushFloat(0.0f);
    }

    void fconst_1::execute(runtime::Frame* frame) {
        frame->operandStack.pushFloat(1.0f);
    }

    void fconst_2::execute(runtime::Frame* frame) {
        frame->operandStack.pushFloat(2.0f);
    }

    void dconst_0::execute(runtime::Frame* frame) {
        frame->operandStack.pushDouble(0.0);
    }

    void dconst_1::execute(runtime::Frame* frame) {
        frame->operandStack.pushDouble(1.0);
    }

    void bipush::fetchOperands(InstructionReader &reader) {
        val = reader.readInt8();
    }

    void bipush::execute(runtime::Frame* frame) {
        frame->operandStack.pushInt((int)val);
    }

    std::string bipush::verbose() {
        return name() + "\t\t" + std::to_string(val);
    }

    void sipush::fetchOperands(InstructionReader &reader) {
        val = reader.readInt16();
    }

    void sipush::execute(runtime::Frame* frame) {
        frame->operandStack.pushInt((int)val);
    }



    void ldc_(runtime::Frame* frame, u4 index) {
        auto &operandStack = frame->operandStack;
        heap::Class* klass = frame->method->klass;
        heap::ConstantPool* constantPool = frame->method->klass->constantPool;
        heap::ConstantType type = constantPool->type(index);
        switch (type) {
            case heap::ConstantType::IntType: {
                operandStack.pushInt(constantPool->intValue(index));
                break;
            }
            case heap::ConstantType::FloatType: {
                operandStack.pushFloat(constantPool->floatValue(index));
                break;
            }
            case heap::ConstantType::StringType: {
                const std::string& str = constantPool->stringValue(index);
                // directly instantiate java.lang.String
                heap::Object* internedStr = heap::StringPool::JString(klass->classloader, str);
                operandStack.pushRef(internedStr);
                break;
            }
            case heap::ConstantType::ClassRefType: {
                heap::ClassRef* classRef = constantPool->classRefValue(index);
                heap::Object* classObj = classRef->resolvedClass()->jClass;
                operandStack.pushRef(classObj);
                //std::cout << "ldc pushed classref " << classRef->resolvedClass()->name << " "  << frame->method->klass->name << "." << frame->method->name << " " << index << std::endl;
                //std::cout << heap::ObjectPool::compressPtr(frame->method->klass->classloader->loadClass("java/lang/Class")->jClass) << std::endl;
                break;
            }
//            case heap::ConstantType::MethodRefType: {
//                heap::MethodRef* methodRef = constantPool->methodRefValue(index);
//                heap::Object* methodObj = methodRef->resolvedMethod()->jClass; // todo:: implement method reflection
//                operandStack.pushRef(methodObj);
//                break;
//            }
//            case heap::ConstantType::FieldRefType: {
//                heap::FieldRef* fieldRef = constantPool->fieldRefValue(index);
//                heap::Object* fieldObj = fieldRef->resolvedField()->jClass;  // todo:: implement field reflection
//                operandStack.pushRef(fieldObj);
//                break;
//            }
//            case heap::ConstantType::InterfaceMemberRefType: {
//                heap::InterfaceMemberRef* interfaceMemberRef = constantPool->interfaceMemberRefValue(index);
//                heap::Object* interfaceMemberObject = interfaceMemberRef->resolvedInterfaceMethod()->jClass; //  todo:: implement method reflection
//                operandStack.pushRef(interfaceMemberObject);
//                break;
//            }
            default: {
                exception::fatal("ldc not fully implemented, type: " + std::to_string(type));
                break;
            }
        }
    }

    /**
     *  load constant (int, float, string, instance of java.lang.Class, MethodType, MethodHandle)
     *  from constant pool. and push it to operand stack
     **/
    void ldc::execute(runtime::Frame* frame) {
        //todo:: implement MethodType, MethodHandle
        ldc_(frame, index);
    }

    // differs operand size from ldc
    void ldc_w::execute(runtime::Frame* frame) {
        ldc_(frame, index);
    }

    /**
     *  load constant (long. double)
     *  from constant pool. and push it to operand stack
     **/
    void ldc2_w::execute(runtime::Frame* frame) {
        auto &operandStack = frame->operandStack;
        heap::ConstantPool* constantPool = frame->method->klass->constantPool;
        heap::ConstantType type = constantPool->type(index);
        switch (type) {
            case heap::ConstantType::LongType: {
                operandStack.pushLong(constantPool->longValue(index));
                break;
            }
            case heap::ConstantType::DoubleType: {
                operandStack.pushDouble(constantPool->doubleValue(index));
                break;
            }
            default: {
                exception::fatal("ldc2_w not fully implemented, type: " + std::to_string(type));
                break;
            }
        }
    }


}