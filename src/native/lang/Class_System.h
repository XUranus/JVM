//
// Created by xuranus on 3/17/19.
//

#ifndef JVM_CLASS_SYSTEM_H
#define JVM_CLASS_SYSTEM_H

#include "../../runtime/Frame.h"

struct Class_System {
    static void init();
    static bool checkArrayCopy(Object* src,Object* dest);
    static void arrayCopy(Object* src,Object* dst,int srcPos,int dstPos,int length);

    static void arraycopy(Frame* frame);
};


#endif //JVM_CLASS_SYSTEM_H
