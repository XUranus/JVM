//
// Created by xuranus on 3/13/19.
//

#include <cstring>
#include <cassert>
#include <set>
#include "../../common/Console.h"
#include "../../common/Exception.h"
#include "ObjectPool.h"

const int MAX_OBJECTS = 4096 * 8; // heap default: 128KB * 8 = 1MB, sizeof(Object) = 2^5 B

namespace heap {

    Object *ObjectPool::pool;
    bool *ObjectPool::mark;
    int ObjectPool::size;
    int ObjectPool::capacity;
    bool ObjectPool::inited = false;

    void ObjectPool::init() {
        if(!ObjectPool::inited) {
            ObjectPool::inited = true;
            ObjectPool::capacity = MAX_OBJECTS;
            ObjectPool::pool = new Object[MAX_OBJECTS];
            ObjectPool::mark = new bool[MAX_OBJECTS];
            ObjectPool::size = 1; // pool[0] reserved as nullptr

            memset(ObjectPool::mark, 0, sizeof(bool) * ObjectPool::capacity);
            mark[0] = true; // pool[0] reserved as nullptr
        }
    }

    u4 ObjectPool::compressPtr(Object *obj) {
        if(obj == nullptr) {
            return 0;
        }
        //auto compressed = (unsigned int) (((unsigned long) obj - (unsigned long) ObjectPool::pool) >> 3);
        auto compressed = (unsigned int) (((unsigned long) obj - (unsigned long) ObjectPool::pool) / sizeof(Object));
        assert(compressed < ObjectPool::capacity);
        return compressed;
    }

    Object *ObjectPool::decompressPtr(u4 index) {
        if(index == 0) {
            return nullptr;
        }
        //return (heap::Object *) ((((unsigned long) ptr) << 3) + (unsigned long) ObjectPool::pool);
        assert(index < ObjectPool::capacity);
        return (heap::Object *) ((((unsigned long) index) * sizeof(Object)) + (unsigned long) ObjectPool::pool);
    }

    int ObjectPool::findSpace() {
        for (int i = 1; i <  ObjectPool::capacity ; i++) {
            if (!mark[i]) {
                ObjectPool::mark[i] = true;
                ObjectPool::size++;
                return i;
            }
        }
        return -1;
    }

    Object *ObjectPool::createObject() {
        return writeObjectToHeap(Object());
    }

    Object *ObjectPool::createObject(Class *klass) {
        return writeObjectToHeap(Object(klass));
    }

    Object *ObjectPool::createObject(Class *klass, int length) {
        return writeObjectToHeap(Object(klass, length));
    }

    Object *ObjectPool::createObject(Class *klass, void *data, int length, ObjectDataType type) {
        return writeObjectToHeap(Object(klass, data, length, type));
    }

    Object *ObjectPool::cloneObject(Object *object) {
        Object cloned;
        cloned.klass = object->klass;
        cloned.dataType = object->dataType;
        cloned.arrLength = object->arrLength;
        cloned.data = nullptr; // init
        unsigned int arrLength = object->arrLength;
        switch (object->dataType) {
            // 1 byte
            case ObjectDataType::BoolArray:
            case ObjectDataType::ByteArray: {
                cloned.data = new char[arrLength];
                memcpy(cloned.data, object->data, sizeof(char ) * arrLength);
                break;
            }
            // 2 byte
            case ObjectDataType::ShortArray:
            case ObjectDataType::CharArray: {
                cloned.data = new short[arrLength];
                memcpy(cloned.data, object->data, sizeof(short) * arrLength);
                break;
            }
            // 4 byte
            case ObjectDataType::IntArray: {
                cloned.data = new int [arrLength];
                memcpy(cloned.data, object->data, sizeof(int ) * arrLength);
                break;
            }
            case ObjectDataType::FloatArray: {
                cloned.data = new float [arrLength];
                memcpy(cloned.data, object->data, sizeof(float ) * arrLength);
                break;
            }
            // 8 byte
            case ObjectDataType::LongArray: {
                cloned.data = new long [arrLength];
                memcpy(cloned.data, object->data, sizeof(long ) * arrLength);
                break;
            }
            case ObjectDataType::DoubleArray: {
                cloned.data = new double [arrLength];
                memcpy(cloned.data, object->data, sizeof(double ) * arrLength);
                break;
            }
            case ObjectDataType::ObjectRefArray: {
                cloned.data = new void *[arrLength];
                memcpy(cloned.data, object->data, sizeof(heap::Object* ) * arrLength);
                break;
            }
            // common slots
            case ObjectDataType::Common: {
                cloned.data = new runtime::Slots(*((runtime::Slots*)(object->data)));
                break;
            }
            default: {
                exception::fatal("unknown object data type: " + std::to_string(object->dataType));
            }
        }
        return writeObjectToHeap(cloned);
    }

