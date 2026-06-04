#include "Slots.h"
#include <iostream>
#include <cassert>
#include <cstring>
#include "../common/Exception.h"
#include "heap/ObjectPool.h"

namespace runtime {

    Slots::Slots(u2 size) : data(size) {}

    bool Slots::isRef(int index) const {
        return data[index].ptrFlag;
    }

    int Slots::size() const {
        return static_cast<int>(data.size());
    }

    void Slots::setInt(u2 index, int val) {
        data[index].num = val;
        data[index].ptrFlag = false;
    }

    int Slots::intValue(u2 index) const {
        return static_cast<int>(data[index].num);
    }

    void Slots::setLong(u2 index, long val) {
        data[index].ptrFlag = false;
        data[index + 1].ptrFlag = false;
        data[index].num = static_cast<int>(val);
        data[index + 1].num = static_cast<int>(val >> 32);
    }

    long Slots::longValue(u2 index) const {
        auto low = static_cast<u4>(data[index].num);
        auto high = static_cast<u4>(data[index + 1].num);
        return (static_cast<long>(high) << 32) | static_cast<long>(low);
    }

    void Slots::setFloat(u2 index, float val) {
        int tmp;
        std::memcpy(&tmp, &val, sizeof(float));
        data[index].num = tmp;
        data[index].ptrFlag = false;
    }

    float Slots::floatValue(u2 index) const {
        float val;
        std::memcpy(&val, &data[index].num, sizeof(float));
        return val;
    }

    bool Slots::boolValue(u2 index) const {
        return intValue(index) == 1;
    }

    void Slots::setDouble(u2 index, double val) {
        long tmp;
        std::memcpy(&tmp, &val, sizeof(double));
        setLong(index, tmp);
    }

    double Slots::doubleValue(u2 index) const {
        long t = longValue(index);
        double val;
        std::memcpy(&val, &t, sizeof(double));
        return val;
    }

    void Slots::setRef(u2 index, heap::Object* ref) {
        data[index].ptrFlag = true;
        data[index].num = heap::ObjectPool::compressPtr(ref);
    }

    heap::Object* Slots::refValue(u2 index) const {
        return heap::ObjectPool::decompressPtr(data[index].num);
    }

    void Slots::setSlot(u2 index, Slot val) {
        data[index] = val;
    }

    Slot Slots::slotValue(u2 index) const {
        return data[index];
    }

    Slot& Slots::operator[](u2 index) {
        return data[index];
    }

    const Slot& Slots::operator[](u2 index) const {
        return data[index];
    }

    void Slots::resize(u2 newSize) {
        data.assign(newSize, Slot{});
    }

    void Slots::dump() const {
        std::cout << "{ ";
        for (size_t i = 0; i < data.size(); i++) {
            if (data[i].ptrFlag) {
                if (data[i].num != 0) {
                    std::string objName = heap::ObjectPool::decompressPtr(data[i].num)->klass->name;
                    std::cout << objName << "[" << data[i].num << "]";
                } else {
                    std::cout << "null";
                }
            } else {
                std::cout << data[i].num;
            }
            if (i + 1 != data.size()) {
                std::cout << ", ";
            }
        }
        std::cout << " }" << std::endl;
    }


    SlotsStack::SlotsStack(u2 capacity) : size(0), slots(capacity) {}

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
        long tmp;
        std::memcpy(&tmp, &v, sizeof(double));
        pushLong(tmp);
    }

    double SlotsStack::popDouble() {
        long t = popLong();
        double val;
        std::memcpy(&val, &t, sizeof(double));
        return val;
    }

    void SlotsStack::pushBoolean(bool v) {
        pushInt(v ? 1 : 0);
    }

    bool SlotsStack::popBoolean() {
        return popInt() == 1;
    }

    void SlotsStack::pushRef(heap::Object* ref) {
        slots.setRef(size++, ref);
    }

    heap::Object* SlotsStack::popRef() {
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

    std::vector<heap::Object*> SlotsStack::refs() const {
        std::vector<heap::Object*> objects;
        for (int i = 0; i < size; i++) {
            if (slots.isRef(i)) {
                objects.push_back(slots.refValue(i));
            }
        }
        return objects;
    }
}
