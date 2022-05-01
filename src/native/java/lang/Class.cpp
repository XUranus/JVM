//
// Created by xuranus on 3/17/19.
//

#include "Class.h"
#include "../../NativeRegistry.h"
#include "../../../runtime/heap/StringPool.h"
#include "../../../instruction/references.h"
#include <cassert>
#include <cstring>


namespace native::java::lang {

    std::map<heap::Object *, heap::Method*> Class::localMethodMap;
    std::map<heap::Object *, heap::Field*> Class::localFieldMap;
    std::map<heap::Object *, heap::Class*> Class::localClassMap;

    void Class::jMethodSetRegister(heap::Object* jMethod, heap::Method* method) {
        Class::localMethodMap[jMethod] = method;
    }

    heap::Method* Class::reflectMethod(heap::Object* jMethodObject) {
        if(Class::localMethodMap.find(jMethodObject) != Class::localMethodMap.end()) {
            return Class::localMethodMap[jMethodObject];
        } else {
            return nullptr;
        }
    }

    void Class::jFieldSetRegister(heap::Object* jField, heap::Field* field) {
        Class::localFieldMap[jField] = field;
    }

    heap::Field* Class::reflectField(heap::Object* jFieldObject) {
        if(Class::localFieldMap.find(jFieldObject) != Class::localFieldMap.end()) {
            return Class::localFieldMap[jFieldObject];
        } else {
            return nullptr;
        }
    }

    void Class::jClassSetRegister(heap::Object* jClass, heap::Class* klass) {
        Class::localClassMap[jClass] = klass;
    }

    heap::Class* Class::reflectClass(heap::Object* jClassObject) {
        if(Class::localClassMap.find(jClassObject) != Class::localClassMap.end()) {
            return Class::localClassMap[jClassObject];
        } else {
            return nullptr;
        }
    }



    void Class::doRegistration() {
        const std::string className = "java/lang/Class";
        setRegister(className, "getPrimitiveClass", "(Ljava/lang/String;)Ljava/lang/Class;", getPrimitiveClass);
        setRegister(className, "getName0", "()Ljava/lang/String;", getName0);
        setRegister(className, "desiredAssertionStatus0", "(Ljava/lang/Class;)Z", desiredAssertionStatus0);
        setRegister(className, "isInterface", "()Z", isInterface);
        setRegister(className, "isPrimitive", "()Z", isPrimitive);
        setRegister(className, "forName0", "(Ljava/lang/String;ZLjava/lang/ClassLoader;Ljava/lang/Class;)Ljava/lang/Class;", forName0);
        setRegister(className, "getModifiers", "()I", getModifiers);
        setRegister(className, "getSuperclass", "()Ljava/lang/Class;", getSuperclass);
        setRegister(className, "getInterfaces0", "()[Ljava/lang/Class;", getInterfaces0);
        setRegister(className, "isArray", "()Z", isArray);
        setRegister(className, "getDeclaredMethods0", "(Z)[Ljava/lang/reflect/Method;", getDeclaredMethods0);
        setRegister(className, "getDeclaredConstructors0", "(Z)[Ljava/lang/reflect/Constructor;", getDeclaredConstructors0);
        setRegister(className, "getDeclaredFields0", "(Z)[Ljava/lang/reflect/Field;", getDeclaredFields0);
        setRegister(className, "getComponentType", "()Ljava/lang/Class;", getComponentType);
        setRegister(className, "isAssignableFrom", "(Ljava/lang/Class;)Z", isAssignableFrom);
    }

    heap::Object* toClassArr(heap::ClassLoader* loader, const std::vector<heap::Class*>& classes) {
        heap::Class* classArrayClass = loader->loadClass("java/lang/Class")->arrayClass();
        heap::Object* classArray = classArrayClass->newArrayObject(classes.size());
        if(!classes.empty()) {
            heap::Object** classObjects = classArray->objectRefArray();
            for(int i = 0; i < classes.size(); i++) {
                classObjects[i] = classes[i]->jClass;
            }
        }
        return classArray;
    }

    heap::Object* JSignatureStr(heap::ClassLoader* classLoader, const std::string& signature) {
        if(signature.empty()) {
            return nullptr;
        } else {
            return heap::StringPool::JString(classLoader, signature);
        }
    }

    heap::Object* JByteArray(heap::ClassLoader* classLoader, std::vector<u1> annotationData) {
        if(annotationData.empty()) {
            return nullptr;
        }
        u1* bytes = new u1[annotationData.size()];
        memcpy(bytes, annotationData.data(), sizeof (u1) * annotationData.size());
        return heap::ObjectPool::createObject(
                classLoader->loadClass("[B"),
                bytes,
                (int)annotationData.size(),
                heap::ObjectDataType::ByteArray
                );
    }

