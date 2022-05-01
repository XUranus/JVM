//
// Created by xuranus on 2/5/19.
//

#include "stores.h"
#include "../runtime/heap/Object.h"
#include "../common/Exception.h"

namespace instruction {

    void istore::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popInt();
        frame->localVars.setInt(index, val);
    }

    void lstore::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popLong();
        frame->localVars.setLong(index, val);
    }

    void fstore::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popFloat();
        frame->localVars.setFloat(index, val);
    }

    void dstore::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popDouble();
        frame->localVars.setDouble(index, val);
    }

    void astore::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popRef();
        frame->localVars.setRef(index, val);
    }

    void istore_0::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popInt();
        frame->localVars.setInt(0, val);
    }

    void istore_1::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popInt();
        frame->localVars.setInt(1, val);
    }

    void istore_2::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popInt();
        frame->localVars.setInt(2, val);
    }

    void istore_3::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popInt();
        frame->localVars.setInt(3, val);
    }

    void lstore_0::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popLong();
        frame->localVars.setLong(0, val);
    }

    void lstore_1::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popLong();
        frame->localVars.setLong(1, val);
    }

    void lstore_2::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popLong();
        frame->localVars.setLong(2, val);
    }

    void lstore_3::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popLong();
        frame->localVars.setLong(3, val);
    }

    void fstore_0::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popFloat();
        frame->localVars.setFloat(0, val);
    }

    void fstore_1::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popFloat();
        frame->localVars.setFloat(1, val);
    }

    void fstore_2::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popFloat();
        frame->localVars.setFloat(2, val);
    }

    void fstore_3::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popFloat();
        frame->localVars.setFloat(3, val);
    }

    void dstore_0::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popDouble();
        frame->localVars.setDouble(0, val);
    }

    void dstore_1::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popDouble();
        frame->localVars.setDouble(1, val);
    }

    void dstore_2::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popDouble();
        frame->localVars.setDouble(2, val);
    }

    void dstore_3::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popDouble();
        frame->localVars.setDouble(3, val);
    }

    void astore_0::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popRef();
        frame->localVars.setRef(0, val);
    }

    void astore_1::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popRef();
        frame->localVars.setRef(1, val);
    }

    void astore_2::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popRef();
        frame->localVars.setRef(2, val);
    }

    void astore_3::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popRef();
        frame->localVars.setRef(3, val);
    }

    void iastore::execute(runtime::Frame* frame) {
        int val = frame->operandStack.popInt();
        int index = frame->operandStack.popInt();
        heap::Object* object = frame->operandStack.popRef();
        if (!object) {
            exception::fatal("java.lang.NullPointerException");
        }
        int* intArray = object->intArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
        }
        intArray[index] = val;
    }

    void lastore::execute(runtime::Frame* frame) {
        long val = frame->operandStack.popLong();
        int index = frame->operandStack.popInt();
        heap::Object* object = frame->operandStack.popRef();
        if (!object) {
            exception::fatal("java.lang.NullPointerException");
        }
        long* longArray = object->longArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
        }
        longArray[index] = val;
    }

    void fastore::execute(runtime::Frame* frame) {
        float val = frame->operandStack.popFloat();
        int index = frame->operandStack.popInt();
        heap::Object* object = frame->operandStack.popRef();
        if (object) {
            exception::fatal("java.lang.NullPointerException");
        }
        float* floatArray = object->floatArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
        }
        floatArray[index] = val;
    }

    void dastore::execute(runtime::Frame* frame) {
        double val = frame->operandStack.popDouble();
        int index = frame->operandStack.popInt();
        heap::Object* object = frame->operandStack.popRef();
        if (!object) {
            exception::fatal("java.lang.NullPointerException");
        }
        double* doubleArray = object->doubleArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
        }
        doubleArray[index] = val;
    }

    void aastore::execute(runtime::Frame* frame) {
        heap::Object* val = frame->operandStack.popRef();
        int index = frame->operandStack.popInt();
        heap::Object* object = frame->operandStack.popRef();
        if (!object) {
            exception::fatal("java.lang.NullPointerException");
        }
        heap::Object** objectRefArray = object->objectRefArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
        }
        objectRefArray[index] = val;
    }

    void bastore::execute(runtime::Frame* frame) {
        char val = frame->operandStack.popInt();
        int index = frame->operandStack.popInt();
        heap::Object* object = frame->operandStack.popRef();
        if (!object) {
            exception::fatal("java.lang.NullPointerException");
        }
        char* byteArray = object->byteArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
        }
        byteArray[index] = val;
    }

    void castore::execute(runtime::Frame* frame) {
        short val = frame->operandStack.popInt();
        int index = frame->operandStack.popInt();
        heap::Object* object = frame->operandStack.popRef();
        if (!object) {
            exception::fatal("java.lang.NullPointerException");
        }
        short* charArray = object->charArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
        }
        charArray[index] =  val;
    }

    void sastore::execute(runtime::Frame* frame) {
        short val = frame->operandStack.popInt();
        int index = frame->operandStack.popInt();
        heap::Object* object = frame->operandStack.popRef();
        if (!object) {
            exception::fatal("java.lang.NullPointerException");
        }
        short* shortArray = object->shortArray();
        if (object->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException");
        }
        shortArray[index] = val;
    }

}