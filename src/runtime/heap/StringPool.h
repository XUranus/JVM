//
// Created by xuranus on 2/18/19.
//

#ifndef JVM_STRINGPOOL_H
#define JVM_STRINGPOOL_H

#include <map>
#include "Object.h"

struct StringPool {
    static StringPool* instance;
    std::map<std::string,Object*> internedStrings;

    static StringPool* getStringPool();
    StringPool();
    static std::u16string stringToUtf16(std::string& str);
    static std::string utf16ToString(std::vector<uint16>& u16source);
    Object* getJString(ClassLoader* loader,std::string& localStr);//cpp string to java string
    Object* newJString(ClassLoader* loader,std::string& localStr);
    std::string getlocalString(Object* jStr);

    void debug();
};


#endif //JVM_STRINGPOOL_H
