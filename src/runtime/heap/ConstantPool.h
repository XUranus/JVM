//
// Created by xuranus on 2/11/19.
//

#ifndef JVM_HEAP_CONSTANTS_POOL_H
#define JVM_HEAP_CONSTANTS_POOL_H

#include <string>
#include "../Slots.h"
#include "Class.h"
#include "SymRef.h"
#include "../../classfile/ConstantsPool.h"

namespace heap {

    class Class;
    class ClassRef;
    class MethodRef;
    class FieldRef;
    class InterfaceMemberRef;

    enum ConstantType {
        NoneType = 0,
        IntType = 1,
        LongType = 2,
        FloatType = 3,
        DoubleType = 4,

        ClassRefType = 5,
        FieldRefType = 6,
        MethodRefType = 7,
        InterfaceMemberRefType = 8,
        StringType = 9,
        UTF8Type = 10
    };

    class ConstantPool {
    private:
        int size;
        runtime::Slots slots; // used to store int, long, float, double
        void**  ptrs;  // used to store string*, SymRef*
        ConstantType* constantType; // ConstantType[size]
    public:
        Class *klass; // for referring, refer to the class it belongs to

    public:
        ConstantPool(Class* classRef, classfile::ConstantsPool* constantsPool);
        ~ConstantPool();

        void setInt(unsigned int index, int v);
        void setLong(unsigned int index, long v);
        void setFloat(unsigned int index, float v);
        void setDouble(unsigned int index, double v);
        void setClassRef(unsigned int index, ClassRef *ref);
        void setFieldRef(unsigned int index, FieldRef *ref);
        void setMethodRef(unsigned int index, MethodRef *ref);
        void setInterfaceMemberRef(unsigned int index, InterfaceMemberRef *ref);
        void setString(unsigned int index, const std::string& str);
        void setUTF8(unsigned int index, const std::string& str);

        int intValue(unsigned int index) const;
        long longValue(unsigned int index) const;
        float floatValue(unsigned int index) const;
        double doubleValue(unsigned int index) const;
        ClassRef* classRefValue(unsigned int index) const;
        FieldRef* fieldRefValue(unsigned int index) const;
        MethodRef* methodRefValue(unsigned int index) const;
        InterfaceMemberRef* interfaceMemberRefValue(unsigned int index) const;
        std::string stringValue(unsigned int index) const;
        std::string UTF8Value(unsigned int index) const;

        ConstantType type(unsigned int index) const;

        void dump() const;
    };

}

#endif //JVM_HEAP_CONSTANTS_POOL_H
