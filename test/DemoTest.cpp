//
// Created by xuranus on 4/22/22.
//

#ifndef JVM_TEST10_H
#define JVM_TEST10_H

#include <bits/stdc++.h>
#include "../src/BootstrapSession.h"

using namespace std;
struct DemoTest {

    static void execute() {
        vector<string> cmd = {"./xjava", "-Xbootclasspath", "/home/xuranus/CLionProjects/xjava/jre", ""};
        vector<string> classNames = {
//                "ThrowTest",
//                "HelloWorld",
//                "Sum",
//                "BubbleSort",
//                "ArgsEcho",
//                "Fibonacci1",
//                "Fibonacci2",
//                "Fibonacci3",
//                "NativeTest",
//                "TestStatic",
//                "ClassInit", // X
//                "FileTest", // X
//                "ScannerTest", // X
        };

        for(auto& className: classNames) {
            std::cout << "Testing " << className << std::endl;
            cmd[3] = className;
            int argc = cmd.size();
            char** argv = new char*[argc];
            for(int i = 0; i < cmd.size(); i++) {
                argv[i] = cmd[i].data();
            }

            BootstrapSession session(console::Command(argc, argv));
            session.run();
        }

    }
};

#endif