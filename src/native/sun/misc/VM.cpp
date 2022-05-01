//
// Created by xuranus on 3/17/19.
//

#include "../../NativeRegistry.h"
#include "../../../runtime/heap/Object.h"
#include "../../../runtime/heap/ClassLoader.h"
#include "../../../runtime/heap/StringPool.h"
#include "../../../instruction/references.h"

#include "VM.h"

namespace native::sun::misc::VM {

    void doRegistration() {
        setRegister("sun/misc/VM", "initialize", "()V", initialize);
    }

    // sum.misc.Vm  initialize()V
//    void initialize(runtime::Frame *frame) {
//        heap::Class* vmClass = frame->method->klass;
//
//        heap::Object* savedProps = vmClass->getRefVar("savedProps", "Ljava/util/Properties;");
//        heap::Object* key = heap::StringPool::JString(vmClass->classloader, "foo");
//        heap::Object* val = heap::StringPool::JString(vmClass->classloader, "bar");
//
//        frame->operandStack.pushRef(savedProps);
//        frame->operandStack.pushRef(key);
//        frame->operandStack.pushRef(val);
//
//        heap::Class* propertiesClass = vmClass->classloader->loadClass("java/util/Properties");
//        heap::Method* setPropertyMethod = propertiesClass->getInstanceMethod("setProperty",
//                                                           "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;");
//        instruction::invokeMethod(frame, setPropertyMethod);
//    }

    void initialize(runtime::Frame *frame) {
        heap::ClassLoader* classLoader = frame->method->klass->classloader;
        heap::Class* jlSysClass = classLoader->loadClass("java/lang/System");
        heap::Method* initSysClass = jlSysClass->getStaticMethod("initializeSystemClass", "()V");
        instruction::invokeMethod(frame, initSysClass); // invoke java.lang.System.initialSystemClass()
    }

}