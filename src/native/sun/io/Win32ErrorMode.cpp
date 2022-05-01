//
// Created by xuranus on 4/30/22.
//

#include "Win32ErrorMode.h"
#include "../../NativeRegistry.h"

namespace native::sun::io::Win32ErrorMode  {

    void doRegistration() {
        setRegister("sun/io/Win32ErrorMode", "setErrorMode", "(J)J", setErrorMode);
    }

    void setErrorMode(runtime::Frame* frame) {
        // TODO::
        frame->operandStack.pushLong(0);
    }
}