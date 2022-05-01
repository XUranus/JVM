//
// Created by xuranus on 3/17/19.
//

#include <cstring>
#include <chrono>
#include <map>
#include "../../NativeRegistry.h"
#include "../../../runtime/heap/Object.h"
#include "../../../runtime/heap/ClassLoader.h"
#include "../../../runtime/heap/StringPool.h"
#include "../../../common/Exception.h"
#include "../../../instruction/references.h"

#include "System.h"

namespace native::java::lang::System {

    void doRegistration() {
        const std::string jlSystem = "java/lang/System";
        setRegister(jlSystem, "arraycopy", "(Ljava/lang/Object;ILjava/lang/Object;II)V", arraycopy);
        setRegister(jlSystem, "setOut0", "(Ljava/io/PrintStream;)V", setOut0);
        setRegister(jlSystem, "setErr0", "(Ljava/io/PrintStream;)V", setErr0);
        setRegister(jlSystem, "setIn0", "(Ljava/io/InputStream;)V", setIn0);
        setRegister(jlSystem, "currentTimeMillis", "()J", currentTimeMillis);
        setRegister(jlSystem, "initProperties", "(Ljava/util/Properties;)Ljava/util/Properties;", initProperties);
    }

    bool checkArrayCopy(heap::Object *src, heap::Object *dest) {
        auto srcClass = src->klass;
        auto destClass = dest->klass;

        if (!srcClass->isArray() || !destClass->isArray()) {
            return false;
        }
        if (srcClass->componentClass()->isPrimitive() ||
            destClass->componentClass()->isPrimitive()) {
            return srcClass == destClass;
        }
        return true; // is ref class
    }

    void arrayCopy(heap::Object *src, heap::Object *dst, int srcPos, int dstPos, int length) {
        switch (src->dataType) {
            case heap::ObjectDataType::BoolArray:
            case heap::ObjectDataType::ByteArray:       {memcpy((char *)        dst->data + dstPos, (char *)        src->data + srcPos, sizeof (char ) *    length); break;};
            case heap::ObjectDataType::ShortArray:
            case heap::ObjectDataType::CharArray:       {memcpy((short *)       dst->data + dstPos, (short *)       src->data + srcPos, sizeof (short ) *   length); break;};
            case heap::ObjectDataType::IntArray:        {memcpy((int *)         dst->data + dstPos, (int *)         src->data + srcPos, sizeof (int ) *     length); break;};
            case heap::ObjectDataType::LongArray:       {memcpy((long *)        dst->data + dstPos, (long *)        src->data + srcPos, sizeof (long ) *    length); break;};
            case heap::ObjectDataType::FloatArray:      {memcpy((float *)       dst->data + dstPos, (float *)       src->data + srcPos, sizeof (float ) *   length); break;};
            case heap::ObjectDataType::DoubleArray:     {memcpy((double *)      dst->data + dstPos, (double *)      src->data + srcPos, sizeof (double ) *  length); break;};
            case heap::ObjectDataType::ObjectRefArray:  {memcpy((heap::Object**)dst->data + dstPos, (heap::Object**)src->data + srcPos, sizeof (heap::Object* ) * length); break;};
            default: {exception::fatal("ArrayCopy(): object not array!");}
        }
    }

    // public static native void arraycopy(Object src, int srcPos, Object dest, int destPos, int length)
    // (Ljava/lang/Object;ILjava/lang/Object;II)V
    void arraycopy(runtime::Frame *frame) {
        auto &vars = frame->localVars;
        heap::Object* src = vars.refValue(0);
        int srcPos = vars.intValue(1);
        heap::Object* dest = vars.refValue(2);
        int destPos = vars.intValue(3);
        int length = vars.intValue(4);

        if (src == nullptr || dest == nullptr) {
            exception::fatal("java.lang.NullPointerException");
        }
        if (!checkArrayCopy(src, dest)) {
            exception::fatal("java.lang.ArrayStoreException");
        }
        if (srcPos < 0 || destPos < 0 || length < 0 || srcPos + length > src->arrayLength() ||
            destPos + length > dest->arrayLength()) {
            exception::fatal("java.lang.IndexOutOfBoundException");
        }
        arrayCopy(src, dest, srcPos, destPos, length);
    }

