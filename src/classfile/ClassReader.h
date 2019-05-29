//
// Created by XUranus on 2019/1/31.
//

#ifndef JVM_CLASSREADER_H
#define JVM_CLASSREADER_H

#include "ClassFile.h"
#include <string>
#include <cstdio>

struct ClassReader {
    long data_size;//n bytes
    long offset; //bytes numbers has read,default 0
    u1 *data;

    ClassReader(const std::string filename);
    ClassReader(byte* d,long size);
    ~ClassReader();
    u1 readU1();
    u2 readU2();
    u4 readU4();
    u1* readBytes(int n);
    FieldInfo* readFieldInfo(CpInfo** constantPool);
    MethodInfo* readMethodInfo(CpInfo** constantPool);
    AttributeInfo* readAttributeInfo(CpInfo** constantPool);


    static std::pair<byte*,int> readAllBytes(std::string filename);
    void printAllHexBytes(); //print all hex bytes to debug
    ClassFile* parseClassFile();

};


#endif //JVM_CLASSREADER_H
