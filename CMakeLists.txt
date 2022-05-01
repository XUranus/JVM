cmake_minimum_required(VERSION 3.21)
project(xjava)

set(CMAKE_CXX_STANDARD 17)

add_executable(xjava main.cpp

        src/basicType.h

        src/common/Console.cpp
        src/common/Console.h
        src/common/FilePath.cpp
        src/common/FilePath.h
        src/common/Exception.h

        src/console/Command.cpp
        src/console/Command.h

        src/classpath/Entry.cpp
        src/classpath/Entry.h
        src/classpath/ClassPath.cpp
        src/classpath/ClassPath.h

        src/classfile/ClassFile.cpp
        src/classfile/ClassFile.h
        src/classfile/ConstantsPool.cpp
        src/classfile/ConstantsPool.h
        src/classfile/Members.cpp
        src/classfile/Members.h
        src/classfile/BytesReader.cpp
        src/classfile/BytesReader.h
        src/classfile/Attributes.cpp
        src/classfile/Attributes.h
        src/classpath/GZipPool.cpp
        src/classpath/GZipPool.h

        src/runtime/Runtime.cpp
        src/runtime/Runtime.h
        src/runtime/Slots.cpp
        src/runtime/Slots.h
        src/runtime/thread/Frame.cpp
        src/runtime/thread/Frame.h
        src/runtime/thread/Stack.cpp
        src/runtime/thread/Stack.h
        src/runtime/thread/Thread.cpp
        src/runtime/thread/Thread.h

        src/instruction/InstructionReader.cpp
        src/instruction/InstructionReader.h
        src/instruction/instruction.cpp
        src/instruction/instruction.h
        src/instruction/comparisons.cpp
        src/instruction/comparisons.h
        src/instruction/constants.cpp
        src/instruction/constants.h
        src/instruction/control.cpp
        src/instruction/control.h
        src/instruction/conversions.cpp
        src/instruction/conversions.h
        src/instruction/extended.cpp
        src/instruction/extended.h
        src/instruction/loads.cpp
        src/instruction/loads.h
        src/instruction/math.cpp
        src/instruction/math.h
        src/instruction/references.cpp
        src/instruction/references.h
        src/instruction/reserved.cpp
        src/instruction/reserved.h
        src/instruction/stack.cpp
        src/instruction/stack.h
        src/instruction/stores.cpp
        src/instruction/stores.h

        src/runtime/heap/Class.cpp
        src/runtime/heap/Class.h
        src/runtime/heap/ClassLoader.cpp
        src/runtime/heap/ClassLoader.h
        src/runtime/heap/ClassMember.cpp
        src/runtime/heap/ClassMember.h
        src/runtime/heap/ConstantPool.cpp
        src/runtime/heap/ConstantPool.h
        src/runtime/heap/Field.cpp
        src/runtime/heap/Field.h
        src/runtime/heap/Method.cpp
        src/runtime/heap/Method.h
        src/runtime/heap/StringPool.cpp
        src/runtime/heap/StringPool.h
        src/runtime/heap/SymRef.cpp
        src/runtime/heap/SymRef.h
        src/runtime/heap/ExceptionHandler.cpp
        src/runtime/heap/ExceptionHandler.h

        src/runtime/heap/Object.cpp
        src/runtime/heap/Object.h
        src/runtime/heap/ObjectPool.cpp
        src/runtime/heap/ObjectPool.h

        src/BootstrapSession.cpp
        src/BootstrapSession.h
        src/JavaVirtualMachine.cpp
        src/JavaVirtualMachine.h

        src/native/NativeRegistry.cpp
        src/native/NativeRegistry.h

        src/native/sun/misc/VM.cpp
        src/native/sun/misc/VM.h
        src/native/sun/misc/Unsafe.cpp
        src/native/sun/misc/Unsafe.h
        src/native/java/io/FileOutputStream.cpp
        src/native/java/io/FileOutputStream.h
        src/native/java/lang/Class.cpp
        src/native/java/lang/Class.h
        src/native/java/lang/Double.cpp
        src/native/java/lang/Double.h
        src/native/java/lang/Float.cpp
        src/native/java/lang/Float.h
        src/native/java/lang/Object.cpp
        src/native/java/lang/Object.h
        src/native/java/lang/String.cpp
        src/native/java/lang/String.h
        src/native/java/lang/System.cpp
        src/native/java/lang/System.h
        src/native/java/lang/Throwable.cpp
        src/native/java/lang/Throwable.h
        src/native/sun/reflect/Reflection.cpp
        src/native/sun/reflect/Reflection.h
        src/native/java/io/FileDescriptor.cpp
        src/native/java/io/FileDescriptor.h
        src/native/java/security/AccessController.cpp
        src/native/java/security/AccessController.h
        src/native/java/lang/Thread.cpp
        src/native/java/lang/Thread.h
        src/runtime/heap/MethodDescriptorParser.cpp
        src/runtime/heap/MethodDescriptorParser.h
        src/native/java/lang/Runtime.cpp
        src/native/java/lang/Runtime.h
        src/native/sun/misc/Signal.cpp
        src/native/sun/misc/Signal.h
        src/native/sun/misc/URLClassPath.cpp
        src/native/sun/misc/URLClassPath.h
        src/native/java/io/UnixFileSystem.cpp
        src/native/java/io/UnixFileSystem.h
        src/native/sun/reflect/NativeConstructorAccessorImpl.cpp
        src/native/sun/reflect/NativeConstructorAccessorImpl.h
        src/native/java/util/concurrent/atomic/AtomicLong.cpp
        src/native/java/util/concurrent/atomic/AtomicLong.h
        src/native/sun/io/Win32ErrorMode.cpp
        src/native/sun/io/Win32ErrorMode.h
        src/native/java/io/FileInputStream.cpp
        src/native/java/io/FileInputStream.h)

target_link_libraries(xjava zip)