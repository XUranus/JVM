//
// Created by xuranus on 2/7/19.
//

#ifndef JVM_SHELLCOMMAND_H
#define JVM_SHELLCOMMAND_H

#include <string>
#include <vector>

struct ShellCommand {
    std::vector<std::string> args;
    bool helpFlag; //-help
    bool versionFlag; //-version
    bool verboseClass;//-verbose:class
    bool verboseInst;//-verbose:inst
    std::string cpOption; //-cp
    std::string XjreOption;// -X
    std::string className; // last argv

    void debug();
    ShellCommand(int argc,char* argv[]); //construct by command line args
    void excute();
    void printVersion();
    void printHelp();
    void startJVM();
};


#endif //JVM_SHELLCOMMAND_H
