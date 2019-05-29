//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_EXTENDED_H
#define JVM_EXTENDED_H


//delclare
#include "instruction.h"



struct wide: public Instruction {//0xC4
    u1 newOpCode;
    uint16 index;
    int32 _const;//iinc 0x84

    void fetchOperands(BytesReader &reader);
    void excute(Frame* frame);
    std::string toString();//used for debug
};

struct multianewarray: public Instruction {//0xC5
    uint16 index;
    uint8 dimensions;

    void fetchOperands(BytesReader &reader);
    void excute(Frame* frame);
    std::string toString();
};

struct ifnull: public BranchInstructions {//0xC6
    void excute(Frame* frame);
};

struct ifnonnull: public BranchInstructions {//0xC7
    void excute(Frame* frame);
};

struct goto_w: public Instruction {//0xC8
    int offset;

    void fetchOperands(BytesReader &reader);
    void excute(Frame* frame);
    std::string toString();//used for debug
};

struct jsr_w: public Instruction {//0xC9
    int offset;

    void fetchOperands(BytesReader &reader);
    void excute(Frame* frame);
    std::string toString();//used for debug
};



#endif //JVM_EXTENDED_H
