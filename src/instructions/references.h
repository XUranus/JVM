//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_REFERENCES_H
#define JVM_REFERENCES_H


//delclare
struct Frame;
#include "instruction.h"

struct InvokeMethodLogic { //assist static method for 4 "invoke" instruction
    static void invokeMethod(Frame* frame,Method* method);
    static void _println(Frame* frame,std::string descriptor);//todo::hack!
    static void _print(Frame* frame,std::string descriptor);//todo::hack!
};





struct getstatic: public Index16Instruction {//0xB2
    void excute(Frame* frame);
};

struct putstatic: public Index16Instruction {//0xB3
    void excute(Frame* frame);
};

struct getfield: public Index16Instruction {//0xB4
    void excute(Frame* frame);
};

struct putfield: public Index16Instruction {//0xB5
    void excute(Frame* frame);
};

struct invokevirtual: public Index16Instruction {//0xB6
    void excute(Frame* frame);
};

struct invokespecial: public Index16Instruction {//0xB7
    void excute(Frame* frame);
};

struct invokestatic: public Index16Instruction {//0xB8
    void excute(Frame* frame);
};

struct invokeinterface: public Instruction {//0xB9
    uint16 index;
    uint8 slotsCount;
    uint8 zero;//must be 0

    void fetchOperands(BytesReader &reader);
    std::string toString();
    void excute(Frame* frame);
};

struct new_: public Index16Instruction {//0xBB
    void excute(Frame* frame);
};

struct newarray: public Instruction {//0xBC
    u1 atype;

    void fetchOperands(BytesReader &reader);
    std::string toString();
    void excute(Frame* frame);
};

struct anewarray: public Index16Instruction {//0xBD
    void excute(Frame* frame);
};

struct arraylength: public NoOperandsInstruction {//0xBE
    void excute(Frame* frame);
};

struct athrow: public NoOperandsInstruction {//0xBF
    void excute(Frame* frame);
};

struct checkcast: public Index16Instruction {//0xC0
    void excute(Frame* frame);
};

struct instanceof: public Index16Instruction {//0xC1
    void excute(Frame* frame);
};

struct monitorenter: public NoOperandsInstruction {//0xC2
    void excute(Frame* frame);
};

struct monitiorexit: public NoOperandsInstruction {//0xC3
    void excute(Frame* frame);
};


#endif //JVM_REFERENCES_H
