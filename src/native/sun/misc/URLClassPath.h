//
// Created by xuranus on 4/27/22.
//

#ifndef JVM_NATIVE_SUN_MISC_URLCLASSPATH_H
#define JVM_NATIVE_SUN_MISC_URLCLASSPATH_H


#include "../../../runtime/thread/Frame.h"

namespace native::sun::misc::URLClassPath {
    void doRegistration();

    void getLookupCacheURLs(runtime::Frame* frame);
};

#endif //JVM_NATIVE_SUN_MISC_URLCLASSPATH_H
