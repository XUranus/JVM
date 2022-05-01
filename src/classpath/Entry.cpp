//
// Created by xuranus on 2/6/19.
//

#include "Entry.h"
#include "../common/FilePath.h"
#include "../common/Exception.h"
#include <vector>
//#include <zip.h>
#include "GZipPool.h"

namespace classpath {

#if defined(__linux__) || defined(__unix__)
    std::string CompositeEntry::separator = ";";
#else
    std::string CompositeEntry::separator = ";";
#endif

    std::unique_ptr<Entry> Entry::createEntry(const std::string &str) {
        if (str.find(CompositeEntry::separator) != std::string::npos) {
            return std::unique_ptr<Entry>(new CompositeEntry(str));
        } else if (FilePath::endsWith(str, "*")) {
            return createWildcardEntry(str);
        } else if (FilePath::endsWith(FilePath::lowerCase(str), ".zip")
                || FilePath::endsWith(FilePath::lowerCase(str), ".jar")) {
            return std::unique_ptr<Entry>(new ZipEntry(str));
        } else {
            return std::unique_ptr<Entry>(new DirEntry(str));
        }
    }


    std::unique_ptr<Entry> Entry::createWildcardEntry(const std::string &wildcardPath) {
        std::string absPath = FilePath::absolutePath(wildcardPath.substr(0, wildcardPath.length() - 2)); //remove /* or \*
        auto dirNames = FilePath::listDir(absPath);
        std::string paths;
        dirNames.emplace_back("");//current dir
        for (const auto &dirName: dirNames) {
            paths += FilePath::join(absPath, dirName) + ";";
        }
        // add jar and zip
        auto zipNames = FilePath::listZip(absPath);
        for (const auto &zipName: zipNames) {
            paths += FilePath::join(absPath, zipName) + ";";
        }

        return createEntry(paths.substr(0, paths.length() - 1));//remove ;
    }


}

namespace classpath {

    DirEntry::DirEntry(const std::string &_dirPath) {
        dirPath = FilePath::absolutePath(_dirPath);
    }

    std::string DirEntry::entryString() {
        return dirPath;
    }

    std::optional<classfile::BytesReader> DirEntry::readClass(const std::string &path) {
        if(FilePath::exists(FilePath::join(dirPath, path))) {
            return classfile::BytesReader(FilePath::join(dirPath, path));
        } else {
            return std::nullopt;
        }
    }


    CompositeEntry::CompositeEntry(const std::string& pathsStr) {
        entries.clear();
        auto paths = FilePath::split(pathsStr, ";");
        for (auto &path: paths) {
            entries.push_back(createEntry(path));
        }
    }

    std::string CompositeEntry::entryString() {
        std::string paths;
        for (auto &entry: entries) {
            paths += entry->entryString() + CompositeEntry::separator;
        }
        return paths;
    }

    std::optional<classfile::BytesReader> CompositeEntry::readClass(const std::string &path) {
        for (auto &entry: entries) {
            auto reader = entry->readClass(path);
            if (reader) {
                // return first valid reader
                return reader;
            }
        }
        return std::nullopt;
    }


    ZipEntry::ZipEntry(const std::string &_zipPath) {
        zipPath = FilePath::absolutePath(_zipPath);
    }

    std::string ZipEntry::entryString() {
        return zipPath;
    }

    //libZip ,documentation: https://libzip.org/documentation
    std::optional<classfile::BytesReader> ZipEntry::readClass(const std::string &path) {
        auto res = classfile::GZipPool::readGzip(zipPath, path);
        if(res) {
            return classfile::BytesReader(res->second, res->first, zipPath);
        } else {
            return std::nullopt;
        }
    }

}

