//
// Created by xuranus on 3/17/19.
//

#include "Class_Float.h"
#include "../NativeRegistry.h"
#include "../../runtime/heap/Object.h"
#include "../../runtime/heap/ClassLoader.h"
#include "../../util/Console.h"

void Class_Float::init()
{
    NativeRegistry::getNativeRegistery()->setRegister("java/lang/Float","floatToRawIntBits", "(F)I", Class_Float::floatToRawIntBits);
    NativeRegistry::getNativeRegistery()->setRegister("java/lang/Float","intBitsToFloat", "(I)F", Class_Float::intBitsToFloat);
}

// public static native int floatToRawIntBits(float value);
// (F)I
void Class_Float::floatToRawIntBits(Frame *frame)
{
    float value = frame->localVars.getFloat(0);
    int bits = *(int*)(&value);//TODO::
    frame->operandStack.pushInt(bits);
}

// public static native float intBitsToFloat(int bits);
// (I)F
void Class_Float::intBitsToFloat(Frame *frame)
{
    int bits = frame->localVars.getInt(0);
    float value = *(float *)(&bits);//TODO::
    frame->operandStack.pushFloat(value);
}