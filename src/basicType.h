//
// Created by XUranus on 2019/1/31.
//

#ifndef JVM_BASIC_TYPE_H
#define JVM_BASIC_TYPE_H

typedef unsigned char           u1;
typedef unsigned short          u2;
typedef unsigned int            u4;
typedef unsigned long           u8;

#define uint8   unsigned char
#define int8    char
#define uint16  unsigned short
#define int16   short
#define uint32  unsigned int
#define int32   int

#define ACC_PUBLIC_FLAG         0x0001 // class     field   method
#define ACC_PRIVATE_FLAG        0x0002 //           field   method
#define ACC_PROTECTED_FLAG      0x0004 //           field   method
#define ACC_STATIC_FLAG         0x0008 //           field   method
#define ACC_FINAL_FLAG          0x0010 // class     field   method
#define ACC_SUPER_FLAG          0x0020 // class
#define ACC_SYNCHRONIZED_FLAG   0x0020 //                   method
#define ACC_VOLATILE_FLAG       0x0040 //           field
#define ACC_BRIDGE_FLAG         0x0040 //                   method
#define ACC_TRANSIENT_FLAG      0x0080 //           field
#define ACC_VARARGS_FLAG        0x0080 //                   method
#define ACC_NATIVE_FLAG         0x0100 //                   method
#define ACC_INTERFACE_FLAG      0x0200 // class
#define ACC_ABSTRACT_FLAG       0x0400 // class             method
#define ACC_STRICT_FLAG         0x0800 //                   method
#define ACC_SYNTHETIC_FLAG      0x1000 // class     field   method
#define ACC_ANNOTATION_FLAG     0x2000 // class
#define ACC_ENUM_FLAG           0x4000 // class     field

#define AT_BOOLEAN              4
#define AT_CHAR                 5
#define AT_FLOAT                6
#define AT_DOUBLE               7
#define AT_BYTE                 8
#define AT_SHORT                9
#define AT_INT                  10
#define AT_LONG                 11

#define CONSTANT_UTF8               1
#define CONSTANT_Integer            3
#define CONSTANT_Float              4
#define CONSTANT_Long               5
#define CONSTANT_Double             6
#define CONSTANT_Class              7
#define CONSTANT_String             8
#define CONSTANT_FieldRef           9
#define CONSTANT_MethodRef          10
#define CONSTANT_InterfaceMethodRef 11
#define CONSTANT_NameAndType        12
#define CONSTANT_MethodHandle       15
#define CONSTANT_MethodType         16
#define CONSTANT_InvokeDynamic      18

#endif //JVM_BASIC_TYPE_H
