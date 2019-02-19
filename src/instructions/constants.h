//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_CONSTANTS_H
#define JVM_CONSTANTS_H

//delclare
struct Frame;

#include "instruction.h"


struct nop: public NoOperandsInstruction {//0x00
    void excute(Frame* frame);
};

struct aconst_null: public NoOperandsInstruction {//0x01
    void excute(Frame* frame);
};

struct iconst_m1: public NoOperandsInstruction {//0x02
    void excute(Frame* frame);
};

struct iconst_0: public NoOperandsInstruction {//0x03
    void excute(Frame* frame);
};

struct iconst_1: public NoOperandsInstruction {//0x04
    void excute(Frame* frame);
};

struct iconst_2: public NoOperandsInstruction {//0x05
    void excute(Frame* frame);
};

struct iconst_3: public NoOperandsInstruction {//0x06
    void excute(Frame* frame);
};

struct iconst_4: public NoOperandsInstruction {//0x07
    void excute(Frame* frame);
};

struct iconst_5: public NoOperandsInstruction {//0x08
    void excute(Frame* frame);
};

struct lconst_0: public NoOperandsInstruction {//0x09
    void excute(Frame* frame);
};

struct lconst_1: public NoOperandsInstruction {//0x0A
    void excute(Frame* frame);
};

struct fconst_0: public NoOperandsInstruction {//0x0B
    void excute(Frame* frame);
};

struct fconst_1: public NoOperandsInstruction {//0x0C
    void excute(Frame* frame);
};

struct fconst_2: public NoOperandsInstruction {//0x0D
    void excute(Frame* frame);
};

struct dconst_0: public NoOperandsInstruction {//0x0E
    void excute(Frame* frame);
};

struct dconst_1: public NoOperandsInstruction {//0x0F
    void excute(Frame* frame);
};

struct bipush: public Instruction {//0x10
    int8 val;

    void fetchOperands(BytesReader &reader);
    std::string toString();
    void excute(Frame* frame);
};

struct sipush: public Instruction {//0x11
    int16 val;

    void fetchOperands(BytesReader &reader);
    std::string toString();
    void excute(Frame* frame);
};

struct ldc: public Index8Instruction {//0x12
    void excute(Frame* frame);
};

struct ldc_w: public Index16Instruction {//0x13
    void excute(Frame* frame);
};

struct ldc2_w: public Index16Instruction {//0x14
    void excute(Frame* frame);
};


#endif //JVM_CONSTANTS_H
