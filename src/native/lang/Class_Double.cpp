//
// Created by xuranus on 3/16/19.
//

#include "Class_Double.h"
#include "../NativeRegistry.h"
#include "../../runtime/heap/Object.h"
#include "../../runtime/heap/ClassLoader.h"
#include "../../util/Console.h"

void Class_Double::init()
{
    NativeRegistry::getNativeRegistery()->setRegister("java/lang/Double","doubleToRawLongBits", "(D)J", Class_Double::doubleToRawLongBits);
    NativeRegistry::getNativeRegistery()->setRegister("java/lang/Double","longBitsToDouble", "(J)D", Class_Double::longBitsToDouble);
}


// public static native long doubleToRawLongBits(double value);
// (D)J
void Class_Double::doubleToRawLongBits(Frame *frame)
{
    double value = frame->localVars.getDouble(0);
    long bits = *(long*)(&value);
    frame->operandStack.pushLong(bits);
}

// public static native double longBitsToDouble(long bits);
// (J)D
void Class_Double::longBitsToDouble(Frame *frame)
{
    long bits = frame->localVars.getLong(0);
    double value = *(double*)(&bits);
    frame->operandStack.pushDouble(value);
}
