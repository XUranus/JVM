//
// Created by xuranus on 2/5/19.
//

#include "reserved.h"
#include "../native/NativeRegistry.h"
#include "../util/Console.h"

typedef void (*PTRFUN)(Frame*);

void breakpoint::excute(Frame *frame) {
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void impdep1::excute(Frame *frame) {
    auto method = frame->method;
    auto className = method->_class->name;
    auto methodDescriptor = method->descriptor;
    auto methodName = method->name;
    auto nativeMethod = NativeRegistry::getNativeRegistery()->findNativeMethod(className,methodName,methodDescriptor);
    if(nativeMethod == nullptr) {
        Console::printlnError("java.lang.UnsatisfiedLinkError: "+className+"."+methodName+"."+methodDescriptor);
    }  else (*nativeMethod)(frame);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void impdep2::excute(Frame *frame) {
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}
