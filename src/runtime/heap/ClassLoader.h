//
// Created by xuranus on 2/11/19.
//

#ifndef JVM_CLASSLOADER_H
#define JVM_CLASSLOADER_H

#include "../../classpath/ClassPath.h"
#include "Class.h"
#include <map>

struct ClassLoader {
    std::map<std::string,Class*> classMap;
    ClassPath* classPath;
    bool verboseClass;

    explicit ClassLoader(ClassPath* cp,bool verboseClass);
    Class* loadClass(std::string className);
    Class* loadNonArrayClass(std::string className);
    Class* loadArrayClass(std::string className);
    void loadBasicClasses();
    void loadPrimitiveClasses();
    void loadPrimitiveClass(std::string className);
    Class* getPrimitiveArrayClass(u1 atype);
    Object* createArgsArrayObject(std::vector<std::string>& args);

    int readClass(std::string classname,byte*& data);

    Class* defineClass(byte* data,long length);
    void resolveSuperClass(Class* _class); //load and resolve super class ref
    void resolveInterfaces(Class* _class); //load and resolve interface class ref

    void link(Class* _class);
    void verify(Class* _class);
    void prepare(Class* _class);

};


#endif //JVM_CLASSLOADER_H
