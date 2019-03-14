//
// Created by xuranus on 3/13/19.
//

#ifndef JVM_OBJECTPOOL_H
#define JVM_OBJECTPOOL_H

#include "Object.h"
#include <vector>
//ready to work for GC

class ObjectPool {
public:
    static ObjectPool* instance;

private:
    std::vector<Object*> objs;

public:
    static ObjectPool* getObjectPool();
    void add(Object* obj);
    void deleteObject(Object* obj);
    unsigned long objectNum();
    void debug();

private:
    ObjectPool();
};


#endif //JVM_OBJECTPOOL_H
