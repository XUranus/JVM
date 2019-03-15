#include <iostream>
#include <fstream>
#include <iomanip>

/*
#include "../test/classFileTest/Test1.cpp"
#include "../test/runtimeTest/Test2.cpp"
#include "../test/runtimeTest/Test3.cpp"
#include "../test/utilTest/Test4.cpp"
#include "../test/classPathTest/Test5.cpp"
#include "../test/testClassLoader/Test6.cpp"
*/

#include "util/ShellCommand.h"
#include "runtime/heap/StringPool.h"

using namespace std;


int main(int args,char* argv[]) {

    //Test1::excute();
    //Test2::excute();
    //Test3::excute();
    //Test4::excute();
    //Test5::excute();
    //Test6::excute();


    ShellCommand cmd(args,argv);
    cmd.excute();
    return 0;
 }