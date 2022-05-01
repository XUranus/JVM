//
// Created by xuranus on 2/5/19.
//

#include "stack.h"

namespace instruction {

    void pop::execute(runtime::Frame* frame) {
        frame->operandStack.popSlot();
    }

    void pop2::execute(runtime::Frame* frame) {
        frame->operandStack.popSlot();
        frame->operandStack.popSlot();
    }

    void dup::execute(runtime::Frame* frame) {
        auto slot = frame->operandStack.popSlot();
        frame->operandStack.pushSlot(slot);
        frame->operandStack.pushSlot(slot);
    }

    void dup_x1::execute(runtime::Frame* frame) {
        auto v1 = frame->operandStack.popSlot();
        auto v2 = frame->operandStack.popSlot();
        frame->operandStack.pushSlot(v1);
        frame->operandStack.pushSlot(v2);
        frame->operandStack.pushSlot(v1);
    }

    void dup_x2::execute(runtime::Frame* frame) {
        auto v1 = frame->operandStack.popSlot();
        auto v2 = frame->operandStack.popSlot();
        auto v3 = frame->operandStack.popSlot();
        frame->operandStack.pushSlot(v1);
        frame->operandStack.pushSlot(v3);
        frame->operandStack.pushSlot(v2);
        frame->operandStack.pushSlot(v1);
    }

    void dup2::execute(runtime::Frame* frame) {
        auto v1 = frame->operandStack.popSlot();
        auto v2 = frame->operandStack.popSlot();
        frame->operandStack.pushSlot(v2);
        frame->operandStack.pushSlot(v1);
        frame->operandStack.pushSlot(v2);
        frame->operandStack.pushSlot(v1);
    }

    void dup2_x1::execute(runtime::Frame* frame) {
        auto v1 = frame->operandStack.popSlot();
        auto v2 = frame->operandStack.popSlot();
        auto v3 = frame->operandStack.popSlot();
        frame->operandStack.pushSlot(v2);
        frame->operandStack.pushSlot(v1);
        frame->operandStack.pushSlot(v3);
        frame->operandStack.pushSlot(v2);
        frame->operandStack.pushSlot(v1);
    }

    void dup2_x2::execute(runtime::Frame* frame) {
        auto v1 = frame->operandStack.popSlot();
        auto v2 = frame->operandStack.popSlot();
        auto v3 = frame->operandStack.popSlot();
        auto v4 = frame->operandStack.popSlot();
        frame->operandStack.pushSlot(v2);
        frame->operandStack.pushSlot(v1);
        frame->operandStack.pushSlot(v4);
        frame->operandStack.pushSlot(v3);
        frame->operandStack.pushSlot(v2);
        frame->operandStack.pushSlot(v1);
    }

    void swap::execute(runtime::Frame* frame) {
        auto v1 = frame->operandStack.popSlot();
        auto v2 = frame->operandStack.popSlot();
        frame->operandStack.pushSlot(v1);
        frame->operandStack.pushSlot(v2);
    }

}