    Object *ObjectPool::writeObjectToHeap(Object object) {
        int index = findSpace();
        assert(index > 0 && index < ObjectPool::capacity);
        ObjectPool::pool[index] = object; // ObjectPool::pool[index] take ownership of data of object
        return ObjectPool::pool + index;
    }


    bool ObjectPool::needGC() {
        return ObjectPool::size + 256 > ObjectPool::capacity;
    }


    void ObjectPool::DFSMarkOop(heap::Object * object) {
        // mark root
        if(object == nullptr) {
            return;
        }

        object->markedOop = 1;

        if(object->dataType == ObjectDataType::ObjectRefArray) {
            // object array
            Object** array = object->objectRefArray();
            if(array == nullptr) {
                return;
            }
            for(int i = 0; i < object->arrayLength(); i++) {
                if(!array[i]->markedOop) {
                    ObjectPool::DFSMarkOop(array[i]);
                }
            }
        } else if(object->dataType == ObjectDataType::Common) {
            // common object
            runtime::Slots* slots = object->fields();
            if(slots == nullptr) {
                return;
            }
            for(int i = 0; i < slots->size(); i++) {
                if(slots->isRef(i) && !slots->refValue(i)->markedOop) {
                    DFSMarkOop(slots->refValue(i));
                }
            }
        }
    }

    void ObjectPool::reachableAnalysisGC(std::set<heap::Object *>& GCRoots) {
        Console::printlnGreen("GC triggered");

        // 1. init all markedOop to 0
        for(int i = 1; i < ObjectPool::size; i++) {
            Object* object = ObjectPool::pool + i;
            object->markedOop = 0;
        }

        // 2. DFS mark
        for(auto GCRoot: GCRoots) {
            ObjectPool::DFSMarkOop(GCRoot);
        }

        // 3. start clean
        int counter = 0;
        for(int i = 1; i < ObjectPool::size; i++) {
            Object* object = ObjectPool::pool + i;

            if(ObjectPool::mark[i]) {
                if(!object->markedOop) {

                    // you need delete this manually, do not use delete macro
                    void* data = object->data;
                    switch (object->dataType) {
                        case ObjectDataType::BoolArray:
                        case ObjectDataType::ByteArray: { delete[]((char *) data); break;}
                        case ObjectDataType::ShortArray:
                        case ObjectDataType::CharArray: { delete[]((short *) data); break;}
                        case ObjectDataType::IntArray: { delete[]((int *) data); break;}
                        case ObjectDataType::LongArray: { delete[]((long *) data); break;}
                        case ObjectDataType::FloatArray: { delete[]((float *) data); break;}
                        case ObjectDataType::DoubleArray: { delete[]((double *) data); break;}
                        case ObjectDataType::ObjectRefArray: { delete[]((Object **) data); break;}
                        case ObjectDataType::Common: { delete ((runtime::Slots *) data); break;}
                        default:break;
                    }

                    ObjectPool::size--;
                    ObjectPool::mark[i] = false;
                    counter++;

                    //Console::printlnGreen("GC finalized 1 object: " + object->klass->name);
                }
            }
        }
        Console::printlnGreen("this batch cleaned " + std::to_string(counter) + " objects, pool space left: " + std::to_string(ObjectPool::capacity - ObjectPool::size));

    }

}