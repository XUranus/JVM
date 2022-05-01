//
// Created by xuranus on 4/21/22.
//

#ifndef JVM_TEST7_H
#define JVM_TEST7_H

#include "../src/runtime/heap/Method.h"
#include <bits/stdc++.h>

using namespace std;

struct DescriptorParserTest {

    static void execute() {
        vector<string> descriptors = {"(Ljava/lang/String;IF)Ljava/lang/String;", "()V", "([[I[S[[[BLjava/lang/Class;)[[Ljava/lang/String;"};
        for(auto& descriptor: descriptors) {
            std::cout << "descriptor: " << descriptor << endl;
            heap::MethodDescriptorParser parser(descriptor);
            auto res = parser.parse();
            std::cout << "params: ";
            for(auto& param: res.first) {
                cout << param << "\t";
            }
            cout << endl;
            cout << "return type: " << res.second << endl;
            cout << "==================================" << endl;
        }
    }

};

#endif