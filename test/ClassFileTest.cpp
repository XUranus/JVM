//
// Created by xuranus on 4/25/19.
//

#ifndef JVM_TEST1_H
#define JVM_TEST1_H


#include <bits/stdc++.h>
#include "../src/classfile/ClassFile.h"
#include "../src/classpath/ClassPath.h"

using namespace std;

class ClassFileTest{
public:

    static void testReadOneClass() {
        classfile::BytesReader reader("/home/xuranus/CLionProjects/xjava/demos/BubbleSort.class");
        classfile::ClassFile klass(reader);
        klass.dumpClassFile();
    }

    static void testReadFullJre() {
        using namespace std::chrono;
        const auto p1 = std::chrono::system_clock::now();

        classpath::ClassPath classPath("/home/xuranus/CLionProjects/xjava/jre",//"/home/xuranus/CLionProjects/xjava/cmake-build-debug",//"/home/xuranus/CLionProjects/xjava/jre",
                                       "/home/xuranus/CLionProjects/xjava/demos");
        classPath.dumpStatus();
        std::fstream in("/home/xuranus/CLionProjects/xjava/all.txt");
        std::string classname;

        int count = 0;
        if(in.is_open()) {
            while(!in.eof()) {
                in >> classname;
                auto reader = classPath.readClass(classname);
                count++;
                if (reader) {
                    std::cout << "test " << classname;
                    classfile::ClassFile klass(reader.value());
                    klass.dumpClassFile();
                    std::cout << " Done" << std::endl;
                }
            }
        }


        const auto p2 = std::chrono::system_clock::now();
        long second = std::chrono::duration_cast<std::chrono::seconds>(p2 - p1).count();
        std::cout << "parsed " << count << " files in " << second << std::endl;
    }

    static void execute() {
        //testReadOneClass();
        testReadFullJre();
    }

};

#endif
