//
// Instruction base classes and opcode dispatch table.
// Created by XUranus on 2019/2/1.
//

#include "instruction.h"

#include "instructions.h"
#include "stack.h"
#include "references.h"
#include "extended.h"
#include "reserved.h"

#include "../common/Exception.h"

namespace instruction {

    // =========================================================================
    // Base class implementations
    // =========================================================================

    std::string Instruction::verbose() const {
        return name();
    }

    void NoOperandsInstruction::fetchOperands(InstructionReader &reader) {}

    std::string NoOperandsInstruction::verbose() const {
        return name();
    }

    void BranchInstructions::fetchOperands(InstructionReader &reader) {
        offset = static_cast<int>(reader.readInt16());
    }

    std::string BranchInstructions::verbose() const {
        return name() + "\t\t" + std::to_string(offset);
    }

    void Index8Instruction::fetchOperands(InstructionReader &reader) {
        index = reader.readUint8();
    }

    std::string Index8Instruction::verbose() const {
        return name() + " \t\t" + std::to_string(index);
    }

    void Index16Instruction::fetchOperands(InstructionReader &reader) {
        index = reader.readUint16();
    }

    std::string Index16Instruction::verbose() const {
        return name() + " \t\t" + std::to_string(index);
    }

    // =========================================================================
    // Opcode dispatch table
    // =========================================================================

    using Slots = runtime::Slots;
    using SlotsStack = runtime::SlotsStack;

    // --- Template type aliases ---

    // Constants
    using iconst_m1_t = ConstPush<&SlotsStack::pushInt, int, -1>;
    using iconst_0_t  = ConstPush<&SlotsStack::pushInt, int, 0>;
    using iconst_1_t  = ConstPush<&SlotsStack::pushInt, int, 1>;
    using iconst_2_t  = ConstPush<&SlotsStack::pushInt, int, 2>;
    using iconst_3_t  = ConstPush<&SlotsStack::pushInt, int, 3>;
    using iconst_4_t  = ConstPush<&SlotsStack::pushInt, int, 4>;
    using iconst_5_t  = ConstPush<&SlotsStack::pushInt, int, 5>;
    using lconst_0_t  = ConstPush<&SlotsStack::pushLong, long, 0>;
    using lconst_1_t  = ConstPush<&SlotsStack::pushLong, long, 1>;
    using fconst_0_t  = ConstFPush<&SlotsStack::pushFloat, float>;
    using fconst_1_t  = ConstFPush<&SlotsStack::pushFloat, float>;
    using fconst_2_t  = ConstFPush<&SlotsStack::pushFloat, float>;
    using dconst_0_t  = ConstFPush<&SlotsStack::pushDouble, double>;
    using dconst_1_t  = ConstFPush<&SlotsStack::pushDouble, double>;

    // Indexed loads
    using iload_t  = IndexedLoad<&Slots::intValue,   &SlotsStack::pushInt>;
    using lload_t  = IndexedLoad<&Slots::longValue,  &SlotsStack::pushLong>;
    using fload_t  = IndexedLoad<&Slots::floatValue, &SlotsStack::pushFloat>;
    using dload_t  = IndexedLoad<&Slots::doubleValue,&SlotsStack::pushDouble>;
    using aload_t  = IndexedLoad<&Slots::refValue,   &SlotsStack::pushRef>;

    // Indexed stores
    using istore_t = IndexedStore<&SlotsStack::popInt,   &Slots::setInt>;
    using lstore_t = IndexedStore<&SlotsStack::popLong,  &Slots::setLong>;
    using fstore_t = IndexedStore<&SlotsStack::popFloat, &Slots::setFloat>;
    using dstore_t = IndexedStore<&SlotsStack::popDouble,&Slots::setDouble>;
    using astore_t = IndexedStore<&SlotsStack::popRef,   &Slots::setRef>;

    // Fixed slot loads
    using iload_0_t = FixedSlotLoad<&Slots::intValue,   &SlotsStack::pushInt,   0>;
    using iload_1_t = FixedSlotLoad<&Slots::intValue,   &SlotsStack::pushInt,   1>;
    using iload_2_t = FixedSlotLoad<&Slots::intValue,   &SlotsStack::pushInt,   2>;
    using iload_3_t = FixedSlotLoad<&Slots::intValue,   &SlotsStack::pushInt,   3>;
    using lload_0_t = FixedSlotLoad<&Slots::longValue,  &SlotsStack::pushLong,  0>;
    using lload_1_t = FixedSlotLoad<&Slots::longValue,  &SlotsStack::pushLong,  1>;
    using lload_2_t = FixedSlotLoad<&Slots::longValue,  &SlotsStack::pushLong,  2>;
    using lload_3_t = FixedSlotLoad<&Slots::longValue,  &SlotsStack::pushLong,  3>;
    using fload_0_t = FixedSlotLoad<&Slots::floatValue, &SlotsStack::pushFloat, 0>;
    using fload_1_t = FixedSlotLoad<&Slots::floatValue, &SlotsStack::pushFloat, 1>;
    using fload_2_t = FixedSlotLoad<&Slots::floatValue, &SlotsStack::pushFloat, 2>;
    using fload_3_t = FixedSlotLoad<&Slots::floatValue, &SlotsStack::pushFloat, 3>;
    using dload_0_t = FixedSlotLoad<&Slots::doubleValue,&SlotsStack::pushDouble,0>;
    using dload_1_t = FixedSlotLoad<&Slots::doubleValue,&SlotsStack::pushDouble,1>;
    using dload_2_t = FixedSlotLoad<&Slots::doubleValue,&SlotsStack::pushDouble,2>;
    using dload_3_t = FixedSlotLoad<&Slots::doubleValue,&SlotsStack::pushDouble,3>;
    using aload_0_t = FixedSlotLoad<&Slots::refValue,   &SlotsStack::pushRef,   0>;
    using aload_1_t = FixedSlotLoad<&Slots::refValue,   &SlotsStack::pushRef,   1>;
    using aload_2_t = FixedSlotLoad<&Slots::refValue,   &SlotsStack::pushRef,   2>;
    using aload_3_t = FixedSlotLoad<&Slots::refValue,   &SlotsStack::pushRef,   3>;

