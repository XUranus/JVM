//
// Created by xuranus on 10/5/20.
//

#include "Bootstrap.h"
#include "classpath/ClassPath.h"
#include "classfile/ClassReader.h"
#include "runtime/heap/ClassLoader.h"
#include "util/Console.h"

Bootstrap::Bootstrap(ShellCommand &cmd):cmd(cmd){}

void Bootstrap::run() const {
    //debug();
    if(cmd.versionFlag)
        printVersion();
    else if(cmd.helpFlag)
        printHelp();
    else if(cmd.classpyFlag)
        classpy();
    else
        startJVM();
}

//java -version
void Bootstrap::printVersion() const {
    printf("XUranus's Toy Java Virtual Machine\n");
    printf("Version 1.0.0\n\n");
}

//java -h
void Bootstrap::printHelp() const {
    printf("Usage: ./JVM [options] class [args...]\n");
    printf("\t\t(to excute a class)\n");
    printf("where options include:\n");
    printf("\t-cp 、\t\t\t<user lass search path of directories and zip/jar files>\n");
    printf("\t-classpath \t\t<user class search path of directories and zip/jar files>\n");
    printf("\t-Xbootclasspath <jre class search path of directories and zip/jar files>\n");
    printf("\t-Xjre \t\t\t<jre class search path of directories and zip/jar files>\n");
    printf("\t-verbose \t\t<class need to be shown detail>\n");
    printf("\t-classpy \t\t<class whose *.class file need to be shown  detail>\n");
}

//java -classpy <class>
void Bootstrap::classpy() const{
    if(cmd.className.empty())
    {
        printHelp();
        exit(0);
    }

    ClassPath classPath(cmd.XjreOption,cmd.cpOption);
    byte* data = nullptr;
    int n_bytes = classPath.readClass(cmd.className, data);
    if(n_bytes > 0) { //read success
        //"data" will be released in classReader
        ClassReader reader(data, n_bytes);
        auto classFile = reader.parseClassFile();
        classFile->verbose();
        delete classFile;
    } else { //read fail
        //now "data" must be null, no need to release memory
        Console::printlnError("classpy error, class " + cmd.className + " open failed");
        exit(1);
    }
}


void Bootstrap::startJVM() const {
    if(cmd.className.empty())
    {
        printHelp();
        exit(0);
    }

    ClassPath classPath(cmd.XjreOption,cmd.cpOption);
    ClassLoader classLoader(&classPath,cmd.verboseClassFlag);

    //get class name
    std::string className = cmd.className;
    className = className.substr(className.rfind('/')+1,className.length());
    auto mainClass = classLoader.loadClass(className);
    auto mainMethod = mainClass->getMainMethod();
    if(mainMethod == nullptr)
    {
        Console::printlnError("Error: Main method not found in class "
        + className
        + ", ""please define the main method as:\n"
        + "   public static void main(String[] args)");
        exit(0);
    } else {
        //mainMethod->debug();
        Method::interpret(mainMethod,cmd.verboseInstFlag,cmd.args);
    }

    //TODO::runtime object garbage collect
}