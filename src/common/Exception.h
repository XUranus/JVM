//
// Created by xuranus on 4/6/22.
//

#ifndef JVM_EXCEPTION_H
#define JVM_EXCEPTION_H

#include <exception>
#include <string>

#include "../common//Console.h"

namespace exception {

    // fatal error in VM runtime
    void static fatal(const std::string& message) {
        Console::printlnRed(message);
        exit(1);
    }

    // error caused by bugs
    void static panic(const std::string& message) {
        Console::printlnRed("[PANIC!]");
        Console::printlnRed(message);
        exit(1);
    }

    // recoverable exception in VM runtime
    void static exception(const std::string message) {
        Console::printlnRed(message);
    };

}


#endif //JVM_EXCEPTION_H