    // Fixed slot stores
    using istore_0_t = FixedSlotStore<&SlotsStack::popInt,   &Slots::setInt,   0>;
    using istore_1_t = FixedSlotStore<&SlotsStack::popInt,   &Slots::setInt,   1>;
    using istore_2_t = FixedSlotStore<&SlotsStack::popInt,   &Slots::setInt,   2>;
    using istore_3_t = FixedSlotStore<&SlotsStack::popInt,   &Slots::setInt,   3>;
    using lstore_0_t = FixedSlotStore<&SlotsStack::popLong,  &Slots::setLong,  0>;
    using lstore_1_t = FixedSlotStore<&SlotsStack::popLong,  &Slots::setLong,  1>;
    using lstore_2_t = FixedSlotStore<&SlotsStack::popLong,  &Slots::setLong,  2>;
    using lstore_3_t = FixedSlotStore<&SlotsStack::popLong,  &Slots::setLong,  3>;
    using fstore_0_t = FixedSlotStore<&SlotsStack::popFloat, &Slots::setFloat, 0>;
    using fstore_1_t = FixedSlotStore<&SlotsStack::popFloat, &Slots::setFloat, 1>;
    using fstore_2_t = FixedSlotStore<&SlotsStack::popFloat, &Slots::setFloat, 2>;
    using fstore_3_t = FixedSlotStore<&SlotsStack::popFloat, &Slots::setFloat, 3>;
    using dstore_0_t = FixedSlotStore<&SlotsStack::popDouble,&Slots::setDouble,0>;
    using dstore_1_t = FixedSlotStore<&SlotsStack::popDouble,&Slots::setDouble,1>;
    using dstore_2_t = FixedSlotStore<&SlotsStack::popDouble,&Slots::setDouble,2>;
    using dstore_3_t = FixedSlotStore<&SlotsStack::popDouble,&Slots::setDouble,3>;
    using astore_0_t = FixedSlotStore<&SlotsStack::popRef,   &Slots::setRef,   0>;
    using astore_1_t = FixedSlotStore<&SlotsStack::popRef,   &Slots::setRef,   1>;
    using astore_2_t = FixedSlotStore<&SlotsStack::popRef,   &Slots::setRef,   2>;
    using astore_3_t = FixedSlotStore<&SlotsStack::popRef,   &Slots::setRef,   3>;

    // Array loads (without widening)
    using iaload_t = ArrayLoad<int,             &heap::Object::intArray,         &SlotsStack::pushInt>;
    using laload_t = ArrayLoad<long,            &heap::Object::longArray,        &SlotsStack::pushLong>;
    using faload_t = ArrayLoad<float,           &heap::Object::floatArray,       &SlotsStack::pushFloat>;
    using daload_t = ArrayLoad<double,          &heap::Object::doubleArray,      &SlotsStack::pushDouble>;
    using aaload_t = ArrayLoad<heap::Object*,   &heap::Object::objectRefArray,   &SlotsStack::pushRef>;

    // Array stores
    using iastore_t = ArrayStore<int,            &SlotsStack::popInt,    &heap::Object::intArray>;
    using lastore_t = ArrayStore<long,           &SlotsStack::popLong,   &heap::Object::longArray>;
    using fastore_t = ArrayStore<float,          &SlotsStack::popFloat,  &heap::Object::floatArray>;
    using dastore_t = ArrayStore<double,         &SlotsStack::popDouble, &heap::Object::doubleArray>;
    using aastore_t = ArrayStore<heap::Object*,  &SlotsStack::popRef,    &heap::Object::objectRefArray>;
    using bastore_t = ArrayStore<char,           &SlotsStack::popInt,    &heap::Object::byteArray>;
    using castore_t = ArrayStore<short,          &SlotsStack::popInt,    &heap::Object::charArray>;
    using sastore_t = ArrayStore<short,          &SlotsStack::popInt,    &heap::Object::shortArray>;

    // Binary math
    using iadd_t = BinMath<&SlotsStack::popInt,    &SlotsStack::pushInt,   std::plus<int>>;
    using ladd_t = BinMath<&SlotsStack::popLong,   &SlotsStack::pushLong,  std::plus<long>>;
    using fadd_t = BinMath<&SlotsStack::popFloat,  &SlotsStack::pushFloat, std::plus<float>>;
    using dadd_t = BinMath<&SlotsStack::popDouble, &SlotsStack::pushDouble,std::plus<double>>;
    using isub_t = BinMath<&SlotsStack::popInt,    &SlotsStack::pushInt,   std::minus<int>>;
    using lsub_t = BinMath<&SlotsStack::popLong,   &SlotsStack::pushLong,  std::minus<long>>;
    using fsub_t = BinMath<&SlotsStack::popFloat,  &SlotsStack::pushFloat, std::minus<float>>;
    using dsub_t = BinMath<&SlotsStack::popDouble, &SlotsStack::pushDouble,std::minus<double>>;
    using imul_t = BinMath<&SlotsStack::popInt,    &SlotsStack::pushInt,   std::multiplies<int>>;
    using lmul_t = BinMath<&SlotsStack::popLong,   &SlotsStack::pushLong,  std::multiplies<long>>;
    using fmul_t = BinMath<&SlotsStack::popFloat,  &SlotsStack::pushFloat, std::multiplies<float>>;
    using dmul_t = BinMath<&SlotsStack::popDouble, &SlotsStack::pushDouble,std::multiplies<double>>;

