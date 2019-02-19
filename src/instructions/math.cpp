//
// Created by xuranus on 2/5/19.
//

#include "math.h"
#include <cmath>

void iadd::excute(Frame *frame) {
    auto v1 = frame->operandStack.popInt();
    auto v2 = frame->operandStack.popInt();
    frame->operandStack.pushInt(v1+v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void ladd::excute(Frame *frame) {
    auto v1 = frame->operandStack.popLong();
    auto v2 = frame->operandStack.popLong();
    frame->operandStack.pushLong(v1+v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void fadd::excute(Frame *frame) {
    auto v1 = frame->operandStack.popFloat();
    auto v2 = frame->operandStack.popFloat();
    frame->operandStack.pushFloat(v1+v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dadd::excute(Frame *frame) {
    auto v1 = frame->operandStack.popDouble();
    auto v2 = frame->operandStack.popDouble();
    frame->operandStack.pushDouble(v1+v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void isub::excute(Frame *frame) {
    auto v2 = frame->operandStack.popInt();
    auto v1 = frame->operandStack.popInt();
    frame->operandStack.pushInt(v1-v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lsub::excute(Frame *frame) {
    auto v2 = frame->operandStack.popLong();
    auto v1 = frame->operandStack.popLong();
    frame->operandStack.pushLong(v1-v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void fsub::excute(Frame *frame) {
    auto v2 = frame->operandStack.popFloat();
    auto v1 = frame->operandStack.popFloat();
    frame->operandStack.pushFloat(v1-v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dsub::excute(Frame *frame) {
    auto v2 = frame->operandStack.popDouble();
    auto v1 = frame->operandStack.popDouble();
    frame->operandStack.pushDouble(v1-v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void imul::excute(Frame *frame) {
    auto v2 = frame->operandStack.popInt();
    auto v1 = frame->operandStack.popInt();
    frame->operandStack.pushInt(v1*v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lmul::excute(Frame *frame) {
    auto v2 = frame->operandStack.popLong();
    auto v1 = frame->operandStack.popLong();
    frame->operandStack.pushLong(v1*v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void fmul::excute(Frame *frame) {
    auto v2 = frame->operandStack.popFloat();
    auto v1 = frame->operandStack.popFloat();
    frame->operandStack.pushFloat(v1*v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dmul::excute(Frame *frame) {
    auto v2 = frame->operandStack.popDouble();
    auto v1 = frame->operandStack.popDouble();
    frame->operandStack.pushDouble(v1*v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void idiv::excute(Frame *frame) {
    auto v2 = frame->operandStack.popInt();
    auto v1 = frame->operandStack.popInt();
    frame->operandStack.pushInt(v1/v2);
    //TODO::div by 0 exception
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void ldiv_::excute(Frame *frame) {
    auto v2 = frame->operandStack.popLong();
    auto v1 = frame->operandStack.popLong();
    frame->operandStack.pushLong(v1/v2);
    //TODO::div by 0 exception
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void fdiv::excute(Frame *frame) {
    auto v2 = frame->operandStack.popFloat();
    auto v1 = frame->operandStack.popFloat();
    frame->operandStack.pushFloat(v1/v2);
    //TODO::div by 0 exception
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void ddiv::excute(Frame *frame) {
    auto v2 = frame->operandStack.popDouble();
    auto v1 = frame->operandStack.popDouble();
    frame->operandStack.pushDouble(v1/v2);
    //TODO::div by 0 exception
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void irem::excute(Frame *frame) {
    auto v2 = frame->operandStack.popInt();
    auto v1 = frame->operandStack.popInt();
    frame->operandStack.pushInt(v1%v2);
    //TODO::div by 0 exception
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lrem::excute(Frame *frame) {
    auto v2 = frame->operandStack.popLong();
    auto v1 = frame->operandStack.popLong();
    frame->operandStack.pushInt(v1%v2);
    //TODO::div by 0 exception
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void frem::excute(Frame *frame) {
    auto v2 = frame->operandStack.popFloat();
    auto v1 = frame->operandStack.popFloat();
    frame->operandStack.pushFloat((float)fmod(v1,v2));
    //TODO::div by 0 exception
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void drem::excute(Frame *frame) {
    auto v2 = frame->operandStack.popDouble();
    auto v1 = frame->operandStack.popDouble();
    frame->operandStack.pushDouble(fmod(v1,v2));
    //TODO::div by 0 exception
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void ineg::excute(Frame *frame) {
    auto val = frame->operandStack.popInt();
    frame->operandStack.pushInt(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lneg::excute(Frame *frame) {
    auto val = frame->operandStack.popLong();
    frame->operandStack.pushLong(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void fneg::excute(Frame *frame) {
    auto val = frame->operandStack.popFloat();
    frame->operandStack.pushFloat(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dneg::excute(Frame *frame) {
    auto val = frame->operandStack.popDouble();
    frame->operandStack.pushDouble(val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void ishl::excute(Frame *frame) {
    auto v2 = frame->operandStack.popInt();
    auto v1 = frame->operandStack.popInt();
    frame->operandStack.pushInt(v1<<(uint32(v2) & 0x1f));
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lshl::excute(Frame *frame) {
    auto v2 = frame->operandStack.popInt();
    auto v1 = frame->operandStack.popLong();
    frame->operandStack.pushLong(v1<<(uint32(v2) & 0x3f));
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void ishr::excute(Frame *frame) {
    auto v2 = frame->operandStack.popInt();
    auto v1 = frame->operandStack.popInt();
    frame->operandStack.pushInt(v1>>(uint32(v2) & 0x1f));
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lshr::excute(Frame *frame) {
    auto v2 = frame->operandStack.popInt();
    auto v1 = frame->operandStack.popLong();
    frame->operandStack.pushLong(v1>>(uint32(v2) & 0x3f));
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void iushr::excute(Frame *frame) {
    auto v2 = frame->operandStack.popInt();
    auto v1 = frame->operandStack.popInt();
    auto s = uint32 (v2) & 0x1f;
    frame->operandStack.pushInt(int32 (uint32(v1) >> s));
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lushr::excute(Frame *frame) {
    auto v2 = frame->operandStack.popInt();
    auto v1 = frame->operandStack.popLong();
    auto s = uint32 (v2) & 0x3f;
    frame->operandStack.pushLong((unsigned long)(v1) >> s);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void iand::excute(Frame *frame) {
    auto v2 = frame->operandStack.popInt();
    auto v1 = frame->operandStack.popInt();
    frame->operandStack.pushInt(v1 & v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void land::excute(Frame *frame) {
    auto v2 = frame->operandStack.popLong();
    auto v1 = frame->operandStack.popLong();
    frame->operandStack.pushLong(v1 & v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void ior::excute(Frame *frame) {
    auto v2 = frame->operandStack.popInt();
    auto v1 = frame->operandStack.popInt();
    frame->operandStack.pushInt(v1 | v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lor::excute(Frame *frame) {
    auto v2 = frame->operandStack.popLong();
    auto v1 = frame->operandStack.popLong();
    frame->operandStack.pushLong(v1 | v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void ixor::excute(Frame *frame) {
    auto v2 = frame->operandStack.popInt();
    auto v1 = frame->operandStack.popInt();
    frame->operandStack.pushInt(v1 ^ v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lxor::excute(Frame *frame) {
    auto v2 = frame->operandStack.popLong();
    auto v1 = frame->operandStack.popLong();
    frame->operandStack.pushLong(v1 ^ v2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void iinc::excute(Frame *frame) {
    auto val = frame->localVars.getInt(index);
    val += _const;
    frame->localVars.setInt(index,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

std::string iinc::toString()
{
    return getInstructionName()+" "+std::to_string(index)+" "+std::to_string(_const);
}

void iinc::fetchOperands(BytesReader &reader)
{
    index = (unsigned int)reader.readUint8();
    _const = int32 (reader.readInt8());
}
