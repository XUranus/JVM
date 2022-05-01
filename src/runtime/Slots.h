//
// Created by xuranus on 2/12/19.
//

#ifndef JVM_RUNTIME_SLOT_H
#define JVM_RUNTIME_SLOT_H

#include "../../src/basicType.h"
#include <vector>
//#include "heap/Object.h"

namespace heap {class Object;}

namespace runtime {

    //typedef u4 Slot;
    struct Slot {
        u4 num;
        bool ptrFlag;
    };

    class Slots {
    private:
        u2 _size;
        Slot *data;

    public:
        explicit Slots(u2 _size);
        Slots(const Slots &slots);
        ~Slots();

        bool isRef(int index) const;
        int size() const;

        void setInt(u2 index, int val);
        void setLong(u2 index, long val);
        void setFloat(u2 index, float val);
        void setDouble(u2 index, double val);
        void setRef(u2 index, heap::Object* ref);
        void setSlot(u2 index, Slot val);

        [[nodiscard]] int intValue(u2 index) const;
        [[nodiscard]] long longValue(u2 index) const;
        [[nodiscard]] bool boolValue(u2 index) const;
        [[nodiscard]] float floatValue(u2 index) const;
        [[nodiscard]] double doubleValue(u2 index) const;
        [[nodiscard]] heap::Object* refValue(u2 index) const;
        [[nodiscard]] Slot slotValue(u2 index) const;

        Slot& operator[] (u2 index) const;
        Slots& operator=(const Slots& slots);
        void resize(u2 _size);
        void dump() const;
    };


    class SlotsStack {
    private:
        u2 size;
        Slots slots;

    public:
        explicit SlotsStack(u2 _capacity);;

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
        void pushRef(heap::Object* ref);
        heap::Object* popRef();
        void pushSlot(Slot v);
        Slot popSlot();

        void clear();
        heap::Object* getRefFromTop(u2 index);
        std::vector<int> popAndCheckCounts(u2 nDimension);

        void dump() const;
        std::vector<heap::Object*> refs() const;
    };

}

#endif //JVM_RUNTIME_SLOT_H
