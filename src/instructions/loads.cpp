//
// Created by xuranus on 2/5/19.
//

#include "loads.h"
#include "../util/Console.h"

void iload::excute(Frame *frame) {
    auto val = frame->localVars.getInt(index);
    frame->operandStack.pushInt(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lload::excute(Frame *frame) {
    auto val = frame->localVars.getLong(index);
    frame->operandStack.pushLong(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void fload::excute(Frame *frame) {
    auto val = frame->localVars.getFloat(index);
    frame->operandStack.pushFloat(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dload::excute(Frame *frame) {
    auto val = frame->localVars.getDouble(index);
    frame->operandStack.pushDouble(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void aload::excute(Frame *frame) {
    auto val = frame->localVars.getRef(index);
    frame->operandStack.pushRef(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void iload_0::excute(Frame *frame) {
    auto val = frame->localVars.getInt(0);
    frame->operandStack.pushInt(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void iload_1::excute(Frame *frame) {
    auto val = frame->localVars.getInt(1);
    frame->operandStack.pushInt(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void iload_2::excute(Frame *frame) {
    auto val = frame->localVars.getInt(2);
    frame->operandStack.pushInt(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void iload_3::excute(Frame *frame) {
    auto val = frame->localVars.getInt(3);
    frame->operandStack.pushInt(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lload_0::excute(Frame *frame) {
    auto val = frame->localVars.getLong(0);
    frame->operandStack.pushLong(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lload_1::excute(Frame *frame) {
    auto val = frame->localVars.getLong(1);
    frame->operandStack.pushLong(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lload_2::excute(Frame *frame) {
    auto val = frame->localVars.getLong(2);
    frame->operandStack.pushLong(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lload_3::excute(Frame *frame) {
    auto val = frame->localVars.getLong(3);
    frame->operandStack.pushLong(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void fload_0::excute(Frame *frame) {
    auto val = frame->localVars.getFloat(0);
    frame->operandStack.pushFloat(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void fload_1::excute(Frame *frame) {
    auto val = frame->localVars.getFloat(1);
    frame->operandStack.pushFloat(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void fload_2::excute(Frame *frame) {
    auto val = frame->localVars.getFloat(2);
    frame->operandStack.pushFloat(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void fload_3::excute(Frame *frame) {
    auto val = frame->localVars.getFloat(3);
    frame->operandStack.pushFloat(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dload_0::excute(Frame *frame) {
    auto val = frame->localVars.getDouble(0);
    frame->operandStack.pushDouble(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dload_1::excute(Frame *frame) {
    auto val = frame->localVars.getDouble(1);
    frame->operandStack.pushDouble(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dload_2::excute(Frame *frame) {
    auto val = frame->localVars.getDouble(2);
    frame->operandStack.pushDouble(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dload_3::excute(Frame *frame) {
    auto val = frame->localVars.getDouble(3);
    frame->operandStack.pushDouble(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void aload_0::excute(Frame *frame) {
    auto val = frame->localVars.getRef(0);
    frame->operandStack.pushRef(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void aload_1::excute(Frame *frame) {
    auto val = frame->localVars.getRef(1);
    frame->operandStack.pushRef(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void aload_2::excute(Frame *frame) {
    auto val = frame->localVars.getRef(2);
    frame->operandStack.pushRef(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void aload_3::excute(Frame *frame) {
    auto val = frame->localVars.getRef(3);
    frame->operandStack.pushRef(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void iaload::excute(Frame *frame) {
    auto& stack = frame->operandStack;
    auto index = stack.popInt();
    auto arrRef = stack.popRef();
    if(arrRef == nullptr){
        Console::printlnException("java.lang.NullPointerException");
        exit(1);
    }
    auto ints = arrRef->ints();
    if(arrRef->arrayLength()<= index || index <0 )
    {
        Console::printlnError("java.lang.ArrayIndexOutOfBoundException");
        exit(1);
    }
    stack.pushInt(ints[index]);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void laload::excute(Frame *frame) {
    auto& stack = frame->operandStack;
    auto index = stack.popInt();
    auto arrRef = stack.popRef();
    if(arrRef == nullptr){
        Console::printlnException("java.lang.NullPointerException");
        exit(1);
    }
    auto longs = arrRef->longs();
    if(arrRef->arrayLength()<= index || index <0 )
    {
        Console::printlnError("java.lang.ArrayIndexOutOfBoundException");
        exit(1);
    }
    stack.pushLong(longs[index]);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void faload::excute(Frame *frame) {
    auto& stack = frame->operandStack;
    auto index = stack.popInt();
    auto arrRef = stack.popRef();
    if(arrRef == nullptr){
        Console::printlnException("java.lang.NullPointerException");
        exit(1);
    }
    auto floats = arrRef->floats();
    if(arrRef->arrayLength()<= index || index <0 )
    {
        Console::printlnError("java.lang.ArrayIndexOutOfBoundException");
        exit(1);
    }
    stack.pushFloat(floats[index]);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void daload::excute(Frame *frame) {
    auto& stack = frame->operandStack;
    auto index = stack.popInt();
    auto arrRef = stack.popRef();
    if(arrRef == nullptr){
        Console::printlnException("java.lang.NullPointerException");
        exit(1);
    }
    auto doubles = arrRef->doubles();
    if(arrRef->arrayLength()<= index || index <0 )
    {
        Console::printlnError("java.lang.ArrayIndexOutOfBoundException");
        exit(1);
    }
    stack.pushDouble(doubles[index]);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void aaload::excute(Frame *frame) {
    auto& stack = frame->operandStack;
    auto index = stack.popInt();
    auto arrRef = stack.popRef();
    if(arrRef == nullptr){
        Console::printlnException("java.lang.NullPointerException");
        exit(1);
    }
    auto refs = arrRef->refs();
    if(arrRef->arrayLength()<= index || index <0 )
    {
        Console::printlnError("java.lang.ArrayIndexOutOfBoundException");
        exit(1);
    }
    stack.pushRef(refs[index]);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void baload::excute(Frame *frame) {
    auto& stack = frame->operandStack;
    auto index = stack.popInt();
    auto arrRef = stack.popRef();
    if(arrRef == nullptr){
        Console::printlnException("java.lang.NullPointerException");
        exit(1);
    }
    auto bytes = arrRef->bytes();
    if(arrRef->arrayLength()<= index || index <0 )
    {
        Console::printlnError("java.lang.ArrayIndexOutOfBoundException");
        exit(1);
    }
    stack.pushInt(bytes[index]);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void caload::excute(Frame *frame) {
    auto& stack = frame->operandStack;
    auto index = stack.popInt();
    auto arrRef = stack.popRef();
    if(arrRef == nullptr){
        Console::printlnException("java.lang.NullPointerException");
        exit(1);
    }
    auto chars = arrRef->chars();
    if(arrRef->arrayLength()<= index || index <0 )
    {
        Console::printlnError("java.lang.ArrayIndexOutOfBoundException");
        exit(1);
    }
    stack.pushInt(chars[index]);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void saload::excute(Frame *frame) {
    auto& stack = frame->operandStack;
    auto index = stack.popInt();
    auto arrRef = stack.popRef();
    if(arrRef == nullptr){
        Console::printlnException("java.lang.NullPointerException");
        exit(1);
    }
    auto shorts = arrRef->shorts();
    if(arrRef->arrayLength()<= index || index <0 )
    {
        Console::printlnError("java.lang.ArrayIndexOutOfBoundException");
        exit(1);
    }
    stack.pushInt(shorts[index]);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}