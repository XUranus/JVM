//
// Created by xuranus on 2/18/19.
//

#pragma once

#include <map>
#include <set>
#include "Object.h"

namespace heap {

    namespace StringPool {

        std::u16string stringToUtf16(const std::string &str);
        std::string utf16ToString(const std::u16string &u16source);
        heap::Object* internString(Object *jString);
        heap::Object* JString(ClassLoader *loader, const std::string& localStr); //cpp string to java string
        std::string localString(heap::Object *jString);
        std::set<heap::Object*> allInternedStrings(); // for GC root collection

    }
}
