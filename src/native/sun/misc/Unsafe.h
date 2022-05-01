//
// Created by xuranus on 4/26/22.
//

#ifndef JVM_NATIVE_SUN_MISC_UNSAFE_H
#define JVM_NATIVE_SUN_MISC_UNSAFE_H


#include "../../../runtime/thread/Frame.h"

namespace native::sun::misc::Unsafe {
    void doRegistration();

    void arrayBaseOffset(runtime::Frame *frame);
    void arrayIndexScale(runtime::Frame* frame);
    void addressSize(runtime::Frame* frame);
    void objectFieldOffset(runtime::Frame* frame);
    void compareAndSwapObject(runtime::Frame* frame);
    void getInt(runtime::Frame* frame);
    void compareAndSwapInt(runtime::Frame* frame);
    void getObject(runtime::Frame* frame);
    void compareAndSwapLong(runtime::Frame* frame);

    // allocate memory
    void allocateMemory(runtime::Frame* frame);
    void reallocateMemory(runtime::Frame* frame);
    void freeMemory(runtime::Frame* frame);
    void getByte(runtime::Frame* frame);
    void putLong(runtime::Frame* frame);
}



#endif //JVM_NATIVE_SUN_MISC_UNSAFE_H
