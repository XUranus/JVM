//
// Created by xuranus on 2/5/19.
//

#include "references.h"
#include "../runtime/heap/SymRef.h"
#include "../runtime/Thread.h"
#include "../util/Console.h"
#include "../runtime/heap/ClassLoader.h"
#include "../runtime/heap/StringPool.h"

void InvokeMethodLogic::invokeMethod(Frame *invokerFrame, Method *method) {
	auto thread = invokerFrame->thread;
	auto newFrame = new Frame(method);
	thread->pushFrame(newFrame);

	auto argSlotsNum = int(method->argSlotCount);
	if (argSlotsNum > 0) {
		//Console::printlnWarning("slot num:"+std::to_string(argSlotsNum));
		for (int i = argSlotsNum - 1; i >= 0; i--) {
			auto slot = invokerFrame->operandStack.popSlot();
			newFrame->localVars.setSlot((unsigned int) i, slot);
		}
	}

	//TODO::hack!
	if(method->accessFlags & ACC_NATIVE_FLAG)
	{
		if(method->name=="registerNatives") {
            thread->popFrame();
            //Console::printlnRed("registerNatives");
        } else {
			Console::printlnWarning("Native Method:"+method->_class->name+"."+method->name+method->descriptor);thread->debug();
			thread->popFrame();
			Console::printlnWarning("after pop:"+std::to_string(thread->stack.size));
		}
	}
}

void InvokeMethodLogic::_print(Frame *frame, std::string descriptor) //TODO::hack!
{
	auto &stack = frame->operandStack;
	if(descriptor=="(Z)V")
		printf("%d",stack.popInt()!=0);
	else if(descriptor=="(C)V")
		printf("%d",stack.popInt());
	else if(descriptor=="(I)V")
		printf("%d",stack.popInt());
	else if(descriptor=="(F)V")
		printf("%f",stack.popFloat());
	else if(descriptor=="(J)V")
		printf("%ld",stack.popLong());
	else if(descriptor=="(D)V")
		printf("%lf",stack.popDouble());
	else if(descriptor=="(Ljava/lang/String;)V") {
		auto jstr = stack.popRef();
		auto localStr = StringPool::getStringPool()->getlocalString(jstr);
		printf("%s",localStr.c_str());
	} else {
		Console::printlnError("hack error,descriptor"+descriptor);
		exit(1);
	}
	stack.popRef();
}

void InvokeMethodLogic::_println(Frame *frame, std::string descriptor) //TODO::hack!
{
    auto &stack = frame->operandStack;
    if(descriptor=="(Z)V")
        printf("%d\n",stack.popInt()!=0);
    else if(descriptor=="(C)V")
        printf("%c\n",stack.popInt());
    else if(descriptor=="(I)V")
        printf("%d\n",stack.popInt());
    else if(descriptor=="(F)V")
        printf("%f\n",stack.popFloat());
    else if(descriptor=="(J)V")
        printf("%ld\n",stack.popLong());
    else if(descriptor=="(D)V")
        printf("%lf\n",stack.popDouble());
    else if(descriptor=="(Ljava/lang/String;)V") {
        auto jstr = stack.popRef();
        auto localStr = StringPool::getStringPool()->getlocalString(jstr);
        printf("%s\n",localStr.c_str());
    } else {
        Console::printlnError("hack error,descriptor"+descriptor);
        exit(1);
    }
    stack.popRef();
}





