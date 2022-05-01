#pragma pack(8)

//#define TEST_MODE   1
#ifdef TEST_MODE

#include "test/UtilTest.cpp"
#include "test/ClassFileTest.cpp"
#include "test/FrameTest.cpp"
#include "test/InsructionTest.cpp"
#include "test/DescriptorParserTest.cpp"
#include "test/DemoTest.cpp"

int main() {
//    UtilTest::execute();
//    ClassFileTest::execute();
//    FrameTest::execute();
//    InstructionTest::execute();
//    DescriptorParserTest::execute();
//    DemoTest::execute();
}

#else

#include "src/BootstrapSession.h"

int main(int argc, char* argv[]) {
    BootstrapSession session(console::Command(argc, argv));
    session.run();
    return 0;
}

#endif
