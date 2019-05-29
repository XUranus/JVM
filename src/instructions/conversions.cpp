//
// Created by xuranus on 2/5/19.
//

#include "conversions.h"



void i2l::excute(Frame *frame) {
    auto v = frame->operandStack.popInt();
    frame->operandStack.pushLong((long)v);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void i2f::excute(Frame *frame) {
    auto v = frame->operandStack.popInt();
    frame->operandStack.pushFloat((float)v);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void i2d::excute(Frame *frame) {
    auto v = frame->operandStack.popInt();
    frame->operandStack.pushDouble((double)v);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void l2i::excute(Frame *frame) {
    auto v = frame->operandStack.popLong();
    frame->operandStack.pushInt((int)v);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void l2f::excute(Frame *frame) {
    auto v = frame->operandStack.popLong();
    frame->operandStack.pushFloat((float)v);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void l2d::excute(Frame *frame) {
    auto v = frame->operandStack.popLong();
    frame->operandStack.pushDouble((double)v);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void f2i::excute(Frame *frame) {
    auto v = frame->operandStack.popFloat();
    frame->operandStack.pushInt(int32(v));
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void f2l::excute(Frame *frame) {
    auto v = frame->operandStack.popFloat();
    frame->operandStack.pushLong((long)v);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void f2d::excute(Frame *frame) {
    auto v = frame->operandStack.popFloat();
    frame->operandStack.pushDouble((double)v);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void d2i::excute(Frame *frame) {
    auto v = frame->operandStack.popDouble();
    frame->operandStack.pushInt((int)v);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void d2l::excute(Frame *frame) {
    auto v = frame->operandStack.popDouble();
    frame->operandStack.pushLong((long)v);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void d2f::excute(Frame *frame) {
    auto v = frame->operandStack.popDouble();
    frame->operandStack.pushFloat((float)v);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void i2b::excute(Frame *frame) {
    auto v = frame->operandStack.popInt();
    frame->operandStack.pushInt((int32)(int8(v)));
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void i2c::excute(Frame *frame) {
    auto v = frame->operandStack.popInt();
    frame->operandStack.pushInt((int32)(uint16(v)));
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void i2s::excute(Frame *frame) {
    auto v = frame->operandStack.popInt();
    frame->operandStack.pushInt((int32)(int16(v)));
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}