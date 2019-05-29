//
// Created by xuranus on 4/25/19.
//


#ifndef JVM_TEST3_H
#define JVM_TEST3_H

#include "../src/classpath/Entry.h"
#include "../src/classpath/ClassPath.h"
#include "../src/classfile/ClassReader.h"

class ClassPathTest {
public:
    static void excute() {

        ///home/xuranus/Desktop/rt.jar (jre)
        ClassPath classPath("","/home/xuranus/CLionProjects/JVM/test/classFileTest");
        auto ret = classPath.readClass("java.lang.Object");
        ClassReader reader(ret.first,ret.second);

        //reader.printAllHexBytes();
        reader.parseClassFile()->debug();

    }
};


#endif //JVM_TEST5_H