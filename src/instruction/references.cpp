//
// Created by xuranus on 2/5/19.
//

#include "references.h"
#include <cassert>
#include "../common/Exception.h"
#include "../runtime/heap/StringPool.h"
#include "../native/java/lang/Throwable.h"

namespace instruction {


    void invokeMethod(runtime::Frame *invokerFrame, heap::Method *method) {
        runtime::Thread* thread = invokerFrame->thread;
        thread->stack->push(runtime::Frame(method->maxLocals,
                                           method->maxStack,
                                           thread,
                                           method));
        runtime::Frame& newFrame = thread->stack->top();

        /**
         *  static method args pass:
         *  |----Operand Stack----|         |-----Local Vars----|
         *  |         arg3        |-------  |       ...         |
         *  |         arg2        |----- |  |       ...         |
         *  |         arg1        |--  | |->|       var2        |
         *  |         ...         | |  |--->|       var1        |
         *  |         ...         | |------>|       var0        |
         *  |----------------------         |-------------------|
         *
         *  non-static method args pass:
         *  |----Operand Stack----|         |-----Local Vars----|
         *  |         arg2        |-------  |       ...         |
         *  |         arg1        |----- |  |       ...         |
         *  |         this        |--  | |->|       var2        |
         *  |         ...         | |  |--->|       var1        |
         *  |         ...         | |------>|       this        |
         *  |----------------------         |-------------------|
         */

        int argSlotsNum = int(method->argSlotCount);
        if (argSlotsNum > 0) {
            for (int i = argSlotsNum - 1; i >= 0; i--) { // except 'this' arg, which take 1 slot space
                runtime::Slot slot = invokerFrame->operandStack.popSlot();
                newFrame.localVars.setSlot(i, slot);
            }
        }
    }

    void _print(runtime::OperandStack &stack, const std::string& descriptor) { //TODO::hack!
        if (descriptor == "(Z)V") {
            printf("%d", stack.popInt() != 0);
        } else if (descriptor == "(C)V") {
            printf("%d", stack.popInt());
        } else if (descriptor == "(I)V") {
            printf("%d", stack.popInt());
        } else if (descriptor == "(F)V") {
            printf("%f", stack.popFloat());
        } else if (descriptor == "(J)V") {
            printf("%ld", stack.popLong());
        } else if (descriptor == "(D)V") {
            printf("%lf", stack.popDouble());
        } else if (descriptor == "(Ljava/lang/String;)V") {
            auto jstr = stack.popRef();
            auto localStr = heap::StringPool::localString(jstr);
            printf("%s", localStr.c_str());
        } else {
            exception::panic("hack System.out.print error, descriptor " + descriptor);
        }
        stack.popRef();
    }

    void _println(runtime::OperandStack &stack, const std::string descriptor) {//TODO::hack!
        _print(stack, descriptor);
        std::cout << std::endl;
    }



    void getstatic::execute(runtime::Frame* frame) {
        heap::ConstantPool* constantPool = frame->method->klass->constantPool;
        heap::FieldRef* fieldRef = constantPool->fieldRefValue(index);
        heap::Field* field = fieldRef->resolvedField();
        assert(field != nullptr);

        heap::Class* klass = field->klass;
        // check class inited
        if (!klass->isInitStarted()) {
            frame->revertNextPC();
            frame->thread->initClass(klass);
            return;
        }

        if (!field->isStatic()) { // non-static field
            exception::fatal("java.lang.IncompatibleClassChangeError");
        }

        std::string descriptor = field->descriptor;
        u4 slotId = field->slotId;
        runtime::Slots& slots = klass->staticVars;
        runtime::SlotsStack &stack = frame->operandStack;

        if (descriptor[0] == 'Z' || descriptor[0] == 'B' || descriptor[0] == 'C'
             || descriptor[0] == 'S' || descriptor[0] == 'I') {
            stack.pushInt(slots.intValue(slotId));
        } else if (descriptor[0] == 'F') {
            stack.pushFloat(slots.floatValue(slotId));
        } else if (descriptor[0] == 'J') {
            stack.pushLong(slots.longValue(slotId));
        } else if (descriptor[0] == 'D') {
            stack.pushDouble(slots.doubleValue(slotId));
        } else if (descriptor[0] == 'L' || descriptor[0] == '[') {
            stack.pushRef(slots.refValue(slotId));
        }
    }

