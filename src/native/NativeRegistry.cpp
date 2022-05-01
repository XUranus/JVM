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

    void initNativeRegistry() {
        sun::misc::VM::doRegistration();
        sun::misc::Unsafe::doRegistration();
        sun::misc::Signal::doRegistration();
        sun::misc::URLClassPath::doRegistration();
        sun::reflect::NativeConstructorAccessorImpl::doRegistration();
        sun::reflect::Reflection::doRegistration();
        java::lang::Object::doRegistration();
        java::lang::Class::doRegistration();
        java::lang::Double::doRegistration();
        java::lang::Float::doRegistration();
        java::lang::String::doRegistration();
        java::lang::System::doRegistration();
        java::lang::Throwable::deRegistration();
        java::lang::Thread::doRegistration();
        java::lang::Runtime::doRegistration();
        java::io::FileOutputStream::doRegistration();
        java::io::FileInputStream::doRegistration();
        java::io::FileDescriptor::doRegistration();
        java::io::UnixFileSystem::doRegistration();
        java::security::AccessController::doRegistration();
        java::util::concurrent::atomic::AtomicLong::doRegistration();
        sun::io::Win32ErrorMode::doRegistration();
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
                return (NativeMethod) &emptyNativeMethod;
            }
        }
        return nullptr;
    }

    void emptyNativeMethod() {}
}