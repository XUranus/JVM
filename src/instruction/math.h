//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_MATH_H
#define JVM_MATH_H


#include "instruction.h"

namespace instruction {

    struct iadd : public NoOperandsInstruction {//0x60
        void execute(runtime::Frame* frame) override;
    };

    struct ladd : public NoOperandsInstruction {//0x61
        void execute(runtime::Frame* frame) override;
    };

    struct fadd : public NoOperandsInstruction {//0x62
        void execute(runtime::Frame* frame) override;
    };

    struct dadd : public NoOperandsInstruction {//0x63
        void execute(runtime::Frame* frame) override;
    };

    struct isub : public NoOperandsInstruction {//0x64
        void execute(runtime::Frame* frame) override;
    };

    struct lsub : public NoOperandsInstruction {//0x65
        void execute(runtime::Frame* frame) override;
    };

    struct fsub : public NoOperandsInstruction {//0x66
        void execute(runtime::Frame* frame) override;
    };

    struct dsub : public NoOperandsInstruction {//0x67
        void execute(runtime::Frame* frame) override;
    };

    struct imul : public NoOperandsInstruction {//0x68
        void execute(runtime::Frame* frame) override;
    };

    struct lmul : public NoOperandsInstruction {//0x69
        void execute(runtime::Frame* frame) override;
    };

    struct fmul : public NoOperandsInstruction {//0x6A
        void execute(runtime::Frame* frame) override;
    };

    struct dmul : public NoOperandsInstruction {//0x6B
        void execute(runtime::Frame* frame) override;
    };

    struct idiv : public NoOperandsInstruction {//0x6C
        void execute(runtime::Frame* frame) override;
    };

    struct ldiv_ : public NoOperandsInstruction {//0x6D
        void execute(runtime::Frame* frame) override;
    };

    struct fdiv : public NoOperandsInstruction {//0x6E
        void execute(runtime::Frame* frame) override;
    };

    struct ddiv : public NoOperandsInstruction {//0x6F
        void execute(runtime::Frame* frame) override;
    };

    struct irem : public NoOperandsInstruction {//0x70
        void execute(runtime::Frame* frame) override;
    };

    struct lrem : public NoOperandsInstruction {//0x71
        void execute(runtime::Frame* frame) override;
    };

    struct frem : public NoOperandsInstruction {//0x72
        void execute(runtime::Frame* frame) override;
    };

    struct drem : public NoOperandsInstruction {//0x73
        void execute(runtime::Frame* frame) override;
    };

    struct ineg : public NoOperandsInstruction {//0x74
        void execute(runtime::Frame* frame) override;
    };

    struct lneg : public NoOperandsInstruction {//0x75
        void execute(runtime::Frame* frame) override;
    };

    struct fneg : public NoOperandsInstruction {//0x76
        void execute(runtime::Frame* frame) override;
    };

    struct dneg : public NoOperandsInstruction {//0x77
        void execute(runtime::Frame* frame) override;
    };

    struct ishl : public NoOperandsInstruction {//0x78
        void execute(runtime::Frame* frame) override;
    };

    struct lshl : public NoOperandsInstruction {//0x79
        void execute(runtime::Frame* frame) override;
    };

    struct ishr : public NoOperandsInstruction {//0x7A
        void execute(runtime::Frame* frame) override;
    };

    struct lshr : public NoOperandsInstruction {//0x7B
        void execute(runtime::Frame* frame) override;
    };

    struct iushr : public NoOperandsInstruction {//0x7C
        void execute(runtime::Frame* frame) override;
    };

    struct lushr : public NoOperandsInstruction {//0x7D
        void execute(runtime::Frame* frame) override;
    };

    struct iand : public NoOperandsInstruction {//0x7E
        void execute(runtime::Frame* frame) override;
    };

    struct land : public NoOperandsInstruction {//0x7F
        void execute(runtime::Frame* frame) override;
    };

    struct ior : public NoOperandsInstruction {//0x80
        void execute(runtime::Frame* frame) override;
    };

    struct lor : public NoOperandsInstruction {//0x81
        void execute(runtime::Frame* frame) override;
    };

    struct ixor : public NoOperandsInstruction {//0x82
        void execute(runtime::Frame* frame) override;
    };

    struct lxor : public NoOperandsInstruction {//0x83
        void execute(runtime::Frame* frame) override;
    };

    struct iinc : public Instruction {//0x84
        unsigned int index;
        int _const;

        void execute(runtime::Frame* frame) override;
        void fetchOperands(InstructionReader &reader) override;
        std::string verbose() override;
    };
}


#endif //JVM_MATH_H
