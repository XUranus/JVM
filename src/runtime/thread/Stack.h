//
// Created by XUranus on 2019/2/1.
//

#ifndef JVM_RUNTIME_STACK_H
#define JVM_RUNTIME_STACK_H

#include "Frame.h"
#include <list>

namespace runtime {

    struct Thread;
    struct Frame;

    class Stack { //JVM Stack
    private:
        int maxCapacity;
        std::list<Frame> frames;

    public:
        Thread* thread;// for referring

    public:
        explicit Stack(int _maxCapacity, runtime::Thread* _thread);
        void push(const runtime::Frame& frame);
        Frame pop();
        Frame& top();
        void clear();
        [[nodiscard]] bool empty() const;

        std::list<Frame*> stackFrames(); // return frames from top to bottom

    };
}

#endif //JVM_RUNTIME_STACK_H
