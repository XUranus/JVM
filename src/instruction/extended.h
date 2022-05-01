//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_EXTENDED_H
#define JVM_EXTENDED_H

#include "instruction.h"

namespace instruction {


    struct wide: public Instruction {//0xC4
        u1 extendOpCode;
        u2 wideIndex; // extend index from u1 to u2
        int _const;//iinc 0x84

        void fetchOperands(InstructionReader &reader) override;
        void execute(runtime::Frame* frame) override;
    };

    struct multianewarray: public Instruction {//0xC5
        u2 index;
        u1 nDimension;

        void fetchOperands(InstructionReader &reader) override;
        void execute(runtime::Frame* frame) override;
    };

    struct ifnull: public BranchInstructions {//0xC6
        void execute(runtime::Frame* frame) override;
    };

    struct ifnonnull: public BranchInstructions {//0xC7
        void execute(runtime::Frame* frame) override;
    };

    struct goto_w: public Instruction {//0xC8
        int offset;

        void fetchOperands(InstructionReader &reader) override;
        void execute(runtime::Frame* frame) override;
    };

    struct jsr_w: public Instruction {//0xC9
        int offset;

        void fetchOperands(InstructionReader &reader) override;
        void execute(runtime::Frame* frame) override;
    };


}
#endif //JVM_EXTENDED_H
