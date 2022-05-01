//
// Created by xuranus on 4/22/22.
//

#include <vector>
#include "../../../runtime/heap/Object.h"
#include "../../NativeRegistry.h"
#include "../../../runtime/heap/StringPool.h"
#include "Throwable.h"
#include <cassert>

namespace native::java::lang {

    std::map<heap::Object *, std::vector<Throwable::StackTraceElement>> Throwable::exceptionStackTraceMap;

    void Throwable::deRegistration() {
        setRegister("java/lang/Throwable", "fillInStackTrace", "(I)Ljava/lang/Throwable;", native::java::lang::Throwable::fillInStackTrace);
    }

    // depth of Exception class inheritance
    int distanceToObject(heap::Class* klass)  {
        int distance = 0;
        for(heap::Class* c = klass->superClass; c != nullptr; c = c->superClass) {
            distance++;
        }
        return distance;
    }

    std::vector<Throwable::StackTraceElement> createStackTraceElement(heap::Object* object,
                                                           runtime::Thread* thread) {
        /**
         *          JVM  Stack
         * |----------------------------|
         * | native fillStackTrace(int) | -- top frame
         * |----------------------------|
         * |    fillStackTrace()        |
         * |----------------------------|
         * |        Exception()         |
         * |----------------------------|
         * |    RuntimeException()      |
         * |----------------------------|
         * |        .........           |
         * |----------------------------|
         */

        int skip = distanceToObject(object->klass) + 2;
        std::list<runtime::Frame*> frames = thread->stack->stackFrames();
        while(skip--) {
            frames.pop_front();
        }

        std::vector<Throwable::StackTraceElement> stackTraceElements;
        for(auto & it : frames) {;
            const runtime::Frame& frame = *it;
            heap::Class* klass = frame.method->klass;
            std::string sourceFile = klass->sourceFileName;
            std::string className = klass->getJavaName();
            std::string methodName = frame.method->name;
            int lineNumber = frame.method->lineNumber(frame.nextPC - 1);

            stackTraceElements.emplace_back(Throwable::StackTraceElement{
                sourceFile,
                className,
                methodName,
                lineNumber
            });
        }

        return stackTraceElements;
    }

    /**
     *
     * java.lang.StackTraceElement {
     *     private String declaringClass;
     *     private String methodName;
     *     private String fileName;
     *     private int lineNumber;
     * }
     *
     * java.lang.Throwable {
     *      ......
     *      private StackTraceElement[] stackTrace;
     *      ......
     *
     *      public synchronized Throwable fillInStackTrace() {
     *          if (this.stackTrace != null || this.backtrace != null) {
     *              this.fillInStackTrace(0); // native
     *              this.stackTrace = UNASSIGNED_STACK; // FUCK!!! Why??? Why??
     *          }
     *          return this;
     *      }
     * }
     *
     *
     */



    void Throwable::fillInStackTrace(runtime::Frame *frame) {
        heap::Object* _this = frame->localVars.refValue(0);
        heap::Class* throwable = frame->method->klass->classloader->loadClass("java/lang/Throwable");
        assert(_this->klass == throwable || _this->klass->isSubClassOf(throwable));
        Throwable::exceptionStackTraceMap[_this] = createStackTraceElement(_this, frame->thread);
        frame->operandStack.pushRef(_this);
    }

};

