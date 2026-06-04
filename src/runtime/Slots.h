#pragma once

#include "basicType.h"
#include <vector>

namespace heap { class Object; }

namespace runtime {

    struct Slot {
        u4 num = 0;
        bool ptrFlag = false;
    };

    class Slots {
    private:
        std::vector<Slot> data;

    public:
        explicit Slots(u2 size);

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

        Slot& operator[](u2 index);
        const Slot& operator[](u2 index) const;
        void resize(u2 newSize);
        void dump() const;
    };

    class SlotsStack {
    private:
        u2 size;
        Slots slots;

    public:
        explicit SlotsStack(u2 capacity);

        void pushInt(int v);
        int popInt();
        void pushLong(long v);
        long popLong();
        void pushFloat(float v);
        float popFloat();
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
