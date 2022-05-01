//
// Created by xuranus on 4/22/22.
//

#ifndef JVM_NATIVE_JAVA_LANG_THROWABLE_H
#define JVM_NATIVE_JAVA_LANG_THROWABLE_H


#include "../../../runtime/thread/Frame.h"

namespace native::java::lang {

    class Throwable {
    public:
        // used to store information of JVM stack frame
        struct StackTraceElement {
            std::string filename;
            std::string className;
            std::string methodName;
            int lineNumber;
        };

        static std::map<heap::Object *, std::vector<StackTraceElement>> exceptionStackTraceMap;
        static void deRegistration();

        static void fillInStackTrace(runtime::Frame *frame);
    };
};


#endif //JVM_NATIVE_JAVA_LANG_THROWABLE_H
