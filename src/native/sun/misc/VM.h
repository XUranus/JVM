//
// Created by xuranus on 3/17/19.
//

#ifndef JVM_NATIVE_SUN_MISC_VM_H
#define JVM_NATIVE_SUN_MISC_VM_H

#include "../../../runtime/thread/Frame.h"

namespace native::sun::misc::VM {
    void doRegistration();

    void initialize(runtime::Frame *frame);
}


#endif //JVM_NATIVE_SUN_MISC_VM_H
