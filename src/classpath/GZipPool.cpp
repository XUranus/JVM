#include "GZipPool.h"

namespace classfile {

    std::map<std::string, zip*> GZipPool::fdCache;

    std::optional<std::vector<u1>>
    GZipPool::readGzip(const std::string& gzipName, const std::string& path) {
        zip* z = nullptr;

        auto it = fdCache.find(gzipName);
        if (it != fdCache.end()) {
            z = it->second;
        } else {
            int err = 0;
            z = zip_open(gzipName.c_str(), ZIP_RDONLY, &err);
            if (z == nullptr) {
                return std::nullopt;
            }
            fdCache[gzipName] = z;
        }

        // Search for the file of given name
        struct zip_stat st{};
        zip_stat_init(&st);
        zip_stat(z, path.c_str(), 0, &st);

        // read the compressed file
        zip_file* f = zip_fopen(z, path.c_str(), 0);
        if (f == nullptr) {
            return std::nullopt;
        }

        std::vector<u1> buffer(st.size);
        zip_fread(f, buffer.data(), st.size);
        zip_fclose(f);

        return buffer;
    }

    void GZipPool::closeAll() {
        for (auto& [name, z] : fdCache) {
            if (z != nullptr) {
                zip_close(z);
            }
        }
        fdCache.clear();
    }
}
