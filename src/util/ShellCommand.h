//
// Created by xuranus on 2/7/19.
//

#ifndef JVM_SHELLCOMMAND_H
#define JVM_SHELLCOMMAND_H

#include <string>
#include <vector>


/*
 * class search criteria:
 *
 * -bootstrap classpath (default $JRE_HOME/lib ,mostly in rt.jar),can be specified by "-Xbootclasspath" option
 * -extension classpath (default $JRE_HOME/lib/ext)
 * -user      classpath (default .), can be specified by "$CLASSPATH" environment variable,
 *                                   or be specified by "-classpath"/"-cp" option (with higher priority)
 *
 * */


/*
 * command:
 * java -version
 * java -h/-help
 *
 * java -cp /xxx/xxx
 * java -cp /xxx/xx.jar
 * java -cp /xxx/xx.zip
 * java -cp \xxx\xx.jar;\xx\xx.zip #windows
 * java　-cp /xx/xx.jar:/xx/xx.zip #unix/linux
 * windows:\
 * linux:/
 *
 *java -Xmx -Xms ro declare heap initial size,min and max
 *
 * */



struct ShellCommand {
    bool helpFlag; //-help
    bool versionFlag; //-version
    bool verboseClassFlag;//-verbose:class (self defined option)
    bool verboseInstFlag;//-verbose:inst (self defined option)
    //"-verbose" option set both flag above true
    bool classpyFlag;//-classpy

    std::string cpOption; //-cp || -classpath
    std::string XjreOption;// -X

    std::string className;

    std::vector<std::string> args;//the jvm args, all native args excluding 1st argv, flag and option, classname

    ShellCommand(int argc,char* argv[]); //construct by command line args

    void debug();
};


#endif //JVM_SHELLCOMMAND_H
