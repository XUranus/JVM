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

std::string FilePath::absolutePath(std::string path)
{
    char absPathBuf[PATH_MAX];
    if(!realpath(path.c_str(),absPathBuf))
    {
        printf("fetch absolute path failed.\n");
        exit(1);
    }
    return std::string(absPathBuf);
}

std::string FilePath::join(std::string path, std::string filename)
{
    removeSideBlank(path);
    removeSideBlank(filename);
    if(FilePath::hasSuffix(path,"/"))
        return path + filename;
    else if(!filename.empty())
        return path + "/" + filename;
    else
        return path;
}

bool FilePath::hasSuffix(std::string filepath, std::string suffix)
{
    removeSideBlank(filepath);
    std::string lower = FilePath::toLowerCase(suffix);
    std::string upper = FilePath::toUpperCase(suffix);
    //Console::printlnInfo("hasSuffix() ["+filepath+"] ["+suffix+"]");
    return ((filepath.rfind(lower)!=std::string::npos && (filepath.rfind(lower) + suffix.length() == filepath.length()))
    || (filepath.rfind(upper)!=std::string::npos && (filepath.rfind(upper) + suffix.length() == filepath.length())));
}


void FilePath::removeSideBlank(std::string &str)
{
    if(!str.empty())
    {
        str.erase(0,str.find_first_not_of(' '));
        str.erase(str.find_last_not_of(' ') + 1);
    }
}

std::string FilePath::toLowerCase(std::string str)
{
    int offset = 'A'-'a';
    for(auto &s:str){
        if(s >= 'A' && s <= 'Z'){
            s -= offset;
        }
    }
    return str;
}

std::string FilePath::toUpperCase(std::string str)
{
    int offset = 'A'-'a';
    for(auto &s:str){
        if(s >= 'a' && s <= 'z'){
            s += offset;
        }
    }
    return str;
}

std::vector<std::string> FilePath::split(std::string s,std::string c)
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

bool FilePath::isDirectory(std::string absPath)
{
    struct stat s;
    lstat(absPath.c_str(),&s);
    return S_ISDIR(s.st_mode);
}

std::vector<std::string> FilePath::getAllFileNames(std::string absPath)
{
    std::vector<std::string> ret;
    ret.clear();
    if(!isDirectory(absPath))
    {
        printf("%s is not a valid directory !\n",absPath.c_str());
        exit(1);
    }

    struct dirent* filename;
    DIR* dir;
    dir = opendir(absPath.c_str());
    if(dir== nullptr)
    {
        printf("could not open directory: %s.\n",absPath.c_str());
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

std::vector<std::string> FilePath::getAllDirNames(std::string absPath)
{
    std::vector<std::string> ret;
    ret.clear();
    auto allNames = getAllFileNames(absPath);
    for(auto filename:allNames)
    {
        if(isDirectory(absPath+"/"+filename))
            ret.push_back(filename);
    }
    return ret;
}

std::vector<std::string> FilePath::getAllZipFileNames(std::string absPath)
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

bool FilePath::pathExists(std::string path)
{
    FILE* fp = fopen(path.c_str(),"r");
    return fp != nullptr;
}