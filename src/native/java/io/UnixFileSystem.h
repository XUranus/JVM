//
// Created by xuranus on 4/27/22.
//

#ifndef JVM_NATIVE_JAVA_IO_UNIXFILESYSTEM_H
#define JVM_NATIVE_JAVA_IO_UNIXFILESYSTEM_H


#include "../../../runtime/thread/Frame.h"

namespace native::java::io::UnixFileSystem {
    void doRegistration();

    void canonicalize0(runtime::Frame *frame);
    void getBooleanAttributes0(runtime::Frame* frame);
}



#endif //JVM_NATIVE_JAVA_IO_UNIXFILESYSTEM_H
