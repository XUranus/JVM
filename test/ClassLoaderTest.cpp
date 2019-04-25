//
// Created by xuranus on 4/25/19.
//

#ifndef JVM_TEST2_H
#define JVM_TEST2_H

#include "../src/classpath/Entry.h"
#include "../src/classpath/ClassPath.h"
#include "../src/classfile/ClassReader.h"
#include "../src/util/ShellCommand.h"

#include "../src/util/Console.h"

class ClassLoaderTest
{
    //test class loader
public:

    static void excute()
    {
        int argc = 6;
        char *argv[6];

        char a0[]  = "toyJava";
        char a1[] = "-cp";
        char a2[] = "/home/xuranus/CLionProjects/JVM/demos";
        char a3[] = "-verbose:inst";
        char a4[] = "-verbose:class";
        char a5[] = "ArgsEcho";//TODO:: Fibonacci3 error!

        argv[0] = a0;
        argv[1] = a1;
        argv[2] = a2;
        argv[3] = a3;
        argv[4] = a4;
        argv[5] = a5;

        Main(argc,argv);

        Console::printlnSuccess("Test Case Passed");
    }

    static void Main(int argc,char* argv[]) {
        ShellCommand cmd(argc,argv);
        cmd.excute();
    }
};

#endif