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

    int8 InstructionReader::readInt8() {
        int8 ret = *(int8 *) (&code[pc]);
        pc++;
        return ret;
    }

    uint8 InstructionReader::readUint8() {
        uint8 ret = code[pc];
        pc++;
        return ret;
    }

    int16 InstructionReader::readInt16() {
        return int16(readUint16());
    }

    uint16 InstructionReader::readUint16() {
        auto byte1 = (uint16) readUint8();
        auto byte2 = (uint16) readUint8();
        return (byte1 << 8) | byte2;
    }

    int32 InstructionReader::readInt32() {
        auto byte1 = (int32) readUint8();
        auto byte2 = (int32) readUint8();
        auto byte3 = (int32) readUint8();
        auto byte4 = (int32) readUint8();
        return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
    }

    void InstructionReader::skipPadding() {
        while (pc % 4 != 0) pc++;
    }

    std::vector<int32> InstructionReader::readInt32s(int jumpOffsetsCount) {
        std::vector<int32> jumpOffsets(jumpOffsetsCount, 0);
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