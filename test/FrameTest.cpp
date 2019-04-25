//
// Created by xuranus on 4/25/19.
//

#ifndef JVM_TEST4_H
#define JVM_TEST4_H

#include "../src/runtime/Frame.h"
#include "../src/runtime/Thread.h"
#include "../src/runtime/Stack.h"
#include <cstdio>

struct FrameTest {
    static void excute()
    {
        auto frame = new Frame(nullptr,1024,1024);
        testLocalVars(frame->localVars);
        printf("\n");
        testOperandStack(frame->operandStack);
    }

    static void testLocalVars(LocalVars& localVars)
    {
        localVars.setInt(0,100);
        localVars.setInt(1,-100);
        localVars.setLong(2,2997924580);
        localVars.setLong(4,-2997924580);
        localVars.setFloat(6,3.14159);
        localVars.setDouble(7,2.71828182845);
        localVars.setRef(9, nullptr);
        printf("%d\n",localVars.getInt(0));
        printf("%d\n",localVars.getInt(1));
        printf("%ld\n",localVars.getLong(2));
        printf("%ld\n",localVars.getLong(4));
        printf("%f\n",localVars.getFloat(6));
        printf("%.10f\n",localVars.getDouble(7));
        printf("%d\n",localVars.getRef(9));
    }

    static void testOperandStack(OperandStack& operandStack)
    {
        operandStack.pushInt(100);
        operandStack.pushInt(-100);
        operandStack.pushLong(2997924580);
        operandStack.pushLong(-2997924580);
        operandStack.pushFloat(3.14159);
        operandStack.pushDouble(2.71828182845);
        operandStack.pushRef(nullptr);
        printf("%d\n",operandStack.popRef());
        printf("%.10f\n",operandStack.popDouble());
        printf("%lf\n",operandStack.popFloat());
        printf("%ld\n",operandStack.popLong());
        printf("%ld\n",operandStack.popLong());
        printf("%d\n",operandStack.popInt());
        printf("%d\n",operandStack.popInt());
    }
};

#endif