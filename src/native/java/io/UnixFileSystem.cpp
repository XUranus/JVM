//
// Created by xuranus on 4/27/22.
//

#include "../../../runtime/heap/Object.h"
#include "../../../runtime/heap/StringPool.h"
#include "../../NativeRegistry.h"
#include "UnixFileSystem.h"
#include "../../../common/FilePath.h"

namespace native::java::io::UnixFileSystem {

    void doRegistration() {
        setRegister("java/io/UnixFileSystem", "canonicalize0", "(Ljava/lang/String;)Ljava/lang/String;", canonicalize0);
        setRegister("java/io/UnixFileSystem", "getBooleanAttributes0", "(Ljava/io/File;)I", getBooleanAttributes0);
    }

    // private native String canonicalize0(String path) throws IOException;
    // (Ljava/lang/String;)Ljava/lang/String;
    void canonicalize0(runtime::Frame *frame) {
        heap::Object* jPath = frame->localVars.refValue(1);
        std::string path = heap::StringPool::localString(jPath);
        // TODO:: implement
        frame->operandStack.pushRef(jPath);
    }

    // public native int getBooleanAttributes0(File f);
    // (Ljava/io/File;)I
    void getBooleanAttributes0(runtime::Frame* frame) {
        heap::Object* f = frame->localVars.refValue(1);
        std::string path = heap::StringPool::localString(f->getRefVar("path", "Ljava/lang/String;"));
        unsigned char attribute0 = 0;
        if(FilePath::exists(path)) {
            attribute0 |= 0x01;
        }
        if(FilePath::isDir(path)) {
            attribute0 |= 0x04;
        }
        frame->operandStack.pushInt(attribute0);
    }
}