    // Binary math with zero check
    using idiv_t = BinMathChecked<&SlotsStack::popInt,    &SlotsStack::pushInt,   std::divides<int>>;
    using ldiv_t = BinMathChecked<&SlotsStack::popLong,   &SlotsStack::pushLong,  std::divides<long>>;
    using fdiv_t = BinMathChecked<&SlotsStack::popFloat,  &SlotsStack::pushFloat, std::divides<float>>;
    using ddiv_t = BinMathChecked<&SlotsStack::popDouble, &SlotsStack::pushDouble,std::divides<double>>;
    using irem_t = BinMathChecked<&SlotsStack::popInt,    &SlotsStack::pushInt,   std::modulus<int>>;
    using lrem_t = BinMathChecked<&SlotsStack::popLong,   &SlotsStack::pushLong,  std::modulus<long>>;
    using frem_t = BinMathChecked<&SlotsStack::popFloat,  &SlotsStack::pushFloat, FModFloat>;
    using drem_t = BinMathChecked<&SlotsStack::popDouble, &SlotsStack::pushDouble,FModDouble>;

    // Unary math
    using ineg_t = UnaryMath<&SlotsStack::popInt,    &SlotsStack::pushInt,   std::negate<int>>;
    using lneg_t = UnaryMath<&SlotsStack::popLong,   &SlotsStack::pushLong,  std::negate<long>>;
    using fneg_t = UnaryMath<&SlotsStack::popFloat,  &SlotsStack::pushFloat, std::negate<float>>;
    using dneg_t = UnaryMath<&SlotsStack::popDouble, &SlotsStack::pushDouble,std::negate<double>>;

    // Conversions
    using i2l_t = Conversion<&SlotsStack::popInt,    &SlotsStack::pushLong,  long>;
    using i2f_t = Conversion<&SlotsStack::popInt,    &SlotsStack::pushFloat, float>;
    using i2d_t = Conversion<&SlotsStack::popInt,    &SlotsStack::pushDouble,double>;
    using l2i_t = Conversion<&SlotsStack::popLong,   &SlotsStack::pushInt,   int>;
    using l2f_t = Conversion<&SlotsStack::popLong,   &SlotsStack::pushFloat, float>;
    using l2d_t = Conversion<&SlotsStack::popLong,   &SlotsStack::pushDouble,double>;
    using f2i_t = Conversion<&SlotsStack::popFloat,  &SlotsStack::pushInt,   int>;
    using f2l_t = Conversion<&SlotsStack::popFloat,  &SlotsStack::pushLong,  long>;
    using f2d_t = Conversion<&SlotsStack::popFloat,  &SlotsStack::pushDouble,double>;
    using d2i_t = Conversion<&SlotsStack::popDouble, &SlotsStack::pushInt,   int>;
    using d2l_t = Conversion<&SlotsStack::popDouble, &SlotsStack::pushLong,  long>;
    using d2f_t = Conversion<&SlotsStack::popDouble, &SlotsStack::pushFloat, float>;
    using i2b_t = Conversion<&SlotsStack::popInt,    &SlotsStack::pushInt,   unsigned char>;
    using i2c_t = Conversion<&SlotsStack::popInt,    &SlotsStack::pushInt,   char>;
    using i2s_t = Conversion<&SlotsStack::popInt,    &SlotsStack::pushInt,   short>;

    // Comparisons
    using lcmp_t  = CmpPush<&SlotsStack::popLong,   0>;
    using fcmpl_t = CmpPush<&SlotsStack::popFloat,  -1>;
    using fcmpg_t = CmpPush<&SlotsStack::popFloat,   1>;
    using dcmpl_t = CmpPush<&SlotsStack::popDouble, -1>;
    using dcmpg_t = CmpPush<&SlotsStack::popDouble,  1>;

    // Single-value branches
    using ifeq_t = IfBranch<cmp_eq>;
    using ifne_t = IfBranch<cmp_ne>;
    using iflt_t = IfBranch<cmp_lt>;
    using ifge_t = IfBranch<cmp_ge>;
    using ifgt_t = IfBranch<cmp_gt>;
    using ifle_t = IfBranch<cmp_le>;

    // Two-value int branches
    using if_icmpeq_t = IfCmpBranch<cmp_eq>;
    using if_icmpne_t = IfCmpBranch<cmp_ne>;
    using if_icmplt_t = IfCmpBranch<cmp_lt>;
    using if_icmpge_t = IfCmpBranch<cmp_ge>;
    using if_icmpgt_t = IfCmpBranch<cmp_gt>;
    using if_icmple_t = IfCmpBranch<cmp_le>;

    // Two-value ref branches
    using if_acmpeq_t = IfCmpRefBranch<cmp_ref_eq>;
    using if_acmpne_t = IfCmpRefBranch<cmp_ref_ne>;

    // Returns
    using ireturn_t = TypedReturn<&SlotsStack::popInt,    &SlotsStack::pushInt>;
    using lreturn_t = TypedReturn<&SlotsStack::popLong,   &SlotsStack::pushLong>;
    using freturn_t = TypedReturn<&SlotsStack::popFloat,  &SlotsStack::pushFloat>;
    using dreturn_t = TypedReturn<&SlotsStack::popDouble, &SlotsStack::pushDouble>;
    using areturn_t = TypedReturn<&SlotsStack::popRef,    &SlotsStack::pushRef>;

    // =========================================================================
    // Dispatch table (constructor-initialized to avoid designated initializer issues)
    // =========================================================================

    struct OpcodeEntry {
        const char* name;
        std::unique_ptr<Instruction>(*factory)();
    };

    struct OpcodeTable {
        OpcodeEntry entries[256];

