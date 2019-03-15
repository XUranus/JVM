//
// Created by XUranus on 2019/2/1.
//

#include "Frame.h"
#include "Thread.h"
#include <cstdio>
#include "Slot.h"
#include "../util/Console.h"

/*****************************************  LocalVars  ********************************************************/

LocalVars::LocalVars(int _capacity)
{
    capacity = _capacity;
    data = new Slot[capacity];
}

LocalVars::~LocalVars()
{
    delete[] data;
}

void LocalVars::setInt(unsigned int index, int val)
{
    data[index].type = Slot::Type::NUM;
    data[index].num = val;
}

int LocalVars::getInt(unsigned int index)
{
    return data[index].num;
}

void LocalVars::setLong(unsigned int index, long val)
{
    data[index].type = Slot::Type::NUM;
    data[index+1].type = Slot::Type::NUM;
    data[index].num = (int)(val);
    data[index+1].num = (int)(val >> 32);
}

long LocalVars::getLong(unsigned int index)
{
    auto low = (unsigned int)data[index].num;
    auto high = (unsigned int)data[index+1].num;
    return (long)high << 32 | (long)low;
}

void LocalVars::setFloat(unsigned int index, float val)
{
    data[index].type = Slot::Type::NUM;
    data[index].num = *(int*)(&val);
}

float LocalVars::getFloat(unsigned int index)
{
    return *(float*)(&data[index].num);
}

void LocalVars::setDouble(unsigned int index, double val)
{
    setLong(index,*(long*)(&val));
}

double LocalVars::getDouble(unsigned int index)
{
    long t = getLong(index);
    return *(double *)(&t);
}

void LocalVars::setRef(unsigned int index, Object *ref)
{
    data[index].type = Slot::Type::REF;
    data[index].ref = ref;
}

Object* LocalVars::getRef(unsigned int index)
{
    return data[index].ref;
}

Slot LocalVars::getSlot(unsigned int index)
{
    return data[index];
}

void LocalVars::setSlot(unsigned int index, Slot slot)
{
    data[index].type = slot.type;
    data[index] = slot;
}

void LocalVars::debug()
{
    printf("[Debug LocalVars] ");
    for(auto i=0;i<capacity;i++) {
        if(data[i].type==Slot::Type::REF)
            printf("(%d)[0x%lx] ",i,(unsigned long)data[i].ref);
        if(data[i].type==Slot::Type::NUM)
            printf("(%d)[%d] ",i,data[i].num);
        if(data[i].type==Slot::Type::UNINITIALIZED)
            printf("(%d)[] ",i);
        if(data[i].type==Slot::Type::SLOT)
            printf("(%d)[SLOT] ",i);
    }
    printf("\n");
}

/*********************************************  OperandStack ******************************************************/
OperandStack::OperandStack(int _capacity)
{
    capacity = _capacity;
    size = 0;
    data = new Slot[capacity];
}

OperandStack::~OperandStack() {
    //TODO::cause double free error
    //delete[] data;
}

void OperandStack::pushInt(int v)
{
    data[size].type = Slot::Type::NUM;
    data[size].num = v;
    size++;
}

int OperandStack::popInt()
{
    size--;
    int ret = data[size].num;
    data[size].clear();
    return ret;
}

void OperandStack::pushLong(long v)
{
    data[size].type = Slot::Type::NUM;
    data[size+1].type = Slot::Type::NUM;
    data[size].num = (int)(v);
    data[size+1].num = (int)(v >> 32);
    size += 2;
}

long OperandStack::popLong()
{
    size -= 2;
    auto low = (unsigned int)data[size].num;
    auto high = (unsigned int)data[size+1].num;
    long ret = (long)high << 32 | (long)low;
    data[size].clear();
    data[size+1].clear();
    return ret;
}

void OperandStack::pushFloat(float v)
{
    data[size].type = Slot::Type::NUM;
    data[size].num = *(int*)(&v);
    size++;
}

float OperandStack::popFloat()
{
    size--;
    float ret = *(float*)(&data[size].num);
    data[size].clear();
    return ret;
}

void OperandStack::pushDouble(double v)
{
    pushLong(*(long*)(&v));
}

double OperandStack::popDouble()
{
    long t = popLong();
    return *(double*)(&t);
}

void OperandStack::pushRef(Object *ref)
{
    data[size].type = Slot::Type::REF;
    data[size].ref = ref;
    size++;
}

Object* OperandStack::popRef()
{
    size--;
    Object* ret = data[size].ref;
    data[size].clear();
    return ret;
}

void OperandStack::pushSlot(Slot s)
{
    data[size].type = s.type;
    data[size] = s;
    size++;
}

Slot OperandStack::popSlot()
{
    size--;
    Slot ret = data[size];
    data[size].clear();
    return ret;
}

Object* OperandStack::getRefFromTop(unsigned int n)
{
    //Console::printlnWarning("getRefFromTop() "+std::to_string(n) + " "+std::to_string(capacity));
    int index = size-n-1;
    if(index<0) {
        Console::printlnError("getRefFromTop() index negative error");
        return nullptr;
    }
    return data[index].ref;
}

std::vector<int32> OperandStack::popAndCheckCounts(unsigned int dimensions)
{
    std::vector<int32> counts(dimensions);
    for(long i=dimensions-1;i>=0;i--)
    {
        counts[i] = popInt();
        if(counts[i]<0)
        {
            Console::printlnException("java.lang.NegativeArraySizeException");
            exit(1);
        }
    }
    return counts;
}

void OperandStack::debug() {
    printf("[Debug OperandStack](size=%d) ",size);
    for(auto i=0;i<capacity;i++) {
        if(data[i].type==Slot::Type::REF)
            printf("(%d)[0x%lx] ",i,(unsigned long)data[i].ref);
        if(data[i].type==Slot::Type::NUM)
            printf("(%d)[%d] ",i,data[i].num);
        if(data[i].type==Slot::Type::UNINITIALIZED)
            printf("(%d)[] ",i);
        if(data[i].type==Slot::Type::SLOT)
            printf("(%d)[SLOT] ",i);
    }
    printf("\n");
}

/************************************************ Frame   *********************************************************/

Frame::Frame(Thread *_thread, unsigned int maxLocalVarsNum, unsigned int operandStackSize):
    localVars(maxLocalVarsNum),operandStack(operandStackSize) {
    lower = nullptr;
    thread = _thread;
    nextPc = 0;
    maxStack = operandStackSize;
    maxLocals = maxLocalVarsNum;
    method = nullptr;
}

Frame::Frame( Method *_method):
    localVars(_method->maxLocals),operandStack(_method->maxStack) {
    lower = nullptr;
    method = _method;
    thread = nullptr;
    nextPc = 0;
    maxStack = _method->maxStack;
    maxLocals = _method->maxLocals;

}

void Frame::branch(int offset)
{
    nextPc = thread->pc + offset;
}

void Frame::revertNextPc()
{
    nextPc = thread->pc;
}

void Frame::debug()
{
    printf("[Debug Frame]\n");
    printf("nextPc:%d\n",nextPc);
    localVars.debug();
    operandStack.debug();
    method->debug();
}