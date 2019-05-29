//
// Created by xuranus on 2/7/19.
//

#include "Object.h"
#include "../../util/Console.h"

Object::Object(Class *c)
{
    _class = c;
    data = new Slots(_class->instanceSlotCount);
    dataType = SLOTS;
    dataCount = 1;
}

Object::Object(Class *c, unsigned int count)
{
    _class = c;
    dataCount = count;
    const auto& name = c->name;
    if(name=="[Z") {
        dataType = INT8;
        data = new int8[count];
    } else if(name=="[B") {
        dataType = INT8;
        data = new int8[count];
    } else if(name=="[C") {
        dataType = UINT16;
        data = new uint16[count];
    } else if(name=="[S") {
        dataType = INT16;
        data = new int16[count];
    } else if(name=="[I") {
        dataType = INT32;
        data = new int32[count];
    } else if(name=="[J") {
        dataType = INT64;
        data = new long[count];
    } else if(name=="[F") {
        dataType = FLOAT32;
        data = new float[count];
    } else if(name=="[D") {
        dataType = FLOAT64;
        data = new double[count];
    } else {
        dataType = REF;
        data = new Object*[count];
    }
}

Object::Object(Class *c, void *_data, unsigned long _dataCount, Object::DataType type)
{
    _class = c;
    data = _data;
    dataCount = _dataCount;
    dataType = type;
}

bool Object::isInstanceOf(Class *c)
{
    return c->isAssignableFrom(_class);
}

Slots* Object::getFields()
{
    return (Slots*)data;
}

void Object::setRefVar(std::string name, std::string descriptor, Object *ref)
{
    if(dataType!=SLOTS)
    {
        Console::printlnError("Object data type not slots!");
        exit(1);
    }
    auto field = _class->getField(name,descriptor, false);
    auto slots = (Slots*)data;
    slots->setRef(field->slotId,ref);
}

Object* Object::getRefVar(std::string name, std::string descriptor)
{
    if(dataType!=SLOTS)
    {
        Console::printlnError("Object data type not slots!");
        exit(1);
    }
    auto field = _class->getField(name,descriptor, false);
    auto slots = (Slots*)data;
    return slots->getRef(field->slotId);
}

int8* Object::bytes()
{
    return (int8*)data;
}

int16* Object::shorts()
{
    return (int16 *)data;
}

int32* Object::ints()
{
    return (int32*)data;
}

long* Object::longs()
{
    return (long*)data;
}

uint16* Object::chars()
{
    return (uint16*)data;
}

float* Object::floats()
{
    return (float*)data;
}

double* Object::doubles()
{
    return (double*)data;
}

Object** Object::refs()
{
    return (Object**)data;
}

int Object::arrayLength()
{
    return dataCount;
}

Object::~Object()
{
    switch (dataType)
    {
        case INT8: delete[]((int8*)data);break;
        case INT16: delete[]((int16*)data);break;
        case INT32: delete[]((int32*)data);break;
        case INT64: delete[]((long*)data);break;
        case UINT16: delete[]((uint16*)data);break;
        case FLOAT32: delete[]((float*)data);break;
        case FLOAT64: delete[]((double*)data);break;
        case REF: delete[]((Object**)data);break;
        case SLOTS: delete((Slots*)data);break;
        default:break;
    }
}