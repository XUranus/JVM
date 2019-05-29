//
// Created by xuranus on 3/13/19.
//

#include "ObjectPool.h"

ObjectPool* ObjectPool::instance = nullptr;

ObjectPool* ObjectPool::getObjectPool() {
    if (ObjectPool::instance == nullptr)
        ObjectPool::instance = new ObjectPool();
    return ObjectPool::instance;
}

ObjectPool::ObjectPool():objs(){
    //nothing
};

unsigned long ObjectPool::objectNum() {
    return objs.size();
}

void ObjectPool::add(Object *obj) {
    objs.push_back(obj);
}

void ObjectPool::deleteObject(Object *obj) {
    for(auto iter = objs.begin();iter!=objs.end();iter++) {
        if (*iter == obj) {
            objs.erase(iter);
        }
    }
}

void ObjectPool::debug() {
    printf("[Debug ObjectPool] (num=%lu) <",objectNum());
    for(auto &obj:objs) {
        printf("%s ",obj->_class->name.c_str());
    }
    printf("\n");
}