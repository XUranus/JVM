//
// Created by xuranus on 4/26/22.
//

#ifndef JVM_RUNTIME_HEAP_METHODDESCRIPTORPARSER_H
#define JVM_RUNTIME_HEAP_METHODDESCRIPTORPARSER_H

#include <string>
#include <vector>

namespace heap {

    class MethodDescriptorParser {
    private:
        std::string descriptor;
        unsigned long offset;
        std::vector<std::string> parameterTypes;
        std::string returnType;

    public:
        explicit MethodDescriptorParser(const std::string& rawDescriptor);
        std::pair<std::vector<std::string>, std::string>  parse(); // the builder design pattern

    private:
        void parseParamTypes();
        char readChar();
        void unreadChar();

        void parseReturnType();
        std::string parseFieldType();
        std::string parseObjectType();
        std::string parseArrayType();
    };
}


#endif //JVM_RUNTIME_HEAP_METHODDESCRIPTORPARSER_H
