#pragma once

#include <memory>
#include <string>
#include "InstructionReader.h"
#include "../basicType.h"
#include "../runtime/thread/Frame.h"

namespace instruction {

    class Instruction {
    public:
        u1 opCode{};

        virtual void fetchOperands(InstructionReader &reader) = 0;
        virtual void execute(runtime::Frame* frame) = 0;
        [[nodiscard]] virtual std::string verbose() const;
        virtual ~Instruction() = default;

        [[nodiscard]] std::string name() const;
    };

    class NoOperandsInstruction : public Instruction {
        void fetchOperands(InstructionReader &reader) override;
        [[nodiscard]] std::string verbose() const override;
    };

    class BranchInstructions : public Instruction {
    protected:
        int offset{};
    public:
        void fetchOperands(InstructionReader &reader) override;
        [[nodiscard]] std::string verbose() const override;
    };

    class Index8Instruction : public Instruction {
    protected:
        u1 index{};
    public:
        void fetchOperands(InstructionReader &reader) override;
        [[nodiscard]] std::string verbose() const override;
    };

    class Index16Instruction : public Instruction {
    protected:
        u2 index{};
    public:
        void fetchOperands(InstructionReader &reader) override;
        [[nodiscard]] std::string verbose() const override;
    };

    std::unique_ptr<Instruction> create(u1 _opCode);

}
