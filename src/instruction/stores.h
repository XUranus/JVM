//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_STORES_H
#define JVM_STORES_H

#include "instruction.h"


namespace instruction {

    struct istore : public Index8Instruction {//0x36
        void execute(runtime::Frame* frame) override;
    };

    struct lstore : public Index8Instruction {//0x37
        void execute(runtime::Frame* frame) override;
    };

    struct fstore : public Index8Instruction {//0x38
        void execute(runtime::Frame* frame) override;
    };

    struct dstore : public Index8Instruction {//0x39
        void execute(runtime::Frame* frame) override;
    };

    struct astore : public Index8Instruction {//0x3A
        void execute(runtime::Frame* frame) override;
    };

    struct istore_0 : public NoOperandsInstruction {//0x3B
        void execute(runtime::Frame* frame) override;
    };

    struct istore_1 : public NoOperandsInstruction {//0x3C
        void execute(runtime::Frame* frame) override;
    };

    struct istore_2 : public NoOperandsInstruction {//0x3D
        void execute(runtime::Frame* frame) override;
    };

    struct istore_3 : public NoOperandsInstruction {//0x3E
        void execute(runtime::Frame* frame) override;
    };

    struct lstore_0 : public NoOperandsInstruction {//0x3F
        void execute(runtime::Frame* frame) override;
    };

    struct lstore_1 : public NoOperandsInstruction {//0x40
        void execute(runtime::Frame* frame) override;
    };

    struct lstore_2 : public NoOperandsInstruction {//0x41
        void execute(runtime::Frame* frame) override;
    };

    struct lstore_3 : public NoOperandsInstruction {//0x42
        void execute(runtime::Frame* frame) override;
    };

    struct fstore_0 : public NoOperandsInstruction {//0x43
        void execute(runtime::Frame* frame) override;
    };

    struct fstore_1 : public NoOperandsInstruction {//0x44
        void execute(runtime::Frame* frame) override;
    };

    struct fstore_2 : public NoOperandsInstruction {//0x45
        void execute(runtime::Frame* frame) override;
    };

    struct fstore_3 : public NoOperandsInstruction {//0x46
        void execute(runtime::Frame* frame) override;
    };

    struct dstore_0 : public NoOperandsInstruction {//0x47
        void execute(runtime::Frame* frame) override;
    };

    struct dstore_1 : public NoOperandsInstruction {//0x48
        void execute(runtime::Frame* frame) override;
    };

    struct dstore_2 : public NoOperandsInstruction {//0x49
        void execute(runtime::Frame* frame) override;
    };

    struct dstore_3 : public NoOperandsInstruction {//0x4A
        void execute(runtime::Frame* frame) override;
    };

    struct astore_0 : public NoOperandsInstruction {//0x4B
        void execute(runtime::Frame* frame) override;
    };

    struct astore_1 : public NoOperandsInstruction {//0x4C
        void execute(runtime::Frame* frame) override;
    };

    struct astore_2 : public NoOperandsInstruction {//0x4D
        void execute(runtime::Frame* frame) override;
    };

    struct astore_3 : public NoOperandsInstruction {//0x4E
        void execute(runtime::Frame* frame) override;
    };

    struct iastore : public NoOperandsInstruction {//0x4F
        void execute(runtime::Frame* frame) override;
    };

    struct lastore : public NoOperandsInstruction {//0x50
        void execute(runtime::Frame* frame) override;
    };

    struct fastore : public NoOperandsInstruction {//0x51
        void execute(runtime::Frame* frame) override;
    };

    struct dastore : public NoOperandsInstruction {//0x52
        void execute(runtime::Frame* frame) override;
    };

    struct aastore : public NoOperandsInstruction {//0x53
        void execute(runtime::Frame* frame) override;
    };

    struct bastore : public NoOperandsInstruction {//0x54
        void execute(runtime::Frame* frame) override;
    };

    struct castore : public NoOperandsInstruction {//0x55
        void execute(runtime::Frame* frame) override;
    };

    struct sastore : public NoOperandsInstruction {//0x56
        void execute(runtime::Frame* frame) override;
    };

}


#endif //JVM_STORES_H
