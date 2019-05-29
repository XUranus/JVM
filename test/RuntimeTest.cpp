//
// Created by xuranus on 4/25/19.
//
#ifndef JVM_TEST5_H
#define JVM_TEST5_H


#include "../src/classfile/ClassReader.h"
#include "../src/runtime/Frame.h"
#include "../src/runtime/Thread.h"
#include "../src/instructions/instruction.h"


struct RuntimeTest {
    //Test Sum.class instruction Excution
    static void excute()
    {
        ClassReader reader("/home/xuranus/CLionProjects/JVM/test/classFileTest/Sum.class");
        auto classFile = reader.parseClassFile();
        auto mainMethod = classFile->getMainMethod();
        if(mainMethod!= nullptr)
        {
            interpretMethod(mainMethod);
        } else {
            printf("no main method found.");
            exit(1);
        }
    }

    static void interpretMethod(MethodInfo* method)
    {
        auto codeAttr = method->getCodeAttribute();
        if(codeAttr == nullptr)
        {
            printf("no Code_Attribute in methodInfo");
            exit(1);
        }

        auto maxLocals = codeAttr->maxLocals;
        auto maxStacks = codeAttr->maxStacks;
        auto byteCode = codeAttr->codes;

        Thread thread(1024);
        Frame frame(&thread,maxLocals,maxStacks);
        thread.pushFrame(&frame);

        BytesReader reader(codeAttr->codes,codeAttr->codeLength);

        int i = 0;
        while (true)
        {
            int pc = frame.nextPc;
            thread.pc = pc;

            reader.reset(codeAttr->codes,pc,codeAttr->codeLength);
            auto opCode = reader.readUint8();

            printf("[%d]:  ",i++);
            auto inst = Instruction::createInstruction(opCode);
            inst->fetchOperands(reader);

            frame.nextPc = reader.pc;
            inst->excute(&frame);
        }
    }
};

#endif
