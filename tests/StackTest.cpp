#include <gtest/gtest.h>
#include "runtime/thread/Stack.h"
#include "runtime/thread/Frame.h"
#include "runtime/heap/ObjectPool.h"

class StackTest : public ::testing::Test {
protected:
    void SetUp() override {
        heap::ObjectPool::init();
    }
};

TEST_F(StackTest, NewStackIsEmpty) {
    runtime::Stack stack(64, nullptr);
    EXPECT_TRUE(stack.empty());
}

TEST_F(StackTest, PushAndPop) {
    runtime::Stack stack(64, nullptr);
    runtime::Frame frame(4, 4, nullptr, nullptr);
    stack.push(frame);
    EXPECT_FALSE(stack.empty());
    auto& top = stack.top();
    EXPECT_EQ(top.localVars.size(), 4);
}

TEST_F(StackTest, PushPopOrder) {
    runtime::Stack stack(64, nullptr);
    runtime::Frame frame1(2, 2, nullptr, nullptr);
    runtime::Frame frame2(4, 4, nullptr, nullptr);
    stack.push(frame1);
    stack.push(frame2);
    // Stack is LIFO — top should be frame2 (4 locals)
    EXPECT_EQ(stack.top().localVars.size(), 4);
    stack.pop();
    EXPECT_EQ(stack.top().localVars.size(), 2);
}

TEST_F(StackTest, MultiplePushPop) {
    runtime::Stack stack(64, nullptr);
    for (int i = 0; i < 10; i++) {
        runtime::Frame frame(i + 1, i + 1, nullptr, nullptr);
        stack.push(frame);
    }
    EXPECT_FALSE(stack.empty());
    for (int i = 9; i >= 0; i--) {
        EXPECT_EQ(stack.top().localVars.size(), i + 1);
        stack.pop();
    }
    EXPECT_TRUE(stack.empty());
}
