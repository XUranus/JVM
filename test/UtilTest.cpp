//
// Created by xuranus on 4/25/19.
//
#ifndef JVM_TEST6_H
#define JVM_TEST6_H

#include <iostream>
#include "../src/util/FilePath.h"

using namespace std;

class UtilTest {
public:
    static void excute()
    {
        cout << FilePath::absolutePath("JVM") << endl;
        cout << FilePath::join("/xxx/ggg/hhh/","file.txt") << endl;
        cout << FilePath::join("/xxx/ggg/hhh","file.txt") << endl;
        cout << FilePath::hasSuffix("dwedd.jpg",".jpg") << endl;
        cout << FilePath::hasSuffix("dwedd.jpg ",".jpg") << endl;
        cout << FilePath::hasSuffix("dwedd.jpg",".JPG") << endl;
        string str = "   xyx   ";
        FilePath::removeSideBlank(str);
        cout << FilePath::toUpperCase("wxxHjVjdj") << endl;
        cout << FilePath::toLowerCase("wefGJBGbcd") << endl;

    }
};

#endif