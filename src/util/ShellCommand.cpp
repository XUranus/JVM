//
// Created by xuranus on 2/7/19.
//

#include "ShellCommand.h"

#include "../../src/classpath/Entry.h"
#include "../../src/classpath/ClassPath.h"
#include "../../src/classfile/ClassReader.h"
#include "../../src/runtime/heap/ClassLoader.h"
#include "../../src/instructions/instruction.h"
#include "Console.h"

void ShellCommand::debug()
{
    printf("shell cmd debug:\n");
    printf("helpflag:%d\n",helpFlag);
    printf("versionFlag:%d\n",versionFlag);
    printf("cpOption:%s\n",cpOption.c_str());
    printf("XjreOption:%s\n",XjreOption.c_str());
    printf("className:%s\n\n",className.c_str());

}

ShellCommand::ShellCommand(int argc, char **argv) //construct by command line args
{
    helpFlag = false;
    versionFlag = false;
    cpOption = "";
    className = "";
    XjreOption = "";

    for(int i=0;i<argc;i++)
    {
        args.emplace_back(std::string(argv[i]));
    }

    for(int i=1;i<argc;i++) { //omit first argv
        if(std::string(argv[i])=="-version") {
            versionFlag = true;
        } else if(std::string(argv[i])=="-help") {
            helpFlag = true;
        } else if(std::string(argv[i])=="-verbose:class") {
            verboseClass = true;
        } else if(std::string(argv[i])=="-verbose:inst") {
            verboseInst = true;
        } else if(std::string(argv[i])=="-verbose") {
            verboseClass = verboseInst = true;
        } else if(std::string(argv[i])=="-cp" && i+1<argc) {
            cpOption = std::string(argv[i+1]);
            i++;
        }  else if(std::string(argv[i])=="-X" && i+1<argc) {
            XjreOption = std::string(argv[i+1]);
            i++;
        }
        else className = std::string(argv[i]);
    }
}


void ShellCommand::excute()
{
    //debug();
    if(versionFlag)
        printVersion();
    else if(helpFlag)
        printHelp();
    else
        startJVM();
}

void ShellCommand::printVersion()
{
    printf("Java Virtual Machine [XUranus Toy Edition]\n");
    printf("Version 1.0.0\n\n");
}

void ShellCommand::printHelp()
{
    printf("Usage: toyjava [options] <mainclass> [args]\n");
    printf("\t\t(to start a class)\n");
    printf("where options include:\n\n");
    printf("\t-cp <class search path of directories and zip/jar files>\n");
    printf("\t-verbose <class need to be shown detail>\n\n");
}

void ShellCommand::startJVM()
{
    ClassPath classPath(XjreOption,cpOption);
    ClassLoader classLoader(&classPath);

    //get class name
    className = className.substr(className.rfind('/')+1,className.length());
    auto mainClass = classLoader.loadClass(className);
    auto mainMethod = mainClass->getMainMethod();
    if(mainMethod == nullptr)
    {
        printf("main class not found.\n");
        exit(0);
    } else {
        //mainMethod->debug();
        Method::interpret(mainMethod,verboseInst,args);
    }

    //TODO::runtime object garbage collect
}