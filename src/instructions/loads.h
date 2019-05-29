//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_LOADS_H
#define JVM_LOADS_H


//delclare
struct Frame;
#include "instruction.h"



struct iload: public Index8Instruction {//0x15
    void excute(Frame* frame);
};

struct lload: public Index8Instruction {//0x16
    void excute(Frame* frame);
};

struct fload: public Index8Instruction {//0x17
    void excute(Frame* frame);
};

struct dload: public Index8Instruction {//0x18
    void excute(Frame* frame);
};

struct aload: public Index8Instruction {//0x19
    void excute(Frame* frame);
};

struct iload_0: public NoOperandsInstruction {//0x1A
    void excute(Frame* frame);
};

struct iload_1: public NoOperandsInstruction {//0x1B
    void excute(Frame* frame);
};

struct iload_2: public NoOperandsInstruction {//0x1C
    void excute(Frame* frame);
};

struct iload_3: public NoOperandsInstruction {//0x1D
    void excute(Frame* frame);
};

struct lload_0: public NoOperandsInstruction {//0x1E
    void excute(Frame* frame);
};

struct lload_1: public NoOperandsInstruction {//0x1F
    void excute(Frame* frame);
};

struct lload_2: public NoOperandsInstruction {//0x20
    void excute(Frame* frame);
};

struct lload_3: public NoOperandsInstruction {//0x21
    void excute(Frame* frame);
};

struct fload_0: public NoOperandsInstruction {//0x22
    void excute(Frame* frame);
};

struct fload_1: public NoOperandsInstruction {//0x23
    void excute(Frame* frame);
};

struct fload_2: public NoOperandsInstruction {//0x24
    void excute(Frame* frame);
};

struct fload_3: public NoOperandsInstruction {//0x25
    void excute(Frame* frame);
};

struct dload_0: public NoOperandsInstruction {//0x26
    void excute(Frame* frame);
};

struct dload_1: public NoOperandsInstruction {//0x27
    void excute(Frame* frame);
};

struct dload_2: public NoOperandsInstruction {//0x28
    void excute(Frame* frame);
};

struct dload_3: public NoOperandsInstruction {//0x29
    void excute(Frame* frame);
};

struct aload_0: public NoOperandsInstruction {//0x2A
    void excute(Frame* frame);
};

struct aload_1: public NoOperandsInstruction {//0x2B
    void excute(Frame* frame);
};

struct aload_2: public NoOperandsInstruction {//0x2C
    void excute(Frame* frame);
};

struct aload_3: public NoOperandsInstruction {//0x2D
    void excute(Frame* frame);
};

struct iaload: public NoOperandsInstruction {//0x2E
    void excute(Frame* frame);
};

struct laload: public NoOperandsInstruction {//0x2F
    void excute(Frame* frame);
};

struct faload: public NoOperandsInstruction {//0x30
    void excute(Frame* frame);
};

struct daload: public NoOperandsInstruction {//0x31
    void excute(Frame* frame);
};

struct aaload: public NoOperandsInstruction {//0x32
    void excute(Frame* frame);
};

struct baload: public NoOperandsInstruction {//0x33
    void excute(Frame* frame);
};

struct caload: public NoOperandsInstruction {//0x34
    void excute(Frame* frame);
};

struct saload: public NoOperandsInstruction {//0x35
    void excute(Frame* frame);
};


#endif //JVM_LOADS_H