    // static native Class<?> getPrimitiveClass(String name);
    // (Ljava/lang/String;)Ljava/lang/Class;
    void Class::getPrimitiveClass(runtime::Frame *frame) {
        heap::Object* nameObj = frame->localVars.refValue(0); // String name;
        std::string name = heap::StringPool::localString(nameObj);
        heap::ClassLoader* loader = frame->method->klass->classloader;
        heap::Object* jClass = loader->loadClass(name)->jClass;
        frame->operandStack.pushRef(jClass);
    }

    // private native String getName0();
    // ()Ljava/lang/String;
    void Class::getName0(runtime::Frame *frame) {
        heap::Object* _this = frame->localVars.refValue(0);
        heap::Class* klass = reflectClass(_this);
        frame->operandStack.pushRef(heap::StringPool::JString(klass->classloader, klass->getJavaName()));
    }

    // private static native boolean desiredAssertionStatus0(Class<?> clazz);
    // (Ljava/lang/Class;)Z
    void Class::desiredAssertionStatus0(runtime::Frame *frame) {
        frame->operandStack.pushBoolean(false); // todo
    }

    // public native boolean isInterface();
    // ()Z
    void Class::isInterface(runtime::Frame *frame) {
        heap::Object* _this = frame->localVars.refValue(0);
        heap::Class* klass = reflectClass(_this);
        frame->operandStack.pushBoolean(klass->isInterface());
    }

    // public native boolean isPrimitive();
    // ()Z
    void Class::isPrimitive(runtime::Frame *frame) {
        heap::Object* _this = frame->localVars.refValue(0);
        heap::Class* klass = reflectClass(_this);
        frame->operandStack.pushBoolean(klass->isPrimitive());
    }


    // private static native Class<?> forName0(String name, boolean initialize,
    //                                         ClassLoader loader,
    //                                         Class<?> caller)
    //     throws ClassNotFoundException;
    // (Ljava/lang/String;ZLjava/lang/ClassLoader;Ljava/lang/Class;)Ljava/lang/Class;
    void Class::forName0(runtime::Frame *frame) {
        auto& vars = frame->localVars;
        heap::Object* jName = vars.refValue(0); // String name;
        bool initialize = vars.intValue(1); // boolean initialize
        // auto jClassLoader = vars.refValue(2);

        // resolve class name
        std::string name = heap::StringPool::localString(jName);
        for(char &ch: name) {
            if(ch == '.') {
                ch = '/';
            }
        }

        // load class
        heap::ClassLoader* classLoader = frame->method->klass->classloader;
        heap::Class* klass = classLoader->loadClass(name);
        heap::Object* jClass = klass->jClass;

        if(initialize && !klass->isInitStarted()) {
            // undo forName0
            runtime::Thread* thread = frame->thread;
            frame->nextPC = thread->pc;
            // init class
            thread->initClass(klass);
        } else {
            frame->operandStack.pushRef(jClass);
        }
    }

    // public native int getModifiers();
    // ()I
    void Class::getModifiers(runtime::Frame *frame) {
        heap::Object* _this = frame->localVars.refValue(0);
        heap::Class* klass = reflectClass(_this);
        unsigned short modifiers = klass->accessFlags;
        frame->operandStack.pushInt(modifiers);
    }

    // public native Class<? super T> getSuperclass();
    // ()Ljava/lang/Class;
    void Class::getSuperclass(runtime::Frame *frame) {
        heap::Object* _this = frame->localVars.refValue(0);
        heap::Class* klass = reflectClass(_this);
        heap::Class* superClass = klass->superClass;

        if(superClass) {
            frame->operandStack.pushRef(superClass->jClass);
        } else {
            frame->operandStack.pushRef(nullptr);
        }
    }


    // private native Class<?>[] getInterfaces0();
    // ()[Ljava/lang/Class;
    void Class::getInterfaces0(runtime::Frame *frame) {
        heap::Object* _this = frame->localVars.refValue(0);
        heap::Class* klass = reflectClass(_this);
        auto& interfaces = klass->interfaces;
        frame->operandStack.pushRef(toClassArr(klass->classloader, interfaces));
    }

    // public native boolean isArray();
    // ()Z
    void Class::isArray(runtime::Frame *frame) {
        heap::Object* _this = frame->localVars.refValue(0);
        heap::Class* klass = reflectClass(_this);
        frame->operandStack.pushBoolean(klass->isArray());
    }

    // public native Class<?> getComponentType();
    // ()Ljava/lang/Class;
    void Class::getComponentType(runtime::Frame *frame) {
        heap::Object* _this = frame->localVars.refValue(0);
        heap::Class* klass = reflectClass(_this);

        heap::Class* componentClass = klass->componentClass();
        heap::Object* componentClassObj = componentClass->jClass;

        frame->operandStack.pushRef(componentClassObj);
    }

