//
// Created by xuranus on 2/18/19.
//

#include "StringPool.h"
#include "ClassLoader.h"
#include <codecvt>
#include <locale>

namespace heap::StringPool {

        std::u16string stringToUtf16(const std::string &str) {
            std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> cvt;
            return cvt.from_bytes(str);
        }

        std::string utf16ToString(const std::u16string& u16source) {
            std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> cvt;
            return cvt.to_bytes(u16source);
        }

        /**
         * java.lang.String {
         *      private final char[] value;
         *      ....
         * }
         */
        std::string localString(Object *jStr) {
            heap::Object* valueObject = jStr->getRefVar("value", "[C");
            unsigned int length = valueObject->arrLength;
            short* chars = valueObject->charArray();
            std::u16string u16source;
            for (int i = 0; i < length; i++) {
                u16source.push_back(chars[i]);
            }
            return utf16ToString(u16source);
        }

        heap::Object* JString(ClassLoader *loader, const std::string& localStr) {
            if (internedStrings.find(localStr) != internedStrings.end()) {
                return internedStrings[localStr];
            } else {
                std::u16string u16source = stringToUtf16(localStr);
                auto *data = new unsigned short[u16source.length()];
                for(int i = 0; i < u16source.length(); i++) {
                    data[i] = u16source[i];
                }
                heap::Object* jChars = ObjectPool::createObject(loader->loadClass("[C"), data, u16source.length(), ObjectDataType::CharArray);
                heap::Object* jStr = loader->loadClass("java/lang/String")->newObject();
                jStr->setRefVar("value", "[C", jChars);
                internedStrings[localStr] = jStr;
                return jStr;
            }
        }

        heap::Object* internString(heap::Object* jStr) {
            std::string localStr = localString(jStr);
            if (internedStrings.find(localStr) == internedStrings.end()) {
                internedStrings[localStr] = jStr;
            }
            return internedStrings[localStr];
        }

    }