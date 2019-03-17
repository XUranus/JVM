//
// Created by xuranus on 2/5/19.
//

//#define DEBUG_MODE 1


#include <string>
#include "constants.h"
#include "../runtime/Frame.h"
#include "../runtime/heap/StringPool.h"
#include "../util/Console.h"
#include "../runtime/heap/SymRef.h"

void nop::excute(Frame *frame) {
    //do nothing
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

void aconst_null::excute(Frame *frame) {
    frame->operandStack.pushRef(nullptr);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

void iconst_m1::excute(Frame *frame) {
    frame->operandStack.pushInt(-1);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

void iconst_0::excute(Frame *frame) {
    frame->operandStack.pushInt(0);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

void iconst_1::excute(Frame *frame) {
    frame->operandStack.pushInt(1);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

void iconst_2::excute(Frame *frame) {
    frame->operandStack.pushInt(2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

void iconst_3::excute(Frame *frame) {
    frame->operandStack.pushInt(3);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

void iconst_4::excute(Frame *frame) {
    frame->operandStack.pushInt(4);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

void iconst_5::excute(Frame *frame) {
    frame->operandStack.pushInt(5);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

void lconst_0::excute(Frame *frame) {
    frame->operandStack.pushLong(0);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

void lconst_1::excute(Frame *frame) {
    frame->operandStack.pushLong(1);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

void fconst_0::excute(Frame *frame) {
    frame->operandStack.pushFloat(0);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

void fconst_1::excute(Frame *frame) {
    frame->operandStack.pushFloat(1);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

void fconst_2::excute(Frame *frame) {
    frame->operandStack.pushFloat(2);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

void dconst_0::excute(Frame *frame) {
    frame->operandStack.pushDouble(0);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

void dconst_1::excute(Frame *frame) {
    frame->operandStack.pushDouble(1);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

void bipush::excute(Frame *frame) {
    frame->operandStack.pushInt(int32(val));
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

std::string bipush::toString()
{
    return getInstructionName()+" "+std::to_string(val);
}

void bipush::fetchOperands(BytesReader &reader)
{
    val = reader.readInt8();
}

void sipush::excute(Frame *frame) {
    frame->operandStack.pushInt(int32(val));
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

std::string sipush::toString()
{
    return getInstructionName()+" "+std::to_string(val);
}

void sipush::fetchOperands(BytesReader &reader)
{
    val = reader.readInt16();
}

void ldc::excute(Frame *frame) {
    auto &stack = frame->operandStack;
    auto _class = frame->method->_class;
    auto cp = frame->method->_class->constantPool;
    auto type = cp->getType(index);
    switch (type)
    {
        case Constant::ValueType::INT: {
            stack.pushInt(cp->getInt(index));
            break;
        }
        case Constant::ValueType::FLOAT: {
            stack.pushFloat(cp->getFloat(index));
            break;
        }
        case Constant::ValueType::STRING: {
            auto c = cp->getString(index);
            auto internedStr = StringPool::getStringPool()->getJString(_class->classloader,c);
            stack.pushRef(internedStr);
            break;
        }
        case Constant::ValueType::REF: {
            auto classRef = (ClassRef*)cp->getRef(index);
            auto classObj = classRef->resolvedClass()->jClass;
            stack.pushRef(classObj);
        }
        default:{
            printf("ldc not fully implemented. type: %d\n",type);
            break;
        }
    }
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

void ldc_w::excute(Frame *frame) {
    //todo::
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}

void ldc2_w::excute(Frame *frame) {
    //todo::
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
    frame->localVars.debug();
    frame->operandStack.debug();
    printf("\n");
#endif
}
