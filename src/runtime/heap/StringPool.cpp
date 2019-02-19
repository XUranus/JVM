//
// Created by xuranus on 2/18/19.
//
#include "../../util/Console.h"
#include "StringPool.h"
#include "ClassLoader.h"
#include <codecvt>
#include <locale>

StringPool* StringPool::instance = nullptr;

StringPool* StringPool::getStringPool()
{
    if(StringPool::instance== nullptr)
        StringPool::instance = new StringPool();
    return StringPool::instance;
}

std::string StringPool::utf16ToString(std::vector<uint16> &u16source)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> cvt;
    std::u16string u16str;
    for(auto c:u16source)
        u16str.push_back(c);
    std::string ret = cvt.to_bytes(u16str);
    return ret;
}

std::string StringPool::getlocalString(Object *jStr)
{
    auto charArr = jStr->getRefVar("value","[C");
    auto len = charArr->dataCount;
    std::vector<uint16 > u16chars;
    for(auto i=0;i<len;i++)
        u16chars.push_back(charArr->chars()[i]);
    return utf16ToString(u16chars);
}

StringPool::StringPool()
{
    internedStrings.clear();
}

std::u16string StringPool::stringToUtf16(std::string &str)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> cvt;
    std::u16string u16_str = cvt.from_bytes(str);
    return u16_str;
}

Object* StringPool::getJString(ClassLoader *loader, std::string& localStr)
{
    if(internedStrings.find(localStr)!=internedStrings.end())
        return internedStrings[localStr];
    else
        return newJString(loader,localStr);
}

Object* StringPool::newJString(ClassLoader *loader, std::string& localStr)
{
    //Console::printlnInfo("newJString["+localStr+"]");
    auto chars = stringToUtf16(localStr);
    auto data = new uint16[chars.length()];
    for(auto i=0;i<chars.length();i++)
        data[i] = chars[i];
    auto jchars = new Object(loader->loadClass("[C"),data,chars.length(),Object::DataType::UINT16);
    auto jstr = loader->loadClass("java/lang/String")->newObject();
    jstr->setRefVar("value","[C",jchars);
    internedStrings[localStr] = jstr;
    return jstr;
}

void StringPool::debug()
{
    printf("[Debug StringPool]\n");
    for(auto& m:internedStrings)
        printf("[%s]<%ld> ",m.first.c_str(),(long)m.second);
    printf("\n");
}