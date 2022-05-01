//
// Created by xuranus on 2/6/19.
//

#ifndef JVM_FILEPATH_H
#define JVM_FILEPATH_H

#include <iostream>
#include <vector>

class FilePath {
public:
    static std::string separator;

    static std::string trim(const std::string& str);//remove front and back blank
    static std::string upperCase(const std::string& str);
    static std::string lowerCase(const std::string& str);
    static bool endsWith(const std::string& str, std::string suffix);
    static bool startsWith(const std::string& str, std::string prefix);
    static std::string cwd();

    static std::string absolutePath(const std::string& path);
    static std::string join(const std::string& dirPath,const std::string& filename);//join an absolute directory path and filename to a absolute file path
    static std::vector<std::string> split(const std::string& str,const std::string& separator);
    static std::vector<std::string> list(const std::string& absPath);//include dir names,no recursive
    static std::vector<std::string> listDir(const std::string& absPath);//not recursive
    static std::vector<std::string> listZip(const std::string& absPath);
    static bool isDir(const std::string& absPath);
    static bool exists(const std::string& path);
};


#endif //JVM_FILEPATH_H
