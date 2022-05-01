//
// Created by xuranus on 2/6/19.
//

#include "ClassPath.h"
#include "../common/FilePath.h"
#include "../common/Console.h"
#include "../common/Exception.h"

namespace classpath {

    ClassPath::ClassPath(const std::string &xBootClassPath, const std::string &cpOption) {
        bootstrapClassPathEntry = std::unique_ptr<Entry>(Entry::createEntry(FilePath::join(getJrePath(xBootClassPath), "lib/*")));
        extendClassPathEntry = std::unique_ptr<Entry>(Entry::createEntry(FilePath::join(getJrePath(xBootClassPath), "lib/ext/*")));
        userClassPathEntry = std::unique_ptr<Entry>(Entry::createEntry(getUserPath(cpOption)));
    }

    std::string ClassPath::getUserPath(const std::string &cpOption) {
        if (cpOption.empty()) {
            return FilePath::absolutePath(".");
        } else {
            // cpOption do not need to be a path, it may contain several path:
            // ./libs/classes;/home/java/classes/*
            return cpOption;
        }
    }

    std::string ClassPath::getJrePath(const std::string &xBootClassPath) {
        auto env = getenv("JAVA_HOME");

            // 1. user specified jre option
        if (!xBootClassPath.empty() && FilePath::exists(FilePath::absolutePath(xBootClassPath))) {
            return FilePath::absolutePath(xBootClassPath);

            // 2. $workingDir/jre
#if defined(__linux__) || defined(__unix__)
        } else if (FilePath::exists(FilePath::absolutePath("./jre"))) {
            return FilePath::absolutePath("./jre");
#endif
#ifdef _MSC_VER
        } else if(FilePath::exists(FilePath::absolutePath(".\\jre"))) {
            return FilePath::absolutePath(".\\jre");
#endif

            // 3. $JAVA_HOME/jre
        } else if (env != nullptr) {
            return FilePath::join(std::string(env), "jre");
        } else {
            exception::fatal("Can not find jre path");
        }
        return "";
    }



    void ClassPath::dumpStatus() const {
        std::cout << "[classpath]" << std::endl;
        std::cout << "bootstrap path: " << bootstrapClassPathEntry->entryString() << std::endl;
        std::cout << "extend path: " << extendClassPathEntry->entryString() << std::endl;
        std::cout << "user path: " << userClassPathEntry->entryString() << std::endl;
    }


    std::optional<classfile::BytesReader> ClassPath::readClass(const std::string& classname) const {
        std::string _classname = classname;
        //replace . with /
        //example: java.lang.Exception java/lang/Exception
        for (char &ch: _classname) {
            if (ch == '.') {
                ch = FilePath::separator[0];
            }
        }
        // classname won't take ".class" suffix! ->java/lang/Exception.class
        if (!FilePath::endsWith(_classname, ".class")) {
            _classname = _classname + ".class";
        }

        auto reader = bootstrapClassPathEntry->readClass(_classname);
        if (reader) {
            return reader;
        }

        reader = extendClassPathEntry->readClass(_classname);
        if (reader) {
            return reader;
        }

        reader = userClassPathEntry->readClass(_classname);
        if (reader) {
            return reader;
        }

        return std::nullopt;
    }

}