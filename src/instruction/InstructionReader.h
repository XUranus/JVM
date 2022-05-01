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
        uint8 readUint8();
        int8 readInt8();
        uint16 readUint16();
        int16 readInt16();
        int32 readInt32();
        std::vector<int32> readInt32s(int jumpOffsetsCount);
        void skipPadding();
        [[nodiscard]] bool end() const;
    };

}


#endif //JVM_INSTRUCTION_READER_H
