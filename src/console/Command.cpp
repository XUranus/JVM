//
// Created by xuranus on 4/9/22.
//



#include "Command.h"

#ifdef DEBUG_MODE
#include <iostream>
#endif

namespace console {

    Command::Command(int argc, char **argv) {
        helpFlag = false;
        versionFlag = false;
        verboseClassFlag = false;
        verboseInstFlag = false;
        classDumpFlag = false;

        for(int i = 1; i < argc; i++) { //omit first argv
            std::string arg = argv[i];
            if(arg == "-version" || arg == "-v" ) {
                versionFlag = true;
            } else if(arg == "-help" || arg == "-h" || arg == "-?") {
                helpFlag = true;
            } else if(arg == "-verbose:class") {
                verboseClassFlag = true;
            } else if(arg == "-verbose:inst") {
                verboseInstFlag = true;
            } else if(arg == "-dump") {
                classDumpFlag = true;
            } else if((arg == "-cp" || arg == "-classpath") && i + 1 < argc) {
                cpOption = argv[i + 1];
                i++;
            }  else if(arg == "-Xbootclasspath" && i + 1 < argc) {
                xBootClassPath = argv[ i + 1];
                i++;
            } else {
                if(className.empty()) {
                    className = arg;
                } else {
                    args.emplace_back(std::string(arg));
                }
            }
        }
    }

#ifdef DEBUG_MODE
    void Command::dump() {
        std::cout << "[console::Command Dump]" << std::endl;
        for(const auto& argv: args) {
            std::cout << argv << " ";
        }
        std::cout << std::endl;
        std::cout << "helpFlag: " << helpFlag << std::endl;
        std::cout << "versionFlag: " << versionFlag << std::endl;
        std::cout << "classDumpFlag: " << classDumpFlag << std::endl;

        std::cout << "cpOption: " << cpOption << std::endl;
        std::cout << "xBootClassPath: " << xBootClassPath << std::endl;
        std::cout << "verboseClassFlag: " << verboseClassFlag << std::endl;
        std::cout << "verboseInstFlag: " << verboseInstFlag << std::endl;
        std::cout << "className: " << className << std::endl;
    }
#endif

}