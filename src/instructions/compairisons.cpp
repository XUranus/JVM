//
// Created by xuranus on 2/5/19.
//

#include "compairisons.h"


void lcmp::excute(Frame *frame) {
    auto v2 = frame->operandStack.popLong();
    auto v1 = frame->operandStack.popLong();
    if(v1 > v2) frame->operandStack.pushInt(1);
    else if(v1 == v2) frame->operandStack.pushInt(0);
    else frame->operandStack.pushInt(-1);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void fcmpl::excute(Frame *frame) {
    auto v2 = frame->operandStack.popFloat();
    auto v1 = frame->operandStack.popFloat();
    if(v1 > v2) frame->operandStack.pushInt(1);
    else if(v1 == v2) frame->operandStack.pushInt(0);
    else if(v1 < v2) frame->operandStack.pushInt(-1);
    else frame->operandStack.pushInt(-1);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void fcmpg::excute(Frame *frame) {
    auto v2 = frame->operandStack.popFloat();
    auto v1 = frame->operandStack.popFloat();
    if(v1 > v2) frame->operandStack.pushInt(1);
    else if(v1 == v2) frame->operandStack.pushInt(0);
    else if(v1 < v2) frame->operandStack.pushInt(-1);
    else frame->operandStack.pushInt(1);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dcmpl::excute(Frame *frame) {
    auto v2 = frame->operandStack.popDouble();
    auto v1 = frame->operandStack.popDouble();
    if(v1 > v2) frame->operandStack.pushInt(1);
    else if(v1 == v2) frame->operandStack.pushInt(0);
        //else if(v1 < v2) frame->operandStack.pushInt(-1); //not necessay to compare
    else frame->operandStack.pushInt(-1);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dcmpg::excute(Frame *frame) {
    auto v2 = frame->operandStack.popDouble();
    auto v1 = frame->operandStack.popDouble();
    if(v1 > v2) frame->operandStack.pushInt(1);
    else if(v1 == v2) frame->operandStack.pushInt(0);
    else if(v1 < v2) frame->operandStack.pushInt(-1);
    else frame->operandStack.pushInt(1);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void ifeq::excute(Frame *frame) {
    auto val = frame->operandStack.popInt();
    if(val == 0) frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void ifne::excute(Frame *frame) {
    auto val = frame->operandStack.popInt();
    if(val != 0) frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void iflt::excute(Frame *frame) {
    auto val = frame->operandStack.popInt();
    if(val < 0) frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void ifge::excute(Frame *frame) {
    auto val = frame->operandStack.popInt();
    if(val >= 0) frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void ifgt::excute(Frame *frame) {
    auto val = frame->operandStack.popInt();
    if(val > 0) frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void ifle::excute(Frame *frame) {
    auto val = frame->operandStack.popInt();
    if(val <= 0) frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void if_icmpeq::excute(Frame *frame) {
    auto val2 = frame->operandStack.popInt();
    auto val1 = frame->operandStack.popInt();
    if(val1 == val2) frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void if_icmpne::excute(Frame *frame) {
    auto val2 = frame->operandStack.popInt();
    auto val1 = frame->operandStack.popInt();
    if(val1 != val2) frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void if_icmplt::excute(Frame *frame) {
    auto val2 = frame->operandStack.popInt();
    auto val1 = frame->operandStack.popInt();
    if(val1 < val2) frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void if_icmpge::excute(Frame *frame) {
    auto val2 = frame->operandStack.popInt();
    auto val1 = frame->operandStack.popInt();
    if(val1 >= val2) frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void if_icmpgt::excute(Frame *frame) {
    auto val2 = frame->operandStack.popInt();
    auto val1 = frame->operandStack.popInt();
    if(val1 > val2) frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void if_icmple::excute(Frame *frame) {
    auto val2 = frame->operandStack.popInt();
    auto val1 = frame->operandStack.popInt();
    if(val1 <= val2) frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void if_acmpeq::excute(Frame *frame) {
    auto val2 = frame->operandStack.popRef();
    auto val1 = frame->operandStack.popRef();
    if(val1 == val2) frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void if_acmpne::excute(Frame *frame) {
    auto val2 = frame->operandStack.popRef();
    auto val1 = frame->operandStack.popRef();
    if(val1 != val2) frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}
