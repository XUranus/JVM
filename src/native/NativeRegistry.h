//
// Created by xuranus on 3/16/19.
//

#ifndef JVM_NATIVEREGISTRY_H
#define JVM_NATIVEREGISTRY_H

#include <map>
#include "../runtime/Frame.h"

typedef void (*NativeMethod)(Frame*);

class NativeRegistry {
public:
    static NativeRegistry* instance;
private:
     std::map<std::string,NativeMethod> registry;

private:
    NativeRegistry();

public:
    static NativeRegistry* getNativeRegistery();
    void init();
    void setRegister(std::string className,std::string methodName,std::string methodDescriptor,NativeMethod method);
    NativeMethod findNativeMethod(std::string className,std::string methodName,std::string methodDescriptor);
    void debug();
};


#endif //JVM_NATIVEREGISTRY_H
