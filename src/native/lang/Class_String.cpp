//
// Created by xuranus on 3/17/19.
//

#include "Class_String.h"
#include "../NativeRegistry.h"
#include "../../runtime/heap/Object.h"
#include "../../runtime/heap/ClassLoader.h"
#include "../../util/Console.h"
#include "../../runtime/heap/StringPool.h"

void Class_String::init()
{
    NativeRegistry::getNativeRegistery()->setRegister("java/lang/String","intern", "()Ljava/lang/String;", Class_String::intern);
}

// public native String intern();
// ()Ljava/lang/String;
void Class_String::intern(Frame *frame)
{
    auto _this = frame->localVars.getRef(0);//getThis
    auto interned = StringPool::getStringPool()->internString(_this);
    frame->operandStack.pushRef(interned);
}