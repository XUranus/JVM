//
// Created by XUranus on 2019/1/31.
//

#ifndef JVM_BASICTYPE_H
#define JVM_BASICTYPE_H

typedef unsigned char u1;
typedef unsigned short int u2;
typedef unsigned long int u4;
typedef unsigned char byte;

#define ACC_PUBLIC_FLAG 0x0001
#define ACC_PRIVATE_FLAG 0x0002
#define ACC_PROTECTED_FLAG 0x0004
#define ACC_STATIC_FLAG 0x0008
#define ACC_FINAL_FLAG 0x0010
#define ACC_SUPER_FLAG 0x0020
#define ACC_SYNCHRONIZED_FLAG 0x0020
#define ACC_VOLATILE_FLAG 0x0040
#define ACC_BRIDGE_FLAG 0x0040
#define ACC_TRANSIENT_FLAG 0x0080
#define ACC_VARARGS_FLAG 0x0080
#define ACC_NATIVE_FLAG 0x0100
#define ACC_INTERFACE_FLAG 0x0200
#define ACC_ABSTRACT_FLAG 0x0400
#define ACC_STRICT_FLAG 0x0800
#define ACC_SYNTHETIC_FLAG 0x1000
#define ACC_ANNOTATION_FLAG 0x2000
#define ACC_ENUM_FLAG 0x4000

#define AT_BOOLEAN 4
#define AT_CHAR 5
#define AT_FLOAT 6
#define AT_DOUBLE 7
#define AT_BYTE 8
#define AT_SHORT 9
#define AT_INT 10
#define AT_LONG 11


#endif //JVM_BASICTYPE_H
