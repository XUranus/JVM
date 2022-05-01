//
// Created by xuranus on 4/26/22.
//

#ifndef JVM_NATIVE_JAVA_LANG_THREAD_H
#define JVM_NATIVE_JAVA_LANG_THREAD_H

#include "../../../runtime/thread/Frame.h"

namespace native::java::lang::Thread {
    void doRegistration();

    void currentThread(runtime::Frame *frame);
    void setPriority0(runtime::Frame *frame);
    void isAlive(runtime::Frame *frame);
    void start0(runtime::Frame *frame);
}

#endif //JVM_NATIVE_JAVA_LANG_THREAD_H
