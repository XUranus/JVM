//
// Created by xuranus on 4/25/19.
//
#ifndef JVM_TEST5_H
#define JVM_TEST5_H


#include "../src/runtime/thread/Frame.h"
#include "../src/runtime/thread/Thread.h"
#include "../src/classfile/ClassFile.h"
#include "../src/instruction/InstructionReader.h"
#include "../src/instruction/instruction.h"
#include <cassert>

using namespace std;

struct InstructionTest {

    static void execute() {
        classfile::BytesReader reader("/home/xuranus/CLionProjects/xjava/demos/Sum.class");
        classfile::ClassFile klassFile(reader);

        const auto &mainMethod = klassFile.mainMethod();
        if (mainMethod) {
            auto codeAttribute = mainMethod->codeAttribute();

            std::unique_ptr<runtime::Thread> thread = std::make_unique<runtime::Thread>(1024, "main");
            runtime::Frame _frame(codeAttribute->maxLocals,
                                 codeAttribute->maxStacks,
                                 thread.get(), nullptr);
            assert(thread.get() != nullptr);
            thread->stack->push(_frame);

            // loop
            runtime::Frame frame = thread->stack->pop();
            instruction::InstructionReader codeReader;

            while (frame.localVars[1].num != 5050) {
                int pc = frame.nextPC;
                thread->pc = pc;
                codeReader.reset(codeAttribute->codes, pc, codeAttribute->codeLength);
                u1 opCode = codeReader.readUint8();
                std::unique_ptr<instruction::Instruction> inst(instruction::create(opCode));
                inst->fetchOperands(codeReader);
                cout << inst->verbose() << endl;
                frame.nextPC = codeReader.PC();
                inst->execute(&frame);

                frame.localVars.dump();
                frame.operandStack.dump();
                cout << "==========================" << endl;
            }

        } else {
            std::cout << "no main method found." << std::endl;
            exit(1);
        }
    }

};

#endif
