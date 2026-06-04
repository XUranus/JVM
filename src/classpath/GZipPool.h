#pragma once

#include <map>
#include <zip.h>
#include <string>
#include <optional>
#include <vector>
#include "../basicType.h"

namespace classfile {
    class GZipPool {
        static std::map<std::string, zip*> fdCache;
    public:
        static std::optional<std::vector<u1>> readGzip(const std::string& gzipName, const std::string& path);
        static void closeAll();
    };
}
