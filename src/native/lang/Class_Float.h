//
// Created by xuranus on 3/17/19.
//

#ifndef JVM_CLASS_FLOAT_H
#define JVM_CLASS_FLOAT_H

#include "../../runtime/Frame.h"

struct Class_Float {
    static void init();
    static void floatToRawIntBits(Frame* frame);
    static void intBitsToFloat(Frame* frame);
};


#endif //JVM_CLASS_FLOAT_H
