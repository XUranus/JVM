//
// Created by xuranus on 4/26/22.
//

#include "Unsafe.h"
#include <cstring>
#include "../../NativeRegistry.h"
#include "../../../common/Exception.h"

namespace native::sun::misc::Unsafe {

    void doRegistration() {
        const std::string klass = "sun/misc/Unsafe";
        setRegister(klass, "arrayBaseOffset", "(Ljava/lang/Class;)I", arrayBaseOffset);
        setRegister(klass, "arrayIndexScale", "(Ljava/lang/Class;)I", arrayIndexScale);
        setRegister(klass, "addressSize", "()I", addressSize);
        setRegister(klass, "objectFieldOffset", "(Ljava/lang/reflect/Field;)J", objectFieldOffset);
        setRegister(klass, "compareAndSwapObject", "(Ljava/lang/Object;JLjava/lang/Object;Ljava/lang/Object;)Z", compareAndSwapObject);
        setRegister(klass, "getIntVolatile", "(Ljava/lang/Object;J)I", getInt);
        setRegister(klass, "compareAndSwapInt", "(Ljava/lang/Object;JII)Z", compareAndSwapInt);
        setRegister(klass, "getObjectVolatile", "(Ljava/lang/Object;J)Ljava/lang/Object;", getObject);
        setRegister(klass, "compareAndSwapLong", "(Ljava/lang/Object;JJJ)Z", compareAndSwapLong);
        // memory allocation
        setRegister(klass, "allocateMemory", "(J)J", allocateMemory);
        setRegister(klass, "reallocateMemory", "(JJ)J", reallocateMemory);
        setRegister(klass, "freeMemory", "(J)V", freeMemory);
        setRegister(klass, "getByte", "(J)B", getByte);
        setRegister(klass, "putLong", "(JJ)V", putLong);
    }

    // public native int arrayBaseOffset(Class<?> type);
    // (Ljava/lang/Class;)I
    void arrayBaseOffset(runtime::Frame *frame) {
        frame->operandStack.pushInt(0); // TODO::implement
    }

    // public native int arrayIndexScale(Class<?> type);
    // (Ljava/lang/Class;)I
    void arrayIndexScale(runtime::Frame* frame) {
        frame->operandStack.pushInt(1); // TODO::implement
    }

    // public native int addressSize();
    // ()I
    void addressSize(runtime::Frame* frame) {
        frame->operandStack.pushInt(8); // TODO::implement
    }

    // public native long objectFieldOffset(Field field);
    // (Ljava/lang/reflect/Field;)J
    void objectFieldOffset(runtime::Frame* frame) {
        heap::Object* jField = frame->localVars.refValue(1);
        int offset = jField->getIntVar("slot", "I");
        frame->operandStack.pushLong((long )offset);
    }


    // compare and swap object, known as CAS
    bool _CASObject(heap::Object* object,
                    runtime::Slots* slots,
                    long offset,
                    heap::Object* expected,
                    heap::Object* newVal) {
        heap::Object* current = slots->refValue(offset);
        if(current == expected) {
            slots->setRef(offset, newVal);
            return true;
        } else {
            return false;
        }
    }

    bool _CASArray(heap::Object** objects,
                    long offset,
                    heap::Object* expected,
                    heap::Object* newVal) {
        heap::Object* current = objects[offset];
        if(current == expected) {
            objects[offset] = newVal;
            return true;
        } else {
            return false;
        }
    }


