//
// Non-template instruction implementations.
// Merged from constants.cpp, math.cpp (partial), control.cpp (partial).
//

#include "instructions.h"
#include "../common/Exception.h"
#include "../runtime/thread/Frame.h"
#include "../runtime/heap/Object.h"
#include "../runtime/heap/ConstantPool.h"
#include "../runtime/heap/StringPool.h"
#include "../runtime/heap/SymRef.h"

#include <cmath>

namespace instruction {

    // =========================================================================
    // Constants: bipush, sipush, ldc, ldc_w, ldc2_w
    // =========================================================================

    void bipush::fetchOperands(InstructionReader &reader) {
        val = reader.readInt8();
    }

    void bipush::execute(runtime::Frame* frame) {
        frame->operandStack.pushInt((int)val);
    }

    std::string bipush::verbose() const {
        return name() + "\t\t" + std::to_string(val);
    }

    void sipush::fetchOperands(InstructionReader &reader) {
        val = reader.readInt16();
    }

    void sipush::execute(runtime::Frame* frame) {
        frame->operandStack.pushInt((int)val);
    }

    static void ldc_(runtime::Frame* frame, u4 index) {
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
                heap::Object* internedStr = heap::StringPool::JString(klass->classloader, str);
                operandStack.pushRef(internedStr);
                break;
            }
            case heap::ConstantType::ClassRefType: {
                heap::ClassRef* classRef = constantPool->classRefValue(index);
                heap::Object* classObj = classRef->resolvedClass()->jClass;
                operandStack.pushRef(classObj);
                break;
            }
            default: {
                exception::fatal("ldc not fully implemented, type: " + std::to_string(type));
                break;
            }
        }
    }

    void ldc::execute(runtime::Frame* frame) {
        ldc_(frame, index);
    }

    void ldc_w::execute(runtime::Frame* frame) {
        ldc_(frame, index);
    }

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

    // =========================================================================
    // Array loads with widening: baload, caload, saload
    // =========================================================================

    void baload::execute(runtime::Frame* frame) {
        auto &stack = frame->operandStack;
        int index = stack.popInt();
        heap::Object* object = stack.popRef();
        if (!object) {
            exception::fatal("java.lang.NullPointerException");
            return;
        }
        char *byteArray = object->byteArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
            return;
        }
        stack.pushInt(byteArray[index]);
    }

    void caload::execute(runtime::Frame* frame) {
        auto &stack = frame->operandStack;
        int index = stack.popInt();
        heap::Object* object = stack.popRef();
        if (!object) {
            exception::fatal("java.lang.NullPointerException");
            return;
        }
        short *charArray = object->charArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
            return;
        }
        stack.pushInt(charArray[index]);
    }

    void saload::execute(runtime::Frame* frame) {
        auto &stack = frame->operandStack;
        int index = stack.popInt();
        heap::Object* object = stack.popRef();
        if (!object) {
            exception::fatal("java.lang.NullPointerException");
            return;
        }
        short *shortArray = object->shortArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
            return;
        }
        stack.pushInt(shortArray[index]);
    }

    // =========================================================================
    // Shift operations: ishl, lshl, ishr, lshr, iushr, lushr
    // =========================================================================

    void ishl::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popInt();
        auto v1 = frame->operandStack.popInt();
        frame->operandStack.pushInt(v1 << ((u4)v2 & 0x1f));
    }

    void lshl::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popInt();
        auto v1 = frame->operandStack.popLong();
        frame->operandStack.pushLong(v1 << (((u4)v2 & 0x3f)));
    }

    void ishr::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popInt();
        auto v1 = frame->operandStack.popInt();
        frame->operandStack.pushInt(v1 >> (((u4)v2 & 0x1f)));
    }

    void lshr::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popInt();
        auto v1 = frame->operandStack.popLong();
        frame->operandStack.pushLong(v1 >> (((u4)v2 & 0x3f)));
    }

    void iushr::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popInt();
        auto v1 = frame->operandStack.popInt();
        auto s = (u4)v2 & 0x1f;
        frame->operandStack.pushInt(int((u4)v1 >> s));
    }

    void lushr::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popInt();
        auto v1 = frame->operandStack.popLong();
        auto s = (u4)v2 & 0x3f;
        frame->operandStack.pushLong((long)((u8)v1 >> s));
    }

    // =========================================================================
    // Bitwise operations: iand, land, ior, lor, ixor, lxor
    // =========================================================================

    void iand::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popInt();
        auto v1 = frame->operandStack.popInt();
        frame->operandStack.pushInt(v1 & v2);
    }

    void land::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popLong();
        auto v1 = frame->operandStack.popLong();
        frame->operandStack.pushLong(v1 & v2);
    }

    void ior::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popInt();
        auto v1 = frame->operandStack.popInt();
        frame->operandStack.pushInt(v1 | v2);
    }

    void lor::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popLong();
        auto v1 = frame->operandStack.popLong();
        frame->operandStack.pushLong(v1 | v2);
    }

    void ixor::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popInt();
        auto v1 = frame->operandStack.popInt();
        frame->operandStack.pushInt(v1 ^ v2);
    }

    void lxor::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popLong();
        auto v1 = frame->operandStack.popLong();
        frame->operandStack.pushLong(v1 ^ v2);
    }

    // =========================================================================
    // iinc
    // =========================================================================

    void iinc::fetchOperands(InstructionReader &reader) {
        index = reader.readUint8();
        _const = reader.readInt8();
    }

    void iinc::execute(runtime::Frame* frame) {
        auto val = frame->localVars.intValue(index);
        val += _const;
        frame->localVars.setInt(index, val);
    }

    std::string iinc::verbose() const {
        return name() + "\t\t" + std::to_string(index) + "\t" + std::to_string(_const);
    }

    // =========================================================================
    // Control flow: goto_, jsr, ret, tableswitch, lookupswitch
    // =========================================================================

    void goto_::execute(runtime::Frame* frame) {
        frame->branch(offset);
    }

    void jsr::execute(runtime::Frame* frame) {
        exception::panic("instruction [jsr] not support after java 6");
    }

    void ret::execute(runtime::Frame* frame) {
        exception::panic("instruction [ret] not support after java 6");
    }

    void tableswitch::execute(runtime::Frame* frame) {
        int offset = 0;
        auto index = frame->operandStack.popInt();
        if (index >= low && index <= high) {
            offset = (int) jumpOffsets[index - low];
        } else {
            offset = (int) defaultOffset;
        }
        frame->branch(offset);
    }

    void tableswitch::fetchOperands(InstructionReader &reader) {
        reader.skipPadding();
        defaultOffset = reader.readInt32();
        low = reader.readInt32();
        high = reader.readInt32();
        int jumpOffsetsCount = high - low + 1;
        jumpOffsets = reader.readInt32s(jumpOffsetsCount);
    }

    void lookupswitch::execute(runtime::Frame* frame) {
        auto key = frame->operandStack.popInt();
        for (int i = 0; i < nPairs * 2; i += 2) {
            if (matchOffsets[i] == key) {
                int offset = matchOffsets[i + 1];
                frame->branch(offset);
                return;
            }
        }
        frame->branch(defaultOffsets);
    }

    void lookupswitch::fetchOperands(InstructionReader &reader) {
        reader.skipPadding();
        defaultOffsets = reader.readInt32();
        nPairs = reader.readInt32();
        matchOffsets = reader.readInt32s(nPairs * 2);
    }

} // namespace instruction
