//
// Created by xuranus on 3/17/19.
//


#include "../../NativeRegistry.h"
#include "../../../runtime/heap/Object.h"
#include "../../../runtime/heap/ClassLoader.h"
#include "../../../runtime/heap/StringPool.h"

#include "String.h"

namespace native::java::lang::String {

    void doRegistration() {
        setRegister("java/lang/String", "intern", "()Ljava/lang/String;", native::java::lang::String::intern);
    }

    // public native String intern();
    // ()Ljava/lang/String;
    void intern(runtime::Frame *frame) {
        heap::Object* _this = frame->localVars.refValue(0); // getThis
        heap::Object* interned = heap::StringPool::internString(_this);
        frame->operandStack.pushRef(interned);
    }

}