//
// Created by xuranus on 4/10/22.
//

#include "InstructionReader.h"
#include <cassert>
#include <vector>
#include <iostream>

namespace instruction {

    InstructionReader::InstructionReader() {
        pc = 0;
        code = nullptr;
        length = 0;
    }


    void InstructionReader::reset(u1 *_code, u4 _pc, u4 _length) {
        pc = _pc;
        code = _code;
        length = _length;
    }

    u4 InstructionReader::PC() const {
        return pc;
    }

    int8_t InstructionReader::readInt8() {
        int8_t ret = *(int8_t *) (&code[pc]);
        pc++;
        return ret;
    }

    u1 InstructionReader::readUint8() {
        u1 ret = code[pc];
        pc++;
        return ret;
    }

    int16_t InstructionReader::readInt16() {
        return int16_t(readUint16());
    }

    u2 InstructionReader::readUint16() {
        auto byte1 = (u2) readUint8();
        auto byte2 = (u2) readUint8();
        return (byte1 << 8) | byte2;
    }

    int InstructionReader::readInt32() {
        auto byte1 = (int) readUint8();
        auto byte2 = (int) readUint8();
        auto byte3 = (int) readUint8();
        auto byte4 = (int) readUint8();
        return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
    }

    void InstructionReader::skipPadding() {
        while (pc % 4 != 0) pc++;
    }

    std::vector<int> InstructionReader::readInt32s(int jumpOffsetsCount) {
        std::vector<int> jumpOffsets(jumpOffsetsCount, 0);
        for (int i = 0; i < jumpOffsetsCount; i++) {
            jumpOffsets[i] = readInt32();
        }
        return jumpOffsets;
    }

    bool InstructionReader::end() const {
        assert(length > pc);
        return length == pc;
    }

}