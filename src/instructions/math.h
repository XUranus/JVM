//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_MATH_H
#define JVM_MATH_H


//delclare
struct Frame;
#include "instruction.h"



struct iadd: public NoOperandsInstruction {//0x60
    void excute(Frame* frame);
};

struct ladd: public NoOperandsInstruction {//0x61
    void excute(Frame* frame);
};

struct fadd: public NoOperandsInstruction {//0x62
    void excute(Frame* frame);
};

struct dadd: public NoOperandsInstruction {//0x63
    void excute(Frame* frame);
};

struct isub: public NoOperandsInstruction {//0x64
    void excute(Frame* frame);
};

struct lsub: public NoOperandsInstruction {//0x65
    void excute(Frame* frame);
};

struct fsub: public NoOperandsInstruction {//0x66
    void excute(Frame* frame);
};

struct dsub: public NoOperandsInstruction {//0x67
    void excute(Frame* frame);
};

struct imul: public NoOperandsInstruction {//0x68
    void excute(Frame* frame);
};

struct lmul: public NoOperandsInstruction {//0x69
    void excute(Frame* frame);
};

struct fmul: public NoOperandsInstruction {//0x6A
    void excute(Frame* frame);
};

struct dmul: public NoOperandsInstruction {//0x6B
    void excute(Frame* frame);
};

struct idiv: public NoOperandsInstruction {//0x6C
    void excute(Frame* frame);
};

struct ldiv_: public NoOperandsInstruction {//0x6D
    void excute(Frame* frame);
};

struct fdiv: public NoOperandsInstruction {//0x6E
    void excute(Frame* frame);
};

struct ddiv: public NoOperandsInstruction {//0x6F
    void excute(Frame* frame);
};

struct irem: public NoOperandsInstruction {//0x70
    void excute(Frame* frame);
};

struct lrem: public NoOperandsInstruction {//0x71
    void excute(Frame* frame);
};

struct frem: public NoOperandsInstruction {//0x72
    void excute(Frame* frame);
};

struct drem: public NoOperandsInstruction {//0x73
    void excute(Frame* frame);
};

struct ineg: public NoOperandsInstruction {//0x74
    void excute(Frame* frame);
};

struct lneg: public NoOperandsInstruction {//0x75
    void excute(Frame* frame);
};

struct fneg: public NoOperandsInstruction {//0x76
    void excute(Frame* frame);
};

struct dneg: public NoOperandsInstruction {//0x77
    void excute(Frame* frame);
};

struct ishl: public NoOperandsInstruction {//0x78
    void excute(Frame* frame);
};

struct lshl: public NoOperandsInstruction {//0x79
    void excute(Frame* frame);
};

struct ishr: public NoOperandsInstruction {//0x7A
    void excute(Frame* frame);
};

struct lshr: public NoOperandsInstruction {//0x7B
    void excute(Frame* frame);
};

struct iushr: public NoOperandsInstruction {//0x7C
    void excute(Frame* frame);
};

struct lushr: public NoOperandsInstruction {//0x7D
    void excute(Frame* frame);
};

struct iand: public NoOperandsInstruction {//0x7E
    void excute(Frame* frame);
};

struct land: public NoOperandsInstruction {//0x7F
    void excute(Frame* frame);
};

struct ior: public NoOperandsInstruction {//0x80
    void excute(Frame* frame);
};

struct lor: public NoOperandsInstruction {//0x81
    void excute(Frame* frame);
};

struct ixor: public NoOperandsInstruction {//0x82
    void excute(Frame* frame);
};

struct lxor: public NoOperandsInstruction {//0x83
    void excute(Frame* frame);
};

struct iinc: public Instruction {//0x84
    unsigned int index;
    int32 _const;

    void excute(Frame* frame);
    std::string toString();
    void fetchOperands(BytesReader &reader);
};


#endif //JVM_MATH_H
