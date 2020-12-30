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

    static std::string getUserPath(const std::string& cpOption);
    static std::string getJrePath(const std::string& jreOption);
    ClassPath(const std::string& jreOption,const std::string& cpOption);
    ~ClassPath();
    int readClass(const std::string& classname,byte*& data);//classname example : java/lang/Object ,not contain ".class" suffix

    void debug();
};


#endif //JVM_CLASSPATH_H
