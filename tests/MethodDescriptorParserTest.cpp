#include <gtest/gtest.h>
#include "runtime/heap/MethodDescriptorParser.h"

using namespace heap;

TEST(MethodDescriptorParserTest, NoArgsVoidReturn) {
    MethodDescriptorParser parser("()V");
    auto [params, ret] = parser.parse();
    EXPECT_TRUE(params.empty());
    EXPECT_EQ(ret, "V");
}

TEST(MethodDescriptorParserTest, NoArgsIntReturn) {
    MethodDescriptorParser parser("()I");
    auto [params, ret] = parser.parse();
    EXPECT_TRUE(params.empty());
    EXPECT_EQ(ret, "I");
}

TEST(MethodDescriptorParserTest, SingleIntParam) {
    MethodDescriptorParser parser("(I)V");
    auto [params, ret] = parser.parse();
    ASSERT_EQ(params.size(), 1u);
    EXPECT_EQ(params[0], "I");
    EXPECT_EQ(ret, "V");
}

TEST(MethodDescriptorParserTest, MultiplePrimitiveParams) {
    MethodDescriptorParser parser("(IJFD)V");
    auto [params, ret] = parser.parse();
    ASSERT_EQ(params.size(), 4u);
    EXPECT_EQ(params[0], "I");
    EXPECT_EQ(params[1], "J");
    EXPECT_EQ(params[2], "F");
    EXPECT_EQ(params[3], "D");
    EXPECT_EQ(ret, "V");
}

TEST(MethodDescriptorParserTest, ObjectParam) {
    MethodDescriptorParser parser("(Ljava/lang/String;)V");
    auto [params, ret] = parser.parse();
    ASSERT_EQ(params.size(), 1u);
    EXPECT_EQ(params[0], "Ljava/lang/String;");
    EXPECT_EQ(ret, "V");
}

TEST(MethodDescriptorParserTest, ArrayParam) {
    MethodDescriptorParser parser("([I)V");
    auto [params, ret] = parser.parse();
    ASSERT_EQ(params.size(), 1u);
    EXPECT_EQ(params[0], "[I");
    EXPECT_EQ(ret, "V");
}

TEST(MethodDescriptorParserTest, ReturnObject) {
    MethodDescriptorParser parser("(I)Ljava/lang/String;");
    auto [params, ret] = parser.parse();
    ASSERT_EQ(params.size(), 1u);
    EXPECT_EQ(params[0], "I");
    EXPECT_EQ(ret, "Ljava/lang/String;");
}

TEST(MethodDescriptorParserTest, MainMethodDescriptor) {
    MethodDescriptorParser parser("([Ljava/lang/String;)V");
    auto [params, ret] = parser.parse();
    ASSERT_EQ(params.size(), 1u);
    EXPECT_EQ(params[0], "[Ljava/lang/String;");
    EXPECT_EQ(ret, "V");
}

TEST(MethodDescriptorParserTest, MultiDimensionArrayParam) {
    MethodDescriptorParser parser("([[I)V");
    auto [params, ret] = parser.parse();
    ASSERT_EQ(params.size(), 1u);
    EXPECT_EQ(params[0], "[[I");
    EXPECT_EQ(ret, "V");
}

TEST(MethodDescriptorParserTest, ComplexDescriptor) {
    MethodDescriptorParser parser("(Ljava/lang/String;IF)Ljava/lang/String;");
    auto [params, ret] = parser.parse();
    ASSERT_EQ(params.size(), 3u);
    EXPECT_EQ(params[0], "Ljava/lang/String;");
    EXPECT_EQ(params[1], "I");
    EXPECT_EQ(params[2], "F");
    EXPECT_EQ(ret, "Ljava/lang/String;");
}
