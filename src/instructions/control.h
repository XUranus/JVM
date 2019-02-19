//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_CONTROL_H
#define JVM_CONTROL_H


//delclare
struct Frame;
#include "instruction.h"



struct goto_: public BranchInstructions {//0xA7
    void excute(Frame* frame);
};

struct jsr: public BranchInstructions {//0xA8
    void excute(Frame* frame);
};

struct ret: public BranchInstructions {//0xA9
    void excute(Frame* frame);
};

struct tableswitch: public Instruction {//0xAA
    int32 defaultOffset;
    int32 low;
    int32 high;
    int32* jumpOffsets;

    void fetchOperands(BytesReader &reader);
    std::string toString();
    void excute(Frame* frame);
};

struct lookupswitch: public Instruction {//0xAB
    int32 defaultOffsets;
    int32 npairs;
    int32* mathchOffsets;

    void fetchOperands(BytesReader &reader);
    std::string toString();
    void excute(Frame* frame);
};

struct ireturn: public NoOperandsInstruction {//0xAC
    void excute(Frame* frame);
};

struct lreturn: public NoOperandsInstruction {//0xAD
    void excute(Frame* frame);
};

struct freturn: public NoOperandsInstruction {//0xAE
    void excute(Frame* frame);
};

struct dreturn: public NoOperandsInstruction {//0xAF
    void excute(Frame* frame);
};

struct areturn: public NoOperandsInstruction {//0xB0
    void excute(Frame* frame);
};

struct return_: public NoOperandsInstruction {//0xB1
    void excute(Frame* frame);
};


#endif //JVM_CONTROL_H
