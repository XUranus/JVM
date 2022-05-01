//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_REFERENCES_H
#define JVM_REFERENCES_H


#include "instruction.h"

namespace instruction {

    //assistant method for 4 "invoke" instruction
    void invokeMethod(runtime::Frame* frame, heap::Method *method);

    struct getstatic : public Index16Instruction {//0xB2
        void execute(runtime::Frame* frame) override;
    };

    struct putstatic : public Index16Instruction {//0xB3
        void execute(runtime::Frame* frame) override;
    };

    struct getfield : public Index16Instruction {//0xB4
        void execute(runtime::Frame* frame) override;
    };

    struct putfield : public Index16Instruction {//0xB5
        void execute(runtime::Frame* frame) override;
    };

    /**
     * todo:: the following 5 method invoke instruction do not take static/default method of
     *  interface into consideration, so they do not fully meet specification of JVM 8
     *
     *  invokestatic: invoke static method
     *  invokespecial: invoke object method that doesn't need dynamic binding
     *  invokevirtual: invoke object method that need dynamic binding, todo:: optimize using Vtable
     *  invokeinterface:
     */

    struct invokevirtual : public Index16Instruction {//0xB6
        void execute(runtime::Frame* frame) override;
    };

    struct invokespecial : public Index16Instruction {//0xB7
        void execute(runtime::Frame* frame) override;
    };

    struct invokestatic : public Index16Instruction {//0xB8
        void execute(runtime::Frame* frame) override;
    };

    struct invokeinterface : public Instruction {//0xB9
        uint16 index;
        /**
         * [slotCount] : number of slot passed to method as parameter,
         * this can be directly calculated from method descriptor,
         * this exists due to historical issue, and is deprecated now
         */
        uint8 slotsCount;
        uint8 zero; // reserved for implementation of some JVM, must be 0

        void fetchOperands(InstructionReader &reader) override;
        void execute(runtime::Frame* frame) override;
    };

    struct invokedynamic : public Instruction {//0xBA
        uint16 index;
        uint8 slotsCount; //must be 0
        uint8 zero; //must be 0

        void fetchOperands(InstructionReader &reader) override;
        void execute(runtime::Frame* frame) override;
    };


    struct new_ : public Index16Instruction {//0xBB
        void execute(runtime::Frame* frame) override;
    };

    struct newarray : public Instruction {//0xBC
        u1 atype;

        void fetchOperands(InstructionReader &reader) override;
        void execute(runtime::Frame* frame) override;
    };

    struct anewarray : public Index16Instruction {//0xBD
        void execute(runtime::Frame* frame) override;
    };

    struct arraylength : public NoOperandsInstruction {//0xBE
        void execute(runtime::Frame* frame) override;
    };

    struct athrow : public NoOperandsInstruction {//0xBF
        void execute(runtime::Frame* frame) override;
    };

    struct checkcast : public Index16Instruction {//0xC0
        void execute(runtime::Frame* frame) override;
    };

    struct instanceof : public Index16Instruction {//0xC1
        void execute(runtime::Frame* frame) override;
    };

    struct monitorenter : public NoOperandsInstruction {//0xC2
        void execute(runtime::Frame* frame) override;
    };

    struct monitiorexit : public NoOperandsInstruction {//0xC3
        void execute(runtime::Frame* frame) override;
    };

}

#endif //JVM_REFERENCES_H
