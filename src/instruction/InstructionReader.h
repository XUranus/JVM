//
// Created by xuranus on 4/10/22.
//

#ifndef JVM_INSTRUCTION_READER_H
#define JVM_INSTRUCTION_READER_H

#include "../../src/basicType.h"
#include <vector>

namespace instruction {

    class InstructionReader {
    private:
        u4 pc;
        u4 length;
        u1 *code;

    public:
        InstructionReader();
        void reset(u1 *code, u4 pc, u4 length);
        [[nodiscard]] u4 PC() const;
        u1 readUint8();
        int8_t readInt8();
        u2 readUint16();
        int16_t readInt16();
        int readInt32();
        std::vector<int> readInt32s(int jumpOffsetsCount);
        void skipPadding();
        [[nodiscard]] bool end() const;
    };

}


#endif //JVM_INSTRUCTION_READER_H
