//
// Created by xuranus on 5/1/22.
//

#ifndef JVM_NATIVE_JAVA_LANG_IO_FILEINPUTSTREAM_H
#define JVM_NATIVE_JAVA_LANG_IO_FILEINPUTSTREAM_H

#include "../../../runtime/thread/Frame.h"

namespace native::java::io::FileInputStream {
    void doRegistration();

    void open0(runtime::Frame* frame);
    void close0(runtime::Frame* frame);
    void readBytes(runtime::Frame* frame);
    void available0(runtime::Frame* frame);
}

#endif //JVM_NATIVE_JAVA_LANG_IO_FILEINPUTSTREAM_H
