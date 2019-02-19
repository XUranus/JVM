//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_STACK_H
#define JVM_STACK_H


//delclare
struct Frame;
#include "instruction.h"

struct pop: public NoOperandsInstruction {//0x57
    void excute(Frame* frame);
};

struct pop2: public NoOperandsInstruction {//0x58
    void excute(Frame* frame);
};

struct dup: public NoOperandsInstruction {//0x59
    void excute(Frame* frame);
};

struct dup_x1: public NoOperandsInstruction {//0x5A
    void excute(Frame* frame);
};

struct dup_x2: public NoOperandsInstruction {//0x5B
    void excute(Frame* frame);
};

struct dup2: public NoOperandsInstruction {//0x5C
    void excute(Frame* frame);
};

struct dup2_x1: public NoOperandsInstruction {//0x5D
    void excute(Frame* frame);
};

struct dup2_x2: public NoOperandsInstruction {//0x5E
    void excute(Frame* frame);
};

struct swap: public NoOperandsInstruction {//0x5F
    void excute(Frame* frame);
};




#endif //JVM_STACK_H
