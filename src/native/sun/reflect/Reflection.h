//
// Created by xuranus on 4/26/22.
//

#ifndef JVM_NATIVE_SUN_REFLECT_REFLECTION_H
#define JVM_NATIVE_SUN_REFLECT_REFLECTION_H

#include "../../../runtime/thread/Frame.h"

namespace native::sun::reflect::Reflection {

    void doRegistration();

    void getCallerClass(runtime::Frame *frame);
    void getClassAccessFlags(runtime::Frame *frame);

}


#endif //JVM_NATIVE_SUN_REFLECT_REFLECTION_H
