//
// Created by XUranus on 2019/2/1.
//

#ifndef JVM_FRAME_H
#define JVM_FRAME_H

#include "heap/Object.h"
#include <string>

struct Thread;


struct LocalVars {
    int capacity;
    Slot* data;

    explicit LocalVars(int _capacity);
    ~LocalVars();

    void setInt(unsigned int index,int val);
    void setLong(unsigned int index,long val);
    void setFloat(unsigned int index,float val);
    void setDouble(unsigned int index,double val);
    void setRef(unsigned int index,Object* ref);
    void setSlot(unsigned int index,Slot slot);


    int getInt(unsigned int index);
    long getLong(unsigned int index);
    float getFloat(unsigned int index);
    double getDouble(unsigned int index);
    Object* getRef(unsigned int index);
    Slot getSlot(unsigned int index);

    void debug();
};

struct OperandStack {
    int capacity;
    int size;
    Slot* data;

    explicit OperandStack(int _capacity);
    ~OperandStack();

    void pushInt(int v);
    int popInt();
    void pushFloat(float v);
    float popFloat();
    void pushLong(long v);
    long popLong();
    void pushDouble(double v);
    double popDouble();
    void pushBoolean(bool v);
    bool popBoolean();
    void pushRef(Object* ref);
    Object* popRef();
    void pushSlot(Slot s);
    Slot popSlot();
    Object* getRefFromTop(unsigned int index);
    std::vector<int32> popAndCheckCounts(unsigned int dimensions);

    void debug();
};

struct Frame {
    LocalVars localVars;
    OperandStack operandStack;

    Frame* lower;
    Thread* thread;
    int nextPc;

    Method* method;
    unsigned int maxLocals;
    unsigned int maxStack;

    Frame(Thread* _thread,unsigned int maxLocalVarsNum,unsigned int operandStackSize);//only for debug use
    explicit Frame(Method* method);
    void branch(int offset);
    void revertNextPc();

    void debug();
};


#endif //JVM_FRAME_H
