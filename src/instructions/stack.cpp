//
// Created by xuranus on 2/5/19.
//

#include "stack.h"


void pop::excute(Frame *frame) {
    frame->operandStack.popSlot();
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void pop2::excute(Frame *frame) {
    frame->operandStack.popSlot();
    frame->operandStack.popSlot();
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dup::excute(Frame *frame) {
    auto slot = frame->operandStack.popSlot();
    frame->operandStack.pushSlot(slot);
    frame->operandStack.pushSlot(slot);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dup_x1::excute(Frame *frame) {
    auto v1 = frame->operandStack.popSlot();
    auto v2 = frame->operandStack.popSlot();
    frame->operandStack.pushSlot(v1);
    frame->operandStack.pushSlot(v2);
    frame->operandStack.pushSlot(v1);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dup_x2::excute(Frame *frame) {
    auto v1 = frame->operandStack.popSlot();
    auto v2 = frame->operandStack.popSlot();
    auto v3 = frame->operandStack.popSlot();
    frame->operandStack.pushSlot(v1);
    frame->operandStack.pushSlot(v3);
    frame->operandStack.pushSlot(v2);
    frame->operandStack.pushSlot(v1);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dup2::excute(Frame *frame) {
    auto v1 = frame->operandStack.popSlot();
    auto v2 = frame->operandStack.popSlot();
    frame->operandStack.pushSlot(v2);
    frame->operandStack.pushSlot(v1);
    frame->operandStack.pushSlot(v2);
    frame->operandStack.pushSlot(v1);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dup2_x1::excute(Frame *frame) {
    auto v1 = frame->operandStack.popSlot();
    auto v2 = frame->operandStack.popSlot();
    auto v3 = frame->operandStack.popSlot();
    frame->operandStack.pushSlot(v2);
    frame->operandStack.pushSlot(v1);
    frame->operandStack.pushSlot(v3);
    frame->operandStack.pushSlot(v2);
    frame->operandStack.pushSlot(v1);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dup2_x2::excute(Frame *frame) {
    auto v1 = frame->operandStack.popSlot();
    auto v2 = frame->operandStack.popSlot();
    auto v3 = frame->operandStack.popSlot();
    auto v4 = frame->operandStack.popSlot();
    frame->operandStack.pushSlot(v2);
    frame->operandStack.pushSlot(v1);
    frame->operandStack.pushSlot(v4);
    frame->operandStack.pushSlot(v3);
    frame->operandStack.pushSlot(v2);
    frame->operandStack.pushSlot(v1);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void swap::excute(Frame *frame) {
    auto v1 = frame->operandStack.popSlot();
    auto v2 = frame->operandStack.popSlot();
    frame->operandStack.pushSlot(v1);
    frame->operandStack.pushSlot(v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}