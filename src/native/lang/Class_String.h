//
// Created by xuranus on 3/17/19.
//

#ifndef JVM_CLASS_STRING_H
#define JVM_CLASS_STRING_H

#include "../../runtime/Frame.h"

struct Class_String {
    static void init();
    static void intern(Frame* frame);
};


#endif //JVM_CLASS_STRING_H