    void putstatic::execute(runtime::Frame* frame) {
        heap::Method* currentMethod = frame->method;
        heap::ConstantPool* constantPool = frame->method->klass->constantPool;
        heap::Class* currentClass = frame->method->klass;
        heap::FieldRef* fieldRef = constantPool->fieldRefValue(index);
        heap::Field* field = fieldRef->resolvedField();
        assert(field != nullptr);

        heap::Class* klass = field->klass;
        // check class inited
        if (!klass->isInitStarted()) {
            frame->revertNextPC();
            frame->thread->initClass(klass);
            return;
        }

        if (!field->isStatic()) { // non-static field
            exception::fatal("java.lang.IncompatibleClassChangeError");
        }
        if (field->isFinal()) { // static final field must be set/initialized by its own class in <clinit> method
            if (currentClass != klass || currentMethod->name != "<clinit>") {
                exception::fatal("java.lang.IllegalAccessError");
            }
        }

        std::string descriptor = field->descriptor;
        u4 slotId = field->slotId;
        runtime::Slots& slots = klass->staticVars;
        runtime::SlotsStack &stack = frame->operandStack;


        if (descriptor[0] == 'Z' || descriptor[0] == 'B' || descriptor[0] == 'C'
            || descriptor[0] == 'S' || descriptor[0] == 'I') {
            slots.setInt(slotId, stack.popInt());
        } else if (descriptor[0] == 'F') {
            slots.setFloat(slotId, stack.popFloat());
        } else if (descriptor[0] == 'J') {
            slots.setLong(slotId, stack.popLong());
        } else if (descriptor[0] == 'D') {
            slots.setDouble(slotId, stack.popDouble());
        } else if (descriptor[0] == 'L' || descriptor[0] == '[') {
            slots.setRef(slotId, stack.popRef());
        }
    }

    void getfield::execute(runtime::Frame* frame) {
        heap::ConstantPool* constantPool = frame->method->klass->constantPool;
        heap::Class* currentClass = frame->method->klass;
        heap::FieldRef* fieldRef = constantPool->fieldRefValue(index);
        heap::Field* field = fieldRef->resolvedField();
        assert(field != nullptr);

        if (field->isStatic()) { // static field
            exception::fatal("java.lang.InCompatibleClassChangeError");
        }
        runtime::OperandStack &stack = frame->operandStack;
        heap::Object* ref = stack.popRef();
        if (ref == nullptr) {
            exception::fatal("java.lang.NullPointerException");
        }
        assert(ref->dataType == heap::ObjectDataType::Common);
        runtime::Slots* slots = ref->fields();

        std::string descriptor = field->descriptor;
        u4 slotId = field->slotId;

        if (descriptor[0] == 'Z' || descriptor[0] == 'B' || descriptor[0] == 'C'
            || descriptor[0] == 'S' || descriptor[0] == 'I') {
            stack.pushInt(slots->intValue(slotId));
        } else if (descriptor[0] == 'F') {
            stack.pushFloat(slots->floatValue(slotId));
        } else if (descriptor[0] == 'J') {
            stack.pushLong(slots->longValue(slotId));
        } else if (descriptor[0] == 'D') {
            stack.pushDouble(slots->doubleValue(slotId));
        } else if (descriptor[0] == 'L' || descriptor[0] == '[') {
            stack.pushRef(slots->refValue(slotId));
        }
    }