    // private static native void setOut0(PrintStream out);
    // (Ljava/io/PrintStream;)V
    void setOut0(runtime::Frame* frame) {
        heap::Object* out = frame->localVars.refValue(0); // java.io.PrintStream out
        heap::Class* jlSysClass = frame->method->klass ; // java.lang.System
        jlSysClass->setRefVar("out", "Ljava/io/PrintStream;", out);
    }

    // private static native void setIn0(InputStream in);
    // (Ljava/io/InputStream;)V
    void setIn0(runtime::Frame* frame) {
        heap::Object* in = frame->localVars.refValue(0); // java.io.InputStream in
        heap::Class* jlSysClass = frame->method->klass ; // java.lang.System
        jlSysClass->setRefVar("in", "Ljava/io/InputStream;", in);
    }

    // private static native void setErr0(PrintStream err);
    // (Ljava/io/PrintStream;)V
    void setErr0(runtime::Frame* frame) {
        heap::Object* err = frame->localVars.refValue(0); // java.io.PrintStream
        heap::Class* jlSysClass = frame->method->klass ; // java.lang.System
        jlSysClass->setRefVar("err", "Ljava/io/PrintStream;", err);
    }

    // public static native long currentTimeMillis();
    // ()J
    void currentTimeMillis(runtime::Frame* frame) {
        const auto p1 = std::chrono::system_clock::now();
        long millis = std::chrono::duration_cast<std::chrono::milliseconds>(
                p1.time_since_epoch()).count();
        frame->operandStack.pushLong(millis);
    }

    // private static native Properties initProperties(Properties props);
    // (Ljava/util/Properties;)Ljava/util/Properties;
    void initProperties(runtime::Frame* frame) {

        std::vector<std::pair<std::string, std::string>> sysProps = {
                {"java.version",         "1.8.0"},
                {"java.vendor",          "xjava"},
                {"java.vendor.url",      "https,//github.com/XUranus/JVM"},
                {"java.home",            "todo"},
                {"java.class.version",   "52.0"},
                {"java.class.path",      "todo"},
                {"java.awt.graphicsenv", "sun.awt.CGraphicsEnvironment"},
                {"os.name",              "linux"},   		  // todo
                {"os.arch",              "amd64"}, 			  // todo
                {"os.version",           ""},             // todo
                {"file.separator",       "/"},            // todo os.PathSeparator
                {"path.separator",       ":"},            // todo os.PathListSeparator
                {"line.separator",       "\n"},           // todo
                {"user.name",            ""},             // todo
                {"user.home",            ""},             // todo
                {"user.dir",             "."},            // todo
                {"user.country",         "CN"},           // todo
                {"file.encoding",        "UTF-8"},
                {"sun.stdout.encoding",  "UTF-8"},
                {"sun.stderr.encoding",  "UTF-8"}
        };

        auto& vars = frame->localVars;
        auto& stack = frame->operandStack;
        runtime::Thread* thread = frame->thread;
        auto classLoader = frame->method->klass->classloader;

        heap::Object* props = vars.refValue(0); // java.util.Properties props
        stack.pushRef(props);

        heap::Method* setPropsMethod = props->klass->getInstanceMethod("setProperty", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;");

        for(auto& pair: sysProps) {
            //std::cout << pair.first << std::endl;
            std::string key = pair.first;
            std::string value = pair.second;
            heap::Object* jKey = heap::StringPool::JString(classLoader, key);
            heap::Object* jValue = heap::StringPool::JString(classLoader, value);

            auto shimMethod = heap::Method::ShimMethod; // shim method
            auto shimFrame = runtime::Frame(0, 3, thread, shimMethod);

            shimFrame.operandStack.pushRef(props);
            shimFrame.operandStack.pushRef(jKey);
            shimFrame.operandStack.pushRef(jValue);

            thread->stack->push(shimFrame);
            instruction::invokeMethod(&thread->stack->top(), setPropsMethod);
        }

    }

}