    // public native boolean isAssignableFrom(Class<?> cls);
    // (Ljava/lang/Class;)Z
    void Class::isAssignableFrom(runtime::Frame *frame) {
        heap::Object* _this = frame->localVars.refValue(0);
        heap::Object* cls = frame->localVars.refValue(1);
        heap::Class* thisClass = reflectClass(_this);
        heap::Class* clsClass = reflectClass(cls);
        frame->operandStack.pushBoolean(thisClass->isAssignableFrom(clsClass));
    }




    /*
    Method(Class<?> declaringClass,
           String name,
           Class<?>[] parameterTypes,
           Class<?> returnType,
           Class<?>[] checkedExceptions,
           int modifiers,
           int slot,
           String signature,
           byte[] annotations,
           byte[] parameterAnnotations,
           byte[] annotationDefault)
    */

    // private native Method[] getDeclaredMethods0(boolean publicOnly);
    // (Z)[Ljava/lang/reflect/Method;
    void Class::getDeclaredMethods0(runtime::Frame *frame) {
        const std::string _methodConstructorDescriptor = std::string("(Ljava/lang/Class;") +
                                             "Ljava/lang/String;" +
                                             "[Ljava/lang/Class;" +
                                             "Ljava/lang/Class;" +
                                             "[Ljava/lang/Class;" +
                                             "II" +
                                             "Ljava/lang/String;" +
                                             "[B[B[B)V";

        auto& vars = frame->localVars;
        auto& stack = frame->operandStack;
        heap::Object* _this = vars.refValue(0);
        bool publicOnly = vars.intValue(1);

        heap::Class* klass = reflectClass(_this);
        auto methods = klass->getMethods(publicOnly);
        int methodCount = methods.size();

        heap::ClassLoader* classLoader = klass->classloader;
        heap::Class* methodClass = classLoader->loadClass("java/lang/reflect/Method");
        heap::Object* methodArrayObject = methodClass->arrayClass()->newArrayObject(methodCount);

        // load methods array object
        if(methodCount > 0) {
            runtime::Thread* thread = frame->thread;
            heap::Object** methodObjs = methodArrayObject->objectRefArray();
            heap::Method* methodConstructor = methodClass->getConstructor(_methodConstructorDescriptor);

            for(int i = 0; i < methods.size(); i++) {
                auto& method = methods[i];
                heap::Object* methodObj = methodClass->newObject();
                methodObjs[i] = methodObj;
                Class::jMethodSetRegister(methodObj, method);

                auto shimMethod = heap::Method::ShimMethod; // shim method
                auto shimFrame = runtime::Frame(0, 12, thread, shimMethod);

                shimFrame.operandStack.pushRef(methodObj);
                shimFrame.operandStack.pushRef(_this);
                shimFrame.operandStack.pushRef(heap::StringPool::JString(classLoader, method->name));
                shimFrame.operandStack.pushRef(toClassArr(classLoader, method->parameterTypes()));
                shimFrame.operandStack.pushRef(method->returnType()->jClass);
                shimFrame.operandStack.pushRef(toClassArr(classLoader, method->exceptionTypes()));
                shimFrame.operandStack.pushInt(method->accessFlags);
                shimFrame.operandStack.pushInt(0);
                shimFrame.operandStack.pushRef(JSignatureStr(classLoader, method->signature));
                shimFrame.operandStack.pushRef(JByteArray(classLoader, method->getAnnotationData()));
                shimFrame.operandStack.pushRef(JByteArray(classLoader, method->getParameterAnnotationData()));
                shimFrame.operandStack.pushRef(JByteArray(classLoader, method->getAnnotationDefaultData()));

                thread->stack->push(shimFrame);
                instruction::invokeMethod(&thread->stack->top(), methodConstructor);
            }
        }


        stack.pushRef(methodArrayObject);
    }


