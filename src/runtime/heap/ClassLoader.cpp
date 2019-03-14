//
// Created by xuranus on 2/11/19.
//

#include "ClassLoader.h"
#include "../../classfile/ClassReader.h"
#include "../../util/Console.h"
#include "Object.h"
#include "StringPool.h"

ClassLoader::ClassLoader(ClassPath *cp, bool _verboseClass)
{
    verboseClass = _verboseClass;
    classPath = cp;
    classMap.clear();
}

Class* ClassLoader::loadClass(std::string className)
{
    if(classMap[className]!= nullptr)
        return classMap[className];
    else {
        if(verboseClass)
            Console::printlnBlue("[ClassLoader]: loading:" + className);
        if (className[0] == '[')
            return loadArrayClass(className);
        else
            return loadNonArrayClass(className);
    }
}

Class* ClassLoader::loadNonArrayClass(std::string className)
{
    //use classMap to store reference
    auto ret = readClass(className);
    auto _class = defineClass(ret.first,ret.second);
    link(_class);
    if(verboseClass)
        Console::printlnBlue("[ClassLoader]: loaded: "+className);//+" addr:"+std::to_string((long)_class));
    return _class;
}

Class* ClassLoader::loadArrayClass(std::string className)
{
    auto _class = new Class(className);
    _class->classloader = this;
    _class->superClass = loadClass("java/lang/Object");
    resolveSuperClass(_class);
    resolveInterfaces(_class);
    classMap[className] = _class;
    if(verboseClass)
        Console::printlnBlue("[ClassLoader]: loaded: "+className);//+" addr:"+std::to_string((long)_class));
    return _class;
}

Class* ClassLoader::getPrimitiveArrayClass(u1 atype)
{
    switch (atype)
    {
        case AT_BOOLEAN: return loadClass("[Z");
        case AT_BYTE: return loadClass("[B");
        case AT_CHAR: return loadClass("[C");
        case AT_SHORT: return loadClass("[S");
        case AT_INT: return loadClass("[I");
        case AT_LONG: return loadClass("[J");
        case AT_FLOAT: return loadClass("[F");
        case AT_DOUBLE: return loadClass("[D");
        default:{
            Console::printlnError("invalid atype:"+std::to_string(atype));
            exit(1);
        }
    }
}

Object* ClassLoader::createArgsArrayObject(std::vector<std::string>& args)
{
    auto stringClass = loadClass("java/lang/String");
    auto argsArr = stringClass->arrayClass()->newArrayObject((unsigned int)args.size());
    auto jArgs = argsArr->refs();
    for(auto i=0;i<args.size();i++)
    {
        jArgs[i] = StringPool::getStringPool()->getJString(this, args[i]);
    }
    return argsArr;
}

std::pair<byte*,long> ClassLoader::readClass(std::string classname)
{
    //printf("readClass(%s)\n",classname.c_str());
    auto ret = classPath->readClass(classname);
    if(ret.first == nullptr)
    {
        Console::printlnException("java.lang.ClassNotFoundException: " + classname);
        exit(1);
    }
    return ret;
}

Class* ClassLoader::defineClass(byte *data, long length)
{
    ClassReader reader(data,length);
    auto classFile = reader.parseClassFile();
    //classFile->debug();
    auto _class = new Class(classFile);//parse classFile to class object
    _class->classloader = this;
    resolveSuperClass(_class);
    resolveInterfaces(_class);
    classMap[_class->name] = _class;


    //TODO::now classfile.constantPool has been traslate to heap.constantPool,pass by value,classFile can be deleted.

    return _class;
}

void ClassLoader::resolveSuperClass(Class *_class)
{
    if(_class->name!="java/lang/Object")
        _class->superClass = _class->classloader->loadClass(_class->superClassName);//recursive load
}

void ClassLoader::resolveInterfaces(Class *_class)
{
    auto interfacesCount = _class->interfacesNames.size();
    if(interfacesCount>0)
    {
        _class->interfaces.resize(interfacesCount);
        for(auto i=0;i<interfacesCount;i++)
            _class->interfaces[i] = _class->classloader->loadClass(_class->interfacesNames[i]);
    }
}

void ClassLoader::link(Class *_class)
{
    verify(_class);
    prepare(_class);
}

void ClassLoader::verify(Class *_class)
{
    //TODO:implemnt it
    //java虚拟机规范 4.10
}

void ClassLoader::prepare(Class *_class)
{
    _class->calculateInstanceFieldSlotsId();
    _class->calculateStaticFieldSlotsId();
    _class->initializeStaticVars();
}