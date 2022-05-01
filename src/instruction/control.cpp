//
// Created by xuranus on 2/5/19.
//

#include "control.h"
#include "../common/Exception.h"
//#include "../runtime/thread/Thread.h"

namespace instruction {

    void goto_::execute(runtime::Frame* frame) {
        frame->branch(offset);
    }

    void jsr::execute(runtime::Frame* frame) {
        exception::panic("instruction [jsr] not support after java 6");
    }

    void ret::execute(runtime::Frame* frame) {
        exception::panic("instruction [ret] not support after java 6");
    }

    void tableswitch::execute(runtime::Frame* frame) {
        int offset = 0;
        auto index = frame->operandStack.popInt();
        if (index >= low && index <= high) {
            offset = (int) jumpOffsets[index - low];
        } else {
            offset = (int) defaultOffset;
        }
        frame->branch(offset);
    }

    void tableswitch::fetchOperands(InstructionReader &reader) {
        reader.skipPadding();
        defaultOffset = reader.readInt32();
        low = reader.readInt32();
        high = reader.readInt32();
        int jumpOffsetsCount = high - low + 1;
        jumpOffsets = reader.readInt32s(jumpOffsetsCount);
    }

    void lookupswitch::execute(runtime::Frame* frame) {
        auto key = frame->operandStack.popInt();
        for (int i = 0; i < nPairs * 2; i += 2) {
            if (matchOffsets[i] == key) {
                int offset = matchOffsets[i + 1];
                frame->branch(offset);
                return;
            }
        }
        frame->branch(defaultOffsets);
    }

    void lookupswitch::fetchOperands(InstructionReader &reader) {
        reader.skipPadding();
        defaultOffsets = reader.readInt32();
        nPairs = reader.readInt32();
        matchOffsets = reader.readInt32s(nPairs * 2);
    }

    void ireturn::execute(runtime::Frame* frame) {
        runtime::Thread* thread = frame->thread;
        runtime::Frame currentFrame = thread->stack->pop();
        runtime::Frame &invokerFrame = thread->stack->top();
        int retVal = currentFrame.operandStack.popInt();
        invokerFrame.operandStack.pushInt(retVal);
    }

    void lreturn::execute(runtime::Frame* frame) {
        runtime::Thread* thread = frame->thread;
        runtime::Frame currentFrame = thread->stack->pop();
        runtime::Frame& invokerFrame = thread->stack->top();
        long retVal = currentFrame.operandStack.popLong();
        invokerFrame.operandStack.pushLong(retVal);
    }

    void freturn::execute(runtime::Frame* frame) {
        runtime::Thread* thread = frame->thread;
        runtime::Frame currentFrame = thread->stack->pop();
        runtime::Frame& invokerFrame = thread->stack->top();
        float retVal = currentFrame.operandStack.popFloat();
        invokerFrame.operandStack.pushFloat(retVal);
    }

    void dreturn::execute(runtime::Frame* frame) {
        runtime::Thread* thread = frame->thread;
        runtime::Frame currentFrame = thread->stack->pop();
        runtime::Frame& invokerFrame = thread->stack->top();
        double retVal = currentFrame.operandStack.popDouble();
        invokerFrame.operandStack.pushDouble(retVal);
    }

    void areturn::execute(runtime::Frame* frame) {
        runtime::Thread* thread = frame->thread;
        runtime::Frame currentFrame = thread->stack->pop();
        runtime::Frame& invokerFrame = thread->stack->top();
        heap::Object* retVal = currentFrame.operandStack.popRef();
        invokerFrame.operandStack.pushRef(retVal);
    }

    void return_::execute(runtime::Frame* frame) {
        frame->thread->stack->pop();
    }

}