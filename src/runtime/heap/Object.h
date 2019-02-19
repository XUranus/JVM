//
// Created by xuranus on 2/7/19.
//

#ifndef JVM_OBJECT_H
#define JVM_OBJECT_H

#include "Class.h"
#include <vector>


struct Object {
    //all java Objects,the root
    Class* _class;
    void* data;
    unsigned int dataCount;
    enum DataType {
        INT8,INT16,INT32,INT64,UINT16,FLOAT32,FLOAT64,REF,SLOTS
    } dataType;

    explicit Object(Class* c);
    Object(Class* c, unsigned int count);//for array init
    Object(Class* c,void* _data,unsigned long _dataCount,DataType type);
    ~Object();
    Slots* getFields();
    Object* getRefVar(std::string name,std::string descriptor);
    void setRefVar(std::string name,std::string descriptor,Object* ref);
    bool isInstanceOf(Class* c);

    //to arrary type ref
    int8* bytes();
    int16* shorts();
    int32* ints();
    long* longs();//int64
    uint16* chars();
    float* floats();//float32
    double* doubles();//float64
    Object** refs();

    int arrayLength();
};


#endif //JVM_OBJECT_H
