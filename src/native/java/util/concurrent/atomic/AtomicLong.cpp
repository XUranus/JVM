//
// Created by xuranus on 4/30/22.
//

#include "AtomicLong.h"
#include "../../../../NativeRegistry.h"

namespace native::java::util::concurrent::atomic::AtomicLong {

    void doRegistration() {
        setRegister("java/util/concurrent/atomic/AtomicLong", "VMSupportsCS8", "()Z", VMSupportsCS8);
    }

    void VMSupportsCS8(runtime::Frame* frame) {
        frame->operandStack.pushBoolean(false);
    }
}