//
// Created by XUranus on 2019/2/1.
//

#include "Thread.h"
#include "../../common/Exception.h"

namespace runtime {

    Thread::Thread(int stackSize, const std::string& _name_):
        stack(std::make_unique<Stack>(stackSize, this)),
        _name(_name_) {
        pc = 0;
    }

    void Thread::initClass(heap::Class *klass) {
        klass->markInitStarted();
        scheduleClinit(klass);
        initSuperClass(klass);
    }


    void Thread::scheduleClinit(heap::Class *klass) {
        heap::Method* clinitMethod = klass->getClinitMethod();
        if (clinitMethod != nullptr) {
            stack->push(Frame(clinitMethod->maxLocals,
                              clinitMethod->maxStack,
                              this,
                              clinitMethod
                              ));
        } else {
            // nop, some classes don't have <clinit> method
        }
    }

    void Thread::initSuperClass(heap::Class *klass) {
        if (!klass->isInterface()) {
            heap::Class* superClass = klass->superClass;
            if (superClass != nullptr && !superClass->isInitStarted()) {
                // to make superclass <clinit> is invoked before current class
                initClass(superClass);
            }
        }
    }

    std::string Thread::name() const {
        return _name;
    }

}