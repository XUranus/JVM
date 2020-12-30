//
// Created by xuranus on 2/6/19.
//

#ifndef JVM_FILEPATH_H
#define JVM_FILEPATH_H

#include <iostream>
#include <vector>

class FilePath {
public:
    static std::string absolutePath(const std::string& path);
    static std::string join(const std::string& dirPath,const std::string& filename);//join an absolute directory path and filename to a absolute file path
    static bool hasSuffix(const std::string& filepath,const std::string& suffix);
    static void removeSideBlank(std::string& str);//remove front and back blank
    static std::string toUpperCase(const std::string& str);
    static std::string toLowerCase(const std::string& str);
    static std::vector<std::string> split(const std::string& str,const std::string& separator);
    static std::vector<std::string> getAllFileNames(const std::string& absPath);//include dir names,no recursive
    static std::vector<std::string> getAllDirNames(const std::string& absPath);//not recursive
    static std::vector<std::string> getAllZipFileNames(const std::string& absPath);
    static bool isDirectory(const std::string& absPath);
    static bool pathExists(const std::string& path);
};


#endif //JVM_FILEPATH_H
