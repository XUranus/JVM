//
// Created by xuranus on 4/23/22.
//

#include "JavaVirtualMachine.h"

#include <utility>
#include "common/Exception.h"
#include "instruction/InstructionReader.h"
#include "instruction/instruction.h"
#include "native/NativeRegistry.h"
#include "runtime/heap/StringPool.h"

JavaVirtualMachine::JavaVirtualMachine(classpath::ClassPath *classPath, console::Command command):
        cmd(std::move(command)),
        mainThread(2048, "main"),
        classLoader(classPath, cmd.verboseClassFlag) {}

void JavaVirtualMachine::start() {
    initVM();
    executeMain();
}

void JavaVirtualMachine::initVM() {
    native::initNativeRegistry();
    heap::Class* vmClass = classLoader.loadClass("sun/misc/VM");
    mainThread.initClass(vmClass);
    interpret(&mainThread);
}

void JavaVirtualMachine::executeMain() {
    std::string className = cmd.className;
    for(char &ch: className) {
        if(ch == '.') {
            ch = '/';
        }
    }

    heap::Class* mainClass = classLoader.loadClass(className);
    if(mainClass) {
        heap::Method* mainMethod = mainClass->getMainMethod();
        if(mainMethod == nullptr) {
            exception::fatal("Error: Main method not found in class " + cmd.className +
                             ", please define the main method as public static void main(String[] args)");
        } else {
            //TODO::runtime object garbage collect thread

            heap::Object* jArgs = classLoader.createArgsArrayObject(cmd.args);
            runtime::Frame frame((int )mainMethod->maxLocals,
                                 (int )mainMethod->maxStack,
                                 &mainThread,
                                 mainMethod);
            frame.localVars.setRef(0, jArgs); // set command line args
            mainThread.stack->push(frame);
            interpret(&mainThread);
        }
    } else {
        exception::fatal("failed to load class: " + cmd.className);
    }
}

void JavaVirtualMachine::interpret(runtime::Thread *thread) const {
    instruction::InstructionReader reader;
    int i = 1;
    while (!thread->stack->empty()) {
        runtime::Frame& frame = thread->stack->top();
        unsigned int pc = frame.nextPC;
        thread->pc = pc;

        reader.reset(frame.method->code.data(), pc, frame.method->code.size());
        u1 opCode = reader.readUint8();

        instruction::Instruction* inst = instruction::create(opCode);
        inst->fetchOperands(reader);

        if (cmd.verboseInstFlag) {
            Console::printlnYellow("[instruction]:" + inst->verbose());
        }

//        // TODO:=============================
//        std::cout << "[" << i++ << "] " << inst->name() << std::endl;
//        frame.localVars.dump();
//        frame.operandStack.dump();
//        // TODO::===============================

        frame.nextPC = reader.PC();
        inst->execute(&frame);

        if(heap::ObjectPool::needGC()) {
            auto GCRoots = collectGCRoots();
            heap::ObjectPool::reachableAnalysisGC(GCRoots);
        }

    }
}

std::set<heap::Object *> JavaVirtualMachine::collectGCRoots() const {
/**
 * Object that can be viewed as GC Root:
 * 1. objects referred by LocalVar in JVM stack
 * 2. objects referred by static field of class in method area
 * 3. objects referred by constants in method area
 * 4. objects referred by native method
 */
    std::set<heap::Object*> res;

    // 1. objects referred by LocalVar in JVM stack
    auto frames = mainThread.stack->stackFrames();
    for(auto& frame: frames) {
        auto& slots = frame->localVars;
        for(int i = 0; i < slots.size(); i++) {
            if(slots.isRef(i)) {
                res.insert(slots.refValue(i));
            }
        }
    }

    // 2. objects referred by static field of class in method area
    std::set<heap::Class*> classes = classLoader.classes();
    for(heap::Class* klass: classes) {
        for(auto object: klass->staticFieldObjects()) {
            res.insert(object);
        }
        res.insert(klass->jClass);
    }

    // 3. objects referred by constants in method area
    // TODO::

    // 4. objects referred by native method
    // TODO::
    // interned string
    for(auto& pair: heap::StringPool::internedStrings) {
        res.insert(pair.second);
    }

    return res;
}
