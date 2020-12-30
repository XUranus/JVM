//
// Created by xuranus on 2/6/19.
//

#include "Entry.h"
#include "../util/FilePath.h"
#include "../util/Console.h"
#include "../classfile/ClassReader.h"
#include <vector>
#include <zip.h>

Entry::~Entry() {}

//factory method
Entry* Entry::createEntry(std::string path)
{
    //printf("createEntry: %s\n",path.c_str());
    const std::string filelistSeparator = ";";
    if(path.find(filelistSeparator) != std::string::npos) //find filelist separator
        return createCompositeEntry(path);
    else if(FilePath::hasSuffix(path,"*"))
        return createWildcardEntry(path);
    else if(FilePath::hasSuffix(path,".zip") || FilePath::hasSuffix(path,".jar"))
        return createZipEntry(path);
    else
        return createDirEntry(path);
}

Entry* Entry::createCompositeEntry(std::string paths)
{
    //printf("createCompositeEntry: %s\n",paths.c_str());
    return new CompositeEntry(paths);
}

Entry* Entry::createDirEntry(std::string path)
{
    //printf("createDirEntry: %s\n",path.c_str());
    return new DirEntry(FilePath::absolutePath(path));
}

Entry* Entry::createWildcardEntry(std::string path)//transform to composite entry
{
    //printf("createWildCardEntry: %s\n",path.c_str());
    std::string absPath = FilePath::absolutePath(path.substr(0,path.length()-2)); //remove /*
    auto dirNames  = FilePath::getAllDirNames(absPath);
    std::string paths = "";
    dirNames.emplace_back("");//current dir
    for(const auto &dirName:dirNames)
        paths += FilePath::join(absPath,dirName)+";";
    //add jar and zip
    auto zipNames = FilePath::getAllZipFileNames(absPath);
    for(const auto &zipName:zipNames)
        paths += FilePath::join(absPath,zipName)+";";

    return createEntry(paths.substr(0,paths.length()-1));//remove ;
}

Entry* Entry::createZipEntry(std::string path)
{
    //printf("createZipEntry: %s\n",path.c_str());
    return new ZipEntry(FilePath::absolutePath(path));
}


DirEntry::DirEntry(const std::string& path)
{
    absPath = path;
}

std::string DirEntry::toString()
{
    return absPath;
}

int DirEntry::readClass(std::string classname, byte*& data)
{
    return ClassReader::readAllBytes(FilePath::join(absPath,classname), data);
}


CompositeEntry::CompositeEntry(const std::string& pathsStr)
{
    entries.clear();
    auto paths = FilePath::split(pathsStr,";");
    for(auto &path:paths)
    {
        entries.push_back(createEntry(path));
    }
}

std::string CompositeEntry::toString()
{
    std::string paths;
    for(auto entry:entries) {
        paths += entry->toString() + ";";
    }
    return paths;
}

int CompositeEntry::readClass(std::string classname, byte*& data)
{
    for(auto entry:entries)
    {
        int n_bytes = entry->readClass(classname,data);
        if(n_bytes >= 0)
            return n_bytes;
    }
    data = nullptr;
    return -1;
}

CompositeEntry::~CompositeEntry() {
    for(auto entry:entries) {
        delete entry;
    }
}

ZipEntry::ZipEntry(const std::string& _absFilePath)
{
    absFilePath = _absFilePath;
}

std::string ZipEntry::toString()
{
    return absFilePath;
}

int ZipEntry::readClass(std::string classname,byte*& data)
{
    //Console::printlnInfo("ZipEntry::readClass() "+classname);
    // absFilePath: /xxxx/xxxx/..../xxx.jar zip
    //libzip ,documentation: https://libzip.org/documentation/

    int err = 0;
    zip *z = zip_open(absFilePath.c_str(), 0, &err);
    //printf("%s",absFilePath.c_str());
    if(z == nullptr)
    {
        Console::printlnError("open zip file " + absFilePath + " failed");
        data = nullptr;
        return -1;
    }

    //Search for the file of given name
    const char *name = classname.c_str();
    struct zip_stat st;
    zip_stat_init(&st);
    zip_stat(z, name, 0, &st);

    //Alloc memory for its uncompressed contents
    data = new byte[st.size];

    //Read the compressed file
    zip_file *f = zip_fopen(z, name, 0);
    if(f == nullptr) {// target file not found
        delete[] data;
        data = nullptr;
        return -1;
    }

    zip_fread(f, data, st.size);
    zip_fclose(f);

    //And close the archive
    zip_close(z);

    return st.size;
}





