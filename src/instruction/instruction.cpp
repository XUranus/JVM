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

    std::string Instruction::verbose() {
        return name();
    }

    void NoOperandsInstruction::fetchOperands(InstructionReader &reader) {}

    std::string NoOperandsInstruction::verbose(){
        return name();
    }



    void BranchInstructions::fetchOperands(InstructionReader &reader) {
        offset = (int)reader.readInt16();
    }

    std::string BranchInstructions::verbose() {
        return name() + "\t\t" + std::to_string(offset);
    }



    void Index8Instruction::fetchOperands(InstructionReader &reader) {
        index = reader.readUint8();
    }

    std::string Index8Instruction::verbose() {
        return name() + " \t\t" + std::to_string(index);
    }



    void Index16Instruction::fetchOperands(InstructionReader &reader) {
        index = reader.readUint16();
    }

    std::string Index16Instruction::verbose() {
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

    Instruction* create(u1 _opCode) {
        Instruction* ins = nullptr;
        switch (_opCode) {
            case 0x00:{ ins = new nop();ins->opCode = _opCode;break;}
            case 0x01:{ ins = new aconst_null();ins->opCode = _opCode;break;}
            case 0x02:{ ins = new iconst_m1();ins->opCode = _opCode;break;}
            case 0x03:{ ins = new iconst_0();ins->opCode = _opCode;break;}
            case 0x04:{ ins = new iconst_1();ins->opCode = _opCode;break;}
            case 0x05:{ ins = new iconst_2();ins->opCode = _opCode;break;}
            case 0x06:{ ins = new iconst_3();ins->opCode = _opCode;break;}
            case 0x07:{ ins = new iconst_4();ins->opCode = _opCode;break;}
            case 0x08:{ ins = new iconst_5();ins->opCode = _opCode;break;}
            case 0x09:{ ins = new lconst_0();ins->opCode = _opCode;break;}
            case 0x0A:{ ins = new lconst_1();ins->opCode = _opCode;break;}
            case 0x0B:{ ins = new fconst_0();ins->opCode = _opCode;break;}
            case 0x0C:{ ins = new fconst_1();ins->opCode = _opCode;break;}
            case 0x0D:{ ins = new fconst_2();ins->opCode = _opCode;break;}
            case 0x0E:{ ins = new dconst_0();ins->opCode = _opCode;break;}
            case 0x0F:{ ins = new dconst_1();ins->opCode = _opCode;break;}
            case 0x10:{ ins = new bipush();ins->opCode = _opCode;break;}
            case 0x11:{ ins = new sipush();ins->opCode = _opCode;break;}
            case 0x12:{ ins = new ldc();ins->opCode = _opCode;break;}
            case 0x13:{ ins = new ldc_w();ins->opCode = _opCode;break;}
            case 0x14:{ ins = new ldc2_w();ins->opCode = _opCode;break;}
            case 0x15:{ ins = new iload();ins->opCode = _opCode;break;}
            case 0x16:{ ins = new lload();ins->opCode = _opCode;break;}
            case 0x17:{ ins = new fload();ins->opCode = _opCode;break;}
            case 0x18:{ ins = new dload();ins->opCode = _opCode;break;}
            case 0x19:{ ins = new aload();ins->opCode = _opCode;break;}
            case 0x1A:{ ins = new iload_0();ins->opCode = _opCode;break;}
            case 0x1B:{ ins = new iload_1();ins->opCode = _opCode;break;}
            case 0x1C:{ ins = new iload_2();ins->opCode = _opCode;break;}
            case 0x1D:{ ins = new iload_3();ins->opCode = _opCode;break;}
            case 0x1E:{ ins = new lload_0();ins->opCode = _opCode;break;}
            case 0x1F:{ ins = new lload_1();ins->opCode = _opCode;break;}
            case 0x20:{ ins = new lload_2();ins->opCode = _opCode;break;}
            case 0x21:{ ins = new lload_3();ins->opCode = _opCode;break;}
            case 0x22:{ ins = new fload_0();ins->opCode = _opCode;break;}
            case 0x23:{ ins = new fload_1();ins->opCode = _opCode;break;}
            case 0x24:{ ins = new fload_2();ins->opCode = _opCode;break;}
            case 0x25:{ ins = new fload_3();ins->opCode = _opCode;break;}
            case 0x26:{ ins = new dload_0();ins->opCode = _opCode;break;}
            case 0x27:{ ins = new dload_1();ins->opCode = _opCode;break;}
            case 0x28:{ ins = new dload_2();ins->opCode = _opCode;break;}
            case 0x29:{ ins = new dload_3();ins->opCode = _opCode;break;}
            case 0x2A:{ ins = new aload_0();ins->opCode = _opCode;break;}
            case 0x2B:{ ins = new aload_1();ins->opCode = _opCode;break;}
            case 0x2C:{ ins = new aload_2();ins->opCode = _opCode;break;}
            case 0x2D:{ ins = new aload_3();ins->opCode = _opCode;break;}
            case 0x2E:{ ins = new iaload();ins->opCode = _opCode;break;}
            case 0x2F:{ ins = new laload();ins->opCode = _opCode;break;}
            case 0x30:{ ins = new faload();ins->opCode = _opCode;break;}
            case 0x31:{ ins = new daload();ins->opCode = _opCode;break;}
            case 0x32:{ ins = new aaload();ins->opCode = _opCode;break;}
            case 0x33:{ ins = new baload();ins->opCode = _opCode;break;}
            case 0x34:{ ins = new caload();ins->opCode = _opCode;break;}
            case 0x35:{ ins = new saload();ins->opCode = _opCode;break;}
            case 0x36:{ ins = new istore();ins->opCode = _opCode;break;}
            case 0x37:{ ins = new lstore();ins->opCode = _opCode;break;}
            case 0x38:{ ins = new fstore();ins->opCode = _opCode;break;}
            case 0x39:{ ins = new dstore();ins->opCode = _opCode;break;}
            case 0x3A:{ ins = new astore();ins->opCode = _opCode;break;}
            case 0x3B:{ ins = new istore_0();ins->opCode = _opCode;break;}
            case 0x3C:{ ins = new istore_1();ins->opCode = _opCode;break;}
            case 0x3D:{ ins = new istore_2();ins->opCode = _opCode;break;}
            case 0x3E:{ ins = new istore_3();ins->opCode = _opCode;break;}
            case 0x3F:{ ins = new lstore_0();ins->opCode = _opCode;break;}
            case 0x40:{ ins = new lstore_1();ins->opCode = _opCode;break;}
            case 0x41:{ ins = new lstore_2();ins->opCode = _opCode;break;}
            case 0x42:{ ins = new lstore_3();ins->opCode = _opCode;break;}
            case 0x43:{ ins = new fstore_0();ins->opCode = _opCode;break;}
            case 0x44:{ ins = new fstore_1();ins->opCode = _opCode;break;}
            case 0x45:{ ins = new fstore_2();ins->opCode = _opCode;break;}
            case 0x46:{ ins = new fstore_3();ins->opCode = _opCode;break;}
            case 0x47:{ ins = new dstore_0();ins->opCode = _opCode;break;}
            case 0x48:{ ins = new dstore_1();ins->opCode = _opCode;break;}
            case 0x49:{ ins = new dstore_2();ins->opCode = _opCode;break;}
            case 0x4A:{ ins = new dstore_3();ins->opCode = _opCode;break;}
            case 0x4B:{ ins = new astore_0();ins->opCode = _opCode;break;}
            case 0x4C:{ ins = new astore_1();ins->opCode = _opCode;break;}
            case 0x4D:{ ins = new astore_2();ins->opCode = _opCode;break;}
            case 0x4E:{ ins = new astore_3();ins->opCode = _opCode;break;}
            case 0x4F:{ ins = new iastore();ins->opCode = _opCode;break;}
            case 0x50:{ ins = new lastore();ins->opCode = _opCode;break;}
            case 0x51:{ ins = new fastore();ins->opCode = _opCode;break;}
            case 0x52:{ ins = new dastore();ins->opCode = _opCode;break;}
            case 0x53:{ ins = new aastore();ins->opCode = _opCode;break;}
            case 0x54:{ ins = new bastore();ins->opCode = _opCode;break;}
            case 0x55:{ ins = new castore();ins->opCode = _opCode;break;}
            case 0x56:{ ins = new sastore();ins->opCode = _opCode;break;}
            case 0x57:{ ins = new pop();ins->opCode = _opCode;break;}
            case 0x58:{ ins = new pop2();ins->opCode = _opCode;break;}
            case 0x59:{ ins = new dup();ins->opCode = _opCode;break;}
            case 0x5A:{ ins = new dup_x1();ins->opCode = _opCode;break;}
            case 0x5B:{ ins = new dup_x2();ins->opCode = _opCode;break;}
            case 0x5C:{ ins = new dup2();ins->opCode = _opCode;break;}
            case 0x5D:{ ins = new dup2_x1();ins->opCode = _opCode;break;}
            case 0x5E:{ ins = new dup2_x2();ins->opCode = _opCode;break;}
            case 0x5F:{ ins = new swap();ins->opCode = _opCode;break;}
            case 0x60:{ ins = new iadd();ins->opCode = _opCode;break;}
            case 0x61:{ ins = new ladd();ins->opCode = _opCode;break;}
            case 0x62:{ ins = new fadd();ins->opCode = _opCode;break;}
            case 0x63:{ ins = new dadd();ins->opCode = _opCode;break;}
            case 0x64:{ ins = new isub();ins->opCode = _opCode;break;}
            case 0x65:{ ins = new lsub();ins->opCode = _opCode;break;}
            case 0x66:{ ins = new fsub();ins->opCode = _opCode;break;}
            case 0x67:{ ins = new dsub();ins->opCode = _opCode;break;}
            case 0x68:{ ins = new imul();ins->opCode = _opCode;break;}
            case 0x69:{ ins = new lmul();ins->opCode = _opCode;break;}
            case 0x6A:{ ins = new fmul();ins->opCode = _opCode;break;}
            case 0x6B:{ ins = new dmul();ins->opCode = _opCode;break;}
            case 0x6C:{ ins = new idiv();ins->opCode = _opCode;break;}
            case 0x6D:{ ins = new ldiv_();ins->opCode = _opCode;break;}
            case 0x6E:{ ins = new fdiv();ins->opCode = _opCode;break;}
            case 0x6F:{ ins = new ddiv();ins->opCode = _opCode;break;}
            case 0x70:{ ins = new irem();ins->opCode = _opCode;break;}
            case 0x71:{ ins = new lrem();ins->opCode = _opCode;break;}
            case 0x72:{ ins = new frem();ins->opCode = _opCode;break;}
            case 0x73:{ ins = new drem();ins->opCode = _opCode;break;}
            case 0x74:{ ins = new ineg();ins->opCode = _opCode;break;}
            case 0x75:{ ins = new lneg();ins->opCode = _opCode;break;}
            case 0x76:{ ins = new fneg();ins->opCode = _opCode;break;}
            case 0x77:{ ins = new dneg();ins->opCode = _opCode;break;}
            case 0x78:{ ins = new ishl();ins->opCode = _opCode;break;}
            case 0x79:{ ins = new lshl();ins->opCode = _opCode;break;}
            case 0x7A:{ ins = new ishr();ins->opCode = _opCode;break;}
            case 0x7B:{ ins = new lshr();ins->opCode = _opCode;break;}
            case 0x7C:{ ins = new iushr();ins->opCode = _opCode;break;}
            case 0x7D:{ ins = new lushr();ins->opCode = _opCode;break;}
            case 0x7E:{ ins = new iand();ins->opCode = _opCode;break;}
            case 0x7F:{ ins = new land();ins->opCode = _opCode;break;}
            case 0x80:{ ins = new ior();ins->opCode = _opCode;break;}
            case 0x81:{ ins = new lor();ins->opCode = _opCode;break;}
            case 0x82:{ ins = new ixor();ins->opCode = _opCode;break;}
            case 0x83:{ ins = new lxor();ins->opCode = _opCode;break;}
            case 0x84:{ ins = new iinc();ins->opCode = _opCode;break;}
            case 0x85:{ ins = new i2l();ins->opCode = _opCode;break;}
            case 0x86:{ ins = new i2f();ins->opCode = _opCode;break;}
            case 0x87:{ ins = new i2d();ins->opCode = _opCode;break;}
            case 0x88:{ ins = new l2i();ins->opCode = _opCode;break;}
            case 0x89:{ ins = new l2f();ins->opCode = _opCode;break;}
            case 0x8A:{ ins = new l2d();ins->opCode = _opCode;break;}
            case 0x8B:{ ins = new f2i();ins->opCode = _opCode;break;}
            case 0x8C:{ ins = new f2l();ins->opCode = _opCode;break;}
            case 0x8D:{ ins = new f2d();ins->opCode = _opCode;break;}
            case 0x8E:{ ins = new d2i();ins->opCode = _opCode;break;}
            case 0x8F:{ ins = new d2l();ins->opCode = _opCode;break;}
            case 0x90:{ ins = new d2f();ins->opCode = _opCode;break;}
            case 0x91:{ ins = new i2b();ins->opCode = _opCode;break;}
            case 0x92:{ ins = new i2c();ins->opCode = _opCode;break;}
            case 0x93:{ ins = new i2s();ins->opCode = _opCode;break;}
            case 0x94:{ ins = new lcmp();ins->opCode = _opCode;break;}
            case 0x95:{ ins = new fcmpl();ins->opCode = _opCode;break;}
            case 0x96:{ ins = new fcmpg();ins->opCode = _opCode;break;}
            case 0x97:{ ins = new dcmpl();ins->opCode = _opCode;break;}
            case 0x98:{ ins = new dcmpg();ins->opCode = _opCode;break;}
            case 0x99:{ ins = new ifeq();ins->opCode = _opCode;break;}
            case 0x9A:{ ins = new ifne();ins->opCode = _opCode;break;}
            case 0x9B:{ ins = new iflt();ins->opCode = _opCode;break;}
            case 0x9C:{ ins = new ifge();ins->opCode = _opCode;break;}
            case 0x9D:{ ins = new ifgt();ins->opCode = _opCode;break;}
            case 0x9E:{ ins = new ifle();ins->opCode = _opCode;break;}
            case 0x9F:{ ins = new if_icmpeq();ins->opCode = _opCode;break;}
            case 0xA0:{ ins = new if_icmpne();ins->opCode = _opCode;break;}
            case 0xA1:{ ins = new if_icmplt();ins->opCode = _opCode;break;}
            case 0xA2:{ ins = new if_icmpge();ins->opCode = _opCode;break;}
            case 0xA3:{ ins = new if_icmpgt();ins->opCode = _opCode;break;}
            case 0xA4:{ ins = new if_icmple();ins->opCode = _opCode;break;}
            case 0xA5:{ ins = new if_acmpeq();ins->opCode = _opCode;break;}
            case 0xA6:{ ins = new if_acmpne();ins->opCode = _opCode;break;}
            case 0xA7:{ ins = new goto_();ins->opCode = _opCode;break;}
            case 0xA8:{ ins = new jsr();ins->opCode = _opCode;break;}
            case 0xA9:{ ins = new ret();ins->opCode = _opCode;break;}
            case 0xAA:{ ins = new tableswitch();ins->opCode = _opCode;break;}
            case 0xAB:{ ins = new lookupswitch();ins->opCode = _opCode;break;}
            case 0xAC:{ ins = new ireturn();ins->opCode = _opCode;break;}
            case 0xAD:{ ins = new lreturn();ins->opCode = _opCode;break;}
            case 0xAE:{ ins = new freturn();ins->opCode = _opCode;break;}
            case 0xAF:{ ins = new dreturn();ins->opCode = _opCode;break;}
            case 0xB0:{ ins = new areturn();ins->opCode = _opCode;break;}
            case 0xB1:{ ins = new return_();ins->opCode = _opCode;break;}
            case 0xB2:{ ins = new getstatic();ins->opCode = _opCode;break;}
            case 0xB3:{ ins = new putstatic();ins->opCode = _opCode;break;}
            case 0xB4:{ ins = new getfield();ins->opCode = _opCode;break;}
            case 0xB5:{ ins = new putfield();ins->opCode = _opCode;break;}
            case 0xB6:{ ins = new invokevirtual();ins->opCode = _opCode;break;}
            case 0xB7:{ ins = new invokespecial();ins->opCode = _opCode;break;}
            case 0xB8:{ ins = new invokestatic();ins->opCode = _opCode;break;}
            case 0xB9:{ ins = new invokeinterface();ins->opCode = _opCode;break;}
            case 0xBA:{ ins = new invokedynamic();ins->opCode = _opCode;break;}
            case 0xBB:{ ins = new new_();ins->opCode = _opCode;break;}
            case 0xBC:{ ins = new newarray();ins->opCode = _opCode;break;}
            case 0xBD:{ ins = new anewarray();ins->opCode = _opCode;break;}
            case 0xBE:{ ins = new arraylength();ins->opCode = _opCode;break;}
            case 0xBF:{ ins = new athrow();ins->opCode = _opCode;break;}
            case 0xC0:{ ins = new checkcast();ins->opCode = _opCode;break;}
            case 0xC1:{ ins = new instanceof();ins->opCode = _opCode;break;}
            case 0xC2:{ ins = new monitorenter();ins->opCode = _opCode;break;}
            case 0xC3:{ ins = new monitiorexit();ins->opCode = _opCode;break;}
            case 0xC4:{ ins = new wide();ins->opCode = _opCode;break;}
            case 0xC5:{ ins = new multianewarray();ins->opCode = _opCode;break;}
            case 0xC6:{ ins = new ifnull();ins->opCode = _opCode;break;}
            case 0xC7:{ ins = new ifnonnull();ins->opCode = _opCode;break;}
            case 0xC8:{ ins = new goto_w();ins->opCode = _opCode;break;}
            case 0xC9:{ ins = new jsr_w();ins->opCode = _opCode;break;}
            case 0xCA:{ ins = new breakpoint();ins->opCode = _opCode;break;}
            case 0xFE:{ ins = new impdep1();ins->opCode = _opCode;break;}
            case 0xFF:{ ins = new impdep2();ins->opCode = _opCode;break;}
            default:exception::panic("no such op code: " + std::to_string(_opCode));
        }
        return ins;
    }

}