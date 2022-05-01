//
// Created by xuranus on 2/11/19.
//


#include "ClassLoader.h"
#include "../../common/Console.h"
#include "../../common/Exception.h"
#include "Object.h"
#include "StringPool.h"
#include <cassert>

namespace heap {
    ClassLoader::ClassLoader(classpath::ClassPath *cp, bool _verboseClass) {
        classPath = cp;
        verboseClass = _verboseClass;
        basicClassesLoaded = false;
        loadBasicClasses(); // load java.lang.Class and its super class and interface recursively
        loadPrimitiveClasses(); // load int, long, double, float ....

//        for (auto &pair: classMap) {
//            pair.second->resolveJClass();
//        }
    }

    ClassLoader::~ClassLoader() {
        while(!classMap.empty()) {
            delete classMap.begin()->second;
        }
    }

    Class *ClassLoader::loadClass(const std::string& className) {
        if (classMap.find(className) != classMap.end() && classMap[className]) { // class already loaded
            return classMap[className];
        } else {
            if (verboseClass) {
                Console::printlnBlue("[ClassLoader]: loading:" + className);
            }
            Class *ret = nullptr;

            if (className[0] == '[') { /** example: String[] classname : "[Ljava/lang/String;", int[][] classname: "[[I"  **/
                ret = loadArrayClass(className);
            } else {
                ret = loadNonArrayClass(className);
            }

            // TODO::
//            if(basicClassesLoaded) {
//                ret->resolveJClass();
//            }
            if(classMap.find("java/lang/Class") != classMap.end()) {
                ret->resolveJClass();
            }

            if (verboseClass) {
                Console::printlnBlue("[ClassLoader]: loaded:" + className);
            }
            assert(ret != nullptr);
            return ret;
        }
    }


    std::set<Class *> ClassLoader::classes() const {
        std::set<Class*> res;
        for(const auto & it : classMap) {
            res.insert(it.second);
        }
        return res;
    }

    Class *ClassLoader::loadNonArrayClass(const std::string& className) {
        std::optional<classfile::BytesReader> reader = classPath->readClass(className);
        if(!reader) {
            exception::fatal("java.lang.ClassNotFoundException: " + className);
        }
        Class* klass = defineClass(reader.value());
        link(klass);
        return klass;
    }

    Class *ClassLoader::defineClass(classfile::BytesReader &reader) {
        classfile::ClassFile classFile(reader);
        auto* klass = new Class(&classFile); //parse classFile to heap::Class object
        // TODO:: hack
        if(klass->name == "java/lang/ClassLoader") {
            auto loadLibrary = klass->getStaticMethod("loadLibrary", "(Ljava/lang/Class;Ljava/lang/String;Z)V");
            loadLibrary->code = { 0xb1 };// return
        }
        klass->classloader = this;
        klass->resolveSuperClass(); // load its super class and interfaces
        klass->resolveInterfaces();
        classMap[klass->name] = klass; // register class ptr
        return klass;
    }

    void ClassLoader::link(Class *klass) {
        verify(klass);
        prepare(klass);
    }

    void ClassLoader::verify(Class *klass) {
        //TODO:implement it
        //java虚拟机规范 4.10
    }

    void ClassLoader::prepare(Class *klass) {
        klass->calculateInstanceFieldSlotsId();
        klass->calculateStaticFieldSlotsId();
        klass->allocAndInitializeStaticVars();
    }




    Class *ClassLoader::loadArrayClass(const std::string& className) {
        auto* klass = new Class(className, this, true);
        classMap[className] = klass;
        return klass;
    }

    void ClassLoader::loadBasicClasses() {
        heap::Class* jlClass = loadClass("java/lang/Class");
        basicClassesLoaded = true;

        // TODO::
        for(auto& it: classMap) {
            if(it.second->jClass == nullptr) {
                it.second->resolveJClass();
            }
        }
            /**                                                                 java.lang.Class
             *                                                              |---------Class---------|
             *                                                              |       .......         |
             *                                                              |------------------------
             *                                                                       |
             *                                  |---------------|                    |
             *       |--------Class---------|   |    |-------Object----------|       |
             *       |       .....          |   |    |      Class* klass ----|--------
             *       |   Object* jClass ----|---|    |      Class* extra ----|---------------
             *       |       .....          |        |       ......          |              |
             *       |----------------------|        |------------------------              |
             *                  |                      instance of java.lang.Class          |
             *                  |                                                           |
             *                  |-----------------------------------------------------------|
             *
             *
             *
             */
    }

    void ClassLoader::loadPrimitiveClasses() {
        std::vector<std::string> _primitiveTypes {"float", "double", "void", "boolean", "int", "long", "byte", "short", "char"};
        for (auto &type: _primitiveTypes) {
            //std::cout << type << std::endl;
            loadPrimitiveClass(type);
        }
    }

    void ClassLoader::loadPrimitiveClass(const std::string& className) { // short, int, float ...
        if(classMap.find(className) == classMap.end()) {
            auto* klass = new Class(className, this, false);
            klass->resolveJClass(); // TODO::
            classMap[className] = klass;
        } else {
            exception::fatal("unknown primitive class: " + className);
        }
    }



    Class* ClassLoader::getPrimitiveArrayClass(u1 aType) {
        switch (aType) {
            case AT_BOOLEAN:    return loadClass("[Z");
            case AT_BYTE:       return loadClass("[B");
            case AT_CHAR:       return loadClass("[C");
            case AT_SHORT:      return loadClass("[S");
            case AT_INT:        return loadClass("[I");
            case AT_LONG:       return loadClass("[J");
            case AT_FLOAT:      return loadClass("[F");
            case AT_DOUBLE:     return loadClass("[D");
            default: exception::fatal("invalid A_TYPE:" + std::to_string(aType));
        }
        return nullptr;
    }

    Object *ClassLoader::createArgsArrayObject(const std::vector<std::string> &args) {
        heap::Class* stringClass = loadClass("java/lang/String");
        heap::Object* argsArray = stringClass->arrayClass()->newArrayObject(args.size());// String[] args
        heap::Object** jArgs = argsArray->objectRefArray();
        for (int i = 0; i < args.size(); i++) {
            jArgs[i] = heap::StringPool::JString(this, args[i]);
        }
        return argsArray;
    }


}