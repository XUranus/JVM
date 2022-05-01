//
// Created by xuranus on 4/6/22.
//

#include "BytesReader.h"

#include "../common/Exception.h"
#include "../classpath/GZipPool.h"
#include <cstring>
//#include <zip.h>

namespace classfile {

    BytesReader::BytesReader(const std::string& _filepath) {
        buffer = nullptr;
        offset = 0;
        size = 0;
        filepath = _filepath;

        FILE *fp = fopen(filepath.c_str(),"rb+"); //read as binary
        if(fp == nullptr) { // not exist
            exception::panic(filepath + " not exists");
        }
        fseek(fp,0L,SEEK_END);
        long fileSize = ftell(fp);//get file size
        if(fileSize == 1L) {
            exception::panic(filepath + " get file size error");
        }
        size = fileSize;
        buffer = new u1[fileSize + 1]; // build buffer size equals to file size

        // read file to buffer
        rewind(fp);
        int readCount = 0;
        readCount = (int)fread(buffer, sizeof(unsigned char),fileSize + 1,fp);
        if(readCount != fileSize)
        {
            exception::panic(filepath + " read file size and buffer size mismatch");
        }
        fclose(fp);

        if(size < 0) {
            exception::panic("class file open failed: " + filepath);
        } else if(size == 0) {
            exception::panic(filepath + " file empty");
        }
    }

    BytesReader::BytesReader(u1* _buffer_, unsigned long _size_, std::string& _filepath) {
        buffer = new u1[_size_];
        size = _size_;
        offset = 0;
        filepath = _filepath;

        if(size <= 0) {
            exception::panic("invalid classfile: " + filepath);
        }
        else {
            // memcpy(buffer, src, _size);
            buffer = _buffer_;
        }
    }

    BytesReader::BytesReader(const BytesReader &reader) {
        size = reader.size;
        offset = reader.offset;
        filepath = reader.filepath;
        buffer = new u1[size];
        memcpy(buffer, reader.buffer, size);
    }

    u1 BytesReader::readU1()
    {
#ifdef DEBUG_MODE
        if(offset >= size) {
            exception::panic("BytesReader.readU1: class data read out of boundary");
        }
#endif
        u1 ret = buffer[offset];
        offset++;
        return ret;
    }

    u2 BytesReader::readU2()
    {
#ifdef DEBUG_MODE
        if(offset + 1 >= size) {
            exception::panic("BytesReader.readU2: class data read out of boundary");
        }
#endif
        u2 ret = ((u2) buffer[offset] << 8) + buffer[offset + 1];
        offset += 2;
        return ret;
    }

    u4 BytesReader::readU4()
    {
#ifdef DEBUG_MODE
        if(offset + 3 >= size) {
            exception::panic("BytesReader.readU4: class data read out of boundary");
        }
#endif
        u4 ret = ((u4) buffer[offset] << 24) + ((u4)buffer[offset + 1] << 16) + ((u4)buffer[offset + 2] << 8) + buffer[offset + 3];
        offset += 4;
        return ret;
    }

    void BytesReader::read(u1* dest, int n) {
        memcpy(dest, buffer + offset, n);
        offset += n;
    }

#ifdef DEBUG_MODE
    void BytesReader::dumpHex()
    {
        for(int i = 0; i < size; i++) {
            printf("%02x ",buffer[i]);
            if((i + 1) % 20 == 0) {
                printf("\n");
            }
        }
        printf("\n");
    }
#endif

    bool BytesReader::end() const {
        return size == offset;
    }

    std::string BytesReader::sourceFile() const {
        return filepath;
    }

};
