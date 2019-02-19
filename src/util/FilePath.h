//
// Created by xuranus on 2/6/19.
//

#ifndef JVM_FILEPATH_H
#define JVM_FILEPATH_H

#include <iostream>
#include <vector>

class FilePath {
public:
    static std::string absolutePath(std::string path);
    static std::string join(std::string dirPath,std::string filename);//join an absolute directory path and filename to a absolute file path
    static bool hasSuffix(std::string filepath,std::string suffix);
    static void removeSideBlank(std::string& str);//remove front and back blank
    static std::string toUpperCase(std::string str);
    static std::string toLowerCase(std::string str);
    static std::vector<std::string> split(std::string str,std::string c);
    static std::vector<std::string> getAllFileNames(std::string absPath);//include dir names,no recursive
    static std::vector<std::string> getAllDirNames(std::string absPath);//not recursive
    static std::vector<std::string> getAllZipFileNames(std::string absPath);
    static bool isDirectory(std::string absPath);
    static bool pathExists(std::string path);
};


#endif //JVM_FILEPATH_H
