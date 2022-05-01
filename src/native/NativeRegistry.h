//
// Created by xuranus on 3/16/19.
//

#ifndef JVM_NATIVE_REGISTRY_H
#define JVM_NATIVE_REGISTRY_H

#include <map>
#include "../runtime/thread/Frame.h"

namespace native {

    typedef void (*NativeMethod)(runtime::Frame *);

    static std::map<std::string, NativeMethod> registry;

    void initNativeRegistry();

    void setRegister(const std::string& className,
                     const std::string& methodName,
                     const std::string& methodDescriptor,
                     NativeMethod method);

    NativeMethod findNativeMethod(const std::string& className,
                                  const std::string& methodName,
                                  const std::string& methodDescriptor);

    void emptyNativeMethod();
}
#endif //JVM_NATIVE_REGISTRY_H
