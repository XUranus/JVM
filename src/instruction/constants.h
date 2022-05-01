//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_CONSTANTS_H
#define JVM_CONSTANTS_H


#include "instruction.h"

namespace instruction {

    struct nop : public NoOperandsInstruction {//0x00
        void execute(runtime::Frame* frame) override;
    };

    struct aconst_null : public NoOperandsInstruction {//0x01
        void execute(runtime::Frame* frame) override;
    };

    struct iconst_m1 : public NoOperandsInstruction {//0x02
        void execute(runtime::Frame* frame) override;
    };

    struct iconst_0 : public NoOperandsInstruction {//0x03
        void execute(runtime::Frame* frame) override;
    };

    struct iconst_1 : public NoOperandsInstruction {//0x04
        void execute(runtime::Frame* frame) override;
    };

    struct iconst_2 : public NoOperandsInstruction {//0x05
        void execute(runtime::Frame* frame) override;
    };

    struct iconst_3 : public NoOperandsInstruction {//0x06
        void execute(runtime::Frame* frame) override;
    };

    struct iconst_4 : public NoOperandsInstruction {//0x07
        void execute(runtime::Frame* frame) override;
    };

    struct iconst_5 : public NoOperandsInstruction {//0x08
        void execute(runtime::Frame* frame) override;
    };

    struct lconst_0 : public NoOperandsInstruction {//0x09
        void execute(runtime::Frame* frame) override;
    };

    struct lconst_1 : public NoOperandsInstruction {//0x0A
        void execute(runtime::Frame* frame) override;
    };

    struct fconst_0 : public NoOperandsInstruction {//0x0B
        void execute(runtime::Frame* frame) override;
    };

    struct fconst_1 : public NoOperandsInstruction {//0x0C
        void execute(runtime::Frame* frame) override;
    };

    struct fconst_2 : public NoOperandsInstruction {//0x0D
        void execute(runtime::Frame* frame) override;
    };

    struct dconst_0 : public NoOperandsInstruction {//0x0E
        void execute(runtime::Frame* frame) override;
    };

    struct dconst_1 : public NoOperandsInstruction {//0x0F
        void execute(runtime::Frame* frame) override;
    };

    struct bipush : public Instruction {//0x10
        int8 val;

        void fetchOperands(InstructionReader &reader) override;
        void execute(runtime::Frame* frame) override;
        std::string verbose() override;
    };

    struct sipush : public Instruction {//0x11
        int16 val;

        void fetchOperands(InstructionReader &reader) override;
        void execute(runtime::Frame* frame) override;
    };

    struct ldc : public Index8Instruction {//0x12
        void execute(runtime::Frame* frame) override;
    };

    struct ldc_w : public Index16Instruction {//0x13
        void execute(runtime::Frame* frame) override;
    };

    struct ldc2_w : public Index16Instruction {//0x14
        void execute(runtime::Frame* frame) override;
    };

}


#endif //JVM_CONSTANTS_H
