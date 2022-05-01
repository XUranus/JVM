//
// Created by xuranus on 4/6/22.
//

#ifndef JVM_CLASSFILE_BYTES_READER_H
#define JVM_CLASSFILE_BYTES_READER_H

#include <string>
#include "../basicType.h"

namespace classfile {

    class BytesReader {
    private:
        u1* buffer;
        unsigned long size; // n bytes
        int offset; // number of bytes read
        std::string filepath;

    public:
        explicit BytesReader(const std::string &_filepath);
        BytesReader(u1* _buffer_, unsigned long _size_, std::string& filepath);
        BytesReader(const BytesReader& reader);

        u1 readU1();
        u2 readU2();
        u4 readU4();
        void read(u1* data, int n);
        [[nodiscard]] bool end() const;
        [[nodiscard]] std::string sourceFile() const;

    #ifdef DEBUG_MODE
        void dumpHex();
    #endif
    };

}

#endif //JVM_CLASSFILE_BYTES_READER_H
