//
// Created by xuranus on 2/16/19.
//

#include "Console.h"

void Console::printlnRed(const std::string &str) {
    printf("\033[31m%s\n\033[0m", str.c_str());
}

void Console::printlnYellow(const std::string &str) {
    printf("\033[33m%s\n\033[0m", str.c_str());
}

void Console::printlnBlue(const std::string &str) {
    printf("\033[34m%s\n\033[0m", str.c_str());
}

void Console::printlnGreen(const std::string &str) {
    printf("\033[32m%s\n\033[0m", str.c_str());
}