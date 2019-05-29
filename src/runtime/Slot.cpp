//
// Created by xuranus on 2/12/19.
//
#include "../util/Console.h"
#include "Slot.h"
#include <cstdio>

Slot::Slot() {
    num = 0;
    ref = nullptr;
    type = UNINITIALIZED;
}

bool Slot::isRef() {
    return type==REF;
}

void Slot::clear() {
    num = 0;
    ref = nullptr;
    type = UNINITIALIZED;
}

/*------------------------------------------------------------------------*/

Slots::Slots(int _capacity)
{
    capacity = _capacity;
    data = new Slot[capacity];
}

Slots::~Slots()
{
    delete data;
}

void Slots::setInt(unsigned int index, int val)
{
    data[index].type = Slot::Type::NUM;
    data[index].num = val;
}

int Slots::getInt(unsigned int index)
{
    return data[index].num;
}

void Slots::setLong(unsigned int index, long val)
{
    data[index].type = Slot::Type::NUM;
    data[index].num = (int)(val);
    data[index+1].num = (int)(val >> 32);
}

long Slots::getLong(unsigned int index)
{
    auto low = (unsigned int)data[index].num;
    auto high = (unsigned int)data[index+1].num;
    return (long)high << 32 | (long)low;
}

void Slots::setFloat(unsigned int index, float val)
{
    data[index].type = Slot::Type::NUM;
    data[index].num = *(int*)(&val);
}

float Slots::getFloat(unsigned int index)
{
    return *(float*)(&data[index].num);
}

void Slots::setDouble(unsigned int index, double val)
{
    data[index].type = Slot::Type::NUM;
    setLong(index,*(long*)(&val));
}

double Slots::getDouble(unsigned int index)
{
    long t = getLong(index);
    return *(double *)(&t);
}

void Slots::setRef(unsigned int index, Object *ref)
{
    data[index].type = Slot::Type::REF;
    data[index].ref = ref;
}

Object* Slots::getRef(unsigned int index)
{
    return data[index].ref;
}

Slot Slots::getSlot(unsigned int index)
{
    return data[index];
}

void Slots::setSlot(unsigned int index, Slot slot)
{
    data[index].type = Slot::Type::SLOT;
    data[index] = slot;
}

void Slots::debug()
{
    printf("Slots: ");
    for(auto i=0;i<capacity;i++) {
        printf("[%d]<0x%08x,0x%08x> ",i,data[i].num,data[i].ref);
    }
    printf("\n");
}