//
// Created by xuranus on 4/23/22.
//

#ifndef JVM_NATIVE_JAVA_LANG_IO_FILEOUTPUTSTREAM_H
#define JVM_NATIVE_JAVA_LANG_IO_FILEOUTPUTSTREAM_H

#include "../../../runtime/thread/Frame.h"

namespace native::java::io::FileOutputStream {
    void doRegistration();

    void writeBytes(runtime::Frame* frame);
    void open0(runtime::Frame* frame);
    void close0(runtime::Frame* frame);
}

#endif //JVM_NATIVE_JAVA_LANG_IO_FILEOUTPUTSTREAM_H
