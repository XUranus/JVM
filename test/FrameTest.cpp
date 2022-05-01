//
// Created by xuranus on 4/25/19.
//

#ifndef JVM_TEST4_H
#define JVM_TEST4_H

#include "../src/runtime/thread/Frame.h"
#include "../src/runtime/heap/ObjectPool.h"
#include <bits/stdc++.h>

using namespace std;

struct FrameTest {

    static void execute() {
        heap::ObjectPool::init();

        runtime::Frame frame(10, 10, nullptr, nullptr);
        testLocalVars(frame.localVars);
        testOperandStack(frame.operandStack);
    }

    static void testLocalVars(runtime::LocalVars& localVars) {
        cout << "testing localVars ... ";
        auto* obj = heap::ObjectPool::createObject();
        localVars.setInt(0,100);
        localVars.setInt(1,-100);
        localVars.setLong(2,2997924580);
        localVars.setLong(4,-2997924580);
        localVars.setFloat(6,3.14159);
        localVars.setDouble(7,2.71828182845);
        localVars.setRef(9, obj);
        assert(localVars.intValue(0) == 100);
        assert(localVars.intValue(1) == -100);
        assert(localVars.longValue(2) == 2997924580);
        assert(localVars.longValue(4) == -2997924580);
        assert(localVars.floatValue(6) == 3.14159f);
        assert(localVars.doubleValue(7) == 2.71828182845);
        assert(localVars.refValue(9) == obj);
        cout << "Done" << endl;
    }

    static void testOperandStack(runtime::OperandStack& operandStack) {
        cout << "testing operand stack ... ";
        auto* obj = heap::ObjectPool::createObject();
        operandStack.pushInt(100);
        operandStack.pushInt(-100);
        operandStack.pushLong(2997924580);
        operandStack.pushLong(-2997924580);
        operandStack.pushFloat(3.14159);
        operandStack.pushDouble(2.71828182845);
        operandStack.pushRef(obj);
        assert(operandStack.popRef() == obj);
        assert(operandStack.popDouble() == 2.71828182845);
        assert(operandStack.popFloat() == 3.14159f);
        assert(operandStack.popLong() == -2997924580);
        assert(operandStack.popLong() == 2997924580);
        assert(operandStack.popInt() == -100);
        assert(operandStack.popInt() == 100);
        cout << "Done" << endl;
    }
};

#endif