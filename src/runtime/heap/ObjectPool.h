//
// Created by xuranus on 3/13/19.
//

#ifndef JVM_OBJECT_POOL_H
#define JVM_OBJECT_POOL_H

#include "Object.h"
#include "../../basicType.h"
#include <set>

namespace heap {

    enum ObjectDataType: unsigned char;

    class ObjectPool {
    public:
        static Object* pool;
        static bool* mark;
        static int capacity;
        static int size;
        static bool inited;

    public:
        static void init();
        static u4 compressPtr(Object* obj);
        static Object* decompressPtr(u4 ptr);
        static int findSpace();

        static Object* createObject(); // for test only
        static Object* createObject(Class* klass); // create common object
        static Object* createObject(Class* klass, int length); // create array object
        static Object* createObject(Class *c, void *_data, int _dataCount, ObjectDataType type); // create object using specific data

        static Object* cloneObject(Object* object);
        static Object* writeObjectToHeap(Object object); // side effect! this will deprecate object

        static bool needGC();
        static void DFSMarkOop(heap::Object* object);
        static void reachableAnalysisGC(std::set<heap::Object*>& GCRoots);
    };

}

#endif //JVM_OBJECT_POOL_H
