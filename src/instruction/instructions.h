//
// Template-based instruction definitions.
// Replaces constants, loads, stores, math, conversions, comparisons, control.
//

#pragma once

#include "instruction.h"
#include "../runtime/thread/Frame.h"
#include "../runtime/heap/Object.h"
#include "../runtime/heap/ConstantPool.h"
#include "../runtime/heap/StringPool.h"
#include "../runtime/heap/SymRef.h"
#include "../common/Exception.h"
#include <cmath>
#include <functional>

namespace instruction {

// Functors for floating-point remainder (std::modulus doesn't work with float/double)
struct FModFloat {
    float operator()(float a, float b) const { return static_cast<float>(std::fmod(a, b)); }
};
struct FModDouble {
    double operator()(double a, double b) const { return std::fmod(a, b); }
};

// ===========================================================================
// Template Classes
// ===========================================================================

// --- Nop ---
struct Nop : NoOperandsInstruction {
    void execute(runtime::Frame*) override {}
};

// --- aconst_null ---
struct aconst_null : NoOperandsInstruction {
    void execute(runtime::Frame* f) override {
        f->operandStack.pushRef(nullptr);
    }
};

// --- Constant Push (integral types) ---
template<auto Push, typename T, T Value>
struct ConstPush : NoOperandsInstruction {
    void execute(runtime::Frame* f) override {
        (f->operandStack.*Push)(Value);
    }
};

// --- Float/Double Constant Push (specialization for non-integral types) ---
template<auto Push, typename T>
struct ConstFPush;

template<>
struct ConstFPush<&runtime::SlotsStack::pushFloat, float> : NoOperandsInstruction {
    float val;
    explicit ConstFPush(float v) : val(v) {}
    void execute(runtime::Frame* f) override { f->operandStack.pushFloat(val); }
};

template<>
struct ConstFPush<&runtime::SlotsStack::pushDouble, double> : NoOperandsInstruction {
    double val;
    explicit ConstFPush(double v) : val(v) {}
    void execute(runtime::Frame* f) override { f->operandStack.pushDouble(val); }
};

// --- Indexed Load (Index8Instruction: iload, lload, fload, dload, aload) ---
template<auto Get, auto Push>
struct IndexedLoad : Index8Instruction {
    void execute(runtime::Frame* f) override {
        (f->operandStack.*Push)((f->localVars.*Get)(index));
    }
};

// --- Indexed Store (Index8Instruction: istore, lstore, fstore, dstore, astore) ---
template<auto Pop, auto Set>
struct IndexedStore : Index8Instruction {
    void execute(runtime::Frame* f) override {
        (f->localVars.*Set)(index, (f->operandStack.*Pop)());
    }
};

// --- Fixed Slot Load (NoOperands: iload_0..aload_3) ---
template<auto Get, auto Push, int Slot>
struct FixedSlotLoad : NoOperandsInstruction {
    void execute(runtime::Frame* f) override {
        (f->operandStack.*Push)((f->localVars.*Get)(Slot));
    }
};

// --- Fixed Slot Store (NoOperands: istore_0..astore_3) ---
template<auto Pop, auto Set, int Slot>
struct FixedSlotStore : NoOperandsInstruction {
    void execute(runtime::Frame* f) override {
        (f->localVars.*Set)(Slot, (f->operandStack.*Pop)());
    }
};

// --- Array Load (iaload, laload, faload, daload, aaload) ---
template<typename E, auto GetArray, auto PushElem>
struct ArrayLoad : NoOperandsInstruction {
    void execute(runtime::Frame* f) override {
        int index = f->operandStack.popInt();
        heap::Object* arr = f->operandStack.popRef();
        if (!arr) { exception::fatal("java.lang.NullPointerException"); return; }
        E* elems = (arr->*GetArray)();
        if (arr->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException"); return;
        }
        (f->operandStack.*PushElem)(elems[index]);
    }
};

// --- Array Store (iastore, lastore, fastore, dastore, aastore, bastore, castore, sastore) ---
template<typename E, auto PopElem, auto GetArray>
struct ArrayStore : NoOperandsInstruction {
    void execute(runtime::Frame* f) override {
        E val = (f->operandStack.*PopElem)();
        int index = f->operandStack.popInt();
        heap::Object* arr = f->operandStack.popRef();
        if (!arr) { exception::fatal("java.lang.NullPointerException"); return; }
        E* elems = (arr->*GetArray)();
        if (arr->arrayLength() <= index || index < 0) {
            exception::fatal("java.lang.ArrayIndexOutOfBoundException"); return;
        }
        elems[index] = val;
    }
};

// --- Binary Math (iadd, ladd, fadd, dadd, isub, lsub, fsub, dsub, imul, lmul, fmul, dmul) ---
template<auto Pop, auto Push, typename Op>
struct BinMath : NoOperandsInstruction {
    void execute(runtime::Frame* f) override {
        auto b = (f->operandStack.*Pop)();
        auto a = (f->operandStack.*Pop)();
        (f->operandStack.*Push)(Op{}(a, b));
    }
};

// --- Binary Math with Zero Check (idiv, ldiv_, fdiv, ddiv, irem, lrem, frem, drem) ---
template<auto Pop, auto Push, typename Op>
struct BinMathChecked : NoOperandsInstruction {
    void execute(runtime::Frame* f) override {
        auto b = (f->operandStack.*Pop)();
        auto a = (f->operandStack.*Pop)();
        using T = decltype(b);
        if (b == T{0}) {
            exception::fatal("java.lang.ArithmeticException: division by zero");
            return;
        }
        (f->operandStack.*Push)(Op{}(a, b));
    }
};

// --- Unary Math (ineg, lneg, fneg, dneg) ---
template<auto Pop, auto Push, typename Op>
struct UnaryMath : NoOperandsInstruction {
    void execute(runtime::Frame* f) override {
        auto a = (f->operandStack.*Pop)();
        (f->operandStack.*Push)(Op{}(a));
    }
};

// --- Conversion (i2l, i2f, i2d, l2i, l2f, l2d, f2i, f2l, f2d, d2i, d2l, d2f, i2b, i2c, i2s) ---
template<auto Pop, auto Push, typename Cast>
struct Conversion : NoOperandsInstruction {
    void execute(runtime::Frame* f) override {
        (f->operandStack.*Push)(static_cast<Cast>((f->operandStack.*Pop)()));
    }
};

// --- Compare (lcmp, fcmpl, fcmpg, dcmpl, dcmpg) ---
template<auto Pop, int nanResult>
struct CmpPush : NoOperandsInstruction {
    void execute(runtime::Frame* f) override {
        auto b = (f->operandStack.*Pop)();
        auto a = (f->operandStack.*Pop)();
        if (a > b) f->operandStack.pushInt(1);
        else if (a < b) f->operandStack.pushInt(-1);
        else if (a == b) f->operandStack.pushInt(0);
        else f->operandStack.pushInt(nanResult);
    }
};

// --- Single-value Branch (ifeq, ifne, iflt, ifge, ifgt, ifle) ---
template<int(*Cmp)(int,int)>
struct IfBranch : BranchInstructions {
    void execute(runtime::Frame* f) override {
        int val = f->operandStack.popInt();
        if (Cmp(val, 0)) f->branch(offset);
    }
};

// --- Two-value Int Branch (if_icmpeq..if_icmple) ---
template<int(*Cmp)(int,int)>
struct IfCmpBranch : BranchInstructions {
    void execute(runtime::Frame* f) override {
        auto b = f->operandStack.popInt();
        auto a = f->operandStack.popInt();
        if (Cmp(a, b)) f->branch(offset);
    }
};

// --- Two-value Ref Branch (if_acmpeq, if_acmpne) ---
template<bool(*Cmp)(heap::Object*,heap::Object*)>
struct IfCmpRefBranch : BranchInstructions {
    void execute(runtime::Frame* f) override {
        auto b = f->operandStack.popRef();
        auto a = f->operandStack.popRef();
        if (Cmp(a, b)) f->branch(offset);
    }
};

// --- Typed Return (ireturn, lreturn, freturn, dreturn, areturn) ---
template<auto Pop, auto Push>
struct TypedReturn : NoOperandsInstruction {
    void execute(runtime::Frame* f) override {
        runtime::Thread* thread = f->thread;
        runtime::Frame currentFrame = thread->stack->pop();
        runtime::Frame& invokerFrame = thread->stack->top();
        (invokerFrame.operandStack.*Push)((currentFrame.operandStack.*Pop)());
    }
};

// --- Void Return ---
struct ReturnVoid : NoOperandsInstruction {
    void execute(runtime::Frame* f) override {
        f->thread->stack->pop();
    }
};

// ===========================================================================
// Comparison helper functions (for template parameters)
// ===========================================================================

inline int cmp_eq(int a, int b) { return a == b; }
inline int cmp_ne(int a, int b) { return a != b; }
inline int cmp_lt(int a, int b) { return a < b; }
inline int cmp_ge(int a, int b) { return a >= b; }
inline int cmp_gt(int a, int b) { return a > b; }
inline int cmp_le(int a, int b) { return a <= b; }
inline bool cmp_ref_eq(heap::Object* a, heap::Object* b) { return a == b; }
inline bool cmp_ref_ne(heap::Object* a, heap::Object* b) { return a != b; }

// ===========================================================================
// Non-template Classes (complex instructions that don't fit templates)
// ===========================================================================

// --- Constants (bipush, sipush, ldc, ldc_w, ldc2_w) ---

struct bipush : public Instruction {
    int8_t val;
    void fetchOperands(InstructionReader &reader) override;
    void execute(runtime::Frame* frame) override;
    [[nodiscard]] std::string verbose() const override;
};

struct sipush : public Instruction {
    int16_t val;
    void fetchOperands(InstructionReader &reader) override;
    void execute(runtime::Frame* frame) override;
};

struct ldc : public Index8Instruction {
    void execute(runtime::Frame* frame) override;
};

struct ldc_w : public Index16Instruction {
    void execute(runtime::Frame* frame) override;
};

struct ldc2_w : public Index16Instruction {
    void execute(runtime::Frame* frame) override;
};

// --- Array loads with widening (baload, caload, saload) ---

struct baload : public NoOperandsInstruction {
    void execute(runtime::Frame* frame) override;
};

struct caload : public NoOperandsInstruction {
    void execute(runtime::Frame* frame) override;
};

struct saload : public NoOperandsInstruction {
    void execute(runtime::Frame* frame) override;
};

// --- Shift operations (mixed int/long types) ---

struct ishl : public NoOperandsInstruction {
    void execute(runtime::Frame* frame) override;
};

struct lshl : public NoOperandsInstruction {
    void execute(runtime::Frame* frame) override;
};

struct ishr : public NoOperandsInstruction {
    void execute(runtime::Frame* frame) override;
};

struct lshr : public NoOperandsInstruction {
    void execute(runtime::Frame* frame) override;
};

struct iushr : public NoOperandsInstruction {
    void execute(runtime::Frame* frame) override;
};

struct lushr : public NoOperandsInstruction {
    void execute(runtime::Frame* frame) override;
};

// --- Bitwise operations (pop second type, pop first type, push first type) ---

struct iand : public NoOperandsInstruction {
    void execute(runtime::Frame* frame) override;
};

struct land : public NoOperandsInstruction {
    void execute(runtime::Frame* frame) override;
};

struct ior : public NoOperandsInstruction {
    void execute(runtime::Frame* frame) override;
};

struct lor : public NoOperandsInstruction {
    void execute(runtime::Frame* frame) override;
};

struct ixor : public NoOperandsInstruction {
    void execute(runtime::Frame* frame) override;
};

struct lxor : public NoOperandsInstruction {
    void execute(runtime::Frame* frame) override;
};

// --- iinc ---

struct iinc : public Instruction {
    unsigned int index;
    int _const;
    void execute(runtime::Frame* frame) override;
    void fetchOperands(InstructionReader &reader) override;
    [[nodiscard]] std::string verbose() const override;
};

// --- Control flow ---

struct goto_ : public BranchInstructions {
    void execute(runtime::Frame* frame) override;
};

struct jsr : public BranchInstructions {
    void execute(runtime::Frame* frame) override;
};

struct ret : public BranchInstructions {
    void execute(runtime::Frame* frame) override;
};

struct tableswitch : public Instruction {
    int defaultOffset;
    int low;
    int high;
    std::vector<int> jumpOffsets;
    void fetchOperands(InstructionReader &reader) override;
    void execute(runtime::Frame* frame) override;
};

struct lookupswitch : public Instruction {
    int defaultOffsets;
    int nPairs;
    std::vector<int> matchOffsets;
    void fetchOperands(InstructionReader &reader) override;
    void execute(runtime::Frame* frame) override;
};

} // namespace instruction
