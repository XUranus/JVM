//
// Created by xuranus on 2/7/19.
//

#ifndef JVM_OBJECT_H
#define JVM_OBJECT_H

#include "Class.h"
#include "ObjectPool.h"
#include <vector>

namespace heap {

    enum ObjectDataType: unsigned char {
        BoolArray = 1, ByteArray = 2,  // int8[]
        ShortArray = 3, CharArray = 4, // int16[]
        IntArray = 5,  // int32[]
        LongArray = 6, // int64[]
        FloatArray = 7, // float32[]
        DoubleArray = 8, //float64[]
        ObjectRefArray = 9, //Object*[]
        Common = 0 // Slot* (non array object)
    };

    // Java Object instance , 40 bytes
    class Object {
    public:
        u8 markedOop;
        Class *klass;
        u4 arrLength; // count data when object is array type
        void *data; // refer to Slots (non-array object), or refer to array ptr

        // Class *extra; // when this is instance of java.lang.Class, extra* refer to its heap::Class*
        ObjectDataType dataType;

    private:
        friend class ObjectPool; // all Object new and delete operation are delegate to ObjectPool
        Object();
        explicit Object(Class *c); // new a non array object
        Object(Class *c, void *_data, int _dataCount, ObjectDataType type); // new an array object
        Object(Class *c, unsigned int length); // new an array object

        Object(Object& object); // side effect copy constructor!!!
        Object& operator= (Object& object);// side effect!!!
        ~Object();

    public:
        bool instanceOf(Class *c) const;
        runtime::Slots *fields() const;

        // common class method, for string pool usage
        void setRefVar(const std::string& name, const std::string& descriptor, Object* val) const;
        void setIntVar(const std::string& name, const std::string& descriptor, int val) const;
        Object *getRefVar(const std::string& name, const std::string& descriptor) const;
        int getIntVar(const std::string& name, const std::string& descriptor) const;

        // array class methods
        int arrayLength() const;
        char* byteArray() const;
        short *shortArray() const;
        int *intArray() const;
        long *longArray() const;
        short *charArray() const; // java char take 2 bytes
        float *floatArray() const;
        double *doubleArray() const;
        Object** objectRefArray() const;
    };

}
#endif //JVM_OBJECT_H
