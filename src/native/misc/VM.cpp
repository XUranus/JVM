//
// Created by xuranus on 3/17/19.
//

#include "VM.h"
#include "../NativeRegistry.h"
#include "../../runtime/heap/Object.h"
#include "../../runtime/heap/ClassLoader.h"
#include "../../util/Console.h"
#include "../../runtime/heap/StringPool.h"
#include "../../instructions/references.h"

void VM::init() {
    NativeRegistry::getNativeRegistery()->setRegister("sun/misc/VM", "initialize", "()V", VM::initialize);
}

void VM::initialize(Frame *frame) {
    auto vmClass = frame->method->_class;
    auto savedProps = vmClass->getRefVar("savedProps", "Ljava/util/Properties;");
    auto key = StringPool::getStringPool()->getJString(vmClass->classloader,"foo");
    auto val = StringPool::getStringPool()->getJString(vmClass->classloader,"bar");

    frame->operandStack.pushRef(savedProps);
    frame->operandStack.pushRef(key);
    frame->operandStack.pushRef(val);

    auto propsClass = vmClass->classloader->loadClass("java/util/Properties");
    auto setPropMethod = propsClass->getInstanceMethod("setProperty","(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;");
    InvokeMethodLogic::invokeMethod(frame,setPropMethod);
}