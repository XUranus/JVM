//
// Created by xuranus on 2/5/19.
//

#include "comparisons.h"

namespace instruction {

    void lcmp::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popLong();
        auto v1 = frame->operandStack.popLong();
        if (v1 > v2) {
            frame->operandStack.pushInt(1);
        } else if (v1 == v2) {
            frame->operandStack.pushInt(0);
        } else {
            frame->operandStack.pushInt(-1);
        }
    }

    void fcmpl::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popFloat();
        auto v1 = frame->operandStack.popFloat();
        if (v1 > v2) {
            frame->operandStack.pushInt(1);
        } else if (v1 == v2) {
            frame->operandStack.pushInt(0);
        } else if (v1 < v2) {
            frame->operandStack.pushInt(-1);
        } else {
            frame->operandStack.pushInt(-1);
        }
    }

    void fcmpg::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popFloat();
        auto v1 = frame->operandStack.popFloat();
        if (v1 > v2) {
            frame->operandStack.pushInt(1);
        } else if (v1 == v2) {
            frame->operandStack.pushInt(0);
        } else if (v1 < v2) {
            frame->operandStack.pushInt(-1);
        } else {
            frame->operandStack.pushInt(1);
        }
    }

    void dcmpl::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popDouble();
        auto v1 = frame->operandStack.popDouble();
        if (v1 > v2) {
            frame->operandStack.pushInt(1);
        } else if (v1 == v2) {
            frame->operandStack.pushInt(0);
        } else {
            frame->operandStack.pushInt(-1);
        }
    }

    void dcmpg::execute(runtime::Frame* frame) {
        auto v2 = frame->operandStack.popDouble();
        auto v1 = frame->operandStack.popDouble();
        if (v1 > v2) {
            frame->operandStack.pushInt(1);
        } else if (v1 == v2) {
            frame->operandStack.pushInt(0);
        } else if (v1 < v2) {
            frame->operandStack.pushInt(-1);
        } else {
            frame->operandStack.pushInt(1);
        }
    }

    void ifeq::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popInt();
        if (val == 0) {
            frame->branch(offset);
        }
    }

    void ifne::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popInt();
        if (val != 0) {
            frame->branch(offset);
        }
    }

    void iflt::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popInt();
        if (val < 0) {
            frame->branch(offset);
        }
    }

    void ifge::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popInt();
        if (val >= 0) {
            frame->branch(offset);
        }
    }

    void ifgt::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popInt();
        if (val > 0) {
            frame->branch(offset);
        }
    }

    void ifle::execute(runtime::Frame* frame) {
        auto val = frame->operandStack.popInt();
        if (val <= 0) {
            frame->branch(offset);
        }
    }

    void if_icmpeq::execute(runtime::Frame* frame) {
        auto val2 = frame->operandStack.popInt();
        auto val1 = frame->operandStack.popInt();
        if (val1 == val2) {
            frame->branch(offset);
        }
    }

    void if_icmpne::execute(runtime::Frame* frame) {
        auto val2 = frame->operandStack.popInt();
        auto val1 = frame->operandStack.popInt();
        if (val1 != val2) {
            frame->branch(offset);
        }
    }

    void if_icmplt::execute(runtime::Frame* frame) {
        auto val2 = frame->operandStack.popInt();
        auto val1 = frame->operandStack.popInt();
        if (val1 < val2) {
            frame->branch(offset);
        }
    }

    void if_icmpge::execute(runtime::Frame* frame) {
        auto val2 = frame->operandStack.popInt();
        auto val1 = frame->operandStack.popInt();
        if (val1 >= val2) {
            frame->branch(offset);
        }
    }

    void if_icmpgt::execute(runtime::Frame* frame) {
        auto val2 = frame->operandStack.popInt();
        auto val1 = frame->operandStack.popInt();
        if (val1 > val2) {
            frame->branch(offset);
        }
    }

    void if_icmple::execute(runtime::Frame* frame) {
        auto val2 = frame->operandStack.popInt();
        auto val1 = frame->operandStack.popInt();
        if (val1 <= val2) {
            frame->branch(offset);
        }
    }

    void if_acmpeq::execute(runtime::Frame* frame) {
        auto val2 = frame->operandStack.popRef();
        auto val1 = frame->operandStack.popRef();
        if (val1 == val2) {
            frame->branch(offset);
        }
    }

    void if_acmpne::execute(runtime::Frame* frame) {
        auto val2 = frame->operandStack.popRef();
        auto val1 = frame->operandStack.popRef();
        if (val1 != val2) {
            frame->branch(offset);
        }
    }

}