//
// Created by xuranus on 2/12/19.
//

#ifndef JVM_SLOT_H
#define JVM_SLOT_H

struct Object;

struct Slot { //TODO::try union later
    int num;
    Object* ref;

    Slot();
};

struct Slots {
    int capacity;
    Slot* data;

    explicit Slots(int _capacity);
    ~Slots();
    void setInt(unsigned int index,int val);
    void setLong(unsigned int index,long val);
    void setFloat(unsigned int index,float val);
    void setDouble(unsigned int index,double val);
    void setRef(unsigned int index,Object* ref);
    void setSlot(unsigned int index,Slot slot);

    Slot getSlot(unsigned int index);
    int getInt(unsigned int index);
    long getLong(unsigned int index);
    float getFloat(unsigned int index);
    double getDouble(unsigned int index);
    Object* getRef(unsigned int index);

    void debug();
};

#endif //JVM_SLOT_H
