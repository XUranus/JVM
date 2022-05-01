//
// Created by xuranus on 4/27/22.
//

#ifndef JVM_NATIVE_SUN_REFLECT_NATIVECONSTRUCTORACCESSORIMPL_H
#define JVM_NATIVE_SUN_REFLECT_NATIVECONSTRUCTORACCESSORIMPL_H

#include "../../../runtime/thread/Frame.h"

namespace native::sun::reflect::NativeConstructorAccessorImpl {
    void doRegistration();

    void newInstance0(runtime::Frame *frame);
}


#endif //JVM_NATIVE_SUN_REFLECT_NATIVECONSTRUCTORACCESSORIMPL_H
