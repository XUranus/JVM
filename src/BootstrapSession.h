//
// Created by xuranus on 4/9/22.
//

#ifndef JVM_BOOTSTRAP_SESSION_H
#define JVM_BOOTSTRAP_SESSION_H

#include "console/Command.h"

class BootstrapSession {
private:
    console::Command cmd;

    static void showVersion();
    static void showHelp();
    void dumpClassFile() const;
    void execute() const;
public:
    explicit BootstrapSession(const console::Command& cmd);
    void run();
};


#endif //JVM_BOOTSTRAP_SESSION_H
