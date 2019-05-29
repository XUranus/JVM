//
// Created by xuranus on 2/6/19.
//

#include "Entry.h"
#include "../util/FilePath.h"
#include "../util/Console.h"
#include "../classfile/ClassReader.h"
#include <vector>
#include <zip.h>



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

Entry* Entry::createWildcardEntry(std::string path)
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



DirEntry::DirEntry(std::string path)
{
    absPath = path;
}

std::string DirEntry::toString()
{
    return absPath;
}

std::pair<byte*,int> DirEntry::readClass(std::string classname)
{
    return ClassReader::readAllBytes(FilePath::join(absPath,classname));
}


CompositeEntry::CompositeEntry(std::string pathsStr)
{
    entries.clear();
    auto paths = FilePath::split(pathsStr,";");
    for(auto path:paths)
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

std::pair<byte*,int> CompositeEntry::readClass(std::string classname)
{
    byte* res;
    for(auto entry:entries)
    {
        auto ret = entry->readClass(classname);
        if(ret.first!= nullptr)
            return ret;
    }
    return std::make_pair(nullptr,0);
}



ZipEntry::ZipEntry(std::string _absFilePath)
{
    absFilePath = _absFilePath;
}

std::string ZipEntry::toString()
{
    return absFilePath;
}

std::pair<byte*,int> ZipEntry::readClass(std::string classname)
{
    //Console::printlnInfo("ZipEntry::readClass() "+classname);
    // absFilePath: /xxxx/xxxx/..../xxx.jar zip
    //libzip ,documentation: https://libzip.org/documentation/

    int err = 0;
    zip *z = zip_open(absFilePath.c_str(), 0, &err);
    if(z == nullptr)
    {
        Console::printlnError("open zip file failed");
        return std::make_pair(nullptr,-1);
    }

    //Search for the file of given name
    const char *name = classname.c_str();
    struct zip_stat st;
    zip_stat_init(&st);
    zip_stat(z, name, 0, &st);

    //Alloc memory for its uncompressed contents
    byte *contents = new byte[st.size];

    //Read the compressed file
    zip_file *f = zip_fopen(z, name, 0);
    if(f== nullptr)// target  file not found
        return std::make_pair(nullptr,0);

    zip_fread(f, contents, st.size);
    zip_fclose(f);

    //And close the archive
    zip_close(z);

    return std::make_pair(contents,st.size);
}





