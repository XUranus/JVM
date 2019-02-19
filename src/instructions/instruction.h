//
// Created by XUranus on 2019/2/1.
//

#ifndef JVM_INSTRUCTION_H
#define JVM_INSTRUCTION_H

#include <iostream>
#include <id3/sized_types.h>
#include "../classfile/basicType.h"
#include "../../src/runtime/Thread.h"

//#define DEBUG_MODE 1


struct BytesReader {
    int pc;
    byte * code;//byte code[]

    BytesReader();
    BytesReader(byte* _code);
    void reset(byte* _code,int _pc);
    uint8 readUint8();
    int8 readInt8();
    uint16 readUint16();
    int16 readInt16();
    int32 readInt32();

    int32* readInt32s(int jumpOffsetsCount);
    void skipPadding();
};


struct Instruction {
    u1 opCode;
    //static void interpretAndExcute(uint8 opCode,Frame* frame,BytesReader& reader);

    static Instruction* createInstruction(u1 _opCode);
    static std::string opCodeToName(u1 _opCode);
    std::string getInstructionName();
    virtual void fetchOperands(BytesReader &reader);
    virtual void excute(Frame* frame);
    virtual std::string toString();//used for debug
};

struct NoOperandsInstruction: public Instruction{
    void fetchOperands(BytesReader &reader);
    std::string toString();
};

struct BranchInstructions: public Instruction {
    int offset;

    void fetchOperands(BytesReader &reader);
    std::string toString();
};

struct Index8Instruction: public Instruction {
    unsigned int index;

    void fetchOperands(BytesReader &reader);
    std::string toString();
};

struct Index16Instruction:public Instruction {
    unsigned int index;

    void fetchOperands(BytesReader &reader);
    std::string toString();
};


#endif //JVM_INSTRUCTION_H





