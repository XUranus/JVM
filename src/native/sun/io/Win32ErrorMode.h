//
// Created by xuranus on 4/30/22.
//

#ifndef JVM_NATIVE_SUN_IO_WIN32ERRORMODE_H
#define JVM_NATIVE_SUN_IO_WIN32ERRORMODE_H


#include "../../../runtime/thread/Frame.h"

namespace native::sun::io::Win32ErrorMode {
    void doRegistration();

    void setErrorMode(runtime::Frame* frame);
}

#endif //JVM_NATIVE_SUN_IO_WIN32ERRORMODE_H
