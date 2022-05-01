//
// Created by xuranus on 4/9/22.
//

#include <iostream>
#include "BootstrapSession.h"
#include "classpath/ClassPath.h"
#include "classfile/ClassFile.h"
#include "common/Exception.h"
#include "JavaVirtualMachine.h"
#include "runtime/heap/ObjectPool.h"

BootstrapSession::BootstrapSession(const console::Command& command): cmd(command) {}

void BootstrapSession::showVersion() {
    std::cout << "Toy Java Virtual Machine By [XUranus]" << std::endl;
    std::cout << "Version 2.0.0" << std::endl;
}

void BootstrapSession::showHelp() {
    std::cout << "Usage: xjava [options] <main class> [args]" << std::endl;
    std::cout << "\t-version | -v " << "\t\t\t print product version and exit" << std::endl;
    std::cout << "\t-help | -h | -? " << "\t\t print this help message" << std::endl;
    std::cout << "\t-classpath | -cp " << "\t\t <class search path of directories and zip/jar files>\n"
                                           "\t\t\t\t\t\t\t A : separated list of directories, JAR archives,\n"
                                           "\t\t\t\t\t\t\t and ZIP archives to search for class files." << std::endl;
    std::cout << "\t-Xbootclasspath " << "\t\t <directories and zip/jar files separated by :>\n"
                                              "\t\t\t\t\t\t\t set search path for bootstrap classes and resources" << std::endl;
    std::cout << "\t-verbose:class " << "\t\t\t enable class verbose output " << std::endl;
    std::cout << "\t-verbose:inst " << "\t\t\t enable instruction verbose output" << std::endl;
    std::cout << "\t-dump " << "\t\t\t\t dump class file, [javap -verbose <class>])" << std::endl;
}

void BootstrapSession::dumpClassFile() const {
    classpath::ClassPath classPath(cmd.xBootClassPath, cmd.cpOption);
    auto reader = classPath.readClass(cmd.className);
    if (reader) {
        classfile::ClassFile klassFile(reader.value());
        klassFile.dumpClassFile();
    } else {
        std::cout << "failed to dump class: " << cmd.className << std::endl;
    }
}

void BootstrapSession::execute() const {
    classpath::ClassPath classPath(cmd.xBootClassPath, cmd.cpOption);
    heap::ObjectPool::init();
    JavaVirtualMachine jvm(&classPath, cmd);
    jvm.start();
}

void BootstrapSession::run() {
    //cmd.dump();
    if(cmd.helpFlag) {
        showHelp();
    } else if(cmd.versionFlag) {
        showVersion();
    } else if(cmd.classDumpFlag && !cmd.className.empty()) {
        dumpClassFile();
    } else if(!cmd.className.empty()) {
        execute();
    } else {
        showHelp();
    }
}