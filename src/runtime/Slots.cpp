//
// Created by xuranus on 2/12/19.
//
#include "Slots.h"
#include <cstring>
#include <iostream>
#include <cassert>
#include "../common/Exception.h"
#include "heap/ObjectPool.h"

namespace runtime {
    Slots::Slots(u2 _size_) : _size(_size_) {
        data = new Slot [_size];
        memset(data, 0, sizeof(Slot) * _size);
    }

    Slots::Slots(const Slots &slots) : _size(slots._size) {
        data = new Slot [slots._size];
        memcpy(data, slots.data, sizeof(Slot) * slots._size);
    }

    Slots::~Slots() {
        delete[] data;
    }

    bool Slots::isRef(int index) const {
        return data[index].ptrFlag;
    }

    int Slots::size() const {
        return _size;
    }


    void Slots::setInt(u2 index, int val) {
        data[index].num = val;
        data[index].ptrFlag = false;
    }

    int Slots::intValue(u2 index) const {
        return (int)data[index].num;
    }

    void Slots::setLong(u2 index, long val) {
        data[index].ptrFlag = false;
        data[index + 1].ptrFlag = false;
        data[index].num = (int) (val);
        data[index + 1].num = (int) (val >> 32);
    }

    long Slots::longValue(u2 index) const {
        auto low = (u4) data[index].num;
        auto high = (u4) data[index + 1].num;
        return (long) high << 32 | (long) low;
    }

    void Slots::setFloat(u2 index, float val) {
        data[index].num = *(int *) (&val);
        data[index].ptrFlag = false;
    }

    float Slots::floatValue(u2 index) const {
        return *(float *) (&data[index].num);
    }

    bool Slots::boolValue(u2 index) const {
        return intValue(index) == 1;
    }

    void Slots::setDouble(u2 index, double val) {
        setLong(index, *(long *) (&val));
    }

    double Slots::doubleValue(u2 index) const {
        long t = longValue(index);
        return *(double *) (&t);
    }

    void Slots::setRef(u2 index, heap::Object* ref) {
        data[index].ptrFlag = true;
        data[index].num = heap::ObjectPool::compressPtr(ref);
    }

    heap::Object* Slots::refValue(u2 index) const {
        heap::Object* ref = heap::ObjectPool::decompressPtr(data[index].num);
        return ref;
    }

    void Slots::setSlot(u2 index, Slot val) {
        data[index] = val;
    }

    Slot Slots::slotValue(u2 index) const {
        return data[index];
    }

    Slot& Slots::operator[](u2 index) const {
        return data[index];
    }

    Slots &Slots::operator=(const Slots &slots) {
        if(this != &slots) {
            _size = slots._size;
            delete[] data;
            data = new Slot[_size];
            memcpy(data, slots.data, sizeof(Slot) * _size);
        }
        return *this;
    }

    void Slots::resize(u2 newSize) {
        _size = newSize;
        delete[] data;
        data = new Slot [newSize];
        memset(data, 0, sizeof(Slot) * newSize);
    }

    void Slots::dump() const {
        std::cout << "{ ";
        for(int i = 0; i < _size; i++) {
            if(data[i].ptrFlag) {
                std::string objName = "obj";
                if(data[i].num != 0) {
                    objName = heap::ObjectPool::decompressPtr(data[i].num)->klass->name;
                    std::cout << objName << "[" <<data[i].num << "]";
                } else {
                    std::cout << "null";
                }

            } else {
                std::cout << data[i].num;
            }
            if(i != _size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " }" << std::endl;
    }




    SlotsStack::SlotsStack(u2 _capacity) :
        slots(_capacity) {
        size = 0;
    }

    void SlotsStack::pushInt(int v) {
        slots.setInt(size++, v);
    }

    int SlotsStack::popInt() {
        return slots.intValue(--size);
    }

    void SlotsStack::pushLong(long v) {
        slots.setLong(size, v);
        size += 2;
    }

    long SlotsStack::popLong() {
        size -= 2;
        return slots.longValue(size);
    }

    void SlotsStack::pushFloat(float v) {
        slots.setFloat(size++, v);
    }

    float SlotsStack::popFloat() {
        return slots.floatValue(--size);
    }

    void SlotsStack::pushDouble(double v) {
        pushLong(*(long *) (&v));
    }

    double SlotsStack::popDouble() {
        long t = popLong();
        return *(double *) (&t);
    }

    void SlotsStack::pushBoolean(bool v) {
        pushInt(v ? 1: 0);
    }

    bool SlotsStack::popBoolean() {
        return popInt() == 1;
    }

    void SlotsStack::pushRef(heap::Object *ref) {
        slots.setRef(size++, ref);
    }

    heap::Object *SlotsStack::popRef() {
        return slots.refValue(--size);
    }

    void SlotsStack::pushSlot(Slot v) {
        slots.setSlot(size++, v);
    }

    Slot SlotsStack::popSlot() {
        return slots.slotValue(--size);
    }

    void SlotsStack::clear() {
        size = 0;
    }

    heap::Object* SlotsStack::getRefFromTop(u2 n) {
        assert(size - n - 1 >= 0);
        return slots.refValue(size - n - 1);
    }

    std::vector<int> SlotsStack::popAndCheckCounts(u2 nDimension) {
        std::vector<int> dimensions(nDimension);
        for (int i = nDimension - 1; i >= 0; i--) {
            dimensions[i] = popInt();
            if (dimensions[i] < 0) {
                exception::fatal("java.lang.NegativeArraySizeException");
            }
        }
        return dimensions;
    }

    void SlotsStack::dump() const {
        std::cout << "(" << size << ") ";
        slots.dump();
    }

    std::vector<heap::Object *> SlotsStack::refs() const {
        std::vector<heap::Object*> objects;
        for(int i = 0; i < size; i++) {
            if(slots.isRef(i)) {
                objects.push_back(slots.refValue(i));
            }
        }
        return objects;
    }
}

