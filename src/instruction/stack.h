//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_STACK_H
#define JVM_STACK_H

#include "instruction.h"

namespace instruction {

    struct pop : public NoOperandsInstruction {//0x57
        void execute(runtime::Frame* frame) override;
    };

    struct pop2 : public NoOperandsInstruction {//0x58
        void execute(runtime::Frame* frame) override;
    };

    struct dup : public NoOperandsInstruction {//0x59
        void execute(runtime::Frame* frame) override;
    };

    struct dup_x1 : public NoOperandsInstruction {//0x5A
        void execute(runtime::Frame* frame) override;
    };

    struct dup_x2 : public NoOperandsInstruction {//0x5B
        void execute(runtime::Frame* frame) override;
    };

    struct dup2 : public NoOperandsInstruction {//0x5C
        void execute(runtime::Frame* frame) override;
    };

    struct dup2_x1 : public NoOperandsInstruction {//0x5D
        void execute(runtime::Frame* frame) override;
    };

    struct dup2_x2 : public NoOperandsInstruction {//0x5E
        void execute(runtime::Frame* frame) override;
    };

    struct swap : public NoOperandsInstruction {//0x5F
        void execute(runtime::Frame* frame) override;
    };

}


#endif //JVM_STACK_H
