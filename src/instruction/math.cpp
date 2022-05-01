//
// Created by xuranus on 2/5/19.
//

#include "math.h"
#include <cmath>
#include "../common/Exception.h"

namespace instruction {


    void iadd::execute(runtime::Frame* frame) {
        auto v1 = frame->operandStack.popInt();
        auto v2 = frame->operandStack.popInt();
        frame->operandStack.pushInt(v1 + v2);
    }

    void ladd::execute(runtime::Frame* frame) {
        auto v1 = frame->operandStack.popLong();
        auto v2 = frame->operandStack.popLong();
        frame->operandStack.pushLong(v1 + v2);
    }

    void fadd::execute(runtime::Frame* frame) {
        auto v1 = frame->operandStack.popFloat();
        auto v2 = frame->operandStack.popFloat();
        frame->operandStack.pushFloat(v1 + v2);
    }

    void dadd::execute(runtime::Frame* frame) {
        auto v1 = frame->operandStack.popDouble();
        auto v2 = frame->operandStack.popDouble();
        frame->operandStack.pushDouble(v1 + v2);
    }

    void isub::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popInt();
        auto v1 = frame->operandStack.popInt();
        frame->operandStack.pushInt(v1 - v2);
    }

    void lsub::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popLong();
        auto v1 = frame->operandStack.popLong();
        frame->operandStack.pushLong(v1 - v2);
    }

    void fsub::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popFloat();
        auto v1 = frame->operandStack.popFloat();
        frame->operandStack.pushFloat(v1 - v2);
    }

    void dsub::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popDouble();
        auto v1 = frame->operandStack.popDouble();
        frame->operandStack.pushDouble(v1 - v2);

    }

    void imul::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popInt();
        auto v1 = frame->operandStack.popInt();
        frame->operandStack.pushInt(v1 * v2);
    }

    void lmul::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popLong();
        auto v1 = frame->operandStack.popLong();
        frame->operandStack.pushLong(v1 * v2);
    }

    void fmul::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popFloat();
        auto v1 = frame->operandStack.popFloat();
        frame->operandStack.pushFloat(v1 * v2);
    }

    void dmul::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popDouble();
        auto v1 = frame->operandStack.popDouble();
        frame->operandStack.pushDouble(v1 * v2);
    }

    void idiv::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popInt();
        auto v1 = frame->operandStack.popInt();
        if(!v2) {
            exception::fatal("java.lang.ArithmeticException: / by zero");
        }
        frame->operandStack.pushInt(v1 / v2);
    }

    void ldiv_::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popLong();
        auto v1 = frame->operandStack.popLong();
        if(!v2) {
            exception::fatal("java.lang.ArithmeticException: / by zero");
        }
        frame->operandStack.pushLong(v1 / v2);
    }

    void fdiv::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popFloat();
        auto v1 = frame->operandStack.popFloat();
        if(v2 == 0.0f) {
            exception::fatal("java.lang.ArithmeticException: / by zero");
        }
        frame->operandStack.pushFloat(v1 / v2);
    }

    void ddiv::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popDouble();
        auto v1 = frame->operandStack.popDouble();
        if(v2 == 0.0) {
            exception::fatal("java.lang.ArithmeticException: / by zero");
        }
        frame->operandStack.pushDouble(v1 / v2);
    }

    void irem::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popInt();
        auto v1 = frame->operandStack.popInt();
        if(!v2) {
            exception::fatal("java.lang.ArithmeticException: % by zero");
        }
        frame->operandStack.pushInt(v1 % v2);
    }

    void lrem::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popLong();
        auto v1 = frame->operandStack.popLong();
        if(!v2) {
            exception::fatal("java.lang.ArithmeticException: % by zero");
        }
        frame->operandStack.pushInt(v1 % v2);
    }

    void frem::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popFloat();
        auto v1 = frame->operandStack.popFloat();
        if(v2 == 0.0f) {
            exception::fatal("java.lang.ArithmeticException: % by zero");
        }
        frame->operandStack.pushFloat((float) fmod(v1, v2));
    }

    void drem::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popDouble();
        auto v1 = frame->operandStack.popDouble();
        if(v2 == 0.0f) {
            exception::fatal("java.lang.ArithmeticException: % by zero");
        }
        frame->operandStack.pushDouble(fmod(v1, v2));
    }

    void ineg::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popInt();
        frame->operandStack.pushInt(-val);
    }

    void lneg::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popLong();
        frame->operandStack.pushLong(-val);
    }

    void fneg::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popFloat();
        frame->operandStack.pushFloat(-val);
    }

    void dneg::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popDouble();
        frame->operandStack.pushDouble(-val);
    }

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
        frame->operandStack.pushInt(int32((u4)v1 >> s));
    }

    void lushr::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popInt();
        auto v1 = frame->operandStack.popLong();
        auto s = (u4)v2 & 0x3f;
        frame->operandStack.pushLong((long)((u8)v1 >> s));
    }

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

    void iinc::fetchOperands(InstructionReader &reader) {
        index = reader.readUint8();
        _const = reader.readInt8();
    }

    void iinc::execute(runtime::Frame* frame) {
        auto val = frame->localVars.intValue(index);
        val += _const;
        frame->localVars.setInt(index, val);
    }

    std::string iinc::verbose() {
        return name() + "\t\t" + std::to_string(index) + "\t" + std::to_string(_const);
    }

}