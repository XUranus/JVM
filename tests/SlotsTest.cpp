#include <gtest/gtest.h>
#include "runtime/Slots.h"

using namespace runtime;

TEST(SlotTest, DefaultValues) {
    Slot s;
    EXPECT_EQ(s.num, 0u);
    EXPECT_FALSE(s.ptrFlag);
}

TEST(SlotsTest, InitialSize) {
    Slots slots(10);
    EXPECT_EQ(slots.size(), 10);
}

TEST(SlotsTest, SetGetInt) {
    Slots slots(4);
    slots.setInt(0, 42);
    EXPECT_EQ(slots.intValue(0), 42);
    EXPECT_FALSE(slots.isRef(0));
}

TEST(SlotsTest, SetGetFloat) {
    Slots slots(4);
    slots.setFloat(0, 3.14f);
    EXPECT_FLOAT_EQ(slots.floatValue(0), 3.14f);
}

TEST(SlotsTest, SetGetLong) {
    Slots slots(4);
    long val = 0x123456789ABCDEF0L;
    slots.setLong(0, val);
    EXPECT_EQ(slots.longValue(0), val);
}

TEST(SlotsTest, SetGetDouble) {
    Slots slots(4);
    slots.setDouble(0, 2.718281828);
    EXPECT_DOUBLE_EQ(slots.doubleValue(0), 2.718281828);
}

TEST(SlotsTest, SetGetRef) {
    Slots slots(4);
    // Use a fake pointer value (nullptr)
    slots.setRef(0, nullptr);
    EXPECT_TRUE(slots.isRef(0));
    EXPECT_EQ(slots.refValue(0), nullptr);
}

TEST(SlotsTest, CopyConstruction) {
    Slots slots(4);
    slots.setInt(0, 100);
    slots.setInt(1, 200);

    Slots copy(slots);
    EXPECT_EQ(copy.intValue(0), 100);
    EXPECT_EQ(copy.intValue(1), 200);
    EXPECT_EQ(copy.size(), 4);
}

TEST(SlotsTest, Resize) {
    Slots slots(4);
    slots.setInt(0, 42);
    slots.resize(8);
    EXPECT_EQ(slots.size(), 8);
    // After resize, values are zeroed
    EXPECT_EQ(slots.intValue(0), 0);
}

TEST(SlotsTest, BoolValue) {
    Slots slots(4);
    slots.setInt(0, 1);
    EXPECT_TRUE(slots.boolValue(0));
    slots.setInt(0, 0);
    EXPECT_FALSE(slots.boolValue(0));
}

TEST(SlotsStackTest, PushPopInt) {
    SlotsStack stack(16);
    stack.pushInt(42);
    stack.pushInt(99);
    EXPECT_EQ(stack.popInt(), 99);
    EXPECT_EQ(stack.popInt(), 42);
}

TEST(SlotsStackTest, PushPopFloat) {
    SlotsStack stack(16);
    stack.pushFloat(1.5f);
    EXPECT_FLOAT_EQ(stack.popFloat(), 1.5f);
}

TEST(SlotsStackTest, PushPopLong) {
    SlotsStack stack(16);
    long val = 0x7FFFFFFFFFFFFFFFL;
    stack.pushLong(val);
    EXPECT_EQ(stack.popLong(), val);
}

TEST(SlotsStackTest, PushPopDouble) {
    SlotsStack stack(16);
    stack.pushDouble(3.14159);
    EXPECT_DOUBLE_EQ(stack.popDouble(), 3.14159);
}

TEST(SlotsStackTest, PushPopBoolean) {
    SlotsStack stack(16);
    stack.pushBoolean(true);
    EXPECT_TRUE(stack.popBoolean());
    stack.pushBoolean(false);
    EXPECT_FALSE(stack.popBoolean());
}

TEST(SlotsStackTest, PushPopRef) {
    SlotsStack stack(16);
    stack.pushRef(nullptr);
    EXPECT_EQ(stack.popRef(), nullptr);
}

TEST(SlotsStackTest, Clear) {
    SlotsStack stack(16);
    stack.pushInt(1);
    stack.pushInt(2);
    stack.clear();
    // After clear, we can push again from the beginning
    stack.pushInt(99);
    EXPECT_EQ(stack.popInt(), 99);
}
