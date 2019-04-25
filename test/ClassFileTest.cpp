//
// Created by xuranus on 4/25/19.
//

#ifndef JVM_TEST1_H
#define JVM_TEST1_H


#include <cstdio>
#include "../src/classfile/ClassFile.h"
#include "../src/classfile/ClassReader.h"

using namespace std;

class ClassFileTest{
public:

    static void testReadBytes()
    {
        ClassReader reader("/home/xuranus/CLionProjects/JVM/test/classFileTest/Sum.class");
        reader.printAllHexBytes();
        u1 v1 = reader.readU1();
        u2 v2 = reader.readU2();
        u4 v3 = reader.readU4();
        u4 v4 = reader.readU4();
        printf("v1 = %02x\n",v1);
        printf("v2 = %02x\n",v2);
        printf("v3 = %02lx\n",v3);
        printf("v4 = %02lx\n",v4);
    }

    static void testReadClass()
    {
        printf("start testing read class..\n");
        ClassReader reader("/home/xuranus/CLionProjects/JVM/test/classFileTest/Sum.class");
        reader.parseClassFile()->debug();
    }

    static void excute()
    {
        testReadBytes();
        testReadClass();
    }

};

#endif
