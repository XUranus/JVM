//
// Created by xuranus on 4/25/19.
//
#ifndef JVM_TEST6_H
#define JVM_TEST6_H

#include <iostream>
#include "../src/common/FilePath.h"

using namespace std;

class UtilTest {
public:

    static void execute() {
        std::cout << FilePath::cwd() << std::endl;
        std::cout << std::endl;
        std::cout << FilePath::absolutePath("") << std::endl;
        std::cout << FilePath::absolutePath(".") << std::endl;
        std::cout << FilePath::absolutePath("..") << std::endl;
        std::cout << FilePath::absolutePath("/") << std::endl;
        std::cout << FilePath::absolutePath("jre") << std::endl;
        std::cout << FilePath::absolutePath("./jre") << std::endl;

        cout << FilePath::absolutePath("JVM") << endl;
        cout << FilePath::join("/xxx/ggg/hhh/","file.txt") << endl;
        cout << FilePath::join("/xxx/ggg/hhh","file.txt") << endl;
        cout << FilePath::endsWith("dwedd.jpg",".jpg") << endl;
        cout << FilePath::endsWith("dwedd.jpg ",".jpg") << endl;
        cout << FilePath::endsWith("dwedd.jpg",".JPG") << endl;

    }
};

#endif