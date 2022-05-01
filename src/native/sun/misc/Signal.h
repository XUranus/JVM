//
// Created by xuranus on 4/27/22.
//

#ifndef JVM_NATIVE_SUN_MISC_SIGNAL_H
#define JVM_NATIVE_SUN_MISC_SIGNAL_H


#include "../../../runtime/thread/Frame.h"

namespace native::sun::misc::Signal {
    void doRegistration();

    void findSignal(runtime::Frame* frame);
    void handle0(runtime::Frame* frame);
};

#endif //JVM_NATIVE_SUN_MISC_SIGNAL_H
