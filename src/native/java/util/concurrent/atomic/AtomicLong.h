//
// Created by xuranus on 4/30/22.
//

#ifndef JVM_NATIVE_JAVA_UTIL_CONCURRENT_ATOMIC_ATOMICLONG_H
#define JVM_NATIVE_JAVA_UTIL_CONCURRENT_ATOMIC_ATOMICLONG_H


#include "../../../../../runtime/thread/Frame.h"

namespace native::java::util::concurrent::atomic::AtomicLong {
    void doRegistration();

    void VMSupportsCS8(runtime::Frame* frame);
}

#endif //JVM_NATIVE_JAVA_UTIL_CONCURRENT_ATOMIC_ATOMICLONG_H
