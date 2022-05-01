//
// Created by xuranus on 3/17/19.
//


#include "../../NativeRegistry.h"
#include "../../../runtime/heap/ClassLoader.h"
#include "Float.h"

namespace native::java::lang::Float {

    void doRegistration() {
        setRegister("java/lang/Float", "floatToRawIntBits", "(F)I", native::java::lang::Float::floatToRawIntBits);
        setRegister("java/lang/Float", "intBitsToFloat", "(I)F", native::java::lang::Float::intBitsToFloat);
    }

    // public static native int floatToRawIntBits(float value);
    // (F)I
    void floatToRawIntBits(runtime::Frame *frame) {
        // convert float32 bits to int32
        float value = frame->localVars.floatValue(0);
        int bits = *(int *) (&value);
        frame->operandStack.pushInt(bits);
    }

    // public static native float intBitsToFloat(int bits);
    // (I)F
    void intBitsToFloat(runtime::Frame *frame) {
        // convert int32 bits to float32
        int bits = frame->localVars.intValue(0);
        float value = *(float *) (&bits);
        frame->operandStack.pushFloat(value);
    }

}