//
// Created by xuranus on 2/11/19.
//

#ifndef JVM_CLASSLOADER_H
#define JVM_CLASSLOADER_H

#include "Class.h"
#include "Object.h"
#include "../../classpath/ClassPath.h"

#include <map>
#include <optional>

namespace heap {


    class ClassLoader {
    public:
        std::map<std::string, Class* > classMap;
        classpath::ClassPath* classPath; // for referring, do not release
        bool verboseClass; // if show class loading process
        bool basicClassesLoaded;

    public:
        explicit ClassLoader(classpath::ClassPath *cp, bool verboseClass);
        ~ClassLoader();

        Class *loadClass(const std::string& className);
        Class* getPrimitiveArrayClass(u1 aType);
        heap::Object *createArgsArrayObject(const std::vector<std::string> &args); // create String[] object for main()
        std::set<Class*> classes() const;

    private:
        // loadNonArrayClass [ read class file -> define -> link[verify ->  prepare]]
        Class *loadNonArrayClass(const std::string& className);
        Class *defineClass(classfile::BytesReader& reader); // trans classfile to heap::Class
        void link(Class *klass); // verify() and prepare()
        void verify(Class *klass); // verify class
        static void prepare(Class *klass); // allocate space for static vars and initialize them

        Class *loadArrayClass(const std::string& className);

        void loadBasicClasses();

        void loadPrimitiveClasses();
        void loadPrimitiveClass(const std::string& className);
    };


}

#endif //JVM_CLASSLOADER_H
