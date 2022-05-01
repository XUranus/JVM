//
// Created by xuranus on 4/9/22.
//

#ifndef JVM_COMMAND_H
#define JVM_COMMAND_H

#include <string>
#include <vector>

#define DEBUG_MODE

namespace console {

    struct Command {

        std::vector <std::string> args;

        /**
         * show help:
         * [ -help | -h | -? ]
         */
        bool helpFlag;
        /**
         * show version:
         * [ -version | -v ]
         */
        bool versionFlag;

        /**
         * classpath option:
         * [ -cp <path> | -classpath <path>]
         */
        std::string cpOption;


        /**
         * set bootclasspath
         */
        std::string xBootClassPath;// -Xbootclasspath

        /**
         * custom option, print class loading process:
         * [ -verbose:class ]
         */
        bool verboseClassFlag;// -verbose:class

        /**
         * custom option, print inst execute process:
         * [ -verbose:inst ]
         */
        bool verboseInstFlag;// -verbose:inst

        /**
         * custom option, equivalent as "javap -verbose":
         * [ -dump <classname>]
         */
        bool classDumpFlag;


        std::string className;

        Command(int argc, char *argv[]); //construct by command line args

#ifdef DEBUG_MODE
        void dump();
#endif
    };
}


#endif //JVM_COMMAND_H
