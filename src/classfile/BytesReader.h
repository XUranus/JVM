#pragma once

#include <string>
#include <vector>
#include "../basicType.h"

namespace classfile {

    class BytesReader {
    private:
        std::vector<u1> buffer;
        int offset = 0;
        std::string filepath;

    public:
        explicit BytesReader(const std::string& _filepath);
        BytesReader(const std::vector<u1>& data, const std::string& filepath);
        BytesReader(std::vector<u1>&& data, const std::string& filepath);

        u1 readU1();
        u2 readU2();
        u4 readU4();
        void read(u1* dest, int n);
        [[nodiscard]] bool end() const;
        [[nodiscard]] std::string sourceFile() const;

    #ifdef DEBUG_MODE
        void dumpHex();
    #endif
    };

}
