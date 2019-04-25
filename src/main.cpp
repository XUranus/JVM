#include <iostream>
#include <fstream>
#include <iomanip>
#include "util/ShellCommand.h"
#include "runtime/heap/StringPool.h"
#include "native/NativeRegistry.h"


//#define TEST_MODE 1

#ifdef TEST_MODE
#include "../test/ClassLoaderTest.cpp"
#include "../test/ClassFileTest.cpp"
#include "../test/FrameTest.cpp"
#include "../test/RuntimeTest.cpp"
#include "../test/ClassPathTest.cpp"
#include "../test/UtilTest.cpp"
#endif

using namespace std;


int main(int args,char* argv[]) {
    NativeRegistry::getNativeRegistery()->init();

#ifdef TEST_MODE
    ClassLoaderTest::excute();
#endif

#ifndef TEST_MODE
    ShellCommand cmd(args,argv);
    cmd.excute();
    return 0;
#endif
 }