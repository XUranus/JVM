#pragma once

#include <cstdint>

// JVM type aliases
using u1 = uint8_t;
using u2 = uint16_t;
using u4 = uint32_t;
using u8 = uint64_t;


// Access flags
inline constexpr u2 ACC_PUBLIC_FLAG       = 0x0001;
inline constexpr u2 ACC_PRIVATE_FLAG      = 0x0002;
inline constexpr u2 ACC_PROTECTED_FLAG    = 0x0004;
inline constexpr u2 ACC_STATIC_FLAG       = 0x0008;
inline constexpr u2 ACC_FINAL_FLAG        = 0x0010;
inline constexpr u2 ACC_SUPER_FLAG        = 0x0020;
inline constexpr u2 ACC_SYNCHRONIZED_FLAG = 0x0020;
inline constexpr u2 ACC_VOLATILE_FLAG     = 0x0040;
inline constexpr u2 ACC_BRIDGE_FLAG       = 0x0040;
inline constexpr u2 ACC_TRANSIENT_FLAG    = 0x0080;
inline constexpr u2 ACC_VARARGS_FLAG      = 0x0080;
inline constexpr u2 ACC_NATIVE_FLAG       = 0x0100;
inline constexpr u2 ACC_INTERFACE_FLAG    = 0x0200;
inline constexpr u2 ACC_ABSTRACT_FLAG     = 0x0400;
inline constexpr u2 ACC_STRICT_FLAG       = 0x0800;
inline constexpr u2 ACC_SYNTHETIC_FLAG    = 0x1000;
inline constexpr u2 ACC_ANNOTATION_FLAG   = 0x2000;
inline constexpr u2 ACC_ENUM_FLAG         = 0x4000;

// Array type codes
inline constexpr u1 AT_BOOLEAN = 4;
inline constexpr u1 AT_CHAR    = 5;
inline constexpr u1 AT_FLOAT   = 6;
inline constexpr u1 AT_DOUBLE  = 7;
inline constexpr u1 AT_BYTE    = 8;
inline constexpr u1 AT_SHORT   = 9;
inline constexpr u1 AT_INT     = 10;
inline constexpr u1 AT_LONG    = 11;

// Constant pool tags
inline constexpr u1 CONSTANT_UTF8               = 1;
inline constexpr u1 CONSTANT_Integer            = 3;
inline constexpr u1 CONSTANT_Float              = 4;
inline constexpr u1 CONSTANT_Long               = 5;
inline constexpr u1 CONSTANT_Double             = 6;
inline constexpr u1 CONSTANT_Class              = 7;
inline constexpr u1 CONSTANT_String             = 8;
inline constexpr u1 CONSTANT_FieldRef           = 9;
inline constexpr u1 CONSTANT_MethodRef          = 10;
inline constexpr u1 CONSTANT_InterfaceMethodRef = 11;
inline constexpr u1 CONSTANT_NameAndType        = 12;
inline constexpr u1 CONSTANT_MethodHandle       = 15;
inline constexpr u1 CONSTANT_MethodType         = 16;
inline constexpr u1 CONSTANT_InvokeDynamic      = 18;
