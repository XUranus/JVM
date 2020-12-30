//
// Created by xuranus on 2/6/19.
//

#include "FilePath.h"

#include <cstdlib>
#include <climits>
#include <libnet.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <dirent.h>
#include <cstdlib>
#include <sys/stat.h>
#include "Console.h"

//TODO::test in win platform

std::string FilePath::absolutePath(const std::string& path)
{
    char absPathBuf[PATH_MAX];
    if(!realpath(path.c_str(),absPathBuf))
    {
        Console::printlnError("fetch absolute path failed: " + path);
        exit(1);
    }
    return std::string(absPathBuf);
}

std::string FilePath::join(const std::string& _path, const std::string& _filename)
{
    std::string path = _path;
    std::string filename = _filename;
    removeSideBlank(path);
    removeSideBlank(filename);
    const std::string separator = "/";
    if(FilePath::hasSuffix(path,separator))
        return path + filename;
    else if(!filename.empty())
        return path + separator + filename;
    else
        return path;
}

bool FilePath::hasSuffix(const std::string& _filepath, const std::string& _suffix)
{
    //rt.jar has suffix JaR
    std::string filepath = FilePath::toLowerCase(_filepath);
    removeSideBlank(filepath);
    std::string suffix = FilePath::toLowerCase(_suffix);
    return filepath.rfind(suffix)!=std::string::npos && filepath.rfind(suffix) + suffix.length() == filepath.length();
}


void FilePath::removeSideBlank(std::string &str)
{
    if(!str.empty())
    {
        str.erase(0,str.find_first_not_of(' '));
        str.erase(str.find_last_not_of(' ') + 1);
    }
}

std::string FilePath::toLowerCase(const std::string& str)
{
    std::string ret = str;
    int offset = 'A'-'a';
    for(auto &s:ret){
        if(s >= 'A' && s <= 'Z'){
            s -= offset;
        }
    }
    return ret;
}

std::string FilePath::toUpperCase(const std::string& str)
{
    std::string ret = str;
    int offset = 'A'-'a';
    for(auto &s:ret){
        if(s >= 'a' && s <= 'z'){
            s += offset;
        }
    }
    return ret;
}

std::vector<std::string> FilePath::split(const std::string& s,const std::string& c)
{
    std::vector<std::string> v;
    v.clear();
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
    return v;
}

bool FilePath::isDirectory(const std::string& absPath)
{
    struct stat s{};
    lstat(absPath.c_str(),&s);
    return S_ISDIR(s.st_mode);
}

std::vector<std::string> FilePath::getAllFileNames(const std::string& absPath)
{
    std::vector<std::string> ret;
    ret.clear();
    if(!isDirectory(absPath))
    {
        Console::printlnError(absPath + " is not a valid directory !");
        exit(1);
    }

    struct dirent* filename;
    DIR* dir;
    dir = opendir(absPath.c_str());
    if(dir== nullptr)
    {
        Console::printlnError("could not open directory: " + absPath);
        exit(1);
    }
    while((filename = readdir(dir) )!= nullptr)
    {
        if(strcmp(filename->d_name,".")==0 || strcmp(filename->d_name,"..")==0)
            continue;
        else {
            ret.emplace_back(std::string(filename->d_name));
        }
    }
    return ret;
}

std::vector<std::string> FilePath::getAllDirNames(const std::string& absPath)
{
    std::vector<std::string> ret;
    ret.clear();
    auto allNames = getAllFileNames(absPath);
    const std::string separator = "/";
    for(auto &filename:allNames)
    {
        if(isDirectory(absPath + separator + filename))
            ret.push_back(filename);
    }
    return ret;
}

std::vector<std::string> FilePath::getAllZipFileNames(const std::string& absPath)
{
    auto files = getAllFileNames(absPath);
    std::vector<std::string> ret;
    for(const auto &file:files)
    {
        if(hasSuffix(file,".jar") || hasSuffix(file,".zip"))
            ret.emplace_back(file);
    }
    return ret;
}

bool FilePath::pathExists(const std::string& path)
{
    FILE* fp = fopen(path.c_str(),"r");
    return fp != nullptr;
}