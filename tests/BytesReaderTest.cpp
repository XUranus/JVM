#include <gtest/gtest.h>
#include "classfile/BytesReader.h"
using namespace classfile;

TEST(BytesReaderTest, ReadFromBuffer) {
    std::vector<u1> data = {0xCA, 0xFE, 0xBA, 0xBE, 0x00, 0x01};
    BytesReader reader(data, "test");
    EXPECT_EQ(reader.readU4(), 0xCAFEBABE);
    EXPECT_EQ(reader.readU2(), 0x0001);
    EXPECT_TRUE(reader.end());
}

TEST(BytesReaderTest, ReadU1) {
    std::vector<u1> data = {0x42, 0xFF};
    BytesReader reader(data, "test");
    EXPECT_EQ(reader.readU1(), 0x42);
    EXPECT_EQ(reader.readU1(), 0xFF);
    EXPECT_TRUE(reader.end());
}

TEST(BytesReaderTest, SourceFile) {
    std::vector<u1> data = {0x00};
    BytesReader reader(data, "MyClass.class");
    EXPECT_EQ(reader.sourceFile(), "MyClass.class");
}

TEST(BytesReaderTest, NotEndInitially) {
    std::vector<u1> data = {0x00, 0x01};
    BytesReader reader(data, "test");
    EXPECT_FALSE(reader.end());
}

TEST(BytesReaderTest, ReadBytes) {
    std::vector<u1> data = {0x01, 0x02, 0x03, 0x04};
    BytesReader reader(data, "test");
    u1 buf[2];
    reader.read(buf, 2);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_FALSE(reader.end());
    reader.read(buf, 2);
    EXPECT_EQ(buf[0], 0x03);
    EXPECT_EQ(buf[1], 0x04);
    EXPECT_TRUE(reader.end());
}
