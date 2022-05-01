//
// Created by xuranus on 2/6/19.
//

#include "FilePath.h"

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <dirent.h>
#include <sys/stat.h>
#include "Exception.h"

//TODO::test in win platform

#if defined(__linux__) || defined(__unix__)
#include <unistd.h>
std::string FilePath::separator = "/";
#else
std::string FilePath::separator = "\\";
#endif

std::string FilePath::absolutePath(const std::string& path) {
#if defined(__linux__) || defined(__unix__)
    if(exists(path)) {
        char absPathBuffer[PATH_MAX];
        if(!realpath(path.c_str(),absPathBuffer)) {
            exception::panic("fetch absolute path failed: " + path);
        }
        return absPathBuffer;
    } else {
        if(path.empty()) {
            return absolutePath(".");
        } else if(startsWith(path, separator)) {
            return path;
        } else if(startsWith(path, ".")) {
            return join(absolutePath("."), path.substr(1));
        } else {
            return join(absolutePath("."), path);
        }
    }
#else

#endif
}

std::string FilePath::join(const std::string& _path, const std::string& _filename) {
    std::string path = trim(_path);
    std::string filename = trim(_filename);
    if(endsWith(path,separator)) {
        path = path.substr(0, path.length() - 1);
    }
    if(startsWith(filename, separator)) {
        filename = filename.substr(1);
    }
    return path + separator + filename;
}

bool FilePath::endsWith(const std::string &str, const std::string suffix) {
    return str.rfind(suffix) != std::string::npos &&
            str.rfind(suffix) + suffix.length() == str.length();
}

bool FilePath::startsWith(const std::string &str, std::string prefix) {
    return str.find(prefix) == 0;
}

std::string FilePath::cwd() {
#if defined(__linux__) || defined(__unix__)
    char cwdBuffer[PATH_MAX];
    getcwd(cwdBuffer, sizeof(cwdBuffer));
    return cwdBuffer;
#endif
}

std::string FilePath::trim(const std::string &str) {
    std::string res = str;
    if(!res.empty()) {
        res.erase(0,res.find_first_not_of(' '));
        res.erase(res.find_last_not_of(' ') + 1);
    }
    return res;
}

std::string FilePath::lowerCase(const std::string& str) {
    std::string res = str;
    for(char &ch: res){
        if(ch >= 'A' && ch <= 'Z'){
            ch = ch - 'A' + 'a';
        }
    }
    return res;
}

std::string FilePath::upperCase(const std::string& str) {
    std::string res = str;
    for(char &ch: res){
        if(ch >= 'a' && ch <= 'z'){
            ch = ch - 'a' + 'A';
        }
    }
    return res;
}

std::vector<std::string> FilePath::split(const std::string& s,const std::string& c) {
    std::vector<std::string> v;
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2) {
        v.push_back(s.substr(pos1, pos2 - pos1));
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length()) {
        v.push_back(s.substr(pos1));
    }
    return v;
}

bool FilePath::isDir(const std::string& path) {
#if defined(__linux__) || defined(__unix__)
    struct stat s{};
    lstat(absolutePath(path).c_str(),&s);
    return S_ISDIR(s.st_mode);
#endif
}

std::vector<std::string> FilePath::list(const std::string& path) {
    std::vector<std::string> ret;
    if(!isDir(absolutePath(path))) {
        //TODO::
        //exception::panic(absolutePath(path) + " is not a valid directory !");
        return ret;
    }

#if defined(__linux__) || defined(__unix__)
    struct dirent* filename;
    DIR* dir;
    dir = opendir(absolutePath(path).c_str());
    if(dir== nullptr) {
        exception::panic("could not open directory: " + absolutePath(path));
    }
    while((filename = readdir(dir) )!= nullptr) {
        if(strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0) {
            // skip . and ..
            continue;
        } else {
            ret.emplace_back(std::string(filename->d_name));
        }
    }
    return ret;
#endif
}

std::vector<std::string> FilePath::listDir(const std::string& path) {
    std::vector<std::string> res;
    auto files = list(absolutePath(path));
    for(auto &filename: files) {
        if(isDir(join(absolutePath(path), filename))) {
            res.push_back(filename);
        }
    }
    return res;
}

std::vector<std::string> FilePath::listZip(const std::string& path) {
    auto files = list(absolutePath(path));
    std::vector<std::string> res;
    for(const auto &file:files) {
        if(endsWith(lowerCase(file),".jar") || endsWith(lowerCase(file),".zip")) {
            res.emplace_back(file);
        }
    }
    return res;
}

bool FilePath::exists(const std::string& path) {
#if defined(__linux__) || defined(__unix__)
    FILE* fp = fopen(path.c_str(),"r");
    return fp != nullptr;
#endif
}