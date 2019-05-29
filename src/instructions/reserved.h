//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_RESERVED_H
#define JVM_RESERVED_H



//delclare
struct Frame;
#include "instruction.h"


struct breakpoint: public NoOperandsInstruction {//0xCA
    void excute(Frame* frame);
};

//invokenative
struct impdep1: public NoOperandsInstruction {//0xFE
    void excute(Frame* frame);
};

struct impdep2: public NoOperandsInstruction {//0xFF
    void excute(Frame* frame);
};


#endif //JVM_RESERVED_H
