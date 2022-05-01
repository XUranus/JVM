//
// Created by xuranus on 4/26/22.
//

#ifndef JVM_NATIVE_JAVA_IO_FILEDESCRIPTOR_H
#define JVM_NATIVE_JAVA_IO_FILEDESCRIPTOR_H


#include "../../../runtime/thread/Frame.h"

namespace native::java::io::FileDescriptor {
    void doRegistration();

    void set(runtime::Frame *frame);
}



#endif //JVM_NATIVE_JAVA_IO_FILEDESCRIPTOR_H
