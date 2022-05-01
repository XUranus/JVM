//
// Created by xuranus on 2/18/19.
//

#ifndef JVM_STRING_POOL_H
#define JVM_STRING_POOL_H

#include <map>
#include "Object.h"

namespace heap {

    namespace StringPool {

        static std::map<std::string, heap::Object*> internedStrings;

        std::u16string stringToUtf16(const std::string &str);
        std::string utf16ToString(const std::u16string &u16source);
        heap::Object* internString(Object *jString);
        heap::Object* JString(ClassLoader *loader, const std::string& localStr); //cpp string to java string
        std::string localString(heap::Object *jString);

    }
}

#endif //JVM_STRING_POOL_H
