//
// Created by xuranus on 3/16/19.
//

#ifndef JVM_NATIVE_JAVA_LANG_DOUBLE_H
#define JVM_NATIVE_JAVA_LANG_DOUBLE_H

#include "../../../runtime/thread/Frame.h"

namespace native::java::lang::Double  {
    void doRegistration();

    void doubleToRawLongBits(runtime::Frame* frame);
    void longBitsToDouble(runtime::Frame* frame);
};


#endif //JVM_NATIVE_JAVA_LANG_DOUBLE_H
