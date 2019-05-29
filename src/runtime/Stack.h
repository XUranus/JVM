//
// Created by XUranus on 2019/2/1.
//

#ifndef JVM_RUNTIME_STACK_H
#define JVM_RUNTIME_STACK_H

#include "Frame.h"

struct Stack { //JVM Stack
    int capacity;
    int size;
    Frame *_top;

    explicit Stack(int capacity);
    void push(Frame* frame);
    Frame* pop();
    Frame* top();
    bool empty();
    ~Stack();

    void debug();
};


#endif //JVM_RUNTIME_STACK_H
