//
// Created by xuranus on 4/27/22.
//

#include "URLClassPath.h"
#include "../../NativeRegistry.h"

namespace native::sun::misc::URLClassPath {

    void doRegistration() {
        setRegister("sun/misc/URLClassPath", "getLookupCacheURLs", "(Ljava/lang/ClassLoader;)[Ljava/net/URL;", getLookupCacheURLs);
    }

    // private static native URL[] getLookupCacheURLs(ClassLoader var0);
    // (Ljava/lang/ClassLoader;)[Ljava/net/URL
    void getLookupCacheURLs(runtime::Frame* frame) {
        frame->operandStack.pushRef(nullptr); // TODO:: implement
    }

}