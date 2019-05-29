//
// Created by xuranus on 3/17/19.
//

#include "Class_System.h"
#include "../NativeRegistry.h"
#include "../../runtime/heap/Object.h"
#include "../../runtime/heap/ClassLoader.h"
#include "../../util/Console.h"

void Class_System::init()
{
    NativeRegistry::getNativeRegistery()->setRegister("java/lang/System","arraycopy", "(Ljava/lang/Object;ILjava/lang/Object;II)V",Class_System::arraycopy);
}


bool Class_System::checkArrayCopy(Object *src, Object *dest)
{
    auto srcClass = src->_class;
    auto destClass = dest->_class;

    if(!srcClass->isArray() || !destClass->isArray())
        return false;
    if(srcClass->componentClass()->isPrimitive() ||
        destClass->componentClass()->isPrimitive())
        return srcClass == destClass;
    return true;
}

void Class_System::arrayCopy(Object *src, Object *dst, int srcPos, int dstPos, int length)
{
    switch (src->dataType) {
        case Object::DataType::INT8: {
            auto _src = (int8*)src->data;
            auto _dst = (int8*)dst->data;
            for(int i = 0; i< length; i++) {
                _dst[dstPos+i] = _src[srcPos+i];
            }
        };
        case Object::DataType::INT16: {
            auto _src = (int16*)src->data;
            auto _dst = (int16*)dst->data;
            for(int i = 0; i< length; i++) {
                _dst[dstPos+i] = _src[srcPos+i];
            }
        };
        case Object::DataType::INT32: {
            auto _src = (int32*)src->data;
            auto _dst = (int32*)dst->data;
            for(int i = 0; i< length; i++) {
                _dst[dstPos+i] = _src[srcPos+i];
            }
        };
        case Object::DataType::INT64: {
            auto _src = (long*)src->data;
            auto _dst = (long*)dst->data;
            for(int i = 0; i< length; i++) {
                _dst[dstPos+i] = _src[srcPos+i];
            }
        };
        case Object::DataType::UINT16: {
            auto _src = (uint16 *)src->data;
            auto _dst = (uint16 *)dst->data;
            for(int i = 0; i< length; i++) {
                _dst[dstPos+i] = _src[srcPos+i];
            }
        };
        case Object::DataType::FLOAT32: {
            auto _src = (float *)src->data;
            auto _dst = (float *)dst->data;
            for(int i = 0; i< length; i++) {
                _dst[dstPos+i] = _src[srcPos+i];
            }
        };
        case Object::DataType::FLOAT64: {
            auto _src = (double *)src->data;
            auto _dst = (double *)dst->data;
            for(int i = 0; i< length; i++) {
                _dst[dstPos+i] = _src[srcPos+i];
            }
        };
        case Object::DataType::REF: {
            auto _src = (Object*)src->data;
            auto _dst = (Object*)dst->data;
            for(int i = 0; i< length; i++) {
                _dst[dstPos+i] = _src[srcPos+i];
            }
        };
        default:{
            Console::printlnError("ArrayCopy(): object not array!");
            exit(1);
        }
    }
}

// public static native void arraycopy(Object src, int srcPos, Object dest, int destPos, int length)
// (Ljava/lang/Object;ILjava/lang/Object;II)V
void Class_System::arraycopy(Frame *frame)
{
    auto& vars = frame->localVars;
    auto src = vars.getRef(0);
    auto srcPos = vars.getInt(1);
    auto dest = vars.getRef(2);
    auto destPos = vars.getInt(3);
    auto length = vars.getInt(4);

    if(src== nullptr || dest == nullptr)
    {
        Console::printlnException("java.lang.NullPointerException");
        exit(1);
    }
    if(!Class_System::checkArrayCopy(src,dest)) {
        Console::printlnException("java.lang.ArrayStoreException");
        exit(1);
    }
    if(srcPos<0 || destPos<0 || length<0 || srcPos+length>src->arrayLength() || destPos+length>dest->arrayLength())
    {
        Console::printlnException("java.lang.IndexOutOfBoundException");
        exit(1);
    }

}
