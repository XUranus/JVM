//
// Created by xuranus on 10/5/20.
//

#ifndef JVM_BOOTSTRAP_H
#define JVM_BOOTSTRAP_H

#include "util/ShellCommand.h"

class Bootstrap {
private:
    ShellCommand cmd;

public:
    Bootstrap(ShellCommand &cmd);

    void run() const;
    void printVersion() const;
    void printHelp() const;
    void classpy() const;
    void startJVM() const;
};


#endif //JVM_BOOTSTRAP_H
