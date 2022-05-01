//
// Created by XUranus on 2019/2/1.
//

#ifndef JVM_FRAME_H
#define JVM_FRAME_H

#include "../../../src/basicType.h"
#include "../Slots.h"
#include "Thread.h"
#include "../heap/Method.h"
#include <string>


namespace runtime {

    class Thread;
    typedef Slots LocalVars;
    typedef SlotsStack OperandStack;

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
#endif //JVM_FRAME_H
