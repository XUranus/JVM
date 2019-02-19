//
// Created by XUranus on 2019/2/1.
//

#ifndef JVM_THREAD_H
#define JVM_THREAD_H

#include "Stack.h"
//#include "Frame.h"


struct Thread {
    int pc;
    Stack stack;

    Thread(int stackSize);
    void pushFrame(Frame* frame);
    Frame* popFrame();
    Frame* currentFrame();
    bool stackEmpty();

    void initClass(Class* _class);
    void initSuperClass(Class* _class);
    void scheduleClinit(Class* _class);

    void debug();
};


#endif //JVM_THREAD_H
