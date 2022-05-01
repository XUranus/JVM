//
// Created by xuranus on 5/1/22.
//

#include "FileInputStream.h"
#include "../../../runtime/heap/StringPool.h"
#include "../../NativeRegistry.h"
#include <cstdio>

namespace native::java::io::FileInputStream {

    static std::map<heap::Object*, FILE *> _fileOpenMap;

    void doRegistration() {
        const std::string className = "java/io/FileInputStream";
        setRegister(className, "open0", "(Ljava/lang/String;)V", open0);
        setRegister(className, "close0", "()V", close0);
        setRegister(className, "readBytes", "([BII)I", readBytes);
        setRegister(className, "available0", "()I", available0);
    }

    // private native void readBytes(byte[] b, int off, int len)
    // throw IOException
    void readBytes(runtime::Frame* frame) {
        auto& vars = frame->localVars;
        auto& stack = frame->operandStack;

        auto _this = vars.refValue(0);
        heap::Object* b = vars.refValue(1);
        int off = vars.intValue(2);
        int len = vars.intValue(3);

        char* bytes = b->byteArray();
        int n = -1;
        if(_fileOpenMap.find(_this) != _fileOpenMap.end()) {
            n = fread(bytes + off, sizeof(char ), len, _fileOpenMap[_this]);
        } else {
            n = fread(bytes + off, sizeof(char ), len, stdin);
        }
        if(n == 0) {
            n = -1;
        }
        stack.pushInt(n);
    }

    // private native void open0(String path)
    void open0(runtime::Frame* frame) {
        auto& vars = frame->localVars;

        heap::Object* _this = vars.refValue(0);
        heap::Object* jPath = vars.refValue(1);

        std::string path = heap::StringPool::localString(jPath);
        FILE *fp = fopen(path.c_str(), "r");
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

    // private native int available()
    void available0(runtime::Frame* frame) {
        frame->operandStack.pushInt(true);
    }
}
