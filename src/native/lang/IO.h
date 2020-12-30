//
// Created by xuranus on 3/16/19.
//

#ifndef JVM_IO_H
#define JVM_IO_H

#include "../../runtime/Frame.h"

struct IO {
    static void init();
    static void print(Frame* frame);
    static void println(Frame* frame);
};

#endif //JVM_IO_H
