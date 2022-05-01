//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_CONVERSIONS_H
#define JVM_CONVERSIONS_H



#include "instruction.h"

namespace instruction {


//declare
    struct Frame;

    struct i2l : public NoOperandsInstruction {//0x85
        void execute(runtime::Frame* frame) override;
    };

    struct i2f : public NoOperandsInstruction {//0x86
        void execute(runtime::Frame* frame) override;
    };

    struct i2d : public NoOperandsInstruction {//0x87
        void execute(runtime::Frame* frame) override;
    };

    struct l2i : public NoOperandsInstruction {//0x88
        void execute(runtime::Frame* frame) override;
    };

    struct l2f : public NoOperandsInstruction {//0x89
        void execute(runtime::Frame* frame) override;
    };

    struct l2d : public NoOperandsInstruction {//0x8A
        void execute(runtime::Frame* frame) override;
    };

    struct f2i : public NoOperandsInstruction {//0x8B
        void execute(runtime::Frame* frame) override;
    };

    struct f2l : public NoOperandsInstruction {//0x8C
        void execute(runtime::Frame* frame) override;
    };

    struct f2d : public NoOperandsInstruction {//0x8D
        void execute(runtime::Frame* frame) override;
    };

    struct d2i : public NoOperandsInstruction {//0x8E
        void execute(runtime::Frame* frame) override;
    };

    struct d2l : public NoOperandsInstruction {//0x8F
        void execute(runtime::Frame* frame) override;
    };

    struct d2f : public NoOperandsInstruction {//0x90
        void execute(runtime::Frame* frame) override;
    };

    struct i2b : public NoOperandsInstruction {//0x91
        void execute(runtime::Frame* frame) override;
    };

    struct i2c : public NoOperandsInstruction {//0x92
        void execute(runtime::Frame* frame) override;
    };

    struct i2s : public NoOperandsInstruction {//0x93
        void execute(runtime::Frame* frame) override;
    };

}
#endif //JVM_CONVERSIONS_H