    // public final native boolean compareAndSwapObject(Object o, long offset, Object expected, Object x)
    // (Ljava/lang/Object;JLjava/lang/Object;Ljava/lang/Object;)Z
    void compareAndSwapObject(runtime::Frame* frame) {
        auto& vars = frame->localVars;
        heap::Object* obj = vars.refValue(1);
        long offset = vars.longValue(2);
        heap::Object* expected = vars.refValue(4);
        heap::Object* newVar = vars.refValue(5);

        if(obj->dataType == heap::ObjectDataType::Common) {
            bool swapped = _CASObject(obj, obj->fields(), offset, expected, newVar);
            frame->operandStack.pushBoolean(swapped);
        } else if(obj->dataType == heap::ObjectDataType::ObjectRefArray) {
            bool swapped = _CASArray(obj->objectRefArray(), offset, expected, newVar);
            frame->operandStack.pushBoolean(swapped);
        } else {
            // TODO:: implement
            exception::panic("implement native: "
                             "sum.misc.Unsafe.compareAndSwapObject"
                             "(Ljava/lang/Object;JLjava/lang/Object;Ljava/lang/Object;)Z");
        }
    }

    // public native boolean getInt(Object o, long offset);
    // (Ljava/lang/Object;J)I
    void getInt(runtime::Frame* frame) {
        auto& vars = frame->localVars;
        auto& stack = frame->operandStack;

        heap::Object* obj = vars.refValue(1);
        long offset = vars.longValue(2);

        if(obj->dataType == heap::ObjectDataType::Common) {
            stack.pushInt(obj->fields()->intValue(offset));
        } else if(obj->dataType == heap::ObjectDataType::IntArray) {
            stack.pushInt(obj->intArray()[offset]);
        } else {
            exception::panic("native error: sun/misc/Unsafe.getInt(Ljava/lang/Object;J)I");
        }
    }

    // public final native boolean compareAndSwapInt(Object o, long offset, int expected, int x);
    // (Ljava/lang/Object;JII)Z
    void compareAndSwapInt(runtime::Frame* frame) {
        auto& vars = frame->localVars;
        heap::Object* obj = vars.refValue(1);
        long offset = vars.longValue(2);
        int expected = vars.intValue(4);
        int newVar = vars.intValue(5);

        if(obj->dataType == heap::ObjectDataType::Common) {
            int oldVal = obj->fields()->intValue(offset);
            if(oldVal == expected) {
                obj->fields()->setInt(offset, newVar);
                frame->operandStack.pushBoolean(true);
            } else {
                frame->operandStack.pushBoolean(false);
            }
        } else if(obj->dataType == heap::ObjectDataType::IntArray){
            int oldVal = obj->intArray()[offset];
            if(oldVal == expected) {
                obj->intArray()[offset] = newVar;
                frame->operandStack.pushBoolean(true);
            } else {
                frame->operandStack.pushBoolean(false);
            }
        } else {
            exception::panic("native error: sun/misc/Unsafe.compareAndSwapInt(Ljava/lang/Object;JII)Z");
        }
    }

    // public native Object getObject(Object o, long offset);
    // (Ljava/lang/Object;J)Ljava/lang/Object;
    void getObject(runtime::Frame* frame) {
        auto& vars = frame->localVars;
        heap::Object* obj = vars.refValue(1);
        long offset = vars.longValue(2);

        if(obj->dataType == heap::ObjectDataType::Common) {
            heap::Object* x = obj->fields()->refValue(offset);
            frame->operandStack.pushRef(x);
        } else if(obj->dataType == heap::ObjectRefArray) {
            heap::Object* x = obj->objectRefArray()[offset];
            frame->operandStack.pushRef(x);
        } else {
            exception::panic("native error: sun/misc/Unsafe.getObject(Ljava/lang/Object;J)Ljava/lang/Object;");
        }
    }

    // public final native boolean compareAndSwapgetIntVolatileLong(Object o, long offset, long expected, long x);
    // (Ljava/lang/Object;JJJ)Z
    void compareAndSwapLong(runtime::Frame* frame) {
        auto& vars = frame->localVars;
        heap::Object* obj = vars.refValue(1);
        long offset = vars.longValue(2);
        long expected = vars.longValue(4);
        long newVar = vars.longValue(6);

        if(obj->dataType == heap::ObjectDataType::Common) {
            long oldVal = obj->fields()->longValue(offset);
            if (oldVal == expected) {
                obj->fields()->setLong(offset, newVar);
                frame->operandStack.pushBoolean(true);
            } else {
                frame->operandStack.pushBoolean(false);
            }
        } else if(obj->dataType == heap::ObjectDataType::LongArray){
            long oldVal = obj->longArray()[offset];
            if(oldVal == expected) {
                obj->longArray()[offset] = newVar;
                frame->operandStack.pushBoolean(true);
            } else {
                frame->operandStack.pushBoolean(false);
            }
        } else {
            exception::panic("native error: sun/misc/Unsafe.compareAndSwapInt(Ljava/lang/Object;JII)Z");
        }
    }



