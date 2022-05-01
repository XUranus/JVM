//
// Created by xuranus on 3/16/19.
//

#include "../../NativeRegistry.h"
#include "../../../runtime/heap/Object.h"
#include "../../../runtime/heap/ClassLoader.h"

#include "Double.h"

namespace native::java::lang::Double {

    void doRegistration() {
        setRegister("java/lang/Double", "doubleToRawLongBits", "(D)J", native::java::lang::Double::doubleToRawLongBits);
        setRegister("java/lang/Double", "longBitsToDouble", "(J)D", native::java::lang::Double::longBitsToDouble);
    }

    // public static native long doubleToRawLongBits(double value);
    // (D)J
    void doubleToRawLongBits(runtime::Frame *frame) {
        // convert float64 bits to int64
        double value = frame->localVars.doubleValue(0);
        long bits = *(long *) (&value);
        frame->operandStack.pushLong(bits);
    }

    // public static native double longBitsToDouble(long bits);
    // (J)D
    void longBitsToDouble(runtime::Frame *frame) {
        // convert int64 bits to float64
        long bits = frame->localVars.longValue(0);
        double value = *(double *) (&bits);
        frame->operandStack.pushDouble(value);
    }

}