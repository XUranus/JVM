#pragma once

#include <string>
#include "../common/Console.h"

namespace exception {

    // fatal error in VM runtime
    inline void fatal(const std::string& message) {
        Console::printlnRed(message);
        exit(1);
    }

    // error caused by bugs
    inline void panic(const std::string& message) {
        Console::printlnRed("[PANIC!]");
        Console::printlnRed(message);
        exit(1);
    }

    // recoverable exception in VM runtime
    inline void exception(const std::string& message) {
        Console::printlnRed(message);
    }

}
