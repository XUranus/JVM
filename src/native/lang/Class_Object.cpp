//
// Created by xuranus on 3/16/19.
//

#include "Class_Object.h"
#include "../NativeRegistry.h"
#include "../../runtime/heap/Object.h"
#include "../../runtime/heap/ClassLoader.h"
#include "../../util/Console.h"

// public final native Class<?> getClass();
// ()Ljava/lang/Class;
void Class_Object::getClass(Frame* frame) {
    auto _this = frame->localVars.getRef(0);//getThis
    auto _class = _this->_class->jClass;
    frame->operandStack.pushRef(_class);
}

// public native int hashCode();
// ()I
void Class_Object::hashCode(Frame* frame) {
    auto _this = frame->localVars.getRef(0);//getThis
    long hash = (long)_this;
    frame->operandStack.pushInt((int)hash);
}


// protected native Object clone() throws CloneNotSupportedException;
// ()Ljava/lang/Object;
void Class_Object::clone(Frame* frame) {
    auto _this = frame->localVars.getRef(0);//getThis
    auto cloneable = _this->_class->classloader->loadClass("java/lang/Cloneable");
    if(!_this->_class->isImplements(cloneable)){
        Console::printlnError("java.lang.CloneNotSupportedException");
        exit(1);
    }
    frame->operandStack.pushRef(_this);
}

void Class_Object::init() {
    NativeRegistry::getNativeRegistery()->setRegister("java/lang/Object","getClass","()Ljava/lang/Class;",Class_Object::getClass);
    NativeRegistry::getNativeRegistery()->setRegister("java/lang/Object","hashCode", "()I", Class_Object::hashCode);
    NativeRegistry::getNativeRegistery()->setRegister("java/lang/Object","clone", "()Ljava/lang/Object;", Class_Object::clone);
}