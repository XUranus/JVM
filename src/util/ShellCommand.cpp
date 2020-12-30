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
#include "FilePath.h"

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
    verboseClassFlag = false;
    verboseInstFlag = false;
    classpyFlag = false;

    cpOption = "";
    XjreOption = "";

    className = "";

    int i = 0;

    for(i = 1;i < argc; i++) { //omit first argv, start to read option, classname
        std::string option(argv[i]);
        if(option =="-version") {
            versionFlag = true;
        } else if(option =="-help" || option == "-h") {
            helpFlag = true;
        } else if(option =="-verbose:class") {
            verboseClassFlag = true;
        } else if(option =="-verbose:inst") {
            verboseInstFlag = true;
        } else if(option =="-verbose") {
            verboseClassFlag = true;
            verboseInstFlag = true;
        } else if(option =="-classpy") {
            classpyFlag = true;
        } else if((option =="-cp" || option == "-classpath") && i + 1 < argc) {
            cpOption = std::string(argv[i+1]);
            i++;
        }  else if((option =="-Xjre" || option == "-Xbootclasspath") && i + 1 < argc) {
            XjreOption = std::string(argv[i+1]);
            i++;
        } else { //option not start with "-", it must be a classname
            className = std::string(argv[i]);
            i++;
            break;
        }
    }

    //send the left args to jvm
    for(;i < argc;i++)
    {
        args.emplace_back(std::string(argv[i]));
    }

}
