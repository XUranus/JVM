//
// Created by xuranus on 3/17/19.
//

#ifndef JVM_NATIVE_JAVA_LANG_FLOAT_H
#define JVM_NATIVE_JAVA_LANG_FLOAT_H

#include "../../../runtime/thread/Frame.h"

namespace native::java::lang::Float {
    void doRegistration();

    void floatToRawIntBits(runtime::Frame* frame);
    void intBitsToFloat(runtime::Frame* frame);
};


#endif //JVM_NATIVE_JAVA_LANG_FLOAT_H
