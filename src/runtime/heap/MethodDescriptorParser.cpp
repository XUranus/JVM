#include "MethodDescriptorParser.h"
#include "../../common/Exception.h"

namespace heap {

    MethodDescriptorParser::MethodDescriptorParser(const std::string& rawDescriptor)
        : descriptor(rawDescriptor), offset(0) {}

    std::pair<std::vector<std::string>, std::string> MethodDescriptorParser::parse() {
        // (Ljava/lang/String;IF)Ljava/lang/String; => {Ljava/lang/String;, I, F}, Ljava/lang/String;
        if (readChar() != '(') {
            exception::panic("invalid method descriptor: expected '(' at start of " + descriptor);
        }
        parseParamTypes();
        if (readChar() != ')') {
            exception::panic("invalid method descriptor: expected ')' after params in " + descriptor);
        }
        parseReturnType();
        return std::make_pair(parameterTypes, returnType);
    }

    void MethodDescriptorParser::parseParamTypes() {
        while (offset < descriptor.size()) {
            auto t = parseFieldType();
            if (!t.empty()) {
                parameterTypes.push_back(t);
            } else {
                break;
            }
        }
    }

    char MethodDescriptorParser::readChar() {
        return descriptor[offset++];
    }

    void MethodDescriptorParser::parseReturnType() {
        char c = descriptor[offset];
        if (c == 'V') {
            offset++;
            returnType = "V";
            return;
        }
        auto t = parseFieldType();
        if (t.empty()) {
            exception::panic("invalid method descriptor: expected return type in " + descriptor);
        }
        returnType = t;
    }

    std::string MethodDescriptorParser::parseFieldType() {
        // Peek without consuming — only consume if we recognize the type
        if (offset >= descriptor.size()) return "";
        char c = descriptor[offset];
        switch (c) {
            case 'B': case 'C': case 'D': case 'F':
            case 'I': case 'J': case 'S': case 'Z':
                offset++;
                return std::string(1, c);
            case 'L':
                offset++;
                return parseObjectType();
            case '[':
                offset++;
                return parseArrayType();
            default:
                return ""; // not a field type, don't consume
        }
    }

    std::string MethodDescriptorParser::parseObjectType() {
        // offset points past 'L', scan for ';'
        auto semicolonIndex = descriptor.find(';', offset);
        if (semicolonIndex == std::string::npos) {
            exception::panic("invalid method descriptor: unterminated object type in " + descriptor);
        }
        int start = offset - 1; // include 'L'
        int len = static_cast<int>(semicolonIndex) - start + 1; // include ';'
        offset = semicolonIndex + 1;
        return descriptor.substr(start, len);
    }

    std::string MethodDescriptorParser::parseArrayType() {
        // offset points past '[', parse the element type
        auto arrStart = offset - 1;
        parseFieldType();
        return descriptor.substr(arrStart, offset - arrStart);
    }
}
