//
// Created by xuranus on 2/7/19.
//

#include "Object.h"
#include <cassert>
#include <cstring>

namespace heap {

    Object::Object() {
        markedOop = 0;
        klass = nullptr;
        data = nullptr;
        dataType = ObjectDataType::Common;
        arrLength = 114514; // useless, not array
    }

    Object::Object(Class *c) {
        markedOop = 0;
        klass = c;
//        if(c->name == "java/lang/Class") {
//            // todo:: try to calculate instance slot correctly
//            //assert(klass->instanceSlotCount == 12);
//            data = new runtime::Slots(12);
//        } else {
//            data = new runtime::Slots(klass->instanceSlotCount);
//        }
        data = new runtime::Slots(klass->instanceSlotCount);
        dataType = ObjectDataType::Common;
        arrLength = klass->instanceSlotCount; // useless, not array
    }

    Object::Object(Class *c, unsigned int length) {
        assert(c->isArray());
        markedOop = 0;
        klass = c;
        arrLength = length;

        const std::string &klassName = klass->name;
        if (klassName == "[Z") { // boolean
            dataType = ObjectDataType::BoolArray;
            data = new char [length];
            memset(data, 0, sizeof (char ) * length);
        } else if (klassName == "[B") {
            dataType = ObjectDataType::ByteArray;
            data = new char [length];
            memset(data, 0, sizeof (char ) * length);
        } else if (klassName == "[C") {
            dataType = ObjectDataType::CharArray;
            data = new short [length];
            memset(data, 0, sizeof (short ) * length);
        } else if (klassName == "[S") {
            dataType = ObjectDataType::ShortArray;
            data = new short [length];
            memset(data, 0, sizeof (short ) * length);
        } else if (klassName == "[I") {
            dataType = ObjectDataType::IntArray;
            data = new int [length];
            memset(data, 0, sizeof (int ) * length);
        } else if (klassName == "[J") {
            dataType = ObjectDataType::LongArray;
            data = new long [length];
            memset(data, 0, sizeof (long ) * length);
        } else if (klassName == "[F") {
            dataType = ObjectDataType::FloatArray;
            data = new float [length];
            memset(data, 0, sizeof (float ) * length);
        } else if (klassName == "[D") {
            dataType = ObjectDataType::DoubleArray;
            data = new double [length];
            memset(data, 0, sizeof (double ) * length);
        } else {
            dataType = ObjectDataType::ObjectRefArray;
            data = new Object*[length];
            memset(data, 0, sizeof (Object * ) * length);
        }
    }

    Object::Object(Class *c, void *_data, int _dataCount, ObjectDataType type) {
        markedOop = 0;
        klass = c;
        data = _data;
        arrLength = _dataCount;
        dataType = type;
    }

    Object::Object(Object &object) {
        markedOop = 0;
        klass = object.klass;
        arrLength = object.arrLength;
        data = object.data;
        dataType = object.dataType;

        // this copy construct will disable origin object instance
        object.data = nullptr;
        object.klass = nullptr;
    }

    Object &Object::operator=(Object &object) {
        // take the ownership of data of object
        if (&object != this) {
            markedOop = object.markedOop;
            klass = object.klass;
            arrLength = object.arrLength;
            data = object.data;
            dataType = object.dataType;

            // this copy construct will disable origin object instance
            object.data = nullptr;
            object.klass = nullptr;
        }
        return *this;
    }

    Object::~Object() {
        switch (dataType) {
            case ObjectDataType::BoolArray:
            case ObjectDataType::ByteArray: { delete[]((char *) data); break;}
            case ObjectDataType::ShortArray:
            case ObjectDataType::CharArray: { delete[]((short *) data); break;}
            case ObjectDataType::IntArray: { delete[]((int *) data); break;}
            case ObjectDataType::FloatArray: { delete[]((float *) data); break;}
            case ObjectDataType::LongArray: { delete[]((long *) data); break;}
            case ObjectDataType::DoubleArray: { delete[]((double *) data); break;}
            case ObjectDataType::ObjectRefArray: { delete[]((Object **) data); break;}
            case ObjectDataType::Common: { delete ((runtime::Slots *) data); break;}
            default: assert(true);
        }
    }



    bool Object::instanceOf(Class *c) const {
        return c->isAssignableFrom(klass);
    }


    runtime::Slots *Object::fields() const {
        assert(dataType == ObjectDataType::Common);
        return (runtime::Slots *) data;
    }


    void Object::setRefVar(const std::string &name, const std::string &descriptor, Object *val) const {
        assert(dataType == ObjectDataType::Common);
        Field* field = klass->getField(name, descriptor, false);
        assert(field != nullptr);
        ((runtime::Slots *) data)->setRef(field->slotId, val);
    }

    void Object::setIntVar(const std::string &name, const std::string &descriptor, int val) const {
        assert(dataType == ObjectDataType::Common);
        Field* field = klass->getField(name, descriptor, false);
        assert(field != nullptr);
        ((runtime::Slots *) data)->setInt(field->slotId, val);
    }

    Object *Object::getRefVar(const std::string &name, const std::string &descriptor) const {
        assert(dataType == ObjectDataType::Common);
        Field* field = klass->getField(name, descriptor, false);
        assert(field != nullptr);
        return ((runtime::Slots *) data)->refValue(field->slotId);
    }

    int Object::getIntVar(const std::string& name, const std::string& descriptor) const {
        assert(dataType == ObjectDataType::Common);
        assert(descriptor == "I");
        Field* field = klass->getField(name, descriptor, false);
        assert(field != nullptr);
        return ((runtime::Slots *) data)->intValue(field->slotId);
    }


    char *Object::byteArray() const {
        assert(dataType == ObjectDataType::ByteArray);
        return (int8 *) data;
    }

    short *Object::shortArray() const {
        assert(dataType == ObjectDataType::ShortArray);
        return (int16 *) data;
    }

    int *Object::intArray() const {
        assert(dataType == ObjectDataType::IntArray);
        return (int32 *) data;
    }

    long *Object::longArray() const {
        assert(dataType == ObjectDataType::LongArray);
        return (long *) data;
    }

    short *Object::charArray() const {
        assert(dataType == ObjectDataType::CharArray);
        return (short *) data;
    }

    float *Object::floatArray() const {
        assert(dataType == ObjectDataType::FloatArray);
        return (float *) data;
    }

    double *Object::doubleArray() const {
        assert(dataType == ObjectDataType::DoubleArray);
        return (double *) data;
    }

    Object** Object::objectRefArray() const {
        assert(dataType == ObjectDataType::ObjectRefArray);
        return (Object **) data;
    }

    int Object::arrayLength() const {
        assert(dataType != ObjectDataType::Common);
        return (int)arrLength;
    }


}