    void putfield::execute(runtime::Frame* frame) {
        heap::ConstantPool* constantPool = frame->method->klass->constantPool;
        heap::Class* currentClass = frame->method->klass;
        heap::Method* currentMethod = frame->method;
        heap::FieldRef* fieldRef = constantPool->fieldRefValue(index);
        heap::Field* field = fieldRef->resolvedField();
        assert(field != nullptr);

        if (field->isStatic()) { // static field
            exception::fatal("java.lang.IncompatibleClassChangeError");
        }
        if (field->isFinal()) { // non-static final field must be initialized/set in <init> (constructor)
            if ((currentClass != field->klass) || (currentMethod->name != "<init>")) {
                exception::fatal("java.lang.IllegalAccessError");
            }
        }

        std::string descriptor = field->descriptor;
        u4 slotId = field->slotId;
        runtime::SlotsStack &stack = frame->operandStack;

        if (descriptor[0] == 'Z' || descriptor[0] == 'B' || descriptor[0] == 'C'
            || descriptor[0] == 'S' || descriptor[0] == 'I') {
            int val = stack.popInt();
            heap::Object* ref = stack.popRef();
            if (ref == nullptr) {
                exception::fatal("java.lang.NullPointerException");
            }
            assert(ref->dataType == heap::ObjectDataType::Common);
            ref->fields()->setInt(slotId, val);
        } else if (descriptor[0] == 'F') {
            float val = stack.popFloat();
            heap::Object* ref = stack.popRef();
            if (ref == nullptr) {
                exception::fatal("java.lang.NullPointerException");
            }
            assert(ref->dataType == heap::ObjectDataType::Common);
            ref->fields()->setFloat(slotId, val);
        } else if (descriptor[0] == 'J') {
            long val = stack.popLong();
            heap::Object* ref = stack.popRef();
            if (ref == nullptr) {
                exception::fatal("java.lang.NullPointerException");
            }
            assert(ref->dataType == heap::ObjectDataType::Common);
            ref->fields()->setLong(slotId, val);
        } else if (descriptor[0] == 'D') {
            double val = stack.popDouble();
            heap::Object* ref = stack.popRef();
            if (ref == nullptr) {
                exception::fatal("java.lang.NullPointerException");
            }
            assert(ref->dataType == heap::ObjectDataType::Common);
            ref->fields()->setDouble(slotId, val);
        } else if (descriptor[0] == 'L' || descriptor[0] == '[') {
            heap::Object* val = stack.popRef();
            heap::Object* ref = stack.popRef();
            if (ref == nullptr) {
                exception::fatal("java.lang.NullPointerException");
            }
            assert(ref->dataType == heap::ObjectDataType::Common);
            ref->fields()->setRef(slotId, val);
        }
    }

    void invokevirtual::execute(runtime::Frame* frame) {
        heap::ConstantPool* constantPool = frame->method->klass->constantPool;
        heap::Class* currentClass = frame->method->klass;
        heap::MethodRef* methodRef = constantPool->methodRefValue(index);
        heap::Method* resolvedMethod = methodRef->resolvedMethod();

        if (resolvedMethod->isStatic()) { // static method
            exception::fatal("java.lang.InCompatibleClassChangeError");
        }

        heap::Object* ref = frame->operandStack.getRefFromTop(resolvedMethod->argSlotCount - 1);
        if(ref == nullptr) {
            exception::fatal("java.lang.NullPointerException");
        }

        // todo:: similar with invoke_special
        if ((resolvedMethod->isProtected()) // protected method
            && (resolvedMethod->klass->isSuperClassOf(currentClass))
            && (resolvedMethod->klass->packageName() != currentClass->packageName())
            && (ref->klass != currentClass)
            && (!ref->klass->isSubClassOf(currentClass))) {

            if(!(ref->klass->isArray() && resolvedMethod->name == "clone")) {
                exception::fatal("java.lang.IllegalAccessError");
            }
        }

        heap::Method* methodToBeInvoked = ref->klass->lookUpMethodInClass(methodRef->name, methodRef->descriptor);
        if (methodToBeInvoked == nullptr || (methodToBeInvoked->isAbstract())) {
            exception::fatal("java.lang.AbstractMethodError");
        }
        invokeMethod(frame, methodToBeInvoked);
    }

    void invokespecial::execute(runtime::Frame* frame) {
        heap::Class* currentClass = frame->method->klass;
        heap::ConstantPool* constantPool = currentClass->constantPool;
        heap::MethodRef* methodRef = constantPool->methodRefValue(index);
        heap::Method* resolvedMethod = methodRef->resolvedMethod();
        heap::Class* resolvedClass = methodRef->resolvedClass();

        // if method is constructor, it must be invoked by its own class
        if (resolvedMethod->name == "<init>" && resolvedMethod->klass != resolvedClass) {
            exception::fatal("java.lang.NoSuchMethodError");
        }

        // static method must be invoked with <invokestatic>
        if (resolvedMethod->isStatic()) {
            exception::fatal("java.lang.InCompatibleClassChangeError");
        }

        // pop <this> reference
        heap::Object* ref = frame->operandStack.getRefFromTop(resolvedMethod->argSlotCount - 1);
        if (ref == nullptr) {
            exception::fatal("java.lang.NullPointerException");
        }

        if ((resolvedMethod->isProtected()) // protected method
            && resolvedMethod->klass->isSuperClassOf(currentClass)
            && (resolvedMethod->klass->packageName() != currentClass->packageName())
            && ref->klass != currentClass
            && !ref->klass->isSubClassOf(currentClass)) {
            exception::fatal("java.lang.IllegalAccessError");
        }

        heap::Method* methodToBeInvoked = resolvedMethod;
        if ((currentClass->isSuper()) // is method of super class
            && resolvedClass->isSuperClassOf(currentClass)
            && (resolvedMethod->name != "<init>")) {
            methodToBeInvoked = currentClass->superClass->lookUpMethodInClass(methodRef->name, methodRef->descriptor);
        }
        if (methodToBeInvoked == nullptr || (methodToBeInvoked->isAbstract())) {
            exception::fatal("java.lang.AbstractMethodError");
        }

        invokeMethod(frame, methodToBeInvoked);
    }

