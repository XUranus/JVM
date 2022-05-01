//
// Created by XUranus on 2019/2/1.
//

#include "Frame.h"
#include <iostream>

namespace runtime {

    Frame::Frame(int _maxLocalVars,
                 int _operandStack,
                 Thread* _thread,
                 heap::Method* _method):
                 localVars(_maxLocalVars),
                 operandStack(_operandStack) {
        method = _method;
        thread = _thread;
        nextPC = 0;
    }

    Frame::Frame(): localVars(0), operandStack(0) {
        nextPC = 0;
        thread = nullptr;
        method = nullptr;
    }

    void Frame::branch(int offset) {
        nextPC = thread->pc + offset;
    }

    void Frame::revertNextPC() {
        nextPC = thread->pc;
    }


}