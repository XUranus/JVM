//
// Created by xuranus on 2/5/19.
//

#ifndef JVM_INSTRUCTION_RESERVED_H
#define JVM_INSTRUCTION_RESERVED_H

#include "instruction.h"

namespace instruction {

    /**
     * these three instruction are reserved for JVM, they are not allowed in classfile
     */

    /**
     * used for debugger
     */
    struct breakpoint : public NoOperandsInstruction {//0xCA
        void execute(runtime::Frame* frame) override;
    };

    /**
     * [invokenative] (custom jvm instruction)
     */
    struct impdep1 : public NoOperandsInstruction {//0xFE
        void execute(runtime::Frame* frame) override;
    };


    /**
     * useless reserved instruction
     */
    struct impdep2 : public NoOperandsInstruction {//0xFF
        void execute(runtime::Frame* frame) override;
    };

}

#endif //JVM_INSTRUCTION_RESERVED_H