void getstatic::excute(Frame *frame) {
	auto cp = frame->method->_class->constantPool;
	auto fieldRef = (FieldRef*)(cp->getRef(index));
	auto field = fieldRef->resolvedField();
	auto _class = field->_class;
    if(!_class->initStarted)
    {
        frame->revertNextPc();
        frame->thread->initClass(_class);
        return;
    }

	if(!(field->accessFlags & ACC_STATIC_FLAG))
	{
		printf("java.lang.IncompatibleClassChangeError.\n");
		exit(1);
	}
	auto descriptor = field->descriptor;
	auto slotId = field->slotId;
	auto &slots = _class->staticVars;
	auto &stack = frame->operandStack;

	if(descriptor[0]=='Z'||descriptor[0]=='B'||descriptor[0]=='C'||descriptor[0]=='S'||descriptor[0]=='I')
		stack.pushInt(slots->getInt(slotId));
	else if(descriptor[0]=='F')
		stack.pushFloat(slots->getFloat(slotId));
	else if(descriptor[0]=='J')
		stack.pushLong(slots->getLong(slotId));
	else if(descriptor[0]=='D')
		stack.pushDouble(slots->getDouble(slotId));
	else if(descriptor[0]=='L' || descriptor[0]=='[')
		stack.pushRef(slots->getRef(slotId));

	
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void putstatic::excute(Frame *frame) {
    auto cp = frame->method->_class->constantPool;
    auto fieldRef = (FieldRef*)(cp->getRef(index));
    auto field = fieldRef->resolvedField();
    if(field== nullptr){
    	printf("null field\n");
    	exit(1);
    }
    auto _class = field->_class;
    if(!_class->initStarted)
    {
        frame->revertNextPc();
        frame->thread->initClass(_class);
        return;
    }

    if(!(field->accessFlags & ACC_STATIC_FLAG))
	{
    	printf("java.lang.IncompatibleClassChangeError.\n");
    	exit(1);
	}
	if(field->accessFlags & ACC_FINAL_FLAG)
	{
		if(frame->method->_class!=_class || frame->method->name!="<clinit>")
		{
			printf("java.lang.IllegalAccessError.\n");
			exit(1);
		}
	}

	auto descriptor = field->descriptor;
	auto slotId = field->slotId;
	auto slots = _class->staticVars;
	auto &stack = frame->operandStack;

	if(descriptor[0]=='Z'||descriptor[0]=='B'||descriptor[0]=='C'||descriptor[0]=='S'||descriptor[0]=='I')
		slots->setInt(slotId,stack.popInt());
	else if(descriptor[0]=='F')
		slots->setFloat(slotId,stack.popFloat());
	else if(descriptor[0]=='J')
		slots->setLong(slotId,stack.popLong());
	else if(descriptor[0]=='D')
		slots->setDouble(slotId,stack.popDouble());
	else if(descriptor[0]=='L' || descriptor[0]=='[')
		slots->setRef(slotId,stack.popRef());

#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void getfield::excute(Frame *frame) {
	auto cp = frame->method->_class->constantPool;
	auto fieldRef = (FieldRef*)(cp->getRef(index));
	auto field = fieldRef->resolvedField();
	if(field->accessFlags & ACC_STATIC_FLAG)
	{
		printf("java.lang.InCompatibleClassChangeError.\n");
		exit(1);
	}
	auto &stack = frame->operandStack;
	auto ref = stack.popRef();
	if(ref== nullptr)
	{
		printf("java.lang.NullPointerException.\n");
		exit(1);
	}
	auto descriptor = field->descriptor;
	auto slotId = field->slotId;
	auto slots = ref->getFields();
	if(descriptor[0]=='Z'||descriptor[0]=='B'||descriptor[0]=='C'||descriptor[0]=='S'||descriptor[0]=='I')
		stack.pushInt(slots->getInt(slotId));
	else if(descriptor[0]=='F')
		stack.pushFloat(slots->getFloat(slotId));
	else if(descriptor[0]=='J')
		stack.pushLong(slots->getLong(slotId));
	else if(descriptor[0]=='D')
		stack.pushDouble(slots->getDouble(slotId));
	else if(descriptor[0]=='L' || descriptor[0]=='[')
		stack.pushRef(slots->getRef(slotId));

#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void putfield::excute(Frame *frame) {printf("here");
    auto currentMethod = frame->method;
    auto currentClass = currentMethod->_class;
    auto cp = currentClass->constantPool;
    auto fieldRef = (FieldRef*)(cp->getRef(index));
    auto field = fieldRef->resolvedField();
    if(field->accessFlags & ACC_STATIC_FLAG)
    {
        printf("java.lang.IncompatibleClassChangeError.\n");
        exit(1);
    }
    if(field->accessFlags & ACC_FINAL_FLAG)
    {
        if((currentClass!=field->_class) || (currentMethod->name!="<init>"))
        {
            printf("java.lang.IllegalAccessError.\n");
            exit(1);
        }
    }
    auto descriptor = field->descriptor;
    auto slotId = field->slotId;
    auto &stack = frame->operandStack;
    if(descriptor[0]=='Z' || descriptor[0]=='B' || descriptor[0]=='C' || descriptor[0]=='S' || descriptor[0]=='I')
    {
        auto val = stack.popInt();
        auto ref = stack.popRef();
        if(ref== nullptr)
        {
            printf("java.lang.NullPointerException\n");
            exit(1);
        }
        ref->getFields()->setInt(slotId,val);
    } else if(descriptor[0]=='F') {
		auto val = stack.popFloat();
		auto ref = stack.popRef();
		if(ref== nullptr)
		{
			printf("java.lang.NullPointerException\n");
			exit(1);
		}
		ref->getFields()->setFloat(slotId,val);
	} else if(descriptor[0]=='J') {
		auto val = stack.popLong();
		auto ref = stack.popRef();
		if(ref== nullptr)
		{
			printf("java.lang.NullPointerException\n");
			exit(1);
		}
		ref->getFields()->setLong(slotId,val);
	} else if(descriptor[0]=='D') {
		auto val = stack.popDouble();
		auto ref = stack.popRef();
		if(ref== nullptr)
		{
			printf("java.lang.NullPointerException\n");
			exit(1);
		}
		ref->getFields()->setDouble(slotId,val);
	} else if(descriptor[0]=='L' || descriptor[0]=='[') {
		auto val = stack.popRef();
		auto ref = stack.popRef();
		if(ref== nullptr)
		{
			printf("java.lang.NullPointerException\n");
			exit(1);
		}
		ref->getFields()->setRef(slotId,val);
	}
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void invokevirtual::excute(Frame *frame) {
	auto currentClass = frame->method->_class;
	auto cp = currentClass->constantPool;
	auto methodRef = (MethodRef*)(cp->getRef(index));
	auto resolvedMethod = methodRef->resolvedMethod();//info log

	if(resolvedMethod->accessFlags & ACC_STATIC_FLAG)
	{
		Console::printlnError("java.lang.InCompatibleClassChangeError");
		exit(1);
	}

	//frame->debug();
	//resolvedMethod->debug();

	auto ref = frame->operandStack.getRefFromTop(resolvedMethod->argSlotCount-1);

	if(methodRef->name=="print") {//todo:: hack!!!
		//Console::printlnWarning("hack println()");
		InvokeMethodLogic::_print(frame, methodRef->descriptor);
		return;
	}
    if(methodRef->name=="println") {//todo:: hack!!!
        //Console::printlnWarning("hack println()");
        InvokeMethodLogic::_println(frame, methodRef->descriptor);
        return;
    }
	//Console::printlnException("java.lang.NullPointerException");

	if((resolvedMethod->accessFlags & ACC_PROTECTED_FLAG)
		&&(resolvedMethod->_class->isSuperClassOf(currentClass))
		&&(resolvedMethod->_class->getPackageName() != currentClass->getPackageName())
		&&(ref->_class!=currentClass)
		&&(!ref->_class->isSubClassOf(currentClass)))
	{
		Console::printlnError("java.lang.IllegalAccessException");
		exit(1);
	}
	auto methodToBeInvoked = ref->_class->lookUpMethodInClass(methodRef->name,methodRef->descriptor);
	if(methodToBeInvoked == nullptr || (methodToBeInvoked->accessFlags & ACC_ABSTRACT_FLAG))
	{
		Console::printlnError("java.lang.AbstractMethodError");
		exit(1);
	}
	InvokeMethodLogic::invokeMethod(frame,methodToBeInvoked);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void invokespecial::excute(Frame *frame) {
	auto currentClass = frame->method->_class;
	auto cp = currentClass->constantPool;
	auto methodRef = (MethodRef*)cp->getRef(index);
	auto resolvedClass = methodRef->resolvedClass();
	auto resolvedMethod = methodRef->resolvedMethod();
	if(resolvedMethod->name=="<init>" && resolvedMethod->_class!=resolvedClass)
	{
		Console::printlnError("java.lang.NoSuchMethodError");
		exit(1);
	}
	if(resolvedMethod->accessFlags & ACC_STATIC_FLAG)
	{
		Console::printlnError("java.lang.InCompatibleClassChangeError");
		exit(1);
	}

	//resolvedMethod->debug();
	auto ref = frame->operandStack.getRefFromTop(resolvedMethod->argSlotCount);
	if(ref== nullptr)
	{
		Console::printlnException("java.lang.NullPointerException");
	}
	if((resolvedMethod->accessFlags & ACC_PROTECTED_FLAG)
		&& (resolvedMethod->_class->isSuperClassOf(currentClass))
		&& (resolvedMethod->_class->getPackageName()!=currentClass->getPackageName())
		&& ref->_class != currentClass
		&& !ref->_class->isSubClassOf(currentClass))
	{
		Console::printlnError("java.lang.IllegalAccessError");
		exit(1);
	}
	auto methodToBeInvoked = resolvedMethod;
	if((currentClass->accessFlags & ACC_SUPER_FLAG)
	&&(resolvedClass->isSuperClassOf(currentClass))
	&&(resolvedMethod->name!="<init>"))
	{
		methodToBeInvoked = currentClass->superClass->lookUpMethodInClass(methodRef->name,methodRef->descriptor);
	}
	if(methodToBeInvoked== nullptr || (methodToBeInvoked->accessFlags & ACC_ABSTRACT_FLAG))
	{
		Console::printlnError("java.lang.AbstractMethodError");
		exit(1);
	}

	InvokeMethodLogic::invokeMethod(frame,methodToBeInvoked);
	//frame->operandStack.popRef();
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void invokestatic::excute(Frame *frame) {
	auto cp = frame->method->_class->constantPool;
	auto methodRef = (MethodRef*)cp->getRef(index);
	auto resolvedMethod = methodRef->resolvedMethod();
	if(!(resolvedMethod->accessFlags & ACC_STATIC_FLAG))
	{
		Console::printlnError("java.lang.InCompatibleClassChangeError");
		exit(1);
	}

	auto _class = resolvedMethod->_class;

	if(!_class->initStarted)
	{
		frame->revertNextPc();
		frame->thread->initClass(_class);
		return;
	}
	InvokeMethodLogic::invokeMethod(frame,resolvedMethod);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void invokeinterface::fetchOperands(BytesReader &reader) {
	index = reader.readUint16();
	slotsCount = reader.readUint8();
	zero = reader.readUint8();
	if(zero!=0)
		Console::printlnWarning("instruction [invokeinterface] zero element not 0");
}

std::string invokeinterface::toString() {
	return "invokesepcial "+std::to_string(index)+" "+std::to_string(slotsCount)+" "+std::to_string(zero);
}

void invokeinterface::excute(Frame *frame) {
	auto cp = frame->method->_class->constantPool;
	auto methodRef = (InterfaceMemberRef *) cp->getRef(index);
	auto resolvedMethod = methodRef->resolvedInterfaceMethod();
	if ((resolvedMethod->accessFlags & ACC_STATIC_FLAG) || (resolvedMethod->accessFlags & ACC_PRIVATE_FLAG)) {
		Console::printlnError("java.lang.InCompatibleClassChangeError");
		exit(1);
	}
	auto ref = frame->operandStack.getRefFromTop(resolvedMethod->argSlotCount - 1);
	if (ref == nullptr) {
		Console::printlnException("java.lang.NullPointerException");
	}
	if (!ref->_class->isImplements(methodRef->resolvedClass()))
	{
		Console::printlnError("java.lang.InCompatibleClassChangeError");
		exit(1);
	}
	auto methodToBeInvoked = ref->_class->lookUpMethodInClass(methodRef->name,methodRef->descriptor);
	if(methodToBeInvoked== nullptr || (methodToBeInvoked->accessFlags & ACC_ABSTRACT_FLAG))
	{
		Console::printlnError("java.lang.AbstractMethodException");
		exit(1);
	}
	if(!(methodToBeInvoked->accessFlags & ACC_PUBLIC_FLAG)) {
		Console::printlnError("java.lang.IllegalAccessException");
		exit(1);
	}
	InvokeMethodLogic::invokeMethod(frame,methodToBeInvoked);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void new_::excute(Frame *frame) {
	auto cp = frame->method->_class->constantPool;
	auto classRef = (ClassRef*)cp->getRef(index);
	auto _class = classRef->resolvedClass();
	if(!_class->initStarted)
    {
	    frame->revertNextPc();
	    frame->thread->initClass(_class);
	    return;
    }

	if((_class->accessFlags & ACC_INTERFACE_FLAG) || (_class->accessFlags & ACC_ABSTRACT_FLAG))
	{
		printf("java.lang.InstantiationError\n");
		exit(1);
	}
	auto ref = _class->newObject();
	frame->operandStack.pushRef(ref);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void newarray::fetchOperands(BytesReader &reader) {
    atype = reader.readUint8();
}

void newarray::excute(Frame *frame) {
    auto& stack = frame->operandStack;
    auto count = stack.popInt();
    if(count < 0)
    {
        Console::printlnException("java.lang.NegetiveArraySizeException");
        exit(1);
    }
    auto classLoader = frame->method->_class->classloader;
    auto arrClass = classLoader->getPrimitiveArrayClass(atype);
    auto arr = arrClass->newArrayObject((unsigned int)count);
    stack.pushRef(arr);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

std::string newarray::toString() {
    return "newarray "+std::to_string(atype);
}

void anewarray::excute(Frame *frame) {
    auto cp = frame->method->_class->constantPool;
    auto classRef = (ClassRef*)cp->getRef(index);
    auto componentClass = classRef->resolvedClass();

    auto& stack = frame->operandStack;
    auto count = stack.popInt();
    if(count < 0)
    {
        Console::printlnException("java.lang.NegetiveArraySizeException");
        exit(1);
    }

    auto arrClass = componentClass->arrayClass();
    auto arr = arrClass->newArrayObject((unsigned int)count);
    stack.pushRef(arr);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void arraylength::excute(Frame *frame) {
	auto& stack = frame->operandStack;
	auto arrRef = stack.popRef();
	if(arrRef == nullptr)
	{
		Console::printlnException("java.lang.NullPointerException");
		exit(1);
	}
	auto arrLength = arrRef->arrayLength();
	stack.pushInt(arrLength);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void athrow::excute(Frame *frame) {
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void checkcast::excute(Frame *frame) {
	auto& stack = frame->operandStack;
	auto ref = stack.popRef();
	stack.pushRef(ref);
	if(ref== nullptr)
		return;
	auto cp = frame->method->_class->constantPool;
	auto classRef = (ClassRef*)(cp->getRef(index));
	auto _class = classRef->resolvedClass();
	if(!ref->isInstanceOf(_class))
	{
		printf("java.lang.ClassCastException.\n");
		exit(1);
	}
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void instanceof::excute(Frame *frame) {
	auto &stack = frame->operandStack;
	auto ref = stack.popRef();
	if(ref== nullptr)
	{
		stack.pushInt(0);
		return;
	}
	auto cp = frame->method->_class->constantPool;
	auto classRef = (ClassRef*)(cp->getRef(index));
	auto _class = classRef->resolvedClass();
	if(ref->isInstanceOf(_class))
		stack.pushInt(1);
	else
		stack.pushInt(0);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void monitorenter::excute(Frame *frame) {
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void monitiorexit::excute(Frame *frame) {
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}
