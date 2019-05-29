//
// Created by xuranus on 2/5/19.
//

#include "extended.h"
#include "../runtime/heap/SymRef.h"
#include "../util/Console.h"

void wide::excute(Frame *frame) {
    switch (newOpCode){
        case 0x15: {//iload
            auto val = frame->localVars.getInt(index);
            frame->operandStack.pushInt(val);
            return;
        }
        case 0x16: {//lload
            auto val = frame->localVars.getLong(index);
            frame->operandStack.pushLong(val);
            return;
        }
        case 0x17: {//fload
            auto val = frame->localVars.getFloat(index);
            frame->operandStack.pushFloat(val);
            return;
        }
        case 0x18: {//dload
            auto val = frame->localVars.getDouble(index);
            frame->operandStack.pushDouble(val);
            return;
        }
        case 0x19: {//aload
            auto val = frame->localVars.getRef(index);
            frame->operandStack.pushRef(val);
            return;
        }
        case 0x36: {//istore
            auto val = frame->operandStack.popInt();
            frame->localVars.setInt(index,val);
            return;
        }
        case 0x37: {//lstore
            auto val = frame->operandStack.popLong();
            frame->localVars.setLong(index,val);
            return;
        }
        case 0x38: {//fstore
            auto val = frame->operandStack.popFloat();
            frame->localVars.setFloat(index,val);
            return;
        }
        case 0x39: {//dstore
            auto val = frame->operandStack.popDouble();
            frame->localVars.setDouble(index,val);
            return;
        }
        case 0x3a: {//astore
            auto val = frame->operandStack.popRef();
            frame->localVars.setRef(index,val);
            return;
        }
        case 0xa9: {//ret
            //TODO:not support yet
            printf("instruction [wide] do not support [ret] anymore.\n");
            exit(1);
        }
        case 0x84: {//iinc
            auto val = frame->localVars.getInt(index);
            val += _const;
            frame->localVars.setInt(index,val);
            return;
        }
        default:{
            printf("instruction [wide] opCode Error,opCode: 0x%02x\n",opCode);
            exit(1);
        }
    }
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

std::string wide::toString() {
    if(newOpCode==0x84)
        return "wide "+std::to_string(newOpCode)+" "+std::to_string(index)+" "+std::to_string(_const);
    else
        return "wide "+std::to_string(newOpCode)+" "+std::to_string(index);
}

void wide::fetchOperands(BytesReader &reader) {
    newOpCode = reader.readUint8();
    index = reader.readUint16();
    if(newOpCode==0x84)//0x84 iinc
        _const = int32(reader.readInt16());
}

void multianewarray::fetchOperands(BytesReader &reader) {
    index = reader.readUint16();
    dimensions = reader.readUint8();
}

void multianewarray::excute(Frame *frame) {
    auto cp = frame->method->_class->constantPool;
    auto classRef = (ClassRef*)cp->getRef(index);
    auto arrClass = classRef->resolvedClass();

    auto& stack = frame->operandStack;
    auto counts = stack.popAndCheckCounts(dimensions);
    auto arr = arrClass->newMultiDimensionArray(counts);
    stack.pushRef(arr);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

std::string multianewarray::toString() {
    return "multianewarray "+std::to_string(index)+" "+std::to_string(dimensions);
}

void ifnull::excute(Frame *frame) {
    auto ref = frame->operandStack.popRef();
    if(ref == nullptr)
        frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void ifnonnull::excute(Frame *frame) {
    auto ref = frame->operandStack.popRef();
    if(ref == nullptr)
        frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void goto_w::excute(Frame *frame) {
    frame->branch(offset);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

std::string goto_w::toString() {
    return "goto_w "+std::to_string(offset);
}

void goto_w::fetchOperands(BytesReader &reader) {
    offset = (int)reader.readInt32();
}


void jsr_w::excute(Frame *frame) {
    printf("instruction [jsr_w] not support after java 6.\n");
    exit(1);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void jsr_w::fetchOperands(BytesReader &reader) {
    offset = (int)reader.readInt32();
}

std::string jsr_w::toString() {
    return "jsr_w "+std::to_string(offset);
}