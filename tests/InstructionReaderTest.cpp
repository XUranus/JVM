#include <gtest/gtest.h>
#include "instruction/InstructionReader.h"

TEST(InstructionReaderTest, ReadUint8) {
    instruction::InstructionReader reader;
    u1 code[] = {0x00, 0x42, 0xFF};
    reader.reset(code, 0, 3);
    EXPECT_EQ(reader.readUint8(), 0x00);
    EXPECT_EQ(reader.readUint8(), 0x42);
    EXPECT_EQ(reader.readUint8(), 0xFF);
}

TEST(InstructionReaderTest, ReadUint16) {
    instruction::InstructionReader reader;
    u1 code[] = {0x01, 0x02};
    reader.reset(code, 0, 2);
    EXPECT_EQ(reader.readUint16(), 0x0102);
}

TEST(InstructionReaderTest, ReadInt16) {
    instruction::InstructionReader reader;
    // 0xFFFE = -2 in signed 16-bit
    u1 code[] = {0xFF, 0xFE};
    reader.reset(code, 0, 2);
    EXPECT_EQ(reader.readInt16(), -2);
}

TEST(InstructionReaderTest, ReadInt32) {
    instruction::InstructionReader reader;
    // 0x000000FF = 255
    u1 code[] = {0x00, 0x00, 0x00, 0xFF};
    reader.reset(code, 0, 4);
    EXPECT_EQ(reader.readInt32(), 255);
}

TEST(InstructionReaderTest, ReadNegativeInt32) {
    instruction::InstructionReader reader;
    // 0xFFFFFFFF = -1
    u1 code[] = {0xFF, 0xFF, 0xFF, 0xFF};
    reader.reset(code, 0, 4);
    EXPECT_EQ(reader.readInt32(), -1);
}

TEST(InstructionReaderTest, PCTracking) {
    instruction::InstructionReader reader;
    u1 code[] = {0x01, 0x02, 0x03, 0x04};
    reader.reset(code, 0, 4);
    EXPECT_EQ(reader.PC(), 0);
    reader.readUint8();
    EXPECT_EQ(reader.PC(), 1);
    reader.readUint16();
    EXPECT_EQ(reader.PC(), 3);
    reader.readUint8();
    EXPECT_EQ(reader.PC(), 4);
}

TEST(InstructionReaderTest, ResetToOffset) {
    instruction::InstructionReader reader;
    u1 code[] = {0x00, 0x01, 0x02, 0x03};
    reader.reset(code, 2, 4);
    EXPECT_EQ(reader.PC(), 2);
    EXPECT_EQ(reader.readUint8(), 0x02);
}

TEST(InstructionReaderTest, SkipPadding) {
    instruction::InstructionReader reader;
    // Create a buffer where offset 4 is not 4-byte aligned
    // skipPadding should align to 4 bytes
    u1 code[16] = {};
    reader.reset(code, 1, 16);
    reader.skipPadding();
    EXPECT_EQ(reader.PC(), 4);
}
