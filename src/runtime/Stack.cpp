//
// Created by XUranus on 2019/2/1.
//

#include "Stack.h"
#include <cstdio>
#include <cstdlib>
#include "../util/Console.h"


Stack::Stack(int _capacity)
{
    capacity = _capacity;
    size = 0;
    _top = nullptr;
}

Stack::~Stack()
{
    std::vector<Frame*> ptrCollect;
    for(auto p = _top; p!= nullptr; p = p->lower)
        ptrCollect.push_back(p);
    for(auto ptr:ptrCollect)
        delete ptr;
}

void Stack::push(Frame* frame)
{
    if(size >= capacity) {
        Console::printlnError("java.lang.StackOverFlowError");
        exit(1);
    }
    if(_top!= nullptr) {
        frame->lower = _top;
    }//?
    _top = frame;
    size++;
}

Frame* Stack::pop()
{
    if(_top == nullptr)
    {
        Console::printlnWarning("JVM Stack Empty");
        return nullptr;
    }
    auto ret = _top;
    _top = _top->lower;
    size--;
    return ret;
}

Frame* Stack::top() {
    return _top;
}

bool Stack::empty()
{
    return top() == nullptr;
}

void Stack::debug()
{
    printf("[Debug Stack]\n");
    printf("capacity:%d\n",capacity);
    printf("size:%d\n",size);
    for(auto p = _top;p!=nullptr;p=p->lower)
        p->debug();
}

