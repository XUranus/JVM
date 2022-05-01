//
// Created by xuranus on 4/26/22.
//

#include "../../NativeRegistry.h"
#include "../../../runtime/heap/Object.h"
#include "../../../runtime/heap/ClassLoader.h"
#include "../../../runtime/heap/StringPool.h"
#include "../../../instruction/references.h"

#include "Thread.h"


namespace native::java::lang::Thread {

    void doRegistration() {
        setRegister("java/lang/Thread", "currentThread", "()Ljava/lang/Thread;", currentThread);
        setRegister("java/lang/Thread", "setPriority0", "(I)V", setPriority0);
        setRegister("java/lang/Thread", "isAlive", "()Z", isAlive);
        setRegister("java/lang/Thread", "start0", "()V", start0);
    }

    // public static native Thread currentThread();
    // ()Ljava/lang/Thread;
    void currentThread(runtime::Frame* frame) {
        heap::ClassLoader* classLoader = frame->method->klass->classloader;

        heap::Class* threadClass = classLoader->loadClass("java/lang/Thread");
        heap::Object* jThread = threadClass->newObject();

        heap::Class* threadGroupClass = classLoader->loadClass("java/lang/ThreadGroup");
        heap::Object* jGroup = threadGroupClass->newObject();

        jThread->setRefVar("group", "Ljava/lang/ThreadGroup;", jGroup); // TODO:: may need check field null
        jThread->setIntVar("priority", "I", 1);

        frame->operandStack.pushRef(jThread);
    }

    // private native void setPriority0(int newPriority);
    // (I)V
    void setPriority0(runtime::Frame* frame) {
        //auto &vars = frame->localVars;
        //heap::Object* _this = vars.refValue(0);
        //int priority = vars.intValue(1);
        // set native thread priority
        // TODO:: implement
    }

    // public final native boolean isAlive();
    // ()Z
    void isAlive(runtime::Frame* frame) {
        // auto &vars = frame->localVars;
        auto &stack = frame->operandStack;
        // heap::Object* _this = vars.refValue(0);
        // TODO:: implement
        stack.pushBoolean(false);
    }

    // private native void start0();
    // ()V
    void start0(runtime::Frame* frame) {
        // TODO:: implement
    }
}