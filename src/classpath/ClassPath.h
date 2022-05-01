//
// Created by xuranus on 2/6/19.
//

#ifndef JVM_CLASSPATH_H
#define JVM_CLASSPATH_H


#include "Entry.h"
#include "../classfile/BytesReader.h"
#include <optional>

namespace classpath {

    class ClassPath {
    private:
        std::unique_ptr<Entry> bootstrapClassPathEntry;
        std::unique_ptr<Entry> extendClassPathEntry;
        std::unique_ptr<Entry> userClassPathEntry;

        [[nodiscard]] static std::string getUserPath(const std::string &cpOption) ;
        [[nodiscard]] static std::string getJrePath(const std::string &xBootClassPath) ;

    public:
        ClassPath(const std::string &xBootClassPath, const std::string &cpOption);
        [[nodiscard]] std::optional<classfile::BytesReader> readClass(const std::string& classname) const; //classname example : java/lang/Object ,not contain ".class" suffix
        void dumpStatus() const;
    };

}


#endif //JVM_CLASSPATH_H
