//
// Created by xuranus on 3/17/19.
//

#ifndef JVM_CLASS_CLASS_H
#define JVM_CLASS_CLASS_H

#include "../../runtime/Frame.h"

struct Class_Class {
    static void init();
    static void getPrimitiveClass(Frame* frame);
    static void getName0(Frame* frame);
    static void desiredAssertionStatus0(Frame* frame);
    static void isInterface(Frame* frame);
    static void isPrimitive(Frame* frame);
};


#endif //JVM_CLASS_CLASS_H
