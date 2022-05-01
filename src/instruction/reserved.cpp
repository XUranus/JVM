//
// Created by xuranus on 2/5/19.
//

#include "reserved.h"
#include "../common/Exception.h"
#include "../native/NativeRegistry.h"

namespace instruction {


    void breakpoint::execute(runtime::Frame* frame) {
        // todo::implement
        exception::panic("instruction [breakpoint] not implemented");
    }

    // invokenative
    void impdep1::execute(runtime::Frame* frame) {
        heap::Method* method = frame->method;
        std::string className = method->klass->name;
        std::string methodName = method->name;
        std::string methodDescriptor = method->descriptor;

        native::NativeMethod nativeMethod = native::findNativeMethod(className, methodName, methodDescriptor);
        if (!nativeMethod) {
            exception::fatal("java.lang.UnsatisfiedLinkError: " + className + "." + methodName + "." + methodDescriptor);
        } else {
            (*nativeMethod)(frame);
        }
    }

    void impdep2::execute(runtime::Frame* frame) {
        // todo::implement
        exception::panic("instruction [impdep2] not implemented");
    }

}
