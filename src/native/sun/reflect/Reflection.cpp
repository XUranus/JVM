//
// Created by xuranus on 4/26/22.
//


#include "../../NativeRegistry.h"
#include "../../../runtime/heap/StringPool.h"
#include "../../../instruction/references.h"
#include "../../java/lang/Class.h"
#include "Reflection.h"
#include <cassert>

namespace native::sun::reflect::Reflection {

    void doRegistration() {
        setRegister("sun/reflect/Reflection", "getCallerClass", "()Ljava/lang/Class;", getCallerClass);
        setRegister("sun/reflect/Reflection", "getClassAccessFlags", "(Ljava/lang/Class;)I", getClassAccessFlags);
    }

    // public static native Class<?> getCallerClass();
    // ()Ljava/lang/Class;
    void getCallerClass(runtime::Frame *frame) {
        // top0 is sun/reflect/Reflection
        // top1 is the caller of getCallerClass()
        // top2 is the caller of method
        std::list<runtime::Frame*> frames = frame->thread->stack->stackFrames();
        auto it = frames.begin(); // it == frames[0]
        it++; // it == frame[1]
        it++; // it == frame[2]
        runtime::Frame* callerFrame = *it;
        heap::Object* callerClass = callerFrame->method->klass->jClass;
        frame->operandStack.pushRef(callerClass);
    }

    // public static native int getClassAccessFlags(Class<?> type);
    // (Ljava/lang/Class;)I
    void getClassAccessFlags(runtime::Frame *frame) {
        heap::Object* type = frame->localVars.refValue(0); // static method
        heap::ClassLoader* classLoader = frame->method->klass->classloader;
        assert(type->klass == classLoader->loadClass("java/lang/Class"));

        heap::Class* klass = java::lang::Class::reflectClass(type);
        unsigned short accessFlag =klass->accessFlags;
        frame->operandStack.pushInt(accessFlag);
    }


}