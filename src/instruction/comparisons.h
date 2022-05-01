//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_COMPAIRISONS_H
#define JVM_COMPAIRISONS_H


#include "instruction.h"

namespace instruction {

    struct lcmp : public NoOperandsInstruction {//0x94
        void execute(runtime::Frame* frame) override;
    };

    struct fcmpl : public NoOperandsInstruction {//0x95
        void execute(runtime::Frame* frame) override;
    };

    struct fcmpg : public NoOperandsInstruction {//0x96
        void execute(runtime::Frame* frame) override;
    };

    struct dcmpl : public NoOperandsInstruction {//0x97
        void execute(runtime::Frame* frame) override;
    };

    struct dcmpg : public NoOperandsInstruction {//0x98
        void execute(runtime::Frame* frame) override;
    };

    struct ifeq : public BranchInstructions {//0x99
        void execute(runtime::Frame* frame) override;
    };

    struct ifne : public BranchInstructions {//0x9A
        void execute(runtime::Frame* frame) override;
    };

    struct iflt : public BranchInstructions {//0x9B
        void execute(runtime::Frame* frame) override;
    };

    struct ifge : public BranchInstructions {//0x9C
        void execute(runtime::Frame* frame) override;
    };

    struct ifgt : public BranchInstructions {//0x9D
        void execute(runtime::Frame* frame) override;
    };

    struct ifle : public BranchInstructions {//0x9E
        void execute(runtime::Frame* frame) override;
    };

    struct if_icmpeq : public BranchInstructions {//0x9F
        void execute(runtime::Frame* frame) override;
    };

    struct if_icmpne : public BranchInstructions {//0xA0
        void execute(runtime::Frame* frame) override;
    };

    struct if_icmplt : public BranchInstructions {//0xA1
        void execute(runtime::Frame* frame) override;
    };

    struct if_icmpge : public BranchInstructions {//0xA2
        void execute(runtime::Frame* frame) override;
    };

    struct if_icmpgt : public BranchInstructions {//0xA3
        void execute(runtime::Frame* frame) override;
    };

    struct if_icmple : public BranchInstructions {//0xA4
        void execute(runtime::Frame* frame) override;
    };

    struct if_acmpeq : public BranchInstructions {//0xA5
        void execute(runtime::Frame* frame) override;
    };

    struct if_acmpne : public BranchInstructions {//0xA6
        void execute(runtime::Frame* frame) override;
    };
}


#endif //JVM_COMPAIRISONS_H
