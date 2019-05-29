//
// Created by xuranus on 3/16/19.
//

#include "NativeRegistry.h"
#include "../util/Console.h"

#include "lang/Class_Object.h"
#include "lang/Class_Class.h"
#include "lang/Class_Double.h"
#include "lang/Class_Float.h"
#include "lang/Class_String.h"
#include "lang/Class_System.h"

NativeRegistry* NativeRegistry::instance = nullptr;

NativeRegistry::NativeRegistry() {}

void emptyNativeMethod() {
    Console::printlnWarning("emptyNativeMethod invoked");
}

NativeRegistry* NativeRegistry::getNativeRegistery() {
    if(NativeRegistry::instance== nullptr)
        NativeRegistry::instance = new NativeRegistry();
    return NativeRegistry::instance;
}

void NativeRegistry::setRegister(std::string className, std::string methodName, std::string methodDescriptor,
                                 NativeMethod method) {
    auto key = className+"~"+methodName+"~"+methodDescriptor;
    registry[key] = method;
}


NativeMethod NativeRegistry::findNativeMethod(std::string className, std::string methodName,
                                              std::string methodDescriptor) {
    auto key = className+"~"+methodName+"~"+methodDescriptor;
    if(registry.find(key)!=registry.end())
        return registry[key];
    if(methodDescriptor=="()V" && methodName=="registerNatives") {
        return (NativeMethod)&emptyNativeMethod;
    }
    return nullptr;
}

void NativeRegistry::init() {
    Class_Object::init();
    Class_Class::init();
    Class_Double::init();
    Class_Float::init();
    Class_String::init();
    Class_System::init();
}

void NativeRegistry::debug()
{
    printf("[Debug NativeRegistry]\n");
    for(auto &m:registry) {
        printf("<%s,%d>\n",m.first.c_str(),m.second);
    }
}