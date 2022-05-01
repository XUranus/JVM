//
// Created by xuranus on 3/16/19.
//

#include "../../NativeRegistry.h"
#include "../../../common/Exception.h"

#include "Object.h"

namespace native::java::lang::Object {

    void doRegistration() {
        setRegister("java/lang/Object", "getClass", "()Ljava/lang/Class;", native::java::lang::Object::getClass);
        setRegister("java/lang/Object", "hashCode", "()I", native::java::lang::Object::hashCode);
        setRegister("java/lang/Object", "clone", "()Ljava/lang/Object;", native::java::lang::Object::clone);
        setRegister("java/lang/Object", "notifyAll", "()V", native::java::lang::Object::notifyAll);
    }

    // public final native Class<?> getClass();
    // ()Ljava/lang/Class;
    void getClass(runtime::Frame *frame) {
        heap::Object* _this = frame->localVars.refValue(0); // getThis
        heap::Object* klass = _this->klass->jClass;
        frame->operandStack.pushRef(klass);
    }

    // public native int hashCode();
    // ()I
    void hashCode(runtime::Frame *frame) {
        heap::Object* _this = frame->localVars.refValue(0); // getThis
        int hash = (int)heap::ObjectPool::compressPtr(_this);
        frame->operandStack.pushInt(hash);
    }

    // protected native Object clone() throws CloneNotSupportedException;
    // ()Ljava/lang/Object;
    void clone(runtime::Frame *frame) {
        heap::Object* _this = frame->localVars.refValue(0); // getThis
        heap::Class* cloneable = _this->klass->classloader->loadClass("java/lang/Cloneable");
        if (!_this->klass->isImplements(cloneable)) {
            exception::fatal("java.lang.CloneNotSupportedException");
        }
        frame->operandStack.pushRef(heap::ObjectPool::cloneObject(_this));
    }

    // protected final native void notify()
    // ()V
    void notifyAll(runtime::Frame *frame) {
        // TODO::
    }
}