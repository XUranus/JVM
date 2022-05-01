//
// Created by XUranus on 2019/2/1.
//

#include "Stack.h"
#include "../../common/Exception.h"
#include <cassert>

namespace runtime {

    Stack::Stack(int _maxCapacity, Thread* _thread) {
        maxCapacity = _maxCapacity;
        thread = _thread;;
    }

    void Stack::push(const Frame &frame) {
        if (frames.size() >= maxCapacity) {
            exception::fatal("java.lang.StackOverFlowError");
        } else {
            frames.push_back(frame);
        }
    }

    Frame Stack::pop() {
        assert(!frames.empty());
        Frame frame(frames.back());
        frames.pop_back();
        return frame;
    }

    Frame &Stack::top() {
        assert(!frames.empty());
        return frames.back();
    }

    void Stack::clear() {
        frames.clear();
    }

    bool Stack::empty() const {
        return frames.empty();
    }

    std::list<Frame *> Stack::stackFrames() {
        std::list<Frame*> res;
        for(auto it = frames.rbegin(); it != frames.rend(); it++) {
            res.push_back(&(*it));
        }
        return res;
    }

}