    // ================== memory allocation ===================

    static std::map<long, unsigned char*> _allocated; // <startAddress, physicalAddress>
    static std::map<long, long> _allocatedSize; // <startAddress, size>
    static long _nextAddress = 64; // not 0, 0 is reserved for null representation

    long allocate(long size) {
        auto* memory = new unsigned char[size];
        long address = _nextAddress;
        _allocated[address] = memory;
        _allocatedSize[address] = size;
        _nextAddress += size;
        return address;
    }

    void free(long address) {
        if(_allocated.find(address) != _allocated.end()) {
            delete[] _allocated[address];
            _allocatedSize.erase(address);
            _allocated.erase(address);
        } else {
            exception::panic("address not allocated! " + std::to_string(address));
        }
    }

    std::pair<unsigned char*, long> memoryAt(long address) { // <physicalAddress, size>
        for(auto & it : _allocated) {
            long startAddress = it.first;
            long endAddress = startAddress + _allocatedSize[startAddress];
            unsigned char* memory = it.second;
            if(address >= startAddress && address < endAddress) {
                long offset = address - startAddress;
                return std::make_pair(memory + offset, _allocatedSize[startAddress] - offset);
            }
        }
        exception::panic("invalid address " + std::to_string(address));
        return std::make_pair(nullptr, 0);
    }

    long reallocate(long address, long size) {
        if(size == 0) {
            return 0;
        } else if(address == 0) {
            return allocate(size);
        } else {
            auto mem = memoryAt(address);
            long _size = mem.second; // size of memory
            if(_size >= size) {
                return address;
            } else {
                _allocated.erase(address);
                _allocatedSize.erase(address);// delete memory TODO::

                long newAddress = allocate(size);
                auto newMem = memoryAt(newAddress);
                memcpy(newMem.first, mem.first, size);
                return newAddress;
            }
        }
    }


    // public native long allocateMemory(long bytes);
    // (J)J
    void allocateMemory(runtime::Frame* frame) {
        auto& vars = frame->localVars;
        auto& stack = frame->operandStack;

        //heap::Object* _this = vars.refValue(0); // this
        long bytes = vars.longValue(1);

        long address = allocate(bytes);
        stack.pushLong(address);
    }


    // public native long reallocateMemory(long address, long bytes);
    // (JJ)J
    void reallocateMemory(runtime::Frame* frame) {
        auto& vars = frame->localVars;
        auto& stack = frame->operandStack;

        //heap::Object* _this = vars.refValue(0); // this
        long address = vars.longValue(1);
        long bytes = vars.longValue(3);

        long newAddress = reallocate(address, bytes);
        stack.pushLong(newAddress);
    }

    // public native void freeMemory(long address);
    // (J)V
    void freeMemory(runtime::Frame* frame) {
        auto& vars = frame->localVars;
        long address = vars.longValue(1);
        free(address);
    }

    // public native byte getByte(long address);
    // (J)B
    void getByte(runtime::Frame* frame) {
        auto& vars = frame->localVars;
        auto& stack = frame->operandStack;

        long address = vars.longValue(1);

        auto mem = memoryAt(address);
        unsigned char value = mem.first[0];
        stack.pushInt(value);
    }

    // public native void putLong(long address, long );
    // (JJ)V
    void putLong(runtime::Frame* frame) {
        auto& vars = frame->localVars;
        long address = vars.longValue(1);
        long value = vars.longValue(3);

        auto mem = memoryAt(address);
        *mem.first = value;
    }



}