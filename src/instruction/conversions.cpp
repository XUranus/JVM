//
// Created by xuranus on 2/5/19.
//

#include "conversions.h"

namespace instruction {

    void i2l::execute(runtime::Frame* frame) {
        auto v = frame->operandStack.popInt();
        frame->operandStack.pushLong((long) v);
    }

    void i2f::execute(runtime::Frame* frame) {
        auto v = frame->operandStack.popInt();
        frame->operandStack.pushFloat((float) v);
    }

    void i2d::execute(runtime::Frame* frame) {
        auto v = frame->operandStack.popInt();
        frame->operandStack.pushDouble((double) v);
    }

    void l2i::execute(runtime::Frame* frame) {
        auto v = frame->operandStack.popLong();
        frame->operandStack.pushInt((int) v);
    }

    void l2f::execute(runtime::Frame* frame) {
        auto v = frame->operandStack.popLong();
        frame->operandStack.pushFloat((float) v);
    }

    void l2d::execute(runtime::Frame* frame) {
        auto v = frame->operandStack.popLong();
        frame->operandStack.pushDouble((double) v);
    }

    void f2i::execute(runtime::Frame* frame) {
        auto v = frame->operandStack.popFloat();
        frame->operandStack.pushInt((int)v);
    }

    void f2l::execute(runtime::Frame* frame) {
        auto v = frame->operandStack.popFloat();
        frame->operandStack.pushLong((long) v);
    }

    void f2d::execute(runtime::Frame* frame) {
        auto v = frame->operandStack.popFloat();
        frame->operandStack.pushDouble((double) v);
    }

    void d2i::execute(runtime::Frame* frame) {
        auto v = frame->operandStack.popDouble();
        frame->operandStack.pushInt((int) v);
    }

    void d2l::execute(runtime::Frame* frame) {
        auto v = frame->operandStack.popDouble();
        frame->operandStack.pushLong((long) v);
    }

    void d2f::execute(runtime::Frame* frame) {
        auto v = frame->operandStack.popDouble();
        frame->operandStack.pushFloat((float) v);
    }

    void i2b::execute(runtime::Frame* frame) {
        auto v = frame->operandStack.popInt();
        frame->operandStack.pushInt((unsigned char)v);
    }

    void i2c::execute(runtime::Frame* frame) {
        auto v = frame->operandStack.popInt();
        frame->operandStack.pushInt((char)v);
    }

    void i2s::execute(runtime::Frame* frame) {
        auto v = frame->operandStack.popInt();
        frame->operandStack.pushInt((short)v);
    }

}