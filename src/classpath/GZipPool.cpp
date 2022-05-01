//
// Created by xuranus on 4/25/22.
//

#include "GZipPool.h"

namespace classfile {

    std::map<std::string, zip*> GZipPool::fdCache;

    std::optional<std::pair<unsigned long, unsigned char *>>
    GZipPool::readGzip(const std::string &gzipName, const std::string &path) {
        zip *z = nullptr;

        if(GZipPool::fdCache.find(gzipName) != GZipPool::fdCache.end()) {
            z = GZipPool::fdCache[gzipName];
        } else {
            int err = 0;
            z = zip_open(gzipName.c_str(), ZIP_RDONLY, &err);
            if(z == nullptr) {
                return std::nullopt;
            } else {
                GZipPool::fdCache[gzipName] = z;
            }
        }

        //Search for the file of given name
        struct zip_stat st{};
        zip_stat_init(&st);
        zip_stat(z, path.c_str(), 0, &st);

        // alloc memory for its uncompressed contents
        auto *buffer = new unsigned char[st.size];

        // read the compressed file
        zip_file *f = zip_fopen(z, path.c_str(), 0);
        if(f == nullptr) {
            return std::nullopt;
        }
        zip_fread(f, buffer, st.size);

        zip_fclose(f); // close the sub file
        // zip_close(z); // close the archive

        return std::make_pair(st.size, buffer);
    }
}