    void invokestatic::execute(runtime::Frame* frame) {
        heap::ConstantPool* constantPool = frame->method->klass->constantPool;
        heap::MethodRef* methodRef = constantPool->methodRefValue(index);
        heap::Method* resolvedMethod = methodRef->resolvedMethod();

        if (!resolvedMethod->isStatic()) { // non-static method
            exception::fatal("java.lang.InCompatibleClassChangeError");
        }

        heap::Class* klass = resolvedMethod->klass;
        // check class inited
        if (!klass->isInitStarted()) {
            frame->revertNextPC();
            frame->thread->initClass(klass);
            return;
        }

        invokeMethod(frame, resolvedMethod);
    }

    void invokeinterface::fetchOperands(InstructionReader &reader) {
        index = reader.readUint16();
        slotsCount = reader.readUint8();
        zero = reader.readUint8(); // must be 0
        assert(zero == 0);
    }

    void invokeinterface::execute(runtime::Frame* frame) {
        heap::ConstantPool* constantPool = frame->method->klass->constantPool;
        heap::InterfaceMemberRef* methodRef = constantPool->interfaceMemberRefValue(index);
        heap::Method* resolvedMethod = methodRef->resolvedInterfaceMethod();

        if (resolvedMethod->isStatic() || resolvedMethod->isPrivate()) {
            exception::fatal("java.lang.InCompatibleClassChangeError");
        }

        // ref of the object that implement the interface method
        heap::Object* ref = frame->operandStack.getRefFromTop(resolvedMethod->argSlotCount - 1);
        if (ref == nullptr) {
            exception::fatal("java.lang.NullPointerException");
        }

        // class of object didn't implement the interface of the method
        if (!ref->klass->isImplements(methodRef->resolvedClass())) {
            exception::fatal("java.lang.InCompatibleClassChangeError");
        }

        heap::Method* methodToBeInvoked = ref->klass->lookUpMethodInClass(methodRef->name, methodRef->descriptor);
        if (methodToBeInvoked == nullptr || methodToBeInvoked->isAbstract()) {
            exception::fatal("java.lang.AbstractMethodException");
        }
        if (!(methodToBeInvoked->isPublic())) { // invoke non-public method
            exception::fatal("java.lang.IllegalAccessException");
        }
        invokeMethod(frame, methodToBeInvoked);
    }

    void invokedynamic::fetchOperands(InstructionReader &reader) {
        index = reader.readInt16();
        slotsCount = reader.readUint8();
        zero = reader.readUint8();
    }

    void invokedynamic::execute(runtime::Frame *frame) {
        // todo:: implement
        assert(false);
    }

    void new_::execute(runtime::Frame* frame) {
        heap::ConstantPool* constantPool = frame->method->klass->constantPool;
        heap::ClassRef* classRef = constantPool->classRefValue(index);
        heap::Class* klass = classRef->resolvedClass();

        // check class inited
        if (!klass->isInitStarted()) {
            frame->revertNextPC();
            frame->thread->initClass(klass);
            return;
        }

        // abstract class or interface cannot be instantiation
        if (klass->isInterface() || klass->isAbstract()) {
            exception::fatal("java.lang.InstantiationError");
        }
        heap::Object* ref = klass->newObject();
        frame->operandStack.pushRef(ref);
    }

    void newarray::fetchOperands(InstructionReader &reader) {
        atype = reader.readUint8();
    }

    void newarray::execute(runtime::Frame* frame) {
        auto &stack = frame->operandStack;
        int length = stack.popInt();
        if (length < 0) {
            exception::fatal("java.lang.NegativeArraySizeException");
        }
        heap::ClassLoader* classLoader = frame->method->klass->classloader;
        heap::Class* arrayClass = classLoader->getPrimitiveArrayClass(atype);
        heap::Object* ref = arrayClass->newArrayObject(length);

        stack.pushRef(ref);
    }

