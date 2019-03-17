//
// Created by xuranus on 3/17/19.
//

#include "Class_Class.h"
#include "../NativeRegistry.h"
#include "../../runtime/heap/Object.h"
#include "../../runtime/heap/ClassLoader.h"
#include "../../util/Console.h"
#include "../../runtime/heap/StringPool.h"

void Class_Class::init()
{
    NativeRegistry::getNativeRegistery()->setRegister("java/lang/Class","getPrimitiveClass", "(Ljava/lang/String;)Ljava/lang/Class;", Class_Class::getPrimitiveClass);
    NativeRegistry::getNativeRegistery()->setRegister("java/lang/Class", "getName0", "()Ljava/lang/String;", Class_Class::getName0);
    NativeRegistry::getNativeRegistery()->setRegister("java/lang/Class", "desiredAssertionStatus0", "(Ljava/lang/Class;)Z", Class_Class::desiredAssertionStatus0);
    NativeRegistry::getNativeRegistery()->setRegister("java/lang/Class", "isInterface", "()Z", Class_Class::isInterface);
    NativeRegistry::getNativeRegistery()->setRegister("java/lang/Class", "isPrimitive", "()Z", Class_Class::isPrimitive);
}


// static native Class<?> getPrimitiveClass(String name);
// (Ljava/lang/String;)Ljava/lang/Class;
void Class_Class::getPrimitiveClass(Frame *frame)
{
    auto nameObj = frame->localVars.getRef(0);

    Console::printlnRed("getPrimitiveClass()");
    frame->debug();

    auto name = StringPool::getStringPool()->getlocalString(nameObj);
    auto loader = frame->method->_class->classloader;
    auto _class = loader->loadClass(name)->jClass;
    frame->operandStack.pushRef(_class);
}

// private native String getName0();
// ()Ljava/lang/String;
void Class_Class::getName0(Frame *frame)
{
    auto _this = frame->localVars.getRef(0);
    auto _class = (Class*)_this->extra;
    auto name = _class->getJavaName();
    auto nameObj = StringPool::getStringPool()->getJString(_class->classloader,name);
    frame->operandStack.pushRef(nameObj);
}

// private static native boolean desiredAssertionStatus0(Class<?> clazz);
// (Ljava/lang/Class;)Z
void Class_Class::desiredAssertionStatus0(Frame *frame)
{
    //TODO::
    frame->operandStack.pushBoolean(false);
}

// public native boolean isInterface();
// ()Z
void Class_Class::isInterface(Frame *frame)
{
    auto& vars = frame->localVars;
    auto _this = vars.getRef(0);
    auto _class = (Class*)_this->extra;

    frame->operandStack.pushBoolean((bool)(_class->accessFlags & ACC_INTERFACE_FLAG));
}

// public native boolean isPrimitive();
// ()Z
void Class_Class::isPrimitive(Frame *frame)
{
    auto &vars = frame->localVars;
    auto _this = vars.getRef(0);
    auto _class = (Class*)_this->extra;
    frame->operandStack.pushBoolean(_class->isPrimitive());
}