//
// Created by XUranus on 2019/2/1.
//

#ifndef JVM_THREAD_H
#define JVM_THREAD_H

#include "Stack.h"
#include <memory>

#include "../heap/Class.h"

/**
 *  Thread {
 *      int                                                 pc
 *      Stack {
 *          int                                 capacity
 *          int                                 size
 *          Frame {
 *              LocalVars       localVars;
                OperandStack    operandStack;
                int             nextPc;
                Thread*         curThread;
                Method*         method;
 *          }[]                                 frame
 *      }                                                   stack
 *
 *
 */

namespace runtime {

    class Stack;

    class Thread {
    public:
        std::string _name;
        unsigned int pc;
        std::unique_ptr<Stack> stack;

    public:
        Thread(int stackSize, const std::string& _name_);

        // init class, run <clinit> method
        void initClass(heap::Class* klass);
        void initSuperClass(heap::Class *klass);
        void scheduleClinit(heap::Class *klass);
        [[nodiscard]] std::string name() const;
    };

}

#endif //JVM_THREAD_H
