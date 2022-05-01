//
// Created by xuranus on 3/17/19.
//

#ifndef JVM_NATIVE_JAVA_LANG_CLASS_H
#define JVM_NATIVE_JAVA_LANG_CLASS_H

#include "../../../runtime/thread/Frame.h"

namespace native::java::lang {
    class Class {
    public:
        // for reflection, reflect from java Class, Method, Field object to local
        static std::map<heap::Object *, heap::Method*> localMethodMap;
        static std::map<heap::Object *, heap::Field*> localFieldMap;
        static std::map<heap::Object *, heap::Class*> localClassMap;

    public:
        // reflection
        static void jMethodSetRegister(heap::Object* jMethod, heap::Method* method);
        static heap::Method* reflectMethod(heap::Object* jMethodObject);
        static void jFieldSetRegister(heap::Object* jField, heap::Field* field);
        static heap::Field* reflectField(heap::Object* jFieldObject);
        static void jClassSetRegister(heap::Object* jClass, heap::Class* klass);
        static heap::Class* reflectClass(heap::Object* jClassObject);

        // native
        static void doRegistration();

        static void getPrimitiveClass(runtime::Frame *frame);
        static void getName0(runtime::Frame *frame);
        static void desiredAssertionStatus0(runtime::Frame *frame);
        static void isInterface(runtime::Frame *frame);
        static void isPrimitive(runtime::Frame *frame);
        static void getDeclaredFields0(runtime::Frame *frame);
        static void forName0(runtime::Frame *frame);
        static void getDeclaredConstructors0(runtime::Frame *frame);
        static void getModifiers(runtime::Frame *frame);
        static void getSuperclass(runtime::Frame *frame);
        static void getInterfaces0(runtime::Frame *frame);
        static void isArray(runtime::Frame *frame);
        static void getDeclaredMethods0(runtime::Frame *frame);
        static void getComponentType(runtime::Frame *frame);
        static void isAssignableFrom(runtime::Frame *frame);
    };
};


#endif //JVM_NATIVE_JAVA_LANG_CLASS_H
