//
// Created by xuranus on 4/26/22.
//


#include "../../NativeRegistry.h"
#include "../../../runtime/heap/Object.h"
#include "../../../runtime/heap/ClassLoader.h"
#include "../../../runtime/heap/StringPool.h"
#include "../../../instruction/references.h"

#include "AccessController.h"


namespace native::java::security::AccessController {

    void doRegistration() {
        setRegister("java/security/AccessController", "doPrivileged", "(Ljava/security/PrivilegedAction;)Ljava/lang/Object;", doPrivileged);
        setRegister("java/security/AccessController", "doPrivileged", "(Ljava/security/PrivilegedExceptionAction;)Ljava/lang/Object;", doPrivileged);
        setRegister("java/security/AccessController", "getStackAccessControlContext", "()Ljava/security/AccessControlContext;", getStackAccessControlContext);
    }

    // @CallerSensitive
    // public static native <T> T
    //     doPrivileged(PrivilegedExceptionAction<T> action)
    //     throws PrivilegedActionException;
    // (Ljava/security/PrivilegedExceptionAction;)Ljava/lang/Object;

    // @CallerSensitive
    // public static native <T> T doPrivileged(PrivilegedAction<T> action);
    // (Ljava/security/PrivilegedAction;)Ljava/lang/Object;
    void doPrivileged(runtime::Frame *frame) {
        auto& vars = frame->localVars;
        auto& stack = frame->operandStack;

        heap::Object* action = vars.refValue(0); // java/security/PrivilegedAction
        stack.pushRef(action);

        heap::Method* method = action->klass->getInstanceMethod("run", "()Ljava/lang/Object;"); // todo
        instruction::invokeMethod(frame, method);
    }

    // private static native AccessControlContext getStackAccessControlContext();
    // ()Ljava/security/AccessControlContext;
    void getStackAccessControlContext(runtime::Frame *frame) {
        // TODO:: implement
        frame->operandStack.pushRef(nullptr);
    }
}