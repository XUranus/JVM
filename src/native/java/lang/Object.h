//
// Created by xuranus on 3/16/19.
//

#ifndef JVM_NATIVE_JAVA_LANG_OBJECT_H
#define JVM_NATIVE_JAVA_LANG_OBJECT_H

#include "../../../runtime/thread/Frame.h"

namespace native::java::lang::Object {
    void doRegistration();

    void getClass(runtime::Frame* frame);
    void hashCode(runtime::Frame* frame);
    void clone(runtime::Frame* frame);
    void notifyAll(runtime::Frame *frame);
};


#endif //JVM_NATIVE_JAVA_LANG_OBJECT_H
