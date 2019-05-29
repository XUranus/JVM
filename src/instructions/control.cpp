//
// Created by xuranus on 2/5/19.
//

#include "control.h"
#include "../util/Console.h"

void goto_::excute(Frame *frame) {
    frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void jsr::excute(Frame *frame) {
    printf("instruction [jsr] not support after java 6.\n");
    exit(1);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void ret::excute(Frame *frame) {
    printf("instruction [ret] not support after java 6.\n");
    exit(1);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void tableswitch::excute(Frame *frame) {
    int offset = 0;
    auto index = frame->operandStack.popInt();
    if(index >= low && index <= high)
        offset = (int)jumpOffsets[index-low];
    else
        offset = (int)defaultOffset;
    frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void tableswitch::fetchOperands(BytesReader &reader) {
    reader.skipPadding();
    defaultOffset = reader.readInt32();
    low = reader.readInt32();
    high = reader.readInt32();
    auto jumpOffsetsCount = high - low + 1;
    jumpOffsets = reader.readInt32s(jumpOffsetsCount);
}

std::string tableswitch::toString() {
    //TODO
    return "tableswitch";
}


void lookupswitch::excute(Frame *frame) {
    auto key = frame->operandStack.popInt();
    for(auto i=int32(0);i<npairs*2;i+=2)
    {
        if(mathchOffsets[i] == key) {
            auto offset = mathchOffsets[i+1];
            frame->branch((int)offset);
            return;
        }
    }
    frame->branch(defaultOffsets);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lookupswitch::fetchOperands(BytesReader &reader) {
    reader.skipPadding();
    defaultOffsets = reader.readInt32();
    npairs = reader.readInt32();
    mathchOffsets = reader.readInt32s(npairs*2);
}

std::string lookupswitch::toString() {
    //TODO:
    return "lookswitch";
}

void ireturn::excute(Frame *frame) {
    auto thread = frame->thread;
    auto currentFrame = thread->popFrame();
    auto invokerFrame = thread->currentFrame();
    auto retVal = currentFrame->operandStack.popInt();
    invokerFrame->operandStack.pushInt(retVal);

    //delete currentFrame;//TODO::fix it! code 134 signal 6
    frame = invokerFrame;//for debug use
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lreturn::excute(Frame *frame) {
    auto thread = frame->thread;
    auto currentFrame = thread->popFrame();
    auto invokerFrame = thread->currentFrame();
    auto retVal = currentFrame->operandStack.popLong();
    invokerFrame->operandStack.pushLong(retVal);

    //delete currentFrame;//TODO::fix it! code 134 signal 6
    frame = invokerFrame;//for debug use
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void freturn::excute(Frame *frame) {
    auto thread = frame->thread;
    auto currentFrame = thread->popFrame();
    auto invokerFrame = thread->currentFrame();
    auto retVal = currentFrame->operandStack.popFloat();
    invokerFrame->operandStack.pushFloat(retVal);

    //delete currentFrame;//TODO::fix it! code 134 signal 6
    frame = invokerFrame;//for debug use
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dreturn::excute(Frame *frame) {
    auto thread = frame->thread;
    auto currentFrame = thread->popFrame();
    auto invokerFrame = thread->currentFrame();
    auto retVal = currentFrame->operandStack.popDouble();
    invokerFrame->operandStack.pushDouble(retVal);

    //delete currentFrame;//TODO::fix it! code 134 signal 6
    frame = invokerFrame;//for debug use
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void areturn::excute(Frame *frame) {
    auto thread = frame->thread;
    auto currentFrame = thread->popFrame();
    auto invokerFrame = thread->currentFrame();
    auto retVal = currentFrame->operandStack.popRef();
    invokerFrame->operandStack.pushRef(retVal);

    //delete currentFrame;//TODO::fix it! code 134 signal 6
    frame = invokerFrame;//for debug use
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void return_::excute(Frame *frame) {
    auto currentFrame = frame->thread->popFrame();
    //delete currentFrame;//TODO::fix it! code 134 signal 6

#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}