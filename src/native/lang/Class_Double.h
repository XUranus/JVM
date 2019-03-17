//
// Created by xuranus on 3/16/19.
//

#ifndef JVM_CLASS_DOUBLE_H
#define JVM_CLASS_DOUBLE_H

#include "../../runtime/Frame.h"

struct Class_Double {
    static void init();
    static void doubleToRawLongBits(Frame* frame);
    static void longBitsToDouble(Frame* frame);
};


#endif //JVM_CLASS_DOUBLE_H
