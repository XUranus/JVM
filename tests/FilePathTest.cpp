#include <gtest/gtest.h>
#include "common/FilePath.h"

TEST(FilePathTest, Trim) {
    EXPECT_EQ(FilePath::trim("  hello  "), "hello");
    EXPECT_EQ(FilePath::trim("no trim"), "no trim");
    EXPECT_EQ(FilePath::trim("   "), "");
    EXPECT_EQ(FilePath::trim(""), "");
}

TEST(FilePathTest, LowerCase) {
    EXPECT_EQ(FilePath::lowerCase("Hello"), "hello");
    EXPECT_EQ(FilePath::lowerCase("ABC"), "abc");
    EXPECT_EQ(FilePath::lowerCase("already"), "already");
}

TEST(FilePathTest, UpperCase) {
    EXPECT_EQ(FilePath::upperCase("hello"), "HELLO");
    EXPECT_EQ(FilePath::upperCase("ABC"), "ABC");
}

TEST(FilePathTest, StartsWith) {
    EXPECT_TRUE(FilePath::startsWith("hello world", "hello"));
    EXPECT_FALSE(FilePath::startsWith("hello world", "world"));
    EXPECT_TRUE(FilePath::startsWith("test", "test"));
}

TEST(FilePathTest, EndsWith) {
    EXPECT_TRUE(FilePath::endsWith("file.jar", ".jar"));
    EXPECT_FALSE(FilePath::endsWith("file.jar", ".zip"));
    EXPECT_TRUE(FilePath::endsWith("test", "test"));
}

TEST(FilePathTest, Split) {
    auto parts = FilePath::split("a:b:c", ":");
    ASSERT_EQ(parts.size(), 3u);
    EXPECT_EQ(parts[0], "a");
    EXPECT_EQ(parts[1], "b");
    EXPECT_EQ(parts[2], "c");
}

TEST(FilePathTest, Join) {
    EXPECT_EQ(FilePath::join("/home/user", "file.txt"), "/home/user/file.txt");
    EXPECT_EQ(FilePath::join("/home/user/", "file.txt"), "/home/user/file.txt");
}

TEST(FilePathTest, ExistsCurrentDir) {
    EXPECT_TRUE(FilePath::exists("."));
}

TEST(FilePathTest, CwdNotEmpty) {
    EXPECT_FALSE(FilePath::cwd().empty());
}
