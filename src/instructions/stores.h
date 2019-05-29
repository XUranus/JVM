//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_STORES_H
#define JVM_STORES_H


//delclare
struct Frame;
#include "instruction.h"


struct istore: public Index8Instruction {//0x36
    void excute(Frame* frame);
};

struct lstore: public Index8Instruction {//0x37
    void excute(Frame* frame);
};

struct fstore: public Index8Instruction {//0x38
    void excute(Frame* frame);
};

struct dstore: public Index8Instruction {//0x39
    void excute(Frame* frame);
};

struct astore: public Index8Instruction {//0x3A
    void excute(Frame* frame);
};

struct istore_0: public NoOperandsInstruction {//0x3B
    void excute(Frame* frame);
};

struct istore_1: public NoOperandsInstruction {//0x3C
    void excute(Frame* frame);
};

struct istore_2: public NoOperandsInstruction {//0x3D
    void excute(Frame* frame);
};

struct istore_3: public NoOperandsInstruction {//0x3E
    void excute(Frame* frame);
};

struct lstore_0: public NoOperandsInstruction {//0x3F
    void excute(Frame* frame);
};

struct lstore_1: public NoOperandsInstruction {//0x40
    void excute(Frame* frame);
};

struct lstore_2: public NoOperandsInstruction {//0x41
    void excute(Frame* frame);
};

struct lstore_3: public NoOperandsInstruction {//0x42
    void excute(Frame* frame);
};

struct fstore_0: public NoOperandsInstruction {//0x43
    void excute(Frame* frame);
};

struct fstore_1: public NoOperandsInstruction {//0x44
    void excute(Frame* frame);
};

struct fstore_2: public NoOperandsInstruction {//0x45
    void excute(Frame* frame);
};

struct fstore_3: public NoOperandsInstruction {//0x46
    void excute(Frame* frame);
};

struct dstore_0: public NoOperandsInstruction {//0x47
    void excute(Frame* frame);
};

struct dstore_1: public NoOperandsInstruction {//0x48
    void excute(Frame* frame);
};

struct dstore_2: public NoOperandsInstruction {//0x49
    void excute(Frame* frame);
};

struct dstore_3: public NoOperandsInstruction {//0x4A
    void excute(Frame* frame);
};

struct astore_0: public NoOperandsInstruction {//0x4B
    void excute(Frame* frame);
};

struct astore_1: public NoOperandsInstruction {//0x4C
    void excute(Frame* frame);
};

struct astore_2: public NoOperandsInstruction {//0x4D
    void excute(Frame* frame);
};

struct astore_3: public NoOperandsInstruction {//0x4E
    void excute(Frame* frame);
};

struct iastore: public NoOperandsInstruction {//0x4F
    void excute(Frame* frame);
};

struct lastore: public NoOperandsInstruction {//0x50
    void excute(Frame* frame);
};

struct fastore: public NoOperandsInstruction {//0x51
    void excute(Frame* frame);
};

struct dastore: public NoOperandsInstruction {//0x52
    void excute(Frame* frame);
};

struct aastore: public NoOperandsInstruction {//0x53
    void excute(Frame* frame);
};

struct bastore: public NoOperandsInstruction {//0x54
    void excute(Frame* frame);
};

struct castore: public NoOperandsInstruction {//0x55
    void excute(Frame* frame);
};

struct sastore: public NoOperandsInstruction {//0x56
    void excute(Frame* frame);
};



#endif //JVM_STORES_H
