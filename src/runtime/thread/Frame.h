//
// Created by XUranus on 2019/2/1.
//

#pragma once

#include "basicType.h"
#include "../Slots.h"
#include "Thread.h"
#include "../heap/Method.h"
#include <string>

namespace runtime {

    class Thread;
    using LocalVars = Slots;
    using OperandStack = SlotsStack;

    class Frame {
    public:
        unsigned int nextPC;
        LocalVars localVars;
        OperandStack operandStack;

        Thread* thread; // for referring, do not release
        heap::Method* method; // for referring, do not release

    public:
        Frame(int _maxLocalVars,
              int _operandStack,
              Thread* _thread,
              heap::Method* _method);

        Frame();

        void branch(int offset);
        void revertNextPC();
    };

}
