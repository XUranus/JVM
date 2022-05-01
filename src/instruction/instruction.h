//
// Created by XUranus on 2019/2/1.
//

#ifndef JVM_INSTRUCTION_H
#define JVM_INSTRUCTION_H

#include <iostream>
#include "InstructionReader.h"
#include "../../src/basicType.h"
//#include "../runtime/thread/Thread.h"
#include "../runtime/thread/Frame.h"

namespace instruction {


    /**
     *                                            Instruction
     *                                                |
     *                       -----------------------------------------------------
     *                      |                 |                 |                |
     *      NoOperandsInstruction   BranchInstructions   Index8Instruction  Index16Instruction
     *              {}                  {u2 offset}         {u1 index}        {u1 index}
     */
    class Instruction {
    public:
        u1 opCode{};

    public:
        virtual void fetchOperands(InstructionReader &reader) = 0;
        virtual void execute(runtime::Frame* frame) = 0;
        virtual std::string verbose(); // return name and operands
        virtual ~Instruction() = default;

        [[nodiscard]] std::string name() const;
    };

    class NoOperandsInstruction : public Instruction {
        void fetchOperands(InstructionReader &reader) override;
        std::string verbose() override;
    };

    class BranchInstructions : public Instruction {
    protected:
        int offset{};
    public:
        void fetchOperands(InstructionReader &reader) override;
        std::string verbose() override;
    };

    class Index8Instruction : public Instruction {
    protected:
        u1 index{};
    public:
        void fetchOperands(InstructionReader &reader) override;
        std::string verbose() override;
    };

    class Index16Instruction : public Instruction {
    protected:
        u2 index{};
    public:
        void fetchOperands(InstructionReader &reader) override;
        std::string verbose() override;
    };

    Instruction* create(u1 _opCode);

}

#endif //JVM_INSTRUCTION_H





