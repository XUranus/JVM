//
// Created by xuranus on 3/16/19.
//

#include "NativeRegistry.h"
#include "../common/Console.h"

#include "java/lang/Object.h"
#include "java/lang/Class.h"
#include "java/lang/Double.h"
#include "java/lang/Float.h"
#include "java/lang/String.h"
#include "java/lang/System.h"
#include "java/lang/Throwable.h"
#include "java/lang/Thread.h"
#include "java/lang/Runtime.h"
#include "sun/misc/VM.h"
#include "sun/misc/Unsafe.h"
#include "sun/reflect/Reflection.h"
#include "sun/reflect/NativeConstructorAccessorImpl.h"
#include "sun/misc/Signal.h"
#include "sun/misc/URLClassPath.h"
#include "java/io/FileOutputStream.h"
#include "java/io/FileInputStream.h"
#include "java/io/FileDescriptor.h"
#include "java/io/UnixFileSystem.h"
#include "java/security/AccessController.h"
#include "java/util/concurrent/atomic/AtomicLong.h"
#include "sun/io/Win32ErrorMode.h"

namespace native {

    static std::map<std::string, NativeMethod> registry;

    static const NativeEntry nativeTable[] = {
        // java.lang.Object
        {"java/lang/Object", "getClass", "()Ljava/lang/Class;", java::lang::Object::getClass},
        {"java/lang/Object", "hashCode", "()I", java::lang::Object::hashCode},
        {"java/lang/Object", "clone", "()Ljava/lang/Object;", java::lang::Object::clone},
        {"java/lang/Object", "notifyAll", "()V", java::lang::Object::notifyAll},

        // java.lang.Class
        {"java/lang/Class", "getPrimitiveClass", "(Ljava/lang/String;)Ljava/lang/Class;", java::lang::Class::getPrimitiveClass},
        {"java/lang/Class", "getName0", "()Ljava/lang/String;", java::lang::Class::getName0},
        {"java/lang/Class", "desiredAssertionStatus0", "(Ljava/lang/Class;)Z", java::lang::Class::desiredAssertionStatus0},
        {"java/lang/Class", "isInterface", "()Z", java::lang::Class::isInterface},
        {"java/lang/Class", "isPrimitive", "()Z", java::lang::Class::isPrimitive},
        {"java/lang/Class", "forName0", "(Ljava/lang/String;ZLjava/lang/ClassLoader;Ljava/lang/Class;)Ljava/lang/Class;", java::lang::Class::forName0},
        {"java/lang/Class", "getModifiers", "()I", java::lang::Class::getModifiers},
        {"java/lang/Class", "getSuperclass", "()Ljava/lang/Class;", java::lang::Class::getSuperclass},
        {"java/lang/Class", "getInterfaces0", "()[Ljava/lang/Class;", java::lang::Class::getInterfaces0},
        {"java/lang/Class", "isArray", "()Z", java::lang::Class::isArray},
        {"java/lang/Class", "getDeclaredMethods0", "(Z)[Ljava/lang/reflect/Method;", java::lang::Class::getDeclaredMethods0},
        {"java/lang/Class", "getDeclaredConstructors0", "(Z)[Ljava/lang/reflect/Constructor;", java::lang::Class::getDeclaredConstructors0},
        {"java/lang/Class", "getDeclaredFields0", "(Z)[Ljava/lang/reflect/Field;", java::lang::Class::getDeclaredFields0},
        {"java/lang/Class", "getComponentType", "()Ljava/lang/Class;", java::lang::Class::getComponentType},
        {"java/lang/Class", "isAssignableFrom", "(Ljava/lang/Class;)Z", java::lang::Class::isAssignableFrom},

        // java.lang.Double
        {"java/lang/Double", "doubleToRawLongBits", "(D)J", java::lang::Double::doubleToRawLongBits},
        {"java/lang/Double", "longBitsToDouble", "(J)D", java::lang::Double::longBitsToDouble},

        // java.lang.Float
        {"java/lang/Float", "floatToRawIntBits", "(F)I", java::lang::Float::floatToRawIntBits},
        {"java/lang/Float", "intBitsToFloat", "(I)F", java::lang::Float::intBitsToFloat},

        // java.lang.String
        {"java/lang/String", "intern", "()Ljava/lang/String;", java::lang::String::intern},

        // java.lang.System
        {"java/lang/System", "arraycopy", "(Ljava/lang/Object;ILjava/lang/Object;II)V", java::lang::System::arraycopy},
        {"java/lang/System", "setOut0", "(Ljava/io/PrintStream;)V", java::lang::System::setOut0},
        {"java/lang/System", "setErr0", "(Ljava/io/PrintStream;)V", java::lang::System::setErr0},
        {"java/lang/System", "setIn0", "(Ljava/io/InputStream;)V", java::lang::System::setIn0},
        {"java/lang/System", "currentTimeMillis", "()J", java::lang::System::currentTimeMillis},
        {"java/lang/System", "initProperties", "(Ljava/util/Properties;)Ljava/util/Properties;", java::lang::System::initProperties},

        // java.lang.Throwable
        {"java/lang/Throwable", "fillInStackTrace", "(I)Ljava/lang/Throwable;", java::lang::Throwable::fillInStackTrace},

        // java.lang.Thread
        {"java/lang/Thread", "currentThread", "()Ljava/lang/Thread;", java::lang::Thread::currentThread},
        {"java/lang/Thread", "setPriority0", "(I)V", java::lang::Thread::setPriority0},
        {"java/lang/Thread", "isAlive", "()Z", java::lang::Thread::isAlive},
        {"java/lang/Thread", "start0", "()V", java::lang::Thread::start0},

        // java.lang.Runtime
        {"java/lang/Runtime", "availableProcessors", "()I", java::lang::Runtime::availableProcessors},

        // java.io.FileOutputStream
        {"java/io/FileOutputStream", "writeBytes", "([BIIZ)V", java::io::FileOutputStream::writeBytes},
        {"java/io/FileOutputStream", "open0", "(Ljava/lang/String;Z)V", java::io::FileOutputStream::open0},
        {"java/io/FileOutputStream", "close0", "()V", java::io::FileOutputStream::close0},

        // java.io.FileInputStream
        {"java/io/FileInputStream", "open0", "(Ljava/lang/String;)V", java::io::FileInputStream::open0},
        {"java/io/FileInputStream", "close0", "()V", java::io::FileInputStream::close0},
        {"java/io/FileInputStream", "readBytes", "([BII)I", java::io::FileInputStream::readBytes},
        {"java/io/FileInputStream", "available0", "()I", java::io::FileInputStream::available0},

        // java.io.FileDescriptor
        {"java/io/FileDescriptor", "set", "(I)J", java::io::FileDescriptor::set},

        // java.io.UnixFileSystem
        {"java/io/UnixFileSystem", "canonicalize0", "(Ljava/lang/String;)Ljava/lang/String;", java::io::UnixFileSystem::canonicalize0},
        {"java/io/UnixFileSystem", "getBooleanAttributes0", "(Ljava/io/File;)I", java::io::UnixFileSystem::getBooleanAttributes0},

        // java.security.AccessController
        {"java/security/AccessController", "doPrivileged", "(Ljava/security/PrivilegedAction;)Ljava/lang/Object;", java::security::AccessController::doPrivileged},
        {"java/security/AccessController", "doPrivileged", "(Ljava/security/PrivilegedExceptionAction;)Ljava/lang/Object;", java::security::AccessController::doPrivileged},
        {"java/security/AccessController", "getStackAccessControlContext", "()Ljava/security/AccessControlContext;", java::security::AccessController::getStackAccessControlContext},

        // java.util.concurrent.atomic.AtomicLong
        {"java/util/concurrent/atomic/AtomicLong", "VMSupportsCS8", "()Z", java::util::concurrent::atomic::AtomicLong::VMSupportsCS8},

        // sun.misc.VM
        {"sun/misc/VM", "initialize", "()V", sun::misc::VM::initialize},

        // sun.misc.Unsafe
        {"sun/misc/Unsafe", "arrayBaseOffset", "(Ljava/lang/Class;)I", sun::misc::Unsafe::arrayBaseOffset},
        {"sun/misc/Unsafe", "arrayIndexScale", "(Ljava/lang/Class;)I", sun::misc::Unsafe::arrayIndexScale},
        {"sun/misc/Unsafe", "addressSize", "()I", sun::misc::Unsafe::addressSize},
        {"sun/misc/Unsafe", "objectFieldOffset", "(Ljava/lang/reflect/Field;)J", sun::misc::Unsafe::objectFieldOffset},
        {"sun/misc/Unsafe", "compareAndSwapObject", "(Ljava/lang/Object;JLjava/lang/Object;Ljava/lang/Object;)Z", sun::misc::Unsafe::compareAndSwapObject},
        {"sun/misc/Unsafe", "getIntVolatile", "(Ljava/lang/Object;J)I", sun::misc::Unsafe::getInt},
        {"sun/misc/Unsafe", "compareAndSwapInt", "(Ljava/lang/Object;JII)Z", sun::misc::Unsafe::compareAndSwapInt},
        {"sun/misc/Unsafe", "getObjectVolatile", "(Ljava/lang/Object;J)Ljava/lang/Object;", sun::misc::Unsafe::getObject},
        {"sun/misc/Unsafe", "compareAndSwapLong", "(Ljava/lang/Object;JJJ)Z", sun::misc::Unsafe::compareAndSwapLong},
        {"sun/misc/Unsafe", "allocateMemory", "(J)J", sun::misc::Unsafe::allocateMemory},
        {"sun/misc/Unsafe", "reallocateMemory", "(JJ)J", sun::misc::Unsafe::reallocateMemory},
        {"sun/misc/Unsafe", "freeMemory", "(J)V", sun::misc::Unsafe::freeMemory},
        {"sun/misc/Unsafe", "getByte", "(J)B", sun::misc::Unsafe::getByte},
        {"sun/misc/Unsafe", "putLong", "(JJ)V", sun::misc::Unsafe::putLong},

        // sun.misc.Signal
        {"sun/misc/Signal", "findSignal", "(Ljava/lang/String;)I", sun::misc::Signal::findSignal},
        {"sun/misc/Signal", "handle0", "(IJ)J", sun::misc::Signal::handle0},

        // sun.misc.URLClassPath
        {"sun/misc/URLClassPath", "getLookupCacheURLs", "(Ljava/lang/ClassLoader;)[Ljava/net/URL;", sun::misc::URLClassPath::getLookupCacheURLs},

        // sun.reflect.NativeConstructorAccessorImpl
        {"sun/reflect/NativeConstructorAccessorImpl", "newInstance0", "(Ljava/lang/reflect/Constructor;[Ljava/lang/Object;)Ljava/lang/Object;", sun::reflect::NativeConstructorAccessorImpl::newInstance0},

        // sun.reflect.Reflection
        {"sun/reflect/Reflection", "getCallerClass", "()Ljava/lang/Class;", sun::reflect::Reflection::getCallerClass},
        {"sun/reflect/Reflection", "getClassAccessFlags", "(Ljava/lang/Class;)I", sun::reflect::Reflection::getClassAccessFlags},

        // sun.io.Win32ErrorMode
        {"sun/io/Win32ErrorMode", "setErrorMode", "(J)J", sun::io::Win32ErrorMode::setErrorMode},
    };

    void initNativeRegistry() {
        for (const auto& e : nativeTable) {
            std::string key = std::string(e.cls) + "~" + e.method + "~" + e.desc;
            registry[key] = e.func;
        }
    }

    void setRegister(const std::string &className,
                     const std::string &methodName,
                     const std::string &methodDescriptor,
                     NativeMethod method) {
        std::string key = className + "~" + methodName + "~" + methodDescriptor;
        registry[key] = method;
    }

    NativeMethod findNativeMethod(const std::string& className,
                                  const std::string& methodName,
                                  const std::string& methodDescriptor) {
        auto key = className + "~" + methodName + "~" + methodDescriptor;
        if (registry.find(key) != registry.end()) {

            //std::cout << "findNativeMethod " << key << std::endl;

            return registry[key];
        } else if (methodDescriptor == "()V") {
            if(methodName == "registerNatives" || methodName == "initIDs") {// todo:: hack
                /**
                 * skip registerNative()V in every class
                 * skip java/io/FileInputStream.initIDs.()V
                 */
                return reinterpret_cast<NativeMethod>(&emptyNativeMethod);
            }
        }
        return nullptr;
    }

    void emptyNativeMethod() {}
}