        OpcodeTable() {
            // Lambda factory helper
            auto E = [](const char* n, auto factoryFn) -> OpcodeEntry {
                return { n, factoryFn };
            };

            // Constants
            entries[0x00] = E("nop",         []() -> std::unique_ptr<Instruction> { return std::make_unique<Nop>(); });
            entries[0x01] = E("aconst_null", []() -> std::unique_ptr<Instruction> { return std::make_unique<aconst_null>(); });
            entries[0x02] = E("iconst_m1",   []() -> std::unique_ptr<Instruction> { return std::make_unique<iconst_m1_t>(); });
            entries[0x03] = E("iconst_0",    []() -> std::unique_ptr<Instruction> { return std::make_unique<iconst_0_t>(); });
            entries[0x04] = E("iconst_1",    []() -> std::unique_ptr<Instruction> { return std::make_unique<iconst_1_t>(); });
            entries[0x05] = E("iconst_2",    []() -> std::unique_ptr<Instruction> { return std::make_unique<iconst_2_t>(); });
            entries[0x06] = E("iconst_3",    []() -> std::unique_ptr<Instruction> { return std::make_unique<iconst_3_t>(); });
            entries[0x07] = E("iconst_4",    []() -> std::unique_ptr<Instruction> { return std::make_unique<iconst_4_t>(); });
            entries[0x08] = E("iconst_5",    []() -> std::unique_ptr<Instruction> { return std::make_unique<iconst_5_t>(); });
            entries[0x09] = E("lconst_0",    []() -> std::unique_ptr<Instruction> { return std::make_unique<lconst_0_t>(); });
            entries[0x0A] = E("lconst_1",    []() -> std::unique_ptr<Instruction> { return std::make_unique<lconst_1_t>(); });
            entries[0x0B] = E("fconst_0",    []() -> std::unique_ptr<Instruction> { return std::make_unique<fconst_0_t>(0.0f); });
            entries[0x0C] = E("fconst_1",    []() -> std::unique_ptr<Instruction> { return std::make_unique<fconst_1_t>(1.0f); });
            entries[0x0D] = E("fconst_2",    []() -> std::unique_ptr<Instruction> { return std::make_unique<fconst_2_t>(2.0f); });
            entries[0x0E] = E("dconst_0",    []() -> std::unique_ptr<Instruction> { return std::make_unique<dconst_0_t>(0.0); });
            entries[0x0F] = E("dconst_1",    []() -> std::unique_ptr<Instruction> { return std::make_unique<dconst_1_t>(1.0); });
            entries[0x10] = E("bipush",      []() -> std::unique_ptr<Instruction> { return std::make_unique<bipush>(); });
            entries[0x11] = E("sipush",      []() -> std::unique_ptr<Instruction> { return std::make_unique<sipush>(); });
            entries[0x12] = E("ldc",         []() -> std::unique_ptr<Instruction> { return std::make_unique<ldc>(); });
            entries[0x13] = E("ldc_w",       []() -> std::unique_ptr<Instruction> { return std::make_unique<ldc_w>(); });
            entries[0x14] = E("ldc2_w",      []() -> std::unique_ptr<Instruction> { return std::make_unique<ldc2_w>(); });

            // Indexed loads
            entries[0x15] = E("iload",       []() -> std::unique_ptr<Instruction> { return std::make_unique<iload_t>(); });
            entries[0x16] = E("lload",       []() -> std::unique_ptr<Instruction> { return std::make_unique<lload_t>(); });
            entries[0x17] = E("fload",       []() -> std::unique_ptr<Instruction> { return std::make_unique<fload_t>(); });
            entries[0x18] = E("dload",       []() -> std::unique_ptr<Instruction> { return std::make_unique<dload_t>(); });
            entries[0x19] = E("aload",       []() -> std::unique_ptr<Instruction> { return std::make_unique<aload_t>(); });

            // Fixed slot loads
            entries[0x1A] = E("iload_0",     []() -> std::unique_ptr<Instruction> { return std::make_unique<iload_0_t>(); });
            entries[0x1B] = E("iload_1",     []() -> std::unique_ptr<Instruction> { return std::make_unique<iload_1_t>(); });
            entries[0x1C] = E("iload_2",     []() -> std::unique_ptr<Instruction> { return std::make_unique<iload_2_t>(); });
            entries[0x1D] = E("iload_3",     []() -> std::unique_ptr<Instruction> { return std::make_unique<iload_3_t>(); });
            entries[0x1E] = E("lload_0",     []() -> std::unique_ptr<Instruction> { return std::make_unique<lload_0_t>(); });
            entries[0x1F] = E("lload_1",     []() -> std::unique_ptr<Instruction> { return std::make_unique<lload_1_t>(); });
            entries[0x20] = E("lload_2",     []() -> std::unique_ptr<Instruction> { return std::make_unique<lload_2_t>(); });
            entries[0x21] = E("lload_3",     []() -> std::unique_ptr<Instruction> { return std::make_unique<lload_3_t>(); });
            entries[0x22] = E("fload_0",     []() -> std::unique_ptr<Instruction> { return std::make_unique<fload_0_t>(); });
            entries[0x23] = E("fload_1",     []() -> std::unique_ptr<Instruction> { return std::make_unique<fload_1_t>(); });
            entries[0x24] = E("fload_2",     []() -> std::unique_ptr<Instruction> { return std::make_unique<fload_2_t>(); });
            entries[0x25] = E("fload_3",     []() -> std::unique_ptr<Instruction> { return std::make_unique<fload_3_t>(); });
            entries[0x26] = E("dload_0",     []() -> std::unique_ptr<Instruction> { return std::make_unique<dload_0_t>(); });
            entries[0x27] = E("dload_1",     []() -> std::unique_ptr<Instruction> { return std::make_unique<dload_1_t>(); });
            entries[0x28] = E("dload_2",     []() -> std::unique_ptr<Instruction> { return std::make_unique<dload_2_t>(); });
            entries[0x29] = E("dload_3",     []() -> std::unique_ptr<Instruction> { return std::make_unique<dload_3_t>(); });
            entries[0x2A] = E("aload_0",     []() -> std::unique_ptr<Instruction> { return std::make_unique<aload_0_t>(); });
            entries[0x2B] = E("aload_1",     []() -> std::unique_ptr<Instruction> { return std::make_unique<aload_1_t>(); });
            entries[0x2C] = E("aload_2",     []() -> std::unique_ptr<Instruction> { return std::make_unique<aload_2_t>(); });
            entries[0x2D] = E("aload_3",     []() -> std::unique_ptr<Instruction> { return std::make_unique<aload_3_t>(); });

            // Array loads
            entries[0x2E] = E("iaload",      []() -> std::unique_ptr<Instruction> { return std::make_unique<iaload_t>(); });
            entries[0x2F] = E("laload",      []() -> std::unique_ptr<Instruction> { return std::make_unique<laload_t>(); });
            entries[0x30] = E("faload",      []() -> std::unique_ptr<Instruction> { return std::make_unique<faload_t>(); });
            entries[0x31] = E("daload",      []() -> std::unique_ptr<Instruction> { return std::make_unique<daload_t>(); });
            entries[0x32] = E("aaload",      []() -> std::unique_ptr<Instruction> { return std::make_unique<aaload_t>(); });
            entries[0x33] = E("baload",      []() -> std::unique_ptr<Instruction> { return std::make_unique<baload>(); });
            entries[0x34] = E("caload",      []() -> std::unique_ptr<Instruction> { return std::make_unique<caload>(); });
            entries[0x35] = E("saload",      []() -> std::unique_ptr<Instruction> { return std::make_unique<saload>(); });

            // Indexed stores
            entries[0x36] = E("istore",      []() -> std::unique_ptr<Instruction> { return std::make_unique<istore_t>(); });
            entries[0x37] = E("lstore",      []() -> std::unique_ptr<Instruction> { return std::make_unique<lstore_t>(); });
            entries[0x38] = E("fstore",      []() -> std::unique_ptr<Instruction> { return std::make_unique<fstore_t>(); });
            entries[0x39] = E("dstore",      []() -> std::unique_ptr<Instruction> { return std::make_unique<dstore_t>(); });
            entries[0x3A] = E("astore",      []() -> std::unique_ptr<Instruction> { return std::make_unique<astore_t>(); });

            // Fixed slot stores
            entries[0x3B] = E("istore_0",    []() -> std::unique_ptr<Instruction> { return std::make_unique<istore_0_t>(); });
            entries[0x3C] = E("istore_1",    []() -> std::unique_ptr<Instruction> { return std::make_unique<istore_1_t>(); });
            entries[0x3D] = E("istore_2",    []() -> std::unique_ptr<Instruction> { return std::make_unique<istore_2_t>(); });
            entries[0x3E] = E("istore_3",    []() -> std::unique_ptr<Instruction> { return std::make_unique<istore_3_t>(); });
            entries[0x3F] = E("lstore_0",    []() -> std::unique_ptr<Instruction> { return std::make_unique<lstore_0_t>(); });
            entries[0x40] = E("lstore_1",    []() -> std::unique_ptr<Instruction> { return std::make_unique<lstore_1_t>(); });
            entries[0x41] = E("lstore_2",    []() -> std::unique_ptr<Instruction> { return std::make_unique<lstore_2_t>(); });
            entries[0x42] = E("lstore_3",    []() -> std::unique_ptr<Instruction> { return std::make_unique<lstore_3_t>(); });
            entries[0x43] = E("fstore_0",    []() -> std::unique_ptr<Instruction> { return std::make_unique<fstore_0_t>(); });
            entries[0x44] = E("fstore_1",    []() -> std::unique_ptr<Instruction> { return std::make_unique<fstore_1_t>(); });
            entries[0x45] = E("fstore_2",    []() -> std::unique_ptr<Instruction> { return std::make_unique<fstore_2_t>(); });
            entries[0x46] = E("fstore_3",    []() -> std::unique_ptr<Instruction> { return std::make_unique<fstore_3_t>(); });
            entries[0x47] = E("dstore_0",    []() -> std::unique_ptr<Instruction> { return std::make_unique<dstore_0_t>(); });
            entries[0x48] = E("dstore_1",    []() -> std::unique_ptr<Instruction> { return std::make_unique<dstore_1_t>(); });
            entries[0x49] = E("dstore_2",    []() -> std::unique_ptr<Instruction> { return std::make_unique<dstore_2_t>(); });
            entries[0x4A] = E("dstore_3",    []() -> std::unique_ptr<Instruction> { return std::make_unique<dstore_3_t>(); });
            entries[0x4B] = E("astore_0",    []() -> std::unique_ptr<Instruction> { return std::make_unique<astore_0_t>(); });
            entries[0x4C] = E("astore_1",    []() -> std::unique_ptr<Instruction> { return std::make_unique<astore_1_t>(); });
            entries[0x4D] = E("astore_2",    []() -> std::unique_ptr<Instruction> { return std::make_unique<astore_2_t>(); });
            entries[0x4E] = E("astore_3",    []() -> std::unique_ptr<Instruction> { return std::make_unique<astore_3_t>(); });

            // Array stores
            entries[0x4F] = E("iastore",     []() -> std::unique_ptr<Instruction> { return std::make_unique<iastore_t>(); });
            entries[0x50] = E("lastore",     []() -> std::unique_ptr<Instruction> { return std::make_unique<lastore_t>(); });
            entries[0x51] = E("fastore",     []() -> std::unique_ptr<Instruction> { return std::make_unique<fastore_t>(); });
            entries[0x52] = E("dastore",     []() -> std::unique_ptr<Instruction> { return std::make_unique<dastore_t>(); });
            entries[0x53] = E("aastore",     []() -> std::unique_ptr<Instruction> { return std::make_unique<aastore_t>(); });
            entries[0x54] = E("bastore",     []() -> std::unique_ptr<Instruction> { return std::make_unique<bastore_t>(); });
            entries[0x55] = E("castore",     []() -> std::unique_ptr<Instruction> { return std::make_unique<castore_t>(); });
            entries[0x56] = E("sastore",     []() -> std::unique_ptr<Instruction> { return std::make_unique<sastore_t>(); });

            // Stack operations
            entries[0x57] = E("pop",         []() -> std::unique_ptr<Instruction> { return std::make_unique<pop>(); });
            entries[0x58] = E("pop2",        []() -> std::unique_ptr<Instruction> { return std::make_unique<pop2>(); });
            entries[0x59] = E("dup",         []() -> std::unique_ptr<Instruction> { return std::make_unique<dup>(); });
            entries[0x5A] = E("dup_x1",      []() -> std::unique_ptr<Instruction> { return std::make_unique<dup_x1>(); });
            entries[0x5B] = E("dup_x2",      []() -> std::unique_ptr<Instruction> { return std::make_unique<dup_x2>(); });
            entries[0x5C] = E("dup2",        []() -> std::unique_ptr<Instruction> { return std::make_unique<dup2>(); });
            entries[0x5D] = E("dup2_x1",     []() -> std::unique_ptr<Instruction> { return std::make_unique<dup2_x1>(); });
            entries[0x5E] = E("dup2_x2",     []() -> std::unique_ptr<Instruction> { return std::make_unique<dup2_x2>(); });
            entries[0x5F] = E("swap",        []() -> std::unique_ptr<Instruction> { return std::make_unique<swap>(); });

            // Binary math
            entries[0x60] = E("iadd",        []() -> std::unique_ptr<Instruction> { return std::make_unique<iadd_t>(); });
            entries[0x61] = E("ladd",        []() -> std::unique_ptr<Instruction> { return std::make_unique<ladd_t>(); });
            entries[0x62] = E("fadd",        []() -> std::unique_ptr<Instruction> { return std::make_unique<fadd_t>(); });
            entries[0x63] = E("dadd",        []() -> std::unique_ptr<Instruction> { return std::make_unique<dadd_t>(); });
            entries[0x64] = E("isub",        []() -> std::unique_ptr<Instruction> { return std::make_unique<isub_t>(); });
            entries[0x65] = E("lsub",        []() -> std::unique_ptr<Instruction> { return std::make_unique<lsub_t>(); });
            entries[0x66] = E("fsub",        []() -> std::unique_ptr<Instruction> { return std::make_unique<fsub_t>(); });
            entries[0x67] = E("dsub",        []() -> std::unique_ptr<Instruction> { return std::make_unique<dsub_t>(); });
            entries[0x68] = E("imul",        []() -> std::unique_ptr<Instruction> { return std::make_unique<imul_t>(); });
            entries[0x69] = E("lmul",        []() -> std::unique_ptr<Instruction> { return std::make_unique<lmul_t>(); });
            entries[0x6A] = E("fmul",        []() -> std::unique_ptr<Instruction> { return std::make_unique<fmul_t>(); });
            entries[0x6B] = E("dmul",        []() -> std::unique_ptr<Instruction> { return std::make_unique<dmul_t>(); });
            entries[0x6C] = E("idiv",        []() -> std::unique_ptr<Instruction> { return std::make_unique<idiv_t>(); });
            entries[0x6D] = E("ldiv",        []() -> std::unique_ptr<Instruction> { return std::make_unique<ldiv_t>(); });
            entries[0x6E] = E("fdiv",        []() -> std::unique_ptr<Instruction> { return std::make_unique<fdiv_t>(); });
            entries[0x6F] = E("ddiv",        []() -> std::unique_ptr<Instruction> { return std::make_unique<ddiv_t>(); });
            entries[0x70] = E("irem",        []() -> std::unique_ptr<Instruction> { return std::make_unique<irem_t>(); });
            entries[0x71] = E("lrem",        []() -> std::unique_ptr<Instruction> { return std::make_unique<lrem_t>(); });
            entries[0x72] = E("frem",        []() -> std::unique_ptr<Instruction> { return std::make_unique<frem_t>(); });
            entries[0x73] = E("drem",        []() -> std::unique_ptr<Instruction> { return std::make_unique<drem_t>(); });

            // Unary math
            entries[0x74] = E("ineg",        []() -> std::unique_ptr<Instruction> { return std::make_unique<ineg_t>(); });
            entries[0x75] = E("lneg",        []() -> std::unique_ptr<Instruction> { return std::make_unique<lneg_t>(); });
            entries[0x76] = E("fneg",        []() -> std::unique_ptr<Instruction> { return std::make_unique<fneg_t>(); });
            entries[0x77] = E("dneg",        []() -> std::unique_ptr<Instruction> { return std::make_unique<dneg_t>(); });

            // Shifts and bitwise (non-template)
            entries[0x78] = E("ishl",        []() -> std::unique_ptr<Instruction> { return std::make_unique<ishl>(); });
            entries[0x79] = E("lshl",        []() -> std::unique_ptr<Instruction> { return std::make_unique<lshl>(); });
            entries[0x7A] = E("ishr",        []() -> std::unique_ptr<Instruction> { return std::make_unique<ishr>(); });
            entries[0x7B] = E("lshr",        []() -> std::unique_ptr<Instruction> { return std::make_unique<lshr>(); });
            entries[0x7C] = E("iushr",       []() -> std::unique_ptr<Instruction> { return std::make_unique<iushr>(); });
            entries[0x7D] = E("lushr",       []() -> std::unique_ptr<Instruction> { return std::make_unique<lushr>(); });
            entries[0x7E] = E("iand",        []() -> std::unique_ptr<Instruction> { return std::make_unique<iand>(); });
            entries[0x7F] = E("land",        []() -> std::unique_ptr<Instruction> { return std::make_unique<land>(); });
            entries[0x80] = E("ior",         []() -> std::unique_ptr<Instruction> { return std::make_unique<ior>(); });
            entries[0x81] = E("lor",         []() -> std::unique_ptr<Instruction> { return std::make_unique<lor>(); });
            entries[0x82] = E("ixor",        []() -> std::unique_ptr<Instruction> { return std::make_unique<ixor>(); });
            entries[0x83] = E("lxor",        []() -> std::unique_ptr<Instruction> { return std::make_unique<lxor>(); });
            entries[0x84] = E("iinc",        []() -> std::unique_ptr<Instruction> { return std::make_unique<iinc>(); });

            // Conversions
            entries[0x85] = E("i2l",         []() -> std::unique_ptr<Instruction> { return std::make_unique<i2l_t>(); });
            entries[0x86] = E("i2f",         []() -> std::unique_ptr<Instruction> { return std::make_unique<i2f_t>(); });
            entries[0x87] = E("i2d",         []() -> std::unique_ptr<Instruction> { return std::make_unique<i2d_t>(); });
            entries[0x88] = E("l2i",         []() -> std::unique_ptr<Instruction> { return std::make_unique<l2i_t>(); });
            entries[0x89] = E("l2f",         []() -> std::unique_ptr<Instruction> { return std::make_unique<l2f_t>(); });
            entries[0x8A] = E("l2d",         []() -> std::unique_ptr<Instruction> { return std::make_unique<l2d_t>(); });
            entries[0x8B] = E("f2i",         []() -> std::unique_ptr<Instruction> { return std::make_unique<f2i_t>(); });
            entries[0x8C] = E("f2l",         []() -> std::unique_ptr<Instruction> { return std::make_unique<f2l_t>(); });
            entries[0x8D] = E("f2d",         []() -> std::unique_ptr<Instruction> { return std::make_unique<f2d_t>(); });
            entries[0x8E] = E("d2i",         []() -> std::unique_ptr<Instruction> { return std::make_unique<d2i_t>(); });
            entries[0x8F] = E("d2l",         []() -> std::unique_ptr<Instruction> { return std::make_unique<d2l_t>(); });
            entries[0x90] = E("d2f",         []() -> std::unique_ptr<Instruction> { return std::make_unique<d2f_t>(); });
            entries[0x91] = E("i2b",         []() -> std::unique_ptr<Instruction> { return std::make_unique<i2b_t>(); });
            entries[0x92] = E("i2c",         []() -> std::unique_ptr<Instruction> { return std::make_unique<i2c_t>(); });
            entries[0x93] = E("i2s",         []() -> std::unique_ptr<Instruction> { return std::make_unique<i2s_t>(); });

            // Comparisons
            entries[0x94] = E("lcmp",        []() -> std::unique_ptr<Instruction> { return std::make_unique<lcmp_t>(); });
            entries[0x95] = E("fcmpl",       []() -> std::unique_ptr<Instruction> { return std::make_unique<fcmpl_t>(); });
            entries[0x96] = E("fcmpg",       []() -> std::unique_ptr<Instruction> { return std::make_unique<fcmpg_t>(); });
            entries[0x97] = E("dcmpl",       []() -> std::unique_ptr<Instruction> { return std::make_unique<dcmpl_t>(); });
            entries[0x98] = E("dcmpg",       []() -> std::unique_ptr<Instruction> { return std::make_unique<dcmpg_t>(); });

            // Single-value branches
            entries[0x99] = E("ifeq",        []() -> std::unique_ptr<Instruction> { return std::make_unique<ifeq_t>(); });
            entries[0x9A] = E("ifne",        []() -> std::unique_ptr<Instruction> { return std::make_unique<ifne_t>(); });
            entries[0x9B] = E("iflt",        []() -> std::unique_ptr<Instruction> { return std::make_unique<iflt_t>(); });
            entries[0x9C] = E("ifge",        []() -> std::unique_ptr<Instruction> { return std::make_unique<ifge_t>(); });
            entries[0x9D] = E("ifgt",        []() -> std::unique_ptr<Instruction> { return std::make_unique<ifgt_t>(); });
            entries[0x9E] = E("ifle",        []() -> std::unique_ptr<Instruction> { return std::make_unique<ifle_t>(); });

            // Two-value branches
            entries[0x9F] = E("if_icmpeq",   []() -> std::unique_ptr<Instruction> { return std::make_unique<if_icmpeq_t>(); });
            entries[0xA0] = E("if_icmpne",   []() -> std::unique_ptr<Instruction> { return std::make_unique<if_icmpne_t>(); });
            entries[0xA1] = E("if_icmplt",   []() -> std::unique_ptr<Instruction> { return std::make_unique<if_icmplt_t>(); });
            entries[0xA2] = E("if_icmpge",   []() -> std::unique_ptr<Instruction> { return std::make_unique<if_icmpge_t>(); });
            entries[0xA3] = E("if_icmpgt",   []() -> std::unique_ptr<Instruction> { return std::make_unique<if_icmpgt_t>(); });
            entries[0xA4] = E("if_icmple",   []() -> std::unique_ptr<Instruction> { return std::make_unique<if_icmple_t>(); });
            entries[0xA5] = E("if_acmpeq",   []() -> std::unique_ptr<Instruction> { return std::make_unique<if_acmpeq_t>(); });
            entries[0xA6] = E("if_acmpne",   []() -> std::unique_ptr<Instruction> { return std::make_unique<if_acmpne_t>(); });

            // Control flow
            entries[0xA7] = E("goto",        []() -> std::unique_ptr<Instruction> { return std::make_unique<goto_>(); });
            entries[0xA8] = E("jsr",         []() -> std::unique_ptr<Instruction> { return std::make_unique<jsr>(); });
            entries[0xA9] = E("ret",         []() -> std::unique_ptr<Instruction> { return std::make_unique<ret>(); });
            entries[0xAA] = E("tableswitch", []() -> std::unique_ptr<Instruction> { return std::make_unique<tableswitch>(); });
            entries[0xAB] = E("lookupswitch",[]() -> std::unique_ptr<Instruction> { return std::make_unique<lookupswitch>(); });

            // Returns
            entries[0xAC] = E("ireturn",     []() -> std::unique_ptr<Instruction> { return std::make_unique<ireturn_t>(); });
            entries[0xAD] = E("lreturn",     []() -> std::unique_ptr<Instruction> { return std::make_unique<lreturn_t>(); });
            entries[0xAE] = E("freturn",     []() -> std::unique_ptr<Instruction> { return std::make_unique<freturn_t>(); });
            entries[0xAF] = E("dreturn",     []() -> std::unique_ptr<Instruction> { return std::make_unique<dreturn_t>(); });
            entries[0xB0] = E("areturn",     []() -> std::unique_ptr<Instruction> { return std::make_unique<areturn_t>(); });
            entries[0xB1] = E("return",      []() -> std::unique_ptr<Instruction> { return std::make_unique<ReturnVoid>(); });

            // References
            entries[0xB2] = E("getstatic",       []() -> std::unique_ptr<Instruction> { return std::make_unique<getstatic>(); });
            entries[0xB3] = E("putstatic",       []() -> std::unique_ptr<Instruction> { return std::make_unique<putstatic>(); });
            entries[0xB4] = E("getfield",        []() -> std::unique_ptr<Instruction> { return std::make_unique<getfield>(); });
            entries[0xB5] = E("putfield",        []() -> std::unique_ptr<Instruction> { return std::make_unique<putfield>(); });
            entries[0xB6] = E("invokevirtual",   []() -> std::unique_ptr<Instruction> { return std::make_unique<invokevirtual>(); });
            entries[0xB7] = E("invokespecial",   []() -> std::unique_ptr<Instruction> { return std::make_unique<invokespecial>(); });
            entries[0xB8] = E("invokestatic",    []() -> std::unique_ptr<Instruction> { return std::make_unique<invokestatic>(); });
            entries[0xB9] = E("invokeinterface", []() -> std::unique_ptr<Instruction> { return std::make_unique<invokeinterface>(); });
            entries[0xBA] = E("invokedynamic",   []() -> std::unique_ptr<Instruction> { return std::make_unique<invokedynamic>(); });
            entries[0xBB] = E("new",             []() -> std::unique_ptr<Instruction> { return std::make_unique<new_>(); });
            entries[0xBC] = E("newarray",        []() -> std::unique_ptr<Instruction> { return std::make_unique<newarray>(); });
            entries[0xBD] = E("anewarray",       []() -> std::unique_ptr<Instruction> { return std::make_unique<anewarray>(); });
            entries[0xBE] = E("arraylength",     []() -> std::unique_ptr<Instruction> { return std::make_unique<arraylength>(); });
            entries[0xBF] = E("athrow",          []() -> std::unique_ptr<Instruction> { return std::make_unique<athrow>(); });
            entries[0xC0] = E("checkcast",       []() -> std::unique_ptr<Instruction> { return std::make_unique<checkcast>(); });
            entries[0xC1] = E("instanceof",      []() -> std::unique_ptr<Instruction> { return std::make_unique<instanceof>(); });
            entries[0xC2] = E("monitorenter",    []() -> std::unique_ptr<Instruction> { return std::make_unique<monitorenter>(); });
            entries[0xC3] = E("monitiorexit",    []() -> std::unique_ptr<Instruction> { return std::make_unique<monitiorexit>(); });

            // Extended
            entries[0xC4] = E("wide",            []() -> std::unique_ptr<Instruction> { return std::make_unique<wide>(); });
            entries[0xC5] = E("multianewarray",  []() -> std::unique_ptr<Instruction> { return std::make_unique<multianewarray>(); });
            entries[0xC6] = E("ifnull",          []() -> std::unique_ptr<Instruction> { return std::make_unique<ifnull>(); });
            entries[0xC7] = E("ifnonnull",       []() -> std::unique_ptr<Instruction> { return std::make_unique<ifnonnull>(); });
            entries[0xC8] = E("goto_w",          []() -> std::unique_ptr<Instruction> { return std::make_unique<goto_w>(); });
            entries[0xC9] = E("jsr_w",           []() -> std::unique_ptr<Instruction> { return std::make_unique<jsr_w>(); });

            // Reserved
            entries[0xCA] = E("breakpoint",      []() -> std::unique_ptr<Instruction> { return std::make_unique<breakpoint>(); });
            entries[0xFE] = E("impdep1",         []() -> std::unique_ptr<Instruction> { return std::make_unique<impdep1>(); });
            entries[0xFF] = E("impdep2",         []() -> std::unique_ptr<Instruction> { return std::make_unique<impdep2>(); });
        }
    };

    static const OpcodeTable opcodeTable;

    // =========================================================================
    // Public API
    // =========================================================================

    std::string Instruction::name() const {
        if (opcodeTable.entries[opCode].name) {
            return opcodeTable.entries[opCode].name;
        }
        exception::panic("no such instruction, opcode = " + std::to_string(opCode));
        return "";
    }

    std::unique_ptr<Instruction> create(u1 _opCode) {
        if (opcodeTable.entries[_opCode].factory) {
            auto ins = opcodeTable.entries[_opCode].factory();
            ins->opCode = _opCode;
            return ins;
        }
        exception::panic("no such op code: " + std::to_string(_opCode));
        return nullptr;
    }

}
