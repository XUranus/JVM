//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_COMPAIRISONS_H
#define JVM_COMPAIRISONS_H

//delclare
struct Frame;


#include "instruction.h"



struct lcmp: public NoOperandsInstruction {//0x94
    void excute(Frame* frame);
};

struct fcmpl: public NoOperandsInstruction {//0x95
    void excute(Frame* frame);
};

struct fcmpg: public NoOperandsInstruction {//0x96
    void excute(Frame* frame);
};

struct dcmpl: public NoOperandsInstruction {//0x97
    void excute(Frame* frame);
};

struct dcmpg: public NoOperandsInstruction {//0x98
    void excute(Frame* frame);
};

struct ifeq: public BranchInstructions {//0x99
    void excute(Frame* frame);
};

struct ifne: public BranchInstructions {//0x9A
    void excute(Frame* frame);
};

struct iflt: public BranchInstructions {//0x9B
    void excute(Frame* frame);
};

struct ifge: public BranchInstructions {//0x9C
    void excute(Frame* frame);
};

struct ifgt: public BranchInstructions {//0x9D
    void excute(Frame* frame);
};

struct ifle: public BranchInstructions {//0x9E
    void excute(Frame* frame);
};

struct if_icmpeq: public BranchInstructions {//0x9F
    void excute(Frame* frame);
};

struct if_icmpne: public BranchInstructions {//0xA0
    void excute(Frame* frame);
};

struct if_icmplt: public BranchInstructions {//0xA1
    void excute(Frame* frame);
};

struct if_icmpge: public BranchInstructions {//0xA2
    void excute(Frame* frame);
};

struct if_icmpgt: public BranchInstructions {//0xA3
    void excute(Frame* frame);
};

struct if_icmple: public BranchInstructions {//0xA4
    void excute(Frame* frame);
};

struct if_acmpeq: public BranchInstructions {//0xA5
    void excute(Frame* frame);
};

struct if_acmpne: public BranchInstructions {//0xA6
    void excute(Frame* frame);
};


#endif //JVM_COMPAIRISONS_H
