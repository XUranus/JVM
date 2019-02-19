//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_CONVERSIONS_H
#define JVM_CONVERSIONS_H


//delclare
struct Frame;
#include "instruction.h"



struct i2l: public NoOperandsInstruction {//0x85
    void excute(Frame* frame);
};

struct i2f: public NoOperandsInstruction {//0x86
    void excute(Frame* frame);
};

struct i2d: public NoOperandsInstruction {//0x87
    void excute(Frame* frame);
};

struct l2i: public NoOperandsInstruction {//0x88
    void excute(Frame* frame);
};

struct l2f: public NoOperandsInstruction {//0x89
    void excute(Frame* frame);
};

struct l2d: public NoOperandsInstruction {//0x8A
    void excute(Frame* frame);
};

struct f2i: public NoOperandsInstruction {//0x8B
    void excute(Frame* frame);
};

struct f2l: public NoOperandsInstruction {//0x8C
    void excute(Frame* frame);
};

struct f2d: public NoOperandsInstruction {//0x8D
    void excute(Frame* frame);
};

struct d2i: public NoOperandsInstruction {//0x8E
    void excute(Frame* frame);
};

struct d2l: public NoOperandsInstruction {//0x8F
    void excute(Frame* frame);
};

struct d2f: public NoOperandsInstruction {//0x90
    void excute(Frame* frame);
};

struct i2b: public NoOperandsInstruction {//0x91
    void excute(Frame* frame);
};

struct i2c: public NoOperandsInstruction {//0x92
    void excute(Frame* frame);
};

struct i2s: public NoOperandsInstruction {//0x93
    void excute(Frame* frame);
};

#endif //JVM_CONVERSIONS_H