    void anewarray::execute(runtime::Frame* frame) {
        heap::ConstantPool* constantPool = frame->method->klass->constantPool;
        heap::ClassRef* classRef = constantPool->classRefValue(index);
        heap::Class* componentClass = classRef->resolvedClass();

        auto &stack = frame->operandStack;
        int length = stack.popInt();
        if (length < 0) {
            exception::fatal("java.lang.NegativeArraySizeException");
        }

        heap::Class* arrayClass = componentClass->arrayClass();
        heap::Object* ref = arrayClass->newArrayObject(length);
        stack.pushRef(ref);
    }

    void arraylength::execute(runtime::Frame* frame) {
        auto &stack = frame->operandStack;
        heap::Object* arrayRef = stack.popRef();
        if (arrayRef == nullptr) {
            exception::fatal("java.lang.NullPointerException");
        }
        int arrayLength = arrayRef->arrayLength();
        stack.pushInt(arrayLength);
    }


    void handleUncaughtException(runtime::Thread* thread, heap::Object* exceptionObject) {
        thread->stack->clear();
        heap::Object* jMessage = exceptionObject->getRefVar("detailMessage", "Ljava/lang/String;");
        std::string message = heap::StringPool::localString(jMessage);
        std::cout << "Exception in thread [" << thread->name() << "] " <<
                exceptionObject->klass->getJavaName() << ": " << message << std::endl;

        auto stackTrace = native::java::lang::Throwable::exceptionStackTraceMap[exceptionObject];
        for(const auto& item: stackTrace) {
            std::cout
                << "\tat "
                << item.className << "."
                << item.methodName
                << "(" << item.filename << ":" << item.lineNumber << ")" << std::endl;
        }
        native::java::lang::Throwable::exceptionStackTraceMap.erase(exceptionObject);
    }


    void athrow::execute(runtime::Frame* frame) {
        heap::Object* ex = frame->operandStack.popRef(); // exception object
        if(ex == nullptr) {
            exception::fatal("java.lang.NullPointerException");
        }

        // find and go to exception handler
        runtime::Thread* thread = frame->thread;
        bool exceptionCaught = false;
        while(true) {
            /**
             * traverse Java stack from current frame to find ExceptionHandler,
             * when didn't find a ExceptionHandler in frame F, pop frame F;
             * when find a ExceptionHandler in frame F', clear the operand stack of F'
             * and push Exception object to operand stack bottom
             */
            //runtime::Frame& frame = thread->stack->top();
            int pc = frame->nextPC - 1; // where exception occurs
            int handlerPC = frame->method->findExceptionHandlerPC(ex->klass, pc);
            if(handlerPC > 0) { // found handler
                auto& operandStack = frame->operandStack;
                operandStack.clear();
                operandStack.pushRef(ex);
                frame->nextPC = handlerPC;
                exceptionCaught = true;
                break;
            } else { // handler not found in this frame, seek next
                thread->stack->pop();
                if(thread->stack->empty()) {
                    break;
                }
            }
        }

        /**
         * if Java stack is empty but Exception remain uncaught, print Exception information and exit
         */
        if(!exceptionCaught) {
            handleUncaughtException(thread, ex);
        }
    }

    void checkcast::execute(runtime::Frame* frame) {
        auto &stack = frame->operandStack;
        auto ref = stack.popRef(); // get top ref
        stack.pushRef(ref);
        if (ref == nullptr) {
            return;
        }
        heap::ConstantPool* constantPool = frame->method->klass->constantPool;
        heap::ClassRef* classRef = constantPool->classRefValue(index);
        heap::Class* klass = classRef->resolvedClass();
        if (!ref->instanceOf(klass)) {
            exception::fatal("java.lang.ClassCastException");
        }
    }

    void instanceof::execute(runtime::Frame* frame) {
        auto &stack = frame->operandStack;
        auto ref = stack.popRef();
        if (ref == nullptr) { // null is not instance of any class
            stack.pushInt(0);
            return;
        }
        heap::ConstantPool* constantPool = frame->method->klass->constantPool;
        heap::ClassRef* classRef = constantPool->classRefValue(index);
        heap::Class* klass = classRef->resolvedClass();
        if (ref->instanceOf(klass)) {
            stack.pushInt(1);
        } else {
            stack.pushInt(0);
        }
    }

    void monitorenter::execute(runtime::Frame* frame) {
        heap::Object* ref = frame->operandStack.popRef();
        if(ref == nullptr) {
            exception::exception("java.lang.NullPointerException");
        }
        // todo:: implement
    }

    void monitiorexit::execute(runtime::Frame* frame) {
        heap::Object* ref = frame->operandStack.popRef();
        if(ref == nullptr) {
            exception::exception("java.lang.NullPointerException");
        }
        // todo:: implement
    }

}