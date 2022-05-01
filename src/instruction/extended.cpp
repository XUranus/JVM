//
// Created by xuranus on 2/5/19.
//

#include "extended.h"
#include "../common/Exception.h"
//#include "../runtime/heap/SymRef.h"

namespace instruction {


    void wide::execute(runtime::Frame* frame) {
        switch (extendOpCode) {
            case 0x15: {//iload
                auto val = frame->localVars.intValue(wideIndex);
                frame->operandStack.pushInt(val);
                return;
            }
            case 0x16: {//lload
                auto val = frame->localVars.longValue(wideIndex);
                frame->operandStack.pushLong(val);
                return;
            }
            case 0x17: {//fload
                auto val = frame->localVars.floatValue(wideIndex);
                frame->operandStack.pushFloat(val);
                return;
            }
            case 0x18: {//dload
                auto val = frame->localVars.doubleValue(wideIndex);
                frame->operandStack.pushDouble(val);
                return;
            }
            case 0x19: {//aload
                auto val = frame->localVars.refValue(wideIndex);
                frame->operandStack.pushRef(val);
                return;
            }
            case 0x36: {//istore
                auto val = frame->operandStack.popInt();
                frame->localVars.setInt(wideIndex, val);
                return;
            }
            case 0x37: {//lstore
                auto val = frame->operandStack.popLong();
                frame->localVars.setLong(wideIndex, val);
                return;
            }
            case 0x38: {//fstore
                auto val = frame->operandStack.popFloat();
                frame->localVars.setFloat(wideIndex, val);
                return;
            }
            case 0x39: {//dstore
                auto val = frame->operandStack.popDouble();
                frame->localVars.setDouble(wideIndex, val);
                return;
            }
            case 0x3a: {//astore
                auto val = frame->operandStack.popRef();
                frame->localVars.setRef(wideIndex, val);
                return;
            }
            case 0x84: {//iinc
                auto val = frame->localVars.intValue(wideIndex);
                val += _const;
                frame->localVars.setInt(wideIndex, val);
                return;
            }
            case 0xa9: {//ret
                exception::panic("instruction [ret] not support after java 6");
            }
            default: {
                exception::panic("instruction [wide] extend opcode error: " + std::to_string(extendOpCode));
            }
        }

    }


    void wide::fetchOperands(InstructionReader &reader) {
        extendOpCode = reader.readUint8();
        wideIndex = reader.readUint16();
        if (extendOpCode == 0x84) { // iinc
            _const = (int)reader.readInt16();
        }
    }

    void multianewarray::fetchOperands(InstructionReader &reader) {
        index = reader.readUint16();
        nDimension = reader.readUint8();
    }

    void multianewarray::execute(runtime::Frame* frame) {
        heap::ConstantPool* constantPool = frame->method->klass->constantPool;
        heap::ClassRef* classRef = constantPool->classRefValue(index);
        heap::Class* arrayClass = classRef->resolvedClass();

        auto &stack = frame->operandStack;
        const std::vector<int>& dimensions = stack.popAndCheckCounts(nDimension);
        heap::Object* arrayObject = arrayClass->newMultiDimensionArray(dimensions);
        stack.pushRef(arrayObject);
    }

    void ifnull::execute(runtime::Frame* frame) {
        auto ref = frame->operandStack.popRef();
        if (!ref) {
            frame->branch(offset);
        }
    }

    void ifnonnull::execute(runtime::Frame* frame) {
        auto ref = frame->operandStack.popRef();
        if (ref) {
            frame->branch(offset);
        }
    }

    void goto_w::execute(runtime::Frame* frame) {
        frame->branch(offset);
    }

    void goto_w::fetchOperands(InstructionReader &reader) {
        offset = reader.readInt32();
    }

    void jsr_w::execute(runtime::Frame* frame) {
        exception::panic("instruction [jsr_w] not support after java 6.");
    }

    void jsr_w::fetchOperands(InstructionReader &reader) {
        offset = reader.readInt32();
    }

}