#include "BytesReader.h"
#include "../common/Exception.h"
#include <fstream>
#include <cstring>

namespace classfile {

    BytesReader::BytesReader(const std::string& _filepath)
        : offset(0), filepath(_filepath)
    {
        std::ifstream file(filepath, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            exception::panic("cannot open file: " + filepath);
        }
        auto fileSize = file.tellg();
        if (fileSize <= 0) {
            exception::panic(filepath + " file empty or unreadable");
        }
        file.seekg(0, std::ios::beg);
        buffer.resize(static_cast<size_t>(fileSize));
        file.read(reinterpret_cast<char*>(buffer.data()), fileSize);
        if (!file) {
            exception::panic(filepath + " read file error");
        }
    }

    BytesReader::BytesReader(const std::vector<u1>& data, const std::string& _filepath)
        : buffer(data), offset(0), filepath(_filepath)
    {
        if (buffer.empty()) {
            exception::panic("invalid classfile: " + filepath);
        }
    }

    BytesReader::BytesReader(std::vector<u1>&& data, const std::string& _filepath)
        : buffer(std::move(data)), offset(0), filepath(_filepath)
    {
        if (buffer.empty()) {
            exception::panic("invalid classfile: " + filepath);
        }
    }

    u1 BytesReader::readU1() {
#ifdef DEBUG_MODE
        if (offset >= static_cast<int>(buffer.size())) {
            exception::panic("BytesReader.readU1: class data read out of boundary");
        }
#endif
        return buffer[offset++];
    }

    u2 BytesReader::readU2() {
#ifdef DEBUG_MODE
        if (offset + 1 >= static_cast<int>(buffer.size())) {
            exception::panic("BytesReader.readU2: class data read out of boundary");
        }
#endif
        u2 ret = (static_cast<u2>(buffer[offset]) << 8) + buffer[offset + 1];
        offset += 2;
        return ret;
    }

    u4 BytesReader::readU4() {
#ifdef DEBUG_MODE
        if (offset + 3 >= static_cast<int>(buffer.size())) {
            exception::panic("BytesReader.readU4: class data read out of boundary");
        }
#endif
        u4 ret = (static_cast<u4>(buffer[offset]) << 24)
               + (static_cast<u4>(buffer[offset + 1]) << 16)
               + (static_cast<u4>(buffer[offset + 2]) << 8)
               + buffer[offset + 3];
        offset += 4;
        return ret;
    }

    void BytesReader::read(u1* dest, int n) {
        std::memcpy(dest, buffer.data() + offset, n);
        offset += n;
    }

#ifdef DEBUG_MODE
    void BytesReader::dumpHex() {
        for (size_t i = 0; i < buffer.size(); i++) {
            printf("%02x ", buffer[i]);
            if ((i + 1) % 20 == 0) {
                printf("\n");
            }
        }
        printf("\n");
    }
#endif

    bool BytesReader::end() const {
        return offset == static_cast<int>(buffer.size());
    }

    std::string BytesReader::sourceFile() const {
        return filepath;
    }

}
