#include <iostream>
#include <vector>
#include "util/ShellCommand.h"
#include "runtime/heap/StringPool.h"
#include "native/NativeRegistry.h"
#include "Bootstrap.h"

#include "classpath/ClassPath.h"
#include "classfile/ClassReader.h"
#include "util/Console.h"

//#define TEST_MODE 1
//#define DEBUG_MODE 1


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
    //ClassPathTest::excute(); //Done
    //ClassFileTest::excute(); //Done
    //UtilTest::excute();
    //FrameTest::excute();
    //RuntimeTest::excute();
    //ClassLoaderTest::excute();

    auto classes = {
            //"java.awt.Cursor",
            //"javax.swing.plaf.BorderUIResource$EmptyBorderUIResource",
            //"javax.swing.plaf.ColorUIResource",
            //"java.awt.Color",
            //"java.awt.geom.AffineTransform",
            //"sun.reflect.CallerSensitive",
    };

    for(auto c=classes.begin();c!=classes.end();c++) {
        ClassPath path("","");
        byte* data;
        int n = path.readClass(string(*c),data);
        ClassReader reader(data,n);
        reader.parseClassFile()->debug();
        Console::printlnSuccess(string(*c));
    }




#endif

#ifndef TEST_MODE
    ShellCommand cmd(args,argv);
    Bootstrap session(cmd);
    session.run();
#endif

    return 0;
 }