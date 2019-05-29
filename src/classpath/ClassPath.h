//
// Created by xuranus on 2/6/19.
//

#ifndef JVM_CLASSPATH_H
#define JVM_CLASSPATH_H


#include "Entry.h"

struct ClassPath {
    Entry* bootstrapClassPath;
    Entry* extendClassPath;
    Entry* userClassPath;

    std::string getUserPath(std::string cpOption);
    std::string getJrePath(std::string jreOption);
    ClassPath(std::string jreOption,std::string cpOption);
    std::pair<byte*,int> readClass(std::string classname);//classname example : java/lang/Object ,not contain ".class" suffix

    void debug();
};


#endif //JVM_CLASSPATH_H
