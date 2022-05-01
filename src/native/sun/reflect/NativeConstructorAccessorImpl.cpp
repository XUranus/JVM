//
// Created by xuranus on 4/27/22.
//

#include "NativeConstructorAccessorImpl.h"

#include "../../NativeRegistry.h"
#include "../../../runtime/heap/StringPool.h"
#include "../../../instruction/references.h"
#include "../../java/lang/Class.h"
#include <cassert>

namespace native::sun::reflect::NativeConstructorAccessorImpl {

    void doRegistration() {
        setRegister("sun/reflect/NativeConstructorAccessorImpl", "newInstance0", "(Ljava/lang/reflect/Constructor;[Ljava/lang/Object;)Ljava/lang/Object;", newInstance0);
    }

    heap::Method* getMethod(heap::Object* methodObj, bool isConstructor) {
        heap::Method* method = native::java::lang::Class::reflectMethod(methodObj);
        if(method) {
            return method;
        } else {
            if(isConstructor) {
                heap::Object* root = methodObj->getRefVar("root", "Ljava/lang/reflect/Constructor;");
                return native::java::lang::Class::reflectMethod(root);
            } else {
                heap::Object* root = methodObj->getRefVar("root", "Ljava/lang/reflect/Method;");
                return native::java::lang::Class::reflectMethod(root);
            }
        }
    }

    // private static native Object newInstance0(Constructor<?> c, Object[] os)
    // throws InstantiationException, IllegalArgumentException, InvocationTargetException;
    // (Ljava/lang/reflect/Constructor;[Ljava/lang/Object;)Ljava/lang/Object;
    void newInstance0(runtime::Frame* frame) {
        auto thread = frame->thread;

        heap::Object* constructorObj = frame->localVars.refValue(0);
        heap::Object* argArrayObj = frame->localVars.refValue(1);

        // get constructor method
        heap::Method* constructor = getMethod(constructorObj, true);

        //std::cout << "WXX " << constructor->klass->name << " " << constructor->name << " " << constructor->descriptor << std::endl;

        assert(constructor != nullptr);
        heap::Class* klass = constructor->klass;
        if(!klass->isInitStarted()) {
            frame->revertNextPC();
            thread->initClass(klass);
            return;
        }

        heap::Object* obj = klass->newObject();
        frame->operandStack.pushRef(obj);

        // call <init>
        auto shimMethod = heap::Method::ShimMethod; // shim method
        auto shimFrame = runtime::Frame(0, (int )constructor->argSlotCount, thread, shimMethod);
        thread->stack->push(shimFrame);

        auto& ops = thread->stack->top().operandStack;
        if(!constructor->isStatic()) {
            ops.pushRef(obj);
        }

        instruction::invokeMethod(&thread->stack->top(), constructor);
    }
}
