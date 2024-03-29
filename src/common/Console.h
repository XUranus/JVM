//
// Created by xuranus on 2/16/19.
//

#ifndef JVM_CONSOLE_H
#define JVM_CONSOLE_H


#include <cstdio>
#include <string>

/**
 * this is an util to print different color of warning (error, exception) text
 **/

class Console {
public:
    static void printlnRed(const std::string &str);
    static void printlnYellow(const std::string &str);
    static void printlnBlue(const std::string &str);
    static void printlnGreen(const std::string &str);
};

#endif //JVM_CONSOLE_H
