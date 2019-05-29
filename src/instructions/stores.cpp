//
// Created by xuranus on 2/5/19.
//

#include "stores.h"
#include "../util/Console.h"

void istore::excute(Frame *frame) {
    auto val = frame->operandStack.popInt();
    frame->localVars.setInt(index,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lstore::excute(Frame *frame) {
    auto val = frame->operandStack.popLong();
    frame->localVars.setLong(index,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void fstore::excute(Frame *frame) {
    auto val = frame->operandStack.popFloat();
    frame->localVars.setFloat(index,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dstore::excute(Frame *frame) {
    auto val = frame->operandStack.popDouble();
    frame->localVars.setDouble(index,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void astore::excute(Frame *frame) {
    auto val = frame->operandStack.popRef();
    frame->localVars.setRef(index,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void istore_0::excute(Frame *frame) {
    auto val = frame->operandStack.popInt();
    frame->localVars.setInt(0,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void istore_1::excute(Frame *frame) {
    auto val = frame->operandStack.popInt();
    frame->localVars.setInt(1,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void istore_2::excute(Frame *frame) {
    auto val = frame->operandStack.popInt();
    frame->localVars.setInt(2,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void istore_3::excute(Frame *frame) {
    auto val = frame->operandStack.popInt();
    frame->localVars.setInt(3,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lstore_0::excute(Frame *frame) {
    auto val = frame->operandStack.popLong();
    frame->localVars.setLong(0,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lstore_1::excute(Frame *frame) {
    auto val = frame->operandStack.popLong();
    frame->localVars.setLong(1,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lstore_2::excute(Frame *frame) {
    auto val = frame->operandStack.popLong();
    frame->localVars.setLong(2,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lstore_3::excute(Frame *frame) {
    auto val = frame->operandStack.popLong();
    frame->localVars.setLong(3,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void fstore_0::excute(Frame *frame) {
    auto val = frame->operandStack.popFloat();
    frame->localVars.setFloat(0,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void fstore_1::excute(Frame *frame) {
    auto val = frame->operandStack.popFloat();
    frame->localVars.setFloat(1,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void fstore_2::excute(Frame *frame) {
    auto val = frame->operandStack.popFloat();
    frame->localVars.setFloat(2,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void fstore_3::excute(Frame *frame) {
    auto val = frame->operandStack.popFloat();
    frame->localVars.setFloat(3,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dstore_0::excute(Frame *frame) {
    auto val = frame->operandStack.popDouble();
    frame->localVars.setDouble(0,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dstore_1::excute(Frame *frame) {
    auto val = frame->operandStack.popDouble();
    frame->localVars.setDouble(1,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dstore_2::excute(Frame *frame) {
    auto val = frame->operandStack.popDouble();
    frame->localVars.setDouble(2,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dstore_3::excute(Frame *frame) {
    auto val = frame->operandStack.popDouble();
    frame->localVars.setDouble(3,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void astore_0::excute(Frame *frame) {
    auto val = frame->operandStack.popRef();
    frame->localVars.setRef(0,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void astore_1::excute(Frame *frame) {
    auto val = frame->operandStack.popRef();
    frame->localVars.setRef(1,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void astore_2::excute(Frame *frame) {
    auto val = frame->operandStack.popRef();
    frame->localVars.setRef(2,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void astore_3::excute(Frame *frame) {
    auto val = frame->operandStack.popRef();
    frame->localVars.setRef(3,val);
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void iastore::excute(Frame *frame) {
    auto val = frame->operandStack.popInt();
    auto index = frame->operandStack.popInt();
    auto arrRef = frame->operandStack.popRef();
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
    ints[index] = val;
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void lastore::excute(Frame *frame) {
    auto val = frame->operandStack.popLong();
    auto index = frame->operandStack.popInt();
    auto arrRef = frame->operandStack.popRef();
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
    longs[index] = val;
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void fastore::excute(Frame *frame) {
    auto val = frame->operandStack.popFloat();
    auto index = frame->operandStack.popInt();
    auto arrRef = frame->operandStack.popRef();
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
    floats[index] = val;
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void dastore::excute(Frame *frame) {
    auto val = frame->operandStack.popDouble();
    auto index = frame->operandStack.popInt();
    auto arrRef = frame->operandStack.popRef();
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
    doubles[index] = val;
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void aastore::excute(Frame *frame) {
    auto val = frame->operandStack.popRef();
    auto index = frame->operandStack.popInt();
    auto arrRef = frame->operandStack.popRef();
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
    refs[index] = val;
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void bastore::excute(Frame *frame) {
    auto val = frame->operandStack.popInt();
    auto index = frame->operandStack.popInt();
    auto arrRef = frame->operandStack.popRef();
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
    bytes[index] = (int8)val;
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void castore::excute(Frame *frame) {
    auto val = frame->operandStack.popInt();
    auto index = frame->operandStack.popInt();
    auto arrRef = frame->operandStack.popRef();
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
    chars[index] = (uint16)val;
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}

void sastore::excute(Frame *frame) {
    auto val = frame->operandStack.popInt();
    auto index = frame->operandStack.popInt();
    auto arrRef = frame->operandStack.popRef();
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
    shorts[index] = (int16)val;
#ifdef DEBUG_MODE
    printf("[Excuting: %s]\n",toString().c_str());
	frame->localVars.debug();
	frame->operandStack.debug();
	printf("\n");
#endif
}
