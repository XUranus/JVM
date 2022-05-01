//
// Created by xuranus on 4/27/22.
//

#include "Signal.h"

#include "../../NativeRegistry.h"

namespace native::sun::misc::Signal {

    void doRegistration() {
        setRegister("sun/misc/Signal", "findSignal", "(Ljava/lang/String;)I", findSignal);
        setRegister("sun/misc/Signal", "handle0", "(IJ)J", handle0);
    }

    // private static native int findSignal(String string);
    // (Ljava/lang/String;)I
    void findSignal(runtime::Frame* frame) {
        // heap::Object* strObj = frame->localVars.refValue(0);
        frame->operandStack.pushInt(0); // TODO:: implement
    }

    // private static native long handle0(int i, long l);
    // (IJ)J
    void handle0(runtime::Frame* frame) {
        // int i = frame->localVars.intValue(0);
        // long l = frame->localVars.longValue(1);
        frame->operandStack.pushLong(0); // TODO:: implement
    }

}