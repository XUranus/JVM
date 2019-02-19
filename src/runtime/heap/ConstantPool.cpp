//
// Created by xuranus on 2/11/19.
//

#include "ConstantPool.h"
#include "../../classfile/ClassFile.h"
#include "SymRef.h"

/****************************************  constants methods  ******************************************/

Constant::Value::Value() {
    ref = nullptr;
}

Constant::Value::~Value() {}

Constant::Constant():value()
{
    type = REF;
}

Constant::~Constant() {}

void Constant::setInt(int v)
{
    type = INT;
    value.intValue = v;
}

void Constant::setLong(long v)
{
    type = LONG;
    value.longValue = v;
}

void Constant::setFloat(float v)
{
    type = FLOAT;
    value.floatValue = v;
}

void Constant::setDouble(double v)
{
    type = DOUBLE;
    value.doubleValue = v;
}

void Constant::setRef(void* _ref)
{
    type = REF;
    value.ref = _ref;
}

void Constant::setString(std::string str)
{
    type = STRING;
    value.stringValue = str;
}

int Constant::getInt()
{
    return value.intValue;
}

long Constant::getLong()
{
    return value.longValue;
}


float Constant::getFloat()
{
    return value.floatValue;
}

double Constant::getDouble()
{
    return value.doubleValue;
}

void* Constant::getRef() {
    return value.ref;
}

std::string Constant::getString()
{
    return value.stringValue;
}

std::string Constant::toString()
{
    std::string v = "";
    std::string t = "";
    switch (type)
    {
        case 0: t = "int"; v = std::to_string(getInt());break;
        case 1: t = "long"; v = std::to_string(getLong()); break;
        case 2: t = "float"; v = std::to_string(getFloat()); break;
        case 3: t = "double"; v = std::to_string(getDouble()); break;
        case 4: t = "string"; v = getString(); break;
        case 5: t = "ref";v = std::to_string((long)getRef());break;
    }
    return "<"+t+","+v+">";
}

/****************************************  constant pool methods  ******************************************/

ConstantPool::ConstantPool(Class *classRef, ClassFile *classFile)
{
    _class = classRef;
    size = classFile->constantPoolCount;
    constants = new Constant[size];
    for(int i=1;i<size;i++)
    {
        auto classFileCpInfo = classFile->constantPool[i];
        //printf("i=%u tag=%u\n",i,classFileCpInfo->tag);
        switch (classFileCpInfo->tag)
        {
            case CONSTANT_Integer_tag:{
                setInt(i,((CONSTANT_Integer*)classFileCpInfo)->getIntValue());
                break;
            }
            case CONSTANT_Long_tag:{
                setLong(i,((CONSTANT_Long*)classFileCpInfo)->getLongValue());
                i++;
                break;
            }
            case CONSTANT_Float_tag:{
                setFloat(i,((CONSTANT_Float*)classFileCpInfo)->getFloatValue());
                break;
            }
            case CONSTANT_Double_tag:{
                setDouble(i,((CONSTANT_Double*)classFileCpInfo)->getDoubleValue());
                i++;
                break;
            }
            case CONSTANT_String_tag:{
                setString(i,((CONSTANT_String*)classFileCpInfo)->getStringValue());
                break;
            }
            case CONSTANT_Utf8_tag:{
                setString(i,((CONSTANT_Utf8*)classFileCpInfo)->getUtf8());
                break;
            }
            case CONSTANT_Class_tag:{
                setRef(i,new ClassRef(this,(CONSTANT_Class*)classFileCpInfo));
                break;
            }
            case CONSTANT_Fieldref_tag:{
                setRef(i,new FieldRef(this,(CONSTANT_Fieldref*)classFileCpInfo));
                break;
            }
            case CONSTANT_Methodref_tag:{
                setRef(i,new MethodRef(this,(CONSTANT_Methodref*)classFileCpInfo));
                break;
            }
            case CONSTANT_InterfaceMethodref_tag:{
                setRef(i,new InterfaceMemberRef(this,(CONSTANT_InterfaceMethodref*)classFileCpInfo));
                break;
            }
            default:{
                //ConstantInvokeDynamic
                //ConstantMethodhanle
                //ConstantMethodType
                //printf("Warning: classfile constant pool to heap constant pool convert failed.unsupport constant: %s\n",classFileCpInfo->getCpInfoName().c_str());
               // exit(1);
            }
        }
    }
}

ConstantPool::~ConstantPool()
{
    delete[] constants;
}


int ConstantPool::getInt(int index)
{
    return constants[index].getInt();
}

long ConstantPool::getLong(int index)
{
    return constants[index].getLong();
}

float ConstantPool::getFloat(int index)
{
    return constants[index].getFloat();
}

double ConstantPool::getDouble(int index)
{
    return constants[index].getDouble();
}


void * ConstantPool::getRef(int index)
{
    return constants[index].getRef();
}

std::string ConstantPool::getString(int index)
{
    return constants[index].getString();
}

void ConstantPool::setInt(int index, int v)
{
    constants[index].setInt(v);
}

void ConstantPool::setLong(int index, long v)
{
    constants[index].setLong(v);
}

void ConstantPool::setFloat(int index, float v)
{
    constants[index].setFloat(v);
}

void ConstantPool::setDouble(int index, double v)
{
    constants[index].setDouble(v);
}

void ConstantPool::setRef(int index, void *_ref)
{
    constants[index].setRef(_ref);
}

void ConstantPool::setString(int index, std::string str)
{
    constants[index].setString(str);
}

int ConstantPool::getType(int index)
{
    return constants[index].type;
}

void ConstantPool::debug()
{
    printf("[Debug ConstanPool] ");
    for(auto i=1;i<size;i++)
        printf("[%d]%s ",i,constants[i].toString().c_str());
    printf("\n");
}