    /*
    Field(Class<?> declaringClass,
          String name,
          Class<?> type,
          int modifiers,
          int slot,
          String signature,
          byte[] annotations)
    */
    // private native Field[] getDeclaredFields0(boolean publicOnly);
    // (Z)[Ljava/lang/reflect/Field;
    void Class::getDeclaredFields0(runtime::Frame *frame) {
        const std::string _fieldConstructorDescriptor = std::string("(Ljava/lang/Class;") +
                                            "Ljava/lang/String;" +
                                            "Ljava/lang/Class;" +
                                            "II" +
                                            "Ljava/lang/String;" +
                                            "[B)V";

        auto& vars = frame->localVars;
        auto& stack = frame->operandStack;
        heap::Object* _this = vars.refValue(0);
        bool publicOnly = vars.boolValue(1);

        heap::Class* klass = reflectClass(_this);
        auto fields = klass->getFields(publicOnly);
        int fieldCount = (int)fields.size();

        heap::ClassLoader* classLoader = klass->classloader;
        heap::Class* fieldClass = classLoader->loadClass("java/lang/reflect/Field");
        heap::Object* fieldArrayObject = fieldClass->arrayClass()->newArrayObject(fieldCount);

        // load methods array object
        if(fieldCount > 0) {
            runtime::Thread* thread = frame->thread;
            heap::Object** fieldObjs = fieldArrayObject->objectRefArray();
            heap::Method* fieldConstructor = fieldClass->getConstructor(_fieldConstructorDescriptor);

            for(int i = 0; i < fields.size(); i++) {
                auto& field = fields[i];
                heap::Object* fieldObj = fieldClass->newObject();
                fieldObjs[i] = fieldObj;
                Class::jFieldSetRegister(fieldObj, field);

                auto shimMethod = heap::Method::ShimMethod; // shim method
                auto shimFrame = runtime::Frame(0, 8, thread, shimMethod);

                shimFrame.operandStack.pushRef(fieldObj);
                shimFrame.operandStack.pushRef(_this);
                shimFrame.operandStack.pushRef(heap::StringPool::JString(classLoader, field->name));
                shimFrame.operandStack.pushRef(field->type()->jClass);
                shimFrame.operandStack.pushInt(field->accessFlags);
                shimFrame.operandStack.pushInt(field->slotId);
                shimFrame.operandStack.pushRef(JSignatureStr(classLoader, field->signature));
                shimFrame.operandStack.pushRef(JByteArray(classLoader, field->getAnnotationData()));

                thread->stack->push(shimFrame);
                instruction::invokeMethod(&thread->stack->top(), fieldConstructor);
            }
        }

        stack.pushRef(fieldArrayObject);
    }


    /*
    Constructor(Class<T> declaringClass,
                Class<?>[] parameterTypes,
                Class<?>[] checkedExceptions,
                int modifiers,
                int slot,
                String signature,
                byte[] annotations,
                byte[] parameterAnnotations)
    }
    */

    // private native Constructor<T>[] getDeclaredConstructors0(boolean publicOnly);
    // (Z)[Ljava/lang/reflect/Constructor;
    void Class::getDeclaredConstructors0(runtime::Frame *frame) {
        const std::string _constructorConstructorDescriptor = std::string("(Ljava/lang/Class;") +
                                                  "[Ljava/lang/Class;" +
                                                  "[Ljava/lang/Class;" +
                                                  "II" +
                                                  "Ljava/lang/String;" +
                                                  "[B[B)V";

        auto& vars = frame->localVars;
        auto& stack = frame->operandStack;
        heap::Object* _this = vars.refValue(0);
        bool publicOnly = vars.intValue(1);

        heap::Class* klass = reflectClass(_this);
        auto constructors = klass->getConstructors(publicOnly);
        int constructorsCount = constructors.size();

        heap::ClassLoader* classLoader = klass->classloader;
        heap::Class* constructorClass = classLoader->loadClass("java/lang/reflect/Constructor");
        heap::Object* constructorArrayObject = constructorClass->arrayClass()->newArrayObject(constructorsCount);

        // load methods array object
        if(constructorsCount > 0) {
            runtime::Thread* thread = frame->thread;
            heap::Object** constructorObjs = constructorArrayObject->objectRefArray();
            heap::Method* methodConstructor = constructorClass->getConstructor(_constructorConstructorDescriptor);

            for(int i = 0; i < constructors.size(); i++) {
                auto& constructor = constructors[i];
                heap::Object* constructorObj = constructorClass->newObject();
                constructorObjs[i] = constructorObj;
                Class::jMethodSetRegister(constructorObj, constructor);

                auto shimMethod = heap::Method::ShimMethod; // shim method
                auto shimFrame = runtime::Frame(0, 9, thread, shimMethod);

                shimFrame.operandStack.pushRef(constructorObj);
                shimFrame.operandStack.pushRef(_this);
                shimFrame.operandStack.pushRef(toClassArr(classLoader, constructor->parameterTypes()));
                shimFrame.operandStack.pushRef(toClassArr(classLoader, constructor->exceptionTypes()));
                shimFrame.operandStack.pushInt(constructor->accessFlags);
                shimFrame.operandStack.pushInt(0);
                shimFrame.operandStack.pushRef(JSignatureStr(classLoader, constructor->signature));
                shimFrame.operandStack.pushRef(JByteArray(classLoader, constructor->getAnnotationData()));
                shimFrame.operandStack.pushRef(JByteArray(classLoader, constructor->getParameterAnnotationData()));\

                thread->stack->push(shimFrame);
                instruction::invokeMethod(&thread->stack->top(), methodConstructor);
            }
        }


        stack.pushRef(constructorArrayObject);
    }

}