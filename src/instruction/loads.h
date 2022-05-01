//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_LOADS_H
#define JVM_LOADS_H

#include "instruction.h"

namespace instruction {

    struct iload : public Index8Instruction {//0x15
        void execute(runtime::Frame* frame) override;
    };

    struct lload : public Index8Instruction {//0x16
        void execute(runtime::Frame* frame) override;
    };

    struct fload : public Index8Instruction {//0x17
        void execute(runtime::Frame* frame) override;
    };

    struct dload : public Index8Instruction {//0x18
        void execute(runtime::Frame* frame) override;
    };

    struct aload : public Index8Instruction {//0x19
        void execute(runtime::Frame* frame) override;
    };

    struct iload_0 : public NoOperandsInstruction {//0x1A
        void execute(runtime::Frame* frame) override;
    };

    struct iload_1 : public NoOperandsInstruction {//0x1B
        void execute(runtime::Frame* frame) override;
    };

    struct iload_2 : public NoOperandsInstruction {//0x1C
        void execute(runtime::Frame* frame) override;
    };

    struct iload_3 : public NoOperandsInstruction {//0x1D
        void execute(runtime::Frame* frame) override;
    };

    struct lload_0 : public NoOperandsInstruction {//0x1E
        void execute(runtime::Frame* frame) override;
    };

    struct lload_1 : public NoOperandsInstruction {//0x1F
        void execute(runtime::Frame* frame) override;
    };

    struct lload_2 : public NoOperandsInstruction {//0x20
        void execute(runtime::Frame* frame) override;
    };

    struct lload_3 : public NoOperandsInstruction {//0x21
        void execute(runtime::Frame* frame) override;
    };

    struct fload_0 : public NoOperandsInstruction {//0x22
        void execute(runtime::Frame* frame) override;
    };

    struct fload_1 : public NoOperandsInstruction {//0x23
        void execute(runtime::Frame* frame) override;
    };

    struct fload_2 : public NoOperandsInstruction {//0x24
        void execute(runtime::Frame* frame) override;
    };

    struct fload_3 : public NoOperandsInstruction {//0x25
        void execute(runtime::Frame* frame) override;
    };

    struct dload_0 : public NoOperandsInstruction {//0x26
        void execute(runtime::Frame* frame) override;
    };

    struct dload_1 : public NoOperandsInstruction {//0x27
        void execute(runtime::Frame* frame) override;
    };

    struct dload_2 : public NoOperandsInstruction {//0x28
        void execute(runtime::Frame* frame) override;
    };

    struct dload_3 : public NoOperandsInstruction {//0x29
        void execute(runtime::Frame* frame) override;
    };

    struct aload_0 : public NoOperandsInstruction {//0x2A
        void execute(runtime::Frame* frame) override;
    };

    struct aload_1 : public NoOperandsInstruction {//0x2B
        void execute(runtime::Frame* frame) override;
    };

    struct aload_2 : public NoOperandsInstruction {//0x2C
        void execute(runtime::Frame* frame) override;
    };

    struct aload_3 : public NoOperandsInstruction {//0x2D
        void execute(runtime::Frame* frame) override;
    };

    struct iaload : public NoOperandsInstruction {//0x2E
        void execute(runtime::Frame* frame) override;
    };

    struct laload : public NoOperandsInstruction {//0x2F
        void execute(runtime::Frame* frame) override;
    };

    struct faload : public NoOperandsInstruction {//0x30
        void execute(runtime::Frame* frame) override;
    };

    struct daload : public NoOperandsInstruction {//0x31
        void execute(runtime::Frame* frame) override;
    };

    struct aaload : public NoOperandsInstruction {//0x32
        void execute(runtime::Frame* frame) override;
    };

    struct baload : public NoOperandsInstruction {//0x33
        void execute(runtime::Frame* frame) override;
    };

    struct caload : public NoOperandsInstruction {//0x34
        void execute(runtime::Frame* frame) override;
    };

    struct saload : public NoOperandsInstruction {//0x35
        void execute(runtime::Frame* frame) override;
    };

}

#endif //JVM_LOADS_H
