//
// Created by xuranus on 2/6/19.
//

#ifndef JVM_CLASSPATH_ENTRY_H
#define JVM_CLASSPATH_ENTRY_H

#include "../basicType.h"
#include "../classfile/BytesReader.h"
#include <iostream>
#include <vector>
#include <optional>
#include <memory>

/**
 * std::pair<byte[],int> readClass(),
 * return byte array and length of byte,
 * if byte == 0 and len == 0 means no file found,
 * if bytes not null means file found,
 * if len < 0 means error occurs.
 *
 * */

namespace classpath {

    class Entry {
    private:
        static std::unique_ptr<Entry> createWildcardEntry(const std::string& wildcardPath);

    public:
        static std::unique_ptr<Entry> createEntry(const std::string& str);
        virtual std::optional<classfile::BytesReader> readClass(const std::string& path) = 0;
        virtual std::string entryString() = 0;
        virtual ~Entry() = default;
    };

    class DirEntry : public Entry { //read a common dir
    private:
        std::string dirPath; //absolute dir path

    public:
        explicit DirEntry(const std::string& _dirPath);
        std::optional<classfile::BytesReader> readClass(const std::string& path) override;
        std::string entryString() override;
    };

    struct ZipEntry : public Entry { // read a *.zip ,*.jar file
    private:
        std::string zipPath;

    public:
        explicit ZipEntry(const std::string& _zipPath);
        std::optional<classfile::BytesReader> readClass(const std::string& path) override;
        std::string entryString() override;
    };

    class CompositeEntry : public Entry { //read multiple directory/file separate by ";" or ":", contains wildcard(*)
    private:
        std::vector<std::unique_ptr<Entry>> entries;
    public:
        static std::string separator;

    public:
        explicit CompositeEntry(const std::string& paths);
        std::optional<classfile::BytesReader> readClass(const std::string& path) override;
        std::string entryString() override;
    };

}
#endif //JVM_CLASSPATH_ENTRY_H
