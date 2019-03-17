//
// Created by xuranus on 3/16/19.
//

#ifndef JVM_CLASS_OBJECT_H
#define JVM_CLASS_OBJECT_H

#include "../../runtime/Frame.h"

struct Class_Object {
    static void init();
    static void getClass(Frame* frame);
    static void hashCode(Frame* frame);
    static void clone(Frame* frame);
};


#endif //JVM_CLASS_OBJECT_H
