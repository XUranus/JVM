//
// Created by xuranus on 3/17/19.
//

#ifndef JVM_NATIVE_JAVA_LANG_STRING_H
#define JVM_NATIVE_JAVA_LANG_STRING_H

#include "../../../runtime/thread/Frame.h"

namespace native::java::lang::String {
    void doRegistration();

    void intern(runtime::Frame* frame);
};


#endif //JVM_NATIVE_JAVA_LANG_STRING_H
