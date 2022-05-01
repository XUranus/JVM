//
// Created by xuranus on 4/26/22.
//

#ifndef JVM_NATIVE_JAVA_SECURITY_ACCESSCONTROLLER_H
#define JVM_NATIVE_JAVA_SECURITY_ACCESSCONTROLLER_H

#include "../../../runtime/thread/Frame.h"

namespace native::java::security::AccessController {
    void doRegistration();

    void doPrivileged(runtime::Frame *frame);
    void getStackAccessControlContext(runtime::Frame *frame);
}

#endif //JVM_NATIVE_JAVA_SECURITY_ACCESSCONTROLLER_H
