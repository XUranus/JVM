//
// Created by xuranus on 4/27/22.
//

#include "Runtime.h"


#include "../../NativeRegistry.h"
#include <thread>

namespace native::java::lang::Runtime {

    void doRegistration() {
        setRegister("java/lang/Runtime", "availableProcessors", "()I", availableProcessors);
    }

    // public native int availableProcessors();
    // ()I
    void availableProcessors(runtime::Frame* frame) {
        const auto processorCount = std::thread::hardware_concurrency();
        frame->operandStack.pushInt((int)processorCount);
    }
}