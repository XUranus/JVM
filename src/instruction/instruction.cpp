//
// Created by XUranus on 2019/2/1.
//

#include "instruction.h"

#include "constants.h"
#include "loads.h"
#include "stores.h"
#include "stack.h"
#include "math.h"
#include "conversions.h"
#include "comparisons.h"
#include "control.h"
#include "references.h"
#include "extended.h"
#include "reserved.h"


#include "../common/Exception.h"



namespace instruction {

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


    std::string Instruction::name() const {
        switch (opCode) {
            case 0x00: return "nop";
            case 0x01: return "aconst_null";
            case 0x02: return "iconst_m1";
            case 0x03: return "iconst_0";
            case 0x04: return "iconst_1";
            case 0x05: return "iconst_2";
            case 0x06: return "iconst_3";
            case 0x07: return "iconst_4";
            case 0x08: return "iconst_5";
            case 0x09: return "lconst_0";
            case 0x0A: return "lconst_1";
            case 0x0B: return "fconst_0";
            case 0x0C: return "fconst_1";
            case 0x0D: return "fconst_2";
            case 0x0E: return "dconst_0";
            case 0x0F: return "dconst_1";
            case 0x10: return "bipush";
            case 0x11: return "sipush";
            case 0x12: return "ldc";
            case 0x13: return "ldc_w";
            case 0x14: return "ldc2_w";
            case 0x15: return "iload";
            case 0x16: return "lload";
            case 0x17: return "fload";
            case 0x18: return "dload";
            case 0x19: return "aload";
            case 0x1A: return "iload_0";
            case 0x1B: return "iload_1";
            case 0x1C: return "iload_2";
            case 0x1D: return "iload_3";
            case 0x1E: return "lload_0";
            case 0x1F: return "lload_1";
            case 0x20: return "lload_2";
            case 0x21: return "lload_3";
            case 0x22: return "fload_0";
            case 0x23: return "fload_1";
            case 0x24: return "fload_2";
            case 0x25: return "fload_3";
            case 0x26: return "dload_0";
            case 0x27: return "dload_1";
            case 0x28: return "dload_2";
            case 0x29: return "dload_3";
            case 0x2A: return "aload_0";
            case 0x2B: return "aload_1";
            case 0x2C: return "aload_2";
            case 0x2D: return "aload_3";
            case 0x2E: return "iaload";
            case 0x2F: return "laload";
            case 0x30: return "faload";
            case 0x31: return "daload";
            case 0x32: return "aaload";
            case 0x33: return "baload";
            case 0x34: return "caload";
            case 0x35: return "saload";
            case 0x36: return "istore";
            case 0x37: return "lstore";
            case 0x38: return "fstore";
            case 0x39: return "dstore";
            case 0x3A: return "astore";
            case 0x3B: return "istore_0";
            case 0x3C: return "istore_1";
            case 0x3D: return "istore_2";
            case 0x3E: return "istore_3";
            case 0x3F: return "lstore_0";
            case 0x40: return "lstore_1";
            case 0x41: return "lstore_2";
            case 0x42: return "lstore_3";
            case 0x43: return "fstore_0";
            case 0x44: return "fstore_1";
            case 0x45: return "fstore_2";
            case 0x46: return "fstore_3";
            case 0x47: return "dstore_0";
            case 0x48: return "dstore_1";
            case 0x49: return "dstore_2";
            case 0x4A: return "dstore_3";
            case 0x4B: return "astore_0";
            case 0x4C: return "astore_1";
            case 0x4D: return "astore_2";
            case 0x4E: return "astore_3";
            case 0x4F: return "iastore";
            case 0x50: return "lastore";
            case 0x51: return "fastore";
            case 0x52: return "dastore";
            case 0x53: return "aastore";
            case 0x54: return "bastore";
            case 0x55: return "castore";
            case 0x56: return "sastore";
            case 0x57: return "pop";
            case 0x58: return "pop2";
            case 0x59: return "dup";
            case 0x5A: return "dup_x1";
            case 0x5B: return "dup_x2";
            case 0x5C: return "dup2";
            case 0x5D: return "dup2_x1";
            case 0x5E: return "dup2_x2";
            case 0x5F: return "swap";
            case 0x60: return "iadd";
            case 0x61: return "ladd";
            case 0x62: return "fadd";
            case 0x63: return "dadd";
            case 0x64: return "isub";
            case 0x65: return "lsub";
            case 0x66: return "fsub";
            case 0x67: return "dsub";
            case 0x68: return "imul";
            case 0x69: return "lmul";
            case 0x6A: return "fmul";
            case 0x6B: return "dmul";
            case 0x6C: return "idiv";
            case 0x6D: return "ldiv";
            case 0x6E: return "fdiv";
            case 0x6F: return "ddiv";
            case 0x70: return "irem";
            case 0x71: return "lrem";
            case 0x72: return "frem";
            case 0x73: return "drem";
            case 0x74: return "ineg";
            case 0x75: return "lneg";
            case 0x76: return "fneg";
            case 0x77: return "dneg";
            case 0x78: return "ishl";
            case 0x79: return "lshl";
            case 0x7A: return "ishr";
            case 0x7B: return "lshr";
            case 0x7C: return "iushr";
            case 0x7D: return "lushr";
            case 0x7E: return "iand";
            case 0x7F: return "land";
            case 0x80: return "ior";
            case 0x81: return "lor";
            case 0x82: return "ixor";
            case 0x83: return "lxor";
            case 0x84: return "iinc";
            case 0x85: return "i2l";
            case 0x86: return "i2f";
            case 0x87: return "i2d";
            case 0x88: return "l2i";
            case 0x89: return "l2f";
            case 0x8A: return "l2d";
            case 0x8B: return "f2i";
            case 0x8C: return "f2l";
            case 0x8D: return "f2d";
            case 0x8E: return "d2i";
            case 0x8F: return "d2l";
            case 0x90: return "d2f";
            case 0x91: return "i2b";
            case 0x92: return "i2c";
            case 0x93: return "i2s";
            case 0x94: return "lcmp";
            case 0x95: return "fcmpl";
            case 0x96: return "fcmpg";
            case 0x97: return "dcmpl";
            case 0x98: return "dcmpg";
            case 0x99: return "ifeq";
            case 0x9A: return "ifne";
            case 0x9B: return "iflt";
            case 0x9C: return "ifge";
            case 0x9D: return "ifgt";
            case 0x9E: return "ifle";
            case 0x9F: return "if_icmpeq";
            case 0xA0: return "if_icmpne";
            case 0xA1: return "if_icmplt";
            case 0xA2: return "if_icmpge";
            case 0xA3: return "if_icmpgt";
            case 0xA4: return "if_icmple";
            case 0xA5: return "if_acmpeq";
            case 0xA6: return "if_acmpne";
            case 0xA7: return "goto";
            case 0xA8: return "jsr";
            case 0xA9: return "ret";
            case 0xAA: return "tableswitch";
            case 0xAB: return "lookupswitch";
            case 0xAC: return "ireturn";
            case 0xAD: return "lreturn";
            case 0xAE: return "freturn";
            case 0xAF: return "dreturn";
            case 0xB0: return "areturn";
            case 0xB1: return "return";
            case 0xB2: return "getstatic";
            case 0xB3: return "putstatic";
            case 0xB4: return "getfield";
            case 0xB5: return "putfield";
            case 0xB6: return "invokevirtual";
            case 0xB7: return "invokespecial";
            case 0xB8: return "invokestatic";
            case 0xB9: return "invokeinterface";
            case 0xBB: return "new";
            case 0xBC: return "newarray";
            case 0xBD: return "anewarray";
            case 0xBE: return "arraylength";
            case 0xBF: return "athrow";
            case 0xC0: return "checkcast";
            case 0xC1: return "instanceof";
            case 0xC2: return "monitorenter";
            case 0xC3: return "monitiorexit";
            case 0xC4: return "wide";
            case 0xC5: return "multianewarray";
            case 0xC6: return "ifnull";
            case 0xC7: return "ifnonnull";
            case 0xC8: return "goto_w";
            case 0xC9: return "jsr_w";
            case 0xCA: return "breakpoint";
            case 0xFE: return "impdep1";
            case 0xFF: return "impdep2";
            default:{
                exception::panic("no such instruction, opcode = " + std::to_string(opCode));
            }
            return "";
        }
    }

    std::unique_ptr<Instruction> create(u1 _opCode) {
        std::unique_ptr<Instruction> ins;
        switch (_opCode) {
            case 0x00:{ ins = std::make_unique<nop>();ins->opCode = _opCode;break;}
            case 0x01:{ ins = std::make_unique<aconst_null>();ins->opCode = _opCode;break;}
            case 0x02:{ ins = std::make_unique<iconst_m1>();ins->opCode = _opCode;break;}
            case 0x03:{ ins = std::make_unique<iconst_0>();ins->opCode = _opCode;break;}
            case 0x04:{ ins = std::make_unique<iconst_1>();ins->opCode = _opCode;break;}
            case 0x05:{ ins = std::make_unique<iconst_2>();ins->opCode = _opCode;break;}
            case 0x06:{ ins = std::make_unique<iconst_3>();ins->opCode = _opCode;break;}
            case 0x07:{ ins = std::make_unique<iconst_4>();ins->opCode = _opCode;break;}
            case 0x08:{ ins = std::make_unique<iconst_5>();ins->opCode = _opCode;break;}
            case 0x09:{ ins = std::make_unique<lconst_0>();ins->opCode = _opCode;break;}
            case 0x0A:{ ins = std::make_unique<lconst_1>();ins->opCode = _opCode;break;}
            case 0x0B:{ ins = std::make_unique<fconst_0>();ins->opCode = _opCode;break;}
            case 0x0C:{ ins = std::make_unique<fconst_1>();ins->opCode = _opCode;break;}
            case 0x0D:{ ins = std::make_unique<fconst_2>();ins->opCode = _opCode;break;}
            case 0x0E:{ ins = std::make_unique<dconst_0>();ins->opCode = _opCode;break;}
            case 0x0F:{ ins = std::make_unique<dconst_1>();ins->opCode = _opCode;break;}
            case 0x10:{ ins = std::make_unique<bipush>();ins->opCode = _opCode;break;}
            case 0x11:{ ins = std::make_unique<sipush>();ins->opCode = _opCode;break;}
            case 0x12:{ ins = std::make_unique<ldc>();ins->opCode = _opCode;break;}
            case 0x13:{ ins = std::make_unique<ldc_w>();ins->opCode = _opCode;break;}
            case 0x14:{ ins = std::make_unique<ldc2_w>();ins->opCode = _opCode;break;}
            case 0x15:{ ins = std::make_unique<iload>();ins->opCode = _opCode;break;}
            case 0x16:{ ins = std::make_unique<lload>();ins->opCode = _opCode;break;}
            case 0x17:{ ins = std::make_unique<fload>();ins->opCode = _opCode;break;}
            case 0x18:{ ins = std::make_unique<dload>();ins->opCode = _opCode;break;}
            case 0x19:{ ins = std::make_unique<aload>();ins->opCode = _opCode;break;}
            case 0x1A:{ ins = std::make_unique<iload_0>();ins->opCode = _opCode;break;}
            case 0x1B:{ ins = std::make_unique<iload_1>();ins->opCode = _opCode;break;}
            case 0x1C:{ ins = std::make_unique<iload_2>();ins->opCode = _opCode;break;}
            case 0x1D:{ ins = std::make_unique<iload_3>();ins->opCode = _opCode;break;}
            case 0x1E:{ ins = std::make_unique<lload_0>();ins->opCode = _opCode;break;}
            case 0x1F:{ ins = std::make_unique<lload_1>();ins->opCode = _opCode;break;}
            case 0x20:{ ins = std::make_unique<lload_2>();ins->opCode = _opCode;break;}
            case 0x21:{ ins = std::make_unique<lload_3>();ins->opCode = _opCode;break;}
            case 0x22:{ ins = std::make_unique<fload_0>();ins->opCode = _opCode;break;}
            case 0x23:{ ins = std::make_unique<fload_1>();ins->opCode = _opCode;break;}
            case 0x24:{ ins = std::make_unique<fload_2>();ins->opCode = _opCode;break;}
            case 0x25:{ ins = std::make_unique<fload_3>();ins->opCode = _opCode;break;}
            case 0x26:{ ins = std::make_unique<dload_0>();ins->opCode = _opCode;break;}
            case 0x27:{ ins = std::make_unique<dload_1>();ins->opCode = _opCode;break;}
            case 0x28:{ ins = std::make_unique<dload_2>();ins->opCode = _opCode;break;}
            case 0x29:{ ins = std::make_unique<dload_3>();ins->opCode = _opCode;break;}
            case 0x2A:{ ins = std::make_unique<aload_0>();ins->opCode = _opCode;break;}
            case 0x2B:{ ins = std::make_unique<aload_1>();ins->opCode = _opCode;break;}
            case 0x2C:{ ins = std::make_unique<aload_2>();ins->opCode = _opCode;break;}
            case 0x2D:{ ins = std::make_unique<aload_3>();ins->opCode = _opCode;break;}
            case 0x2E:{ ins = std::make_unique<iaload>();ins->opCode = _opCode;break;}
            case 0x2F:{ ins = std::make_unique<laload>();ins->opCode = _opCode;break;}
            case 0x30:{ ins = std::make_unique<faload>();ins->opCode = _opCode;break;}
            case 0x31:{ ins = std::make_unique<daload>();ins->opCode = _opCode;break;}
            case 0x32:{ ins = std::make_unique<aaload>();ins->opCode = _opCode;break;}
            case 0x33:{ ins = std::make_unique<baload>();ins->opCode = _opCode;break;}
            case 0x34:{ ins = std::make_unique<caload>();ins->opCode = _opCode;break;}
            case 0x35:{ ins = std::make_unique<saload>();ins->opCode = _opCode;break;}
            case 0x36:{ ins = std::make_unique<istore>();ins->opCode = _opCode;break;}
            case 0x37:{ ins = std::make_unique<lstore>();ins->opCode = _opCode;break;}
            case 0x38:{ ins = std::make_unique<fstore>();ins->opCode = _opCode;break;}
            case 0x39:{ ins = std::make_unique<dstore>();ins->opCode = _opCode;break;}
            case 0x3A:{ ins = std::make_unique<astore>();ins->opCode = _opCode;break;}
            case 0x3B:{ ins = std::make_unique<istore_0>();ins->opCode = _opCode;break;}
            case 0x3C:{ ins = std::make_unique<istore_1>();ins->opCode = _opCode;break;}
            case 0x3D:{ ins = std::make_unique<istore_2>();ins->opCode = _opCode;break;}
            case 0x3E:{ ins = std::make_unique<istore_3>();ins->opCode = _opCode;break;}
            case 0x3F:{ ins = std::make_unique<lstore_0>();ins->opCode = _opCode;break;}
            case 0x40:{ ins = std::make_unique<lstore_1>();ins->opCode = _opCode;break;}
            case 0x41:{ ins = std::make_unique<lstore_2>();ins->opCode = _opCode;break;}
            case 0x42:{ ins = std::make_unique<lstore_3>();ins->opCode = _opCode;break;}
            case 0x43:{ ins = std::make_unique<fstore_0>();ins->opCode = _opCode;break;}
            case 0x44:{ ins = std::make_unique<fstore_1>();ins->opCode = _opCode;break;}
            case 0x45:{ ins = std::make_unique<fstore_2>();ins->opCode = _opCode;break;}
            case 0x46:{ ins = std::make_unique<fstore_3>();ins->opCode = _opCode;break;}
            case 0x47:{ ins = std::make_unique<dstore_0>();ins->opCode = _opCode;break;}
            case 0x48:{ ins = std::make_unique<dstore_1>();ins->opCode = _opCode;break;}
            case 0x49:{ ins = std::make_unique<dstore_2>();ins->opCode = _opCode;break;}
            case 0x4A:{ ins = std::make_unique<dstore_3>();ins->opCode = _opCode;break;}
            case 0x4B:{ ins = std::make_unique<astore_0>();ins->opCode = _opCode;break;}
            case 0x4C:{ ins = std::make_unique<astore_1>();ins->opCode = _opCode;break;}
            case 0x4D:{ ins = std::make_unique<astore_2>();ins->opCode = _opCode;break;}
            case 0x4E:{ ins = std::make_unique<astore_3>();ins->opCode = _opCode;break;}
            case 0x4F:{ ins = std::make_unique<iastore>();ins->opCode = _opCode;break;}
            case 0x50:{ ins = std::make_unique<lastore>();ins->opCode = _opCode;break;}
            case 0x51:{ ins = std::make_unique<fastore>();ins->opCode = _opCode;break;}
            case 0x52:{ ins = std::make_unique<dastore>();ins->opCode = _opCode;break;}
            case 0x53:{ ins = std::make_unique<aastore>();ins->opCode = _opCode;break;}
            case 0x54:{ ins = std::make_unique<bastore>();ins->opCode = _opCode;break;}
            case 0x55:{ ins = std::make_unique<castore>();ins->opCode = _opCode;break;}
            case 0x56:{ ins = std::make_unique<sastore>();ins->opCode = _opCode;break;}
            case 0x57:{ ins = std::make_unique<pop>();ins->opCode = _opCode;break;}
            case 0x58:{ ins = std::make_unique<pop2>();ins->opCode = _opCode;break;}
            case 0x59:{ ins = std::make_unique<dup>();ins->opCode = _opCode;break;}
            case 0x5A:{ ins = std::make_unique<dup_x1>();ins->opCode = _opCode;break;}
            case 0x5B:{ ins = std::make_unique<dup_x2>();ins->opCode = _opCode;break;}
            case 0x5C:{ ins = std::make_unique<dup2>();ins->opCode = _opCode;break;}
            case 0x5D:{ ins = std::make_unique<dup2_x1>();ins->opCode = _opCode;break;}
            case 0x5E:{ ins = std::make_unique<dup2_x2>();ins->opCode = _opCode;break;}
            case 0x5F:{ ins = std::make_unique<swap>();ins->opCode = _opCode;break;}
            case 0x60:{ ins = std::make_unique<iadd>();ins->opCode = _opCode;break;}
            case 0x61:{ ins = std::make_unique<ladd>();ins->opCode = _opCode;break;}
            case 0x62:{ ins = std::make_unique<fadd>();ins->opCode = _opCode;break;}
            case 0x63:{ ins = std::make_unique<dadd>();ins->opCode = _opCode;break;}
            case 0x64:{ ins = std::make_unique<isub>();ins->opCode = _opCode;break;}
            case 0x65:{ ins = std::make_unique<lsub>();ins->opCode = _opCode;break;}
            case 0x66:{ ins = std::make_unique<fsub>();ins->opCode = _opCode;break;}
            case 0x67:{ ins = std::make_unique<dsub>();ins->opCode = _opCode;break;}
            case 0x68:{ ins = std::make_unique<imul>();ins->opCode = _opCode;break;}
            case 0x69:{ ins = std::make_unique<lmul>();ins->opCode = _opCode;break;}
            case 0x6A:{ ins = std::make_unique<fmul>();ins->opCode = _opCode;break;}
            case 0x6B:{ ins = std::make_unique<dmul>();ins->opCode = _opCode;break;}
            case 0x6C:{ ins = std::make_unique<idiv>();ins->opCode = _opCode;break;}
            case 0x6D:{ ins = std::make_unique<ldiv_>();ins->opCode = _opCode;break;}
            case 0x6E:{ ins = std::make_unique<fdiv>();ins->opCode = _opCode;break;}
            case 0x6F:{ ins = std::make_unique<ddiv>();ins->opCode = _opCode;break;}
            case 0x70:{ ins = std::make_unique<irem>();ins->opCode = _opCode;break;}
            case 0x71:{ ins = std::make_unique<lrem>();ins->opCode = _opCode;break;}
            case 0x72:{ ins = std::make_unique<frem>();ins->opCode = _opCode;break;}
            case 0x73:{ ins = std::make_unique<drem>();ins->opCode = _opCode;break;}
            case 0x74:{ ins = std::make_unique<ineg>();ins->opCode = _opCode;break;}
            case 0x75:{ ins = std::make_unique<lneg>();ins->opCode = _opCode;break;}
            case 0x76:{ ins = std::make_unique<fneg>();ins->opCode = _opCode;break;}
            case 0x77:{ ins = std::make_unique<dneg>();ins->opCode = _opCode;break;}
            case 0x78:{ ins = std::make_unique<ishl>();ins->opCode = _opCode;break;}
            case 0x79:{ ins = std::make_unique<lshl>();ins->opCode = _opCode;break;}
            case 0x7A:{ ins = std::make_unique<ishr>();ins->opCode = _opCode;break;}
            case 0x7B:{ ins = std::make_unique<lshr>();ins->opCode = _opCode;break;}
            case 0x7C:{ ins = std::make_unique<iushr>();ins->opCode = _opCode;break;}
            case 0x7D:{ ins = std::make_unique<lushr>();ins->opCode = _opCode;break;}
            case 0x7E:{ ins = std::make_unique<iand>();ins->opCode = _opCode;break;}
            case 0x7F:{ ins = std::make_unique<land>();ins->opCode = _opCode;break;}
            case 0x80:{ ins = std::make_unique<ior>();ins->opCode = _opCode;break;}
            case 0x81:{ ins = std::make_unique<lor>();ins->opCode = _opCode;break;}
            case 0x82:{ ins = std::make_unique<ixor>();ins->opCode = _opCode;break;}
            case 0x83:{ ins = std::make_unique<lxor>();ins->opCode = _opCode;break;}
            case 0x84:{ ins = std::make_unique<iinc>();ins->opCode = _opCode;break;}
            case 0x85:{ ins = std::make_unique<i2l>();ins->opCode = _opCode;break;}
            case 0x86:{ ins = std::make_unique<i2f>();ins->opCode = _opCode;break;}
            case 0x87:{ ins = std::make_unique<i2d>();ins->opCode = _opCode;break;}
            case 0x88:{ ins = std::make_unique<l2i>();ins->opCode = _opCode;break;}
            case 0x89:{ ins = std::make_unique<l2f>();ins->opCode = _opCode;break;}
            case 0x8A:{ ins = std::make_unique<l2d>();ins->opCode = _opCode;break;}
            case 0x8B:{ ins = std::make_unique<f2i>();ins->opCode = _opCode;break;}
            case 0x8C:{ ins = std::make_unique<f2l>();ins->opCode = _opCode;break;}
            case 0x8D:{ ins = std::make_unique<f2d>();ins->opCode = _opCode;break;}
            case 0x8E:{ ins = std::make_unique<d2i>();ins->opCode = _opCode;break;}
            case 0x8F:{ ins = std::make_unique<d2l>();ins->opCode = _opCode;break;}
            case 0x90:{ ins = std::make_unique<d2f>();ins->opCode = _opCode;break;}
            case 0x91:{ ins = std::make_unique<i2b>();ins->opCode = _opCode;break;}
            case 0x92:{ ins = std::make_unique<i2c>();ins->opCode = _opCode;break;}
            case 0x93:{ ins = std::make_unique<i2s>();ins->opCode = _opCode;break;}
            case 0x94:{ ins = std::make_unique<lcmp>();ins->opCode = _opCode;break;}
            case 0x95:{ ins = std::make_unique<fcmpl>();ins->opCode = _opCode;break;}
            case 0x96:{ ins = std::make_unique<fcmpg>();ins->opCode = _opCode;break;}
            case 0x97:{ ins = std::make_unique<dcmpl>();ins->opCode = _opCode;break;}
            case 0x98:{ ins = std::make_unique<dcmpg>();ins->opCode = _opCode;break;}
            case 0x99:{ ins = std::make_unique<ifeq>();ins->opCode = _opCode;break;}
            case 0x9A:{ ins = std::make_unique<ifne>();ins->opCode = _opCode;break;}
            case 0x9B:{ ins = std::make_unique<iflt>();ins->opCode = _opCode;break;}
            case 0x9C:{ ins = std::make_unique<ifge>();ins->opCode = _opCode;break;}
            case 0x9D:{ ins = std::make_unique<ifgt>();ins->opCode = _opCode;break;}
            case 0x9E:{ ins = std::make_unique<ifle>();ins->opCode = _opCode;break;}
            case 0x9F:{ ins = std::make_unique<if_icmpeq>();ins->opCode = _opCode;break;}
            case 0xA0:{ ins = std::make_unique<if_icmpne>();ins->opCode = _opCode;break;}
            case 0xA1:{ ins = std::make_unique<if_icmplt>();ins->opCode = _opCode;break;}
            case 0xA2:{ ins = std::make_unique<if_icmpge>();ins->opCode = _opCode;break;}
            case 0xA3:{ ins = std::make_unique<if_icmpgt>();ins->opCode = _opCode;break;}
            case 0xA4:{ ins = std::make_unique<if_icmple>();ins->opCode = _opCode;break;}
            case 0xA5:{ ins = std::make_unique<if_acmpeq>();ins->opCode = _opCode;break;}
            case 0xA6:{ ins = std::make_unique<if_acmpne>();ins->opCode = _opCode;break;}
            case 0xA7:{ ins = std::make_unique<goto_>();ins->opCode = _opCode;break;}
            case 0xA8:{ ins = std::make_unique<jsr>();ins->opCode = _opCode;break;}
            case 0xA9:{ ins = std::make_unique<ret>();ins->opCode = _opCode;break;}
            case 0xAA:{ ins = std::make_unique<tableswitch>();ins->opCode = _opCode;break;}
            case 0xAB:{ ins = std::make_unique<lookupswitch>();ins->opCode = _opCode;break;}
            case 0xAC:{ ins = std::make_unique<ireturn>();ins->opCode = _opCode;break;}
            case 0xAD:{ ins = std::make_unique<lreturn>();ins->opCode = _opCode;break;}
            case 0xAE:{ ins = std::make_unique<freturn>();ins->opCode = _opCode;break;}
            case 0xAF:{ ins = std::make_unique<dreturn>();ins->opCode = _opCode;break;}
            case 0xB0:{ ins = std::make_unique<areturn>();ins->opCode = _opCode;break;}
            case 0xB1:{ ins = std::make_unique<return_>();ins->opCode = _opCode;break;}
            case 0xB2:{ ins = std::make_unique<getstatic>();ins->opCode = _opCode;break;}
            case 0xB3:{ ins = std::make_unique<putstatic>();ins->opCode = _opCode;break;}
            case 0xB4:{ ins = std::make_unique<getfield>();ins->opCode = _opCode;break;}
            case 0xB5:{ ins = std::make_unique<putfield>();ins->opCode = _opCode;break;}
            case 0xB6:{ ins = std::make_unique<invokevirtual>();ins->opCode = _opCode;break;}
            case 0xB7:{ ins = std::make_unique<invokespecial>();ins->opCode = _opCode;break;}
            case 0xB8:{ ins = std::make_unique<invokestatic>();ins->opCode = _opCode;break;}
            case 0xB9:{ ins = std::make_unique<invokeinterface>();ins->opCode = _opCode;break;}
            case 0xBA:{ ins = std::make_unique<invokedynamic>();ins->opCode = _opCode;break;}
            case 0xBB:{ ins = std::make_unique<new_>();ins->opCode = _opCode;break;}
            case 0xBC:{ ins = std::make_unique<newarray>();ins->opCode = _opCode;break;}
            case 0xBD:{ ins = std::make_unique<anewarray>();ins->opCode = _opCode;break;}
            case 0xBE:{ ins = std::make_unique<arraylength>();ins->opCode = _opCode;break;}
            case 0xBF:{ ins = std::make_unique<athrow>();ins->opCode = _opCode;break;}
            case 0xC0:{ ins = std::make_unique<checkcast>();ins->opCode = _opCode;break;}
            case 0xC1:{ ins = std::make_unique<instanceof>();ins->opCode = _opCode;break;}
            case 0xC2:{ ins = std::make_unique<monitorenter>();ins->opCode = _opCode;break;}
            case 0xC3:{ ins = std::make_unique<monitiorexit>();ins->opCode = _opCode;break;}
            case 0xC4:{ ins = std::make_unique<wide>();ins->opCode = _opCode;break;}
            case 0xC5:{ ins = std::make_unique<multianewarray>();ins->opCode = _opCode;break;}
            case 0xC6:{ ins = std::make_unique<ifnull>();ins->opCode = _opCode;break;}
            case 0xC7:{ ins = std::make_unique<ifnonnull>();ins->opCode = _opCode;break;}
            case 0xC8:{ ins = std::make_unique<goto_w>();ins->opCode = _opCode;break;}
            case 0xC9:{ ins = std::make_unique<jsr_w>();ins->opCode = _opCode;break;}
            case 0xCA:{ ins = std::make_unique<breakpoint>();ins->opCode = _opCode;break;}
            case 0xFE:{ ins = std::make_unique<impdep1>();ins->opCode = _opCode;break;}
            case 0xFF:{ ins = std::make_unique<impdep2>();ins->opCode = _opCode;break;}
            default:exception::panic("no such op code: " + std::to_string(_opCode));
        }
        return ins;
    }

}