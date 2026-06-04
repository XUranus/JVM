#include <gtest/gtest.h>
#include "runtime/thread/Frame.h"
#include "runtime/thread/Thread.h"
#include "runtime/heap/ObjectPool.h"

class FrameTest : public ::testing::Test {
protected:
    void SetUp() override {
        heap::ObjectPool::init();
    }
};

TEST_F(FrameTest, LocalVarsSetGetInt) {
    runtime::Frame frame(10, 10, nullptr, nullptr);
    frame.localVars.setInt(0, 100);
    frame.localVars.setInt(1, -100);
    EXPECT_EQ(frame.localVars.intValue(0), 100);
    EXPECT_EQ(frame.localVars.intValue(1), -100);
}

TEST_F(FrameTest, LocalVarsSetGetLong) {
    runtime::Frame frame(10, 10, nullptr, nullptr);
    frame.localVars.setLong(0, 2997924580L);
    frame.localVars.setLong(2, -2997924580L);
    EXPECT_EQ(frame.localVars.longValue(0), 2997924580L);
    EXPECT_EQ(frame.localVars.longValue(2), -2997924580L);
}

TEST_F(FrameTest, LocalVarsSetGetFloat) {
    runtime::Frame frame(10, 10, nullptr, nullptr);
    frame.localVars.setFloat(0, 3.14159f);
    EXPECT_FLOAT_EQ(frame.localVars.floatValue(0), 3.14159f);
}

TEST_F(FrameTest, LocalVarsSetGetDouble) {
    runtime::Frame frame(10, 10, nullptr, nullptr);
    frame.localVars.setDouble(0, 2.71828182845);
    EXPECT_DOUBLE_EQ(frame.localVars.doubleValue(0), 2.71828182845);
}

TEST_F(FrameTest, LocalVarsSetGetRef) {
    runtime::Frame frame(10, 10, nullptr, nullptr);
    auto* obj = heap::ObjectPool::createObject();
    frame.localVars.setRef(0, obj);
    EXPECT_EQ(frame.localVars.refValue(0), obj);
}

TEST_F(FrameTest, OperandStackPushPopInt) {
    runtime::Frame frame(4, 16, nullptr, nullptr);
    frame.operandStack.pushInt(100);
    frame.operandStack.pushInt(-100);
    EXPECT_EQ(frame.operandStack.popInt(), -100);
    EXPECT_EQ(frame.operandStack.popInt(), 100);
}

TEST_F(FrameTest, OperandStackPushPopLong) {
    runtime::Frame frame(4, 16, nullptr, nullptr);
    frame.operandStack.pushLong(2997924580L);
    frame.operandStack.pushLong(-2997924580L);
    EXPECT_EQ(frame.operandStack.popLong(), -2997924580L);
    EXPECT_EQ(frame.operandStack.popLong(), 2997924580L);
}

TEST_F(FrameTest, OperandStackPushPopFloat) {
    runtime::Frame frame(4, 16, nullptr, nullptr);
    frame.operandStack.pushFloat(3.14159f);
    EXPECT_FLOAT_EQ(frame.operandStack.popFloat(), 3.14159f);
}

TEST_F(FrameTest, OperandStackPushPopDouble) {
    runtime::Frame frame(4, 16, nullptr, nullptr);
    frame.operandStack.pushDouble(2.71828182845);
    EXPECT_DOUBLE_EQ(frame.operandStack.popDouble(), 2.71828182845);
}

TEST_F(FrameTest, OperandStackPushPopRef) {
    runtime::Frame frame(4, 16, nullptr, nullptr);
    auto* obj = heap::ObjectPool::createObject();
    frame.operandStack.pushRef(obj);
    EXPECT_EQ(frame.operandStack.popRef(), obj);
}

TEST_F(FrameTest, OperandStackMixedOperations) {
    runtime::Frame frame(4, 32, nullptr, nullptr);
    auto* obj = heap::ObjectPool::createObject();
    frame.operandStack.pushInt(42);
    frame.operandStack.pushLong(1000000000L);
    frame.operandStack.pushFloat(1.5f);
    frame.operandStack.pushDouble(2.5);
    frame.operandStack.pushRef(obj);
    EXPECT_EQ(frame.operandStack.popRef(), obj);
    EXPECT_DOUBLE_EQ(frame.operandStack.popDouble(), 2.5);
    EXPECT_FLOAT_EQ(frame.operandStack.popFloat(), 1.5f);
    EXPECT_EQ(frame.operandStack.popLong(), 1000000000L);
    EXPECT_EQ(frame.operandStack.popInt(), 42);
}

TEST_F(FrameTest, Branch) {
    runtime::Thread thread(64, "test-thread");
    thread.pc = 10;
    runtime::Frame frame(4, 4, &thread, nullptr);
    frame.branch(5);
    EXPECT_EQ(frame.nextPC, 15);
    thread.pc = 15;
    frame.branch(-3);
    EXPECT_EQ(frame.nextPC, 12);
}
