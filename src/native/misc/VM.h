//
// Created by xuranus on 3/17/19.
//

#ifndef JVM_VM_H
#define JVM_VM_H

#include "../../runtime/Frame.h"

struct VM {
    static void init();
    static void initialize(Frame* frame);
};


#endif //JVM_VM_H
