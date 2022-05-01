//
// Created by xuranus on 4/26/22.
//

#include "MethodDescriptorParser.h"
#include <cassert>

namespace heap {
    MethodDescriptorParser::MethodDescriptorParser(const std::string &rawDescriptor) {
        descriptor = rawDescriptor;
        offset = 0;
    }

    std::pair<std::vector<std::string>, std::string>  MethodDescriptorParser::parse() {
        // (Ljava/lang/String;IF)Ljava/lang/String; => {Ljava/lang/String, I, F}, Ljava/lang/String
        assert(readChar() == '('); // startParams
        parseParamTypes();
        unreadChar();
        assert(readChar() == ')'); // endParams;
        parseReturnType();
        assert(offset == descriptor.length());
        return std::make_pair(parameterTypes, returnType);
    }


    void MethodDescriptorParser::parseParamTypes() {
        while (true) {
            auto t = parseFieldType();
            if (!t.empty()) {
                parameterTypes.push_back(t);
            } else {
                break;
            }
        }
    }

    char MethodDescriptorParser::readChar() {
        char b = descriptor[offset];
        offset++;
        return  b;
    }

    void MethodDescriptorParser::unreadChar() {
        offset--;
    }

    void MethodDescriptorParser::parseReturnType() {
        if (readChar() == 'V') {
            returnType = "V";
            return;
        }
        unreadChar();

        auto t = parseFieldType();
        assert(!t.empty());
        returnType = t;
    }

    std::string MethodDescriptorParser::parseFieldType() {
        switch (readChar()) {
            case 'B': return "B";
            case 'C': return "C";
            case 'D': return "D";
            case 'F': return "F";
            case 'I': return "I";
            case 'J': return "J";
            case 'S': return "S";
            case 'Z': return "Z";
            case 'L': return parseObjectType();
            case '[': return parseArrayType();
            default:  return "";
        }
    }

    std::string MethodDescriptorParser::parseObjectType() {
        std::string unread = descriptor.substr(offset);
        auto semicolonIndex = unread.find(';');
        assert(semicolonIndex != std::string::npos);
        int start = offset - 1;
        offset = offset + semicolonIndex + 1;
        return descriptor.substr(start, semicolonIndex + 2);
    }

    std::string MethodDescriptorParser::parseArrayType() {
        auto arrStart = offset - 1;
        parseFieldType();
        return descriptor.substr(arrStart, offset - arrStart);
    }
}