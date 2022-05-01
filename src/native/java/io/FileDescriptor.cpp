//
// Created by xuranus on 4/26/22.
//

#include "FileDescriptor.h"

#include "../../NativeRegistry.h"
#include "../../../runtime/heap/Object.h"
#include "../../../runtime/heap/ClassLoader.h"
#include "../../../runtime/heap/StringPool.h"
#include "../../../instruction/references.h"

namespace native::java::io::FileDescriptor {

    void doRegistration() {
        setRegister("java/io/FileDescriptor", "set", "(I)J", set);
    }

    // private static native long set(int d);
    // (I)J
    void set(runtime::Frame *frame) {
        // TODO:: implement
        frame->operandStack.pushLong(0);
    }
}