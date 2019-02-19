//
// Created by XUranus on 2019/2/1.
//

#include "Thread.h"
#include "../util/Console.h"

Thread::Thread(int stackSize):stack(stackSize)
{
    pc = 0;
}

Frame* Thread::currentFrame()
{
    return stack.top();
}

Frame* Thread::popFrame()
{
    return stack.pop();
}

void Thread::pushFrame(Frame *frame)
{
    frame->thread = this;
    stack.push(frame);
}

bool Thread::stackEmpty()
{
    return stack.empty();
}

void Thread::debug()
{
    printf("[Debug Thread]\n");
    printf("pc:%d\n",pc);
    stack.debug();
}

void Thread::initClass(Class *_class)
{
    Console::printlnWarning("initClass() "+_class->name);
    _class->initStarted = true;
    scheduleClinit(_class);
    initSuperClass(_class);
}


void Thread::scheduleClinit(Class *_class)
{
    Console::printlnWarning("scheduleClinit() "+_class->name);
    auto clinit = _class->getClinitMethod();
    if(clinit != nullptr)
    {
        pushFrame(new Frame(clinit));
    }
}

void Thread::initSuperClass(Class *_class)
{
    Console::printlnWarning("initSuperClass() "+_class->name);
    if(!(_class->accessFlags & ACC_INTERFACE_FLAG))
    {
        auto superClass = _class->superClass;
        if(superClass != nullptr && !superClass->initStarted)
            initClass(superClass);
    }
}