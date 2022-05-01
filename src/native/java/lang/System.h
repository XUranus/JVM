//
// Created by xuranus on 3/17/19.
//

#ifndef JVM_NATIVE_JAVA_LANG_SYSTEM_H
#define JVM_NATIVE_JAVA_LANG_SYSTEM_H

#include "../../../runtime/thread/Frame.h"

namespace native::java::lang::System {
    void doRegistration();

    void arraycopy(runtime::Frame* frame);
    void setOut0(runtime::Frame* frame);
    void setIn0(runtime::Frame* frame);
    void setErr0(runtime::Frame* frame);
    void initProperties(runtime::Frame* frame);
    void currentTimeMillis(runtime::Frame* frame);
};


#endif //JVM_NATIVE_JAVA_LANG_SYSTEM_H
