//
// Created by xuranus on 4/30/22.
//

#include "AtomicLong.h"
#include "../../../../NativeRegistry.h"

namespace native::java::util::concurrent::atomic::AtomicLong {

    void VMSupportsCS8(runtime::Frame* frame) {
        frame->operandStack.pushBoolean(false);
    }
}