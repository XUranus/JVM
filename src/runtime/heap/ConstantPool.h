//
// Created by xuranus on 2/11/19.
//

#ifndef JVM_CONSTANTPOOL_H
#define JVM_CONSTANTPOOL_H

#include <string>

struct Class;
struct SymRef;
struct ClassFile;



struct Constant{
    struct Value { //TODO::union may be better
        std::string stringValue;
        int intValue;
        long longValue;
        float floatValue;
        double doubleValue;
        void* ref;

        Value();
        ~Value();
    } value;

    enum ValueType {
        INT = 0,
        LONG = 1,
        FLOAT = 2,
        DOUBLE = 3,
        STRING = 4,
        REF = 5
    } type;

    Constant();
    ~Constant();
    void setInt(int v);
    void setLong(long v);
    void setFloat(float v);
    void setDouble(double v);
    void setRef(void* _ref);
    void setString(std::string str);

    int getInt();
    long getLong();
    float getFloat();
    double getDouble();
    void* getRef();
    std::string getString();

    std::string toString();
};


struct ConstantPool {
    Class* _class;
    Constant* constants;
    int size;

    ConstantPool(Class* classRef,ClassFile* classFile);
    ~ConstantPool();

    void setInt(int index,int v);
    void setLong(int index,long v);
    void setFloat(int index,float v);
    void setDouble(int index,double v);
    void setRef(int index,void* _ref);
    void setString(int index,std::string str);

    int getInt(int index);
    long getLong(int index);
    float getFloat(int index);
    double getDouble(int index);
    void* getRef(int index);
    std::string getString(int index);

    int getType(int index);
    void debug();
};

#endif //JVM_CONSTANTPOOL_H
