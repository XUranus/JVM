//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_CONTROL_H
#define JVM_CONTROL_H


#include "instruction.h"

namespace instruction {

    struct goto_ : public BranchInstructions {//0xA7
        void execute(runtime::Frame* frame) override;
    };

    struct jsr : public BranchInstructions {//0xA8
        void execute(runtime::Frame* frame) override;
    };

    struct ret : public BranchInstructions {//0xA9
        void execute(runtime::Frame* frame) override;
    };

    struct tableswitch : public Instruction {//0xAA
        int defaultOffset;
        int low;
        int high;
        std::vector<int> jumpOffsets;

        void fetchOperands(InstructionReader &reader) override;
        void execute(runtime::Frame* frame) override;
    };

    struct lookupswitch : public Instruction {//0xAB
        int defaultOffsets;
        int nPairs;
        std::vector<int> matchOffsets;

        void fetchOperands(InstructionReader &reader) override;
        void execute(runtime::Frame* frame) override;
    };

    struct ireturn : public NoOperandsInstruction {//0xAC
        void execute(runtime::Frame* frame) override;
    };

    struct lreturn : public NoOperandsInstruction {//0xAD
        void execute(runtime::Frame* frame) override;
    };

    struct freturn : public NoOperandsInstruction {//0xAE
        void execute(runtime::Frame* frame) override;
    };

    struct dreturn : public NoOperandsInstruction {//0xAF
        void execute(runtime::Frame* frame) override;
    };

    struct areturn : public NoOperandsInstruction {//0xB0
        void execute(runtime::Frame* frame) override;
    };

    struct return_ : public NoOperandsInstruction {//0xB1
        void execute(runtime::Frame* frame) override;
    };

}

#endif //JVM_CONTROL_H
