include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(xjava_tests
    SlotsTest.cpp
    BytesReaderTest.cpp
    FilePathTest.cpp
    InstructionReaderTest.cpp
    MethodDescriptorParserTest.cpp
    StackTest.cpp
    FrameTest.cpp
)

target_link_libraries(xjava_tests PRIVATE xjava_lib gtest_main libzip::zip)

include(GoogleTest)
gtest_discover_tests(xjava_tests)
