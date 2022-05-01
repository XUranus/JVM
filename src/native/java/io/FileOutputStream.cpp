//
// Created by xuranus on 4/23/22.
//

#include "../../../runtime/heap/Object.h"
#include "../../../runtime/heap/StringPool.h"
#include "../../NativeRegistry.h"
#include <cstdio>
#include "FileOutputStream.h"

namespace native::java::io::FileOutputStream {

    static std::map<heap::Object*, FILE *> _fileOpenMap;

    void doRegistration() {
        const std::string className = "java/io/FileOutputStream";
        setRegister(className, "writeBytes", "([BIIZ)V", writeBytes);
        setRegister(className, "open0", "(Ljava/lang/String;Z)V", open0);
        setRegister(className, "close0", "()V", close0);
    }

    // private native void writeBytes(byte[] b, int off, int len, boolean append)
    // throw IOException
    void writeBytes(runtime::Frame* frame) {
        auto& vars = frame->localVars;
        auto _this = vars.refValue(0);
        heap::Object* b = vars.refValue(1);
        int off = vars.intValue(2);
        int len = vars.intValue(3);
        bool append = vars.intValue(4);

        char* bytes = b->byteArray();
        if(_fileOpenMap.find(_this) != _fileOpenMap.end()) {
            fwrite(bytes + off, sizeof(char ), len, _fileOpenMap[_this]);
        } else {
            fwrite(bytes + off, sizeof(char ), len, stdout);
        }
    }

    // private native void open0(String path, boolean var1)
    void open0(runtime::Frame* frame) {
        auto& vars = frame->localVars;

        heap::Object* _this = vars.refValue(0);
        heap::Object* jPath = vars.refValue(1);
        bool var1 = vars.refValue(2);

        std::string path = heap::StringPool::localString(jPath);
        FILE *fp = fopen(path.c_str(), "w");
        _fileOpenMap[_this] = fp;
    }

    // private native void close0()
    void close0(runtime::Frame* frame) {
        auto &vars = frame->localVars;
        heap::Object* _this = vars.refValue(0);
        FILE * fp = _fileOpenMap[_this];
        fclose(fp);
        _fileOpenMap.erase(_this);
    }
}
