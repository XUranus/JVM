//
// Created by xuranus on 2/5/19.
//

#include "loads.h"
#include "../common/Exception.h"
#include "../runtime/heap/Object.h"

namespace instruction {

    void iload::execute(runtime::Frame* frame) {
        auto val = frame->localVars.intValue(index);
        frame->operandStack.pushInt(val);
    }

    void lload::execute(runtime::Frame* frame) {
        auto val = frame->localVars.longValue(index);
        frame->operandStack.pushLong(val);
    }

    void fload::execute(runtime::Frame* frame) {
        auto val = frame->localVars.floatValue(index);
        frame->operandStack.pushFloat(val);
    }

    void dload::execute(runtime::Frame* frame) {
        auto val = frame->localVars.doubleValue(index);
        frame->operandStack.pushDouble(val);
    }

    void aload::execute(runtime::Frame* frame) {
        auto val = frame->localVars.refValue(index);
        frame->operandStack.pushRef(val);
    }

    void iload_0::execute(runtime::Frame* frame) {
        auto val = frame->localVars.intValue(0);
        frame->operandStack.pushInt(val);
    }

    void iload_1::execute(runtime::Frame* frame) {
        auto val = frame->localVars.intValue(1);
        frame->operandStack.pushInt(val);
    }

    void iload_2::execute(runtime::Frame* frame) {
        auto val = frame->localVars.intValue(2);
        frame->operandStack.pushInt(val);
    }

    void iload_3::execute(runtime::Frame* frame) {
        auto val = frame->localVars.intValue(3);
        frame->operandStack.pushInt(val);
    }

    void lload_0::execute(runtime::Frame* frame) {
        auto val = frame->localVars.longValue(0);
        frame->operandStack.pushLong(val);
    }

    void lload_1::execute(runtime::Frame* frame) {
        auto val = frame->localVars.longValue(1);
        frame->operandStack.pushLong(val);
    }

    void lload_2::execute(runtime::Frame* frame) {
        auto val = frame->localVars.longValue(2);
        frame->operandStack.pushLong(val);
    }

    void lload_3::execute(runtime::Frame* frame) {
        auto val = frame->localVars.longValue(3);
        frame->operandStack.pushLong(val);
    }

    void fload_0::execute(runtime::Frame* frame) {
        auto val = frame->localVars.floatValue(0);
        frame->operandStack.pushFloat(val);
    }

    void fload_1::execute(runtime::Frame* frame) {
        auto val = frame->localVars.floatValue(1);
        frame->operandStack.pushFloat(val);
    }

    void fload_2::execute(runtime::Frame* frame) {
        auto val = frame->localVars.floatValue(2);
        frame->operandStack.pushFloat(val);
    }

    void fload_3::execute(runtime::Frame* frame) {
        auto val = frame->localVars.floatValue(3);
        frame->operandStack.pushFloat(val);
    }

    void dload_0::execute(runtime::Frame* frame) {
        auto val = frame->localVars.doubleValue(0);
        frame->operandStack.pushDouble(val);
    }

    void dload_1::execute(runtime::Frame* frame) {
        auto val = frame->localVars.doubleValue(1);
        frame->operandStack.pushDouble(val);
    }

    void dload_2::execute(runtime::Frame* frame) {
        auto val = frame->localVars.doubleValue(2);
        frame->operandStack.pushDouble(val);
    }

    void dload_3::execute(runtime::Frame* frame) {
        auto val = frame->localVars.doubleValue(3);
        frame->operandStack.pushDouble(val);
    }

    void aload_0::execute(runtime::Frame* frame) {
        auto val = frame->localVars.refValue(0);
        frame->operandStack.pushRef(val);
    }

    void aload_1::execute(runtime::Frame* frame) {
        auto val = frame->localVars.refValue(1);
        frame->operandStack.pushRef(val);
    }

    void aload_2::execute(runtime::Frame* frame) {
        auto val = frame->localVars.refValue(2);
        frame->operandStack.pushRef(val);
    }

    void aload_3::execute(runtime::Frame* frame) {
        auto val = frame->localVars.refValue(3);
        frame->operandStack.pushRef(val);
    }

    void iaload::execute(runtime::Frame* frame) {
        auto &stack = frame->operandStack;
        int index = stack.popInt();
        heap::Object* object = stack.popRef();
        if (!object) {
            exception::fatal("java.lang.NullPointerException");
        }
        int* intArray = object->intArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
        }
        stack.pushInt(intArray[index]);
    }

    void laload::execute(runtime::Frame* frame) {
        auto &stack = frame->operandStack;
        int index = stack.popInt();
        heap::Object* object = stack.popRef();
        if (!object) {
            exception::fatal("java.lang.NullPointerException");
        }
        long* longArray = object->longArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
        }
        stack.pushLong(longArray[index]);
    }

    void faload::execute(runtime::Frame* frame) {
        auto &stack = frame->operandStack;
        int index = stack.popInt();
        heap::Object* object = stack.popRef();
        if (!object) {
            exception::fatal("java.lang.NullPointerException");
        }
        float* floatArray = object->floatArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
        }
        stack.pushFloat(floatArray[index]);
    }

    void daload::execute(runtime::Frame* frame) {
        auto &stack = frame->operandStack;
        int index = stack.popInt();
        heap::Object* object = stack.popRef();
        if (!object) {
            exception::fatal("java.lang.NullPointerException");
        }
        double* doubleArray = object->doubleArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
        }
        stack.pushDouble(doubleArray[index]);
    }

    void aaload::execute(runtime::Frame* frame) {
        auto &stack = frame->operandStack;
        int index = stack.popInt();
        heap::Object* object = stack.popRef();
        if (!object) {
            exception::fatal("java.lang.NullPointerException");
        }
        heap::Object** refArray = object->objectRefArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
        }
        stack.pushRef(refArray[index]);
    }

    void baload::execute(runtime::Frame* frame) {
        auto &stack = frame->operandStack;
        int index = stack.popInt();
        heap::Object* object = stack.popRef();
        if (!object) {
            exception::fatal("java.lang.NullPointerException");
        }
        char *byteArray = object->byteArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
        }
        stack.pushInt(byteArray[index]);
    }

    void caload::execute(runtime::Frame* frame) {
        auto &stack = frame->operandStack;
        int index = stack.popInt();
        heap::Object* object = stack.popRef();
        if (!object) {
            exception::fatal("java.lang.NullPointerException");
        }
        short *charArray = object->charArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
        }
        stack.pushInt(charArray[index]);
    }

    void saload::execute(runtime::Frame* frame) {
        auto &stack = frame->operandStack;
        int index = stack.popInt();
        heap::Object* object = stack.popRef();
        if (!object) {
            exception::fatal("java.lang.NullPointerException");
        }
        short *shortArray = object->shortArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
        }
        stack.pushInt(shortArray[index]);
    }

}