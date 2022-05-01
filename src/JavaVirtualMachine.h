//
// Created by xuranus on 4/23/22.
//

#ifndef JVM_JAVA_VIRTUAL_MACHINE_H
#define JVM_JAVA_VIRTUAL_MACHINE_H

#include "console/Command.h"
#include "runtime/thread/Thread.h"
#include "runtime/heap/ClassLoader.h"

class JavaVirtualMachine {
private:
    console::Command cmd;
    runtime::Thread mainThread;
    heap::ClassLoader classLoader;

public:
    JavaVirtualMachine(classpath::ClassPath* classPath, console::Command  cmd);
    void start();

private:
    void initVM();
    void executeMain();
    void interpret(runtime::Thread* thread) const;

    [[nodiscard]] std::set<heap::Object*> collectGCRoots() const;
};


#endif // JVM_JAVA_VIRTUAL_MACHINE_H
