//
// Created by xuranus on 4/25/22.
//

#ifndef JVM_ZIPFILEDESCRIPTORPOOL_H
#define JVM_ZIPFILEDESCRIPTORPOOL_H

#include <map>
#include <zip.h>
#include <string>
#include <optional>

namespace classfile {
    class GZipPool {
        static std::map<std::string, zip*> fdCache;
    public:
        static std::optional<std::pair<unsigned long, unsigned char*>>  readGzip(const std::string& gzipName, const std::string& path);
    };

}

#endif //JVM_ZIPFILEDESCRIPTORPOOL_H
