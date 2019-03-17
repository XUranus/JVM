//
// Created by XUranus on 2019/2/1.
//

#include <cstdio>
#include "instruction.h"
#include "../runtime/Frame.h"

#include "constants.h"
#include "loads.h"
#include "stores.h"
#include "stack.h"
#include "math.h"
#include "conversions.h"
#include "compairisons.h"
#include "control.h"
#include "references.h"
#include "extended.h"
#include "reserved.h"

#define DEBUG_MODE 1

BytesReader::BytesReader()
{
    pc = 0;
    code = nullptr;
    length = 0;
}

BytesReader::BytesReader(byte *_code, unsigned int _length) {
    pc = 0;
    code = _code;
    length = _length;
}

void BytesReader::reset(byte *_code, int _pc, unsigned int _length) {
    pc = _pc;
    code = _code;
    length = _length;
}

int8 BytesReader::readInt8()
{
    int8 ret = code[pc];
    pc++;
    return ret;
}

uint8 BytesReader::readUint8()
{
    uint8 ret = code[pc];
    pc++;
    return ret;
}

int16 BytesReader::readInt16()
{
    return int16 (readUint16());
}

uint16 BytesReader::readUint16()
{
    auto byte1 = (uint16)readUint8();
    auto byte2 = (uint16)readUint8();
    return (byte1<<8) | byte2;
}

int32 BytesReader::readInt32()
{
    auto byte1 = (int32)readUint8();
    auto byte2 = (int32)readUint8();
    auto byte3 = (int32)readUint8();
    auto byte4 = (int32)readUint8();
    return (byte1<<24)|(byte2<<16)|(byte3<<8)|byte4;
}

void BytesReader::skipPadding()
{
    while (pc%4!=0)
        readUint8();
}

int32* BytesReader::readInt32s(int jumpOffsetsCount)
{
    auto jumpOffsets = new int32[jumpOffsetsCount];
    for(int i=0;i<jumpOffsetsCount;i++)
    {
        jumpOffsets[i] = readInt32();
    }
    return jumpOffsets;
}

bool BytesReader::hasByte() {
    return length>=pc;
}


/***************************************************   Instructions   ***************************************************/
std::vector<std::string> Instruction::byteCodesNames(std::vector<u1> &codes) {
    BytesReader reader(codes.data(),codes.size());
    std::vector<std::string> ans;
    while (reader.hasByte()) {
        auto opCode = reader.readUint8();
        auto inst = Instruction::createInstruction(opCode);
        inst->fetchOperands(reader);
        ans.push_back(inst->toString());
    }
    return ans;
}

void Instruction::fetchOperands(BytesReader &reader) {
    printf("not implement method fetchOperands(),op name:%s\n");
    exit(1);
}

void Instruction::excute(Frame *frame) {
    printf("not implement method excute()\n");
    exit(1);
}

std::string Instruction::toString() {
    printf("not implement method toString()\n");
    exit(1);
}

void NoOperandsInstruction::fetchOperands(BytesReader &reader)
{
    //do nothing
}

std::string NoOperandsInstruction::toString()
{
    return getInstructionName();
}

void BranchInstructions::fetchOperands(BytesReader &reader)
{
    offset = (int)reader.readInt16();
}

std::string BranchInstructions::toString()
{
    return getInstructionName()+" "+std::to_string(offset);
}

void Index8Instruction::fetchOperands(BytesReader &reader)
{
    index = reader.readUint8();
}

std::string Index8Instruction::toString()
{
    return getInstructionName()+" "+std::to_string(index);
}

void Index16Instruction::fetchOperands(BytesReader &reader)
{
    index = (unsigned int)reader.readUint16();
}

std::string Index16Instruction::toString()
{
    return getInstructionName()+" "+std::to_string(index);
}


std::string Instruction::opCodeToName(u1 _opCode) {
    switch (_opCode) {
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
            printf("no such opCode: 0x%02x",_opCode);
            exit(1);
            return "unknown"+std::to_string(_opCode);
        }
    }
}

std::string Instruction::getInstructionName() {
    return opCodeToName(opCode);
}

Instruction* Instruction::createInstruction(u1 _opCode) {
    Instruction* retAttr = nullptr;
    switch (_opCode) {
        case 0x00:{ retAttr = new nop();retAttr->opCode = _opCode;break;}
        case 0x01:{ retAttr = new aconst_null();retAttr->opCode = _opCode;break;}
        case 0x02:{ retAttr = new iconst_m1();retAttr->opCode = _opCode;break;}
        case 0x03:{ retAttr = new iconst_0();retAttr->opCode = _opCode;break;}
        case 0x04:{ retAttr = new iconst_1();retAttr->opCode = _opCode;break;}
        case 0x05:{ retAttr = new iconst_2();retAttr->opCode = _opCode;break;}
        case 0x06:{ retAttr = new iconst_3();retAttr->opCode = _opCode;break;}
        case 0x07:{ retAttr = new iconst_4();retAttr->opCode = _opCode;break;}
        case 0x08:{ retAttr = new iconst_5();retAttr->opCode = _opCode;break;}
        case 0x09:{ retAttr = new lconst_0();retAttr->opCode = _opCode;break;}
        case 0x0A:{ retAttr = new lconst_1();retAttr->opCode = _opCode;break;}
        case 0x0B:{ retAttr = new fconst_0();retAttr->opCode = _opCode;break;}
        case 0x0C:{ retAttr = new fconst_1();retAttr->opCode = _opCode;break;}
        case 0x0D:{ retAttr = new fconst_2();retAttr->opCode = _opCode;break;}
        case 0x0E:{ retAttr = new dconst_0();retAttr->opCode = _opCode;break;}
        case 0x0F:{ retAttr = new dconst_1();retAttr->opCode = _opCode;break;}
        case 0x10:{ retAttr = new bipush();retAttr->opCode = _opCode;break;}
        case 0x11:{ retAttr = new sipush();retAttr->opCode = _opCode;break;}
        case 0x12:{ retAttr = new ldc();retAttr->opCode = _opCode;break;}
        case 0x13:{ retAttr = new ldc_w();retAttr->opCode = _opCode;break;}
        case 0x14:{ retAttr = new ldc2_w();retAttr->opCode = _opCode;break;}
        case 0x15:{ retAttr = new iload();retAttr->opCode = _opCode;break;}
        case 0x16:{ retAttr = new lload();retAttr->opCode = _opCode;break;}
        case 0x17:{ retAttr = new fload();retAttr->opCode = _opCode;break;}
        case 0x18:{ retAttr = new dload();retAttr->opCode = _opCode;break;}
        case 0x19:{ retAttr = new aload();retAttr->opCode = _opCode;break;}
        case 0x1A:{ retAttr = new iload_0();retAttr->opCode = _opCode;break;}
        case 0x1B:{ retAttr = new iload_1();retAttr->opCode = _opCode;break;}
        case 0x1C:{ retAttr = new iload_2();retAttr->opCode = _opCode;break;}
        case 0x1D:{ retAttr = new iload_3();retAttr->opCode = _opCode;break;}
        case 0x1E:{ retAttr = new lload_0();retAttr->opCode = _opCode;break;}
        case 0x1F:{ retAttr = new lload_1();retAttr->opCode = _opCode;break;}
        case 0x20:{ retAttr = new lload_2();retAttr->opCode = _opCode;break;}
        case 0x21:{ retAttr = new lload_3();retAttr->opCode = _opCode;break;}
        case 0x22:{ retAttr = new fload_0();retAttr->opCode = _opCode;break;}
        case 0x23:{ retAttr = new fload_1();retAttr->opCode = _opCode;break;}
        case 0x24:{ retAttr = new fload_2();retAttr->opCode = _opCode;break;}
        case 0x25:{ retAttr = new fload_3();retAttr->opCode = _opCode;break;}
        case 0x26:{ retAttr = new dload_0();retAttr->opCode = _opCode;break;}
        case 0x27:{ retAttr = new dload_1();retAttr->opCode = _opCode;break;}
        case 0x28:{ retAttr = new dload_2();retAttr->opCode = _opCode;break;}
        case 0x29:{ retAttr = new dload_3();retAttr->opCode = _opCode;break;}
        case 0x2A:{ retAttr = new aload_0();retAttr->opCode = _opCode;break;}
        case 0x2B:{ retAttr = new aload_1();retAttr->opCode = _opCode;break;}
        case 0x2C:{ retAttr = new aload_2();retAttr->opCode = _opCode;break;}
        case 0x2D:{ retAttr = new aload_3();retAttr->opCode = _opCode;break;}
        case 0x2E:{ retAttr = new iaload();retAttr->opCode = _opCode;break;}
        case 0x2F:{ retAttr = new laload();retAttr->opCode = _opCode;break;}
        case 0x30:{ retAttr = new faload();retAttr->opCode = _opCode;break;}
        case 0x31:{ retAttr = new daload();retAttr->opCode = _opCode;break;}
        case 0x32:{ retAttr = new aaload();retAttr->opCode = _opCode;break;}
        case 0x33:{ retAttr = new baload();retAttr->opCode = _opCode;break;}
        case 0x34:{ retAttr = new caload();retAttr->opCode = _opCode;break;}
        case 0x35:{ retAttr = new saload();retAttr->opCode = _opCode;break;}
        case 0x36:{ retAttr = new istore();retAttr->opCode = _opCode;break;}
        case 0x37:{ retAttr = new lstore();retAttr->opCode = _opCode;break;}
        case 0x38:{ retAttr = new fstore();retAttr->opCode = _opCode;break;}
        case 0x39:{ retAttr = new dstore();retAttr->opCode = _opCode;break;}
        case 0x3A:{ retAttr = new astore();retAttr->opCode = _opCode;break;}
        case 0x3B:{ retAttr = new istore_0();retAttr->opCode = _opCode;break;}
        case 0x3C:{ retAttr = new istore_1();retAttr->opCode = _opCode;break;}
        case 0x3D:{ retAttr = new istore_2();retAttr->opCode = _opCode;break;}
        case 0x3E:{ retAttr = new istore_3();retAttr->opCode = _opCode;break;}
        case 0x3F:{ retAttr = new lstore_0();retAttr->opCode = _opCode;break;}
        case 0x40:{ retAttr = new lstore_1();retAttr->opCode = _opCode;break;}
        case 0x41:{ retAttr = new lstore_2();retAttr->opCode = _opCode;break;}
        case 0x42:{ retAttr = new lstore_3();retAttr->opCode = _opCode;break;}
        case 0x43:{ retAttr = new fstore_0();retAttr->opCode = _opCode;break;}
        case 0x44:{ retAttr = new fstore_1();retAttr->opCode = _opCode;break;}
        case 0x45:{ retAttr = new fstore_2();retAttr->opCode = _opCode;break;}
        case 0x46:{ retAttr = new fstore_3();retAttr->opCode = _opCode;break;}
        case 0x47:{ retAttr = new dstore_0();retAttr->opCode = _opCode;break;}
        case 0x48:{ retAttr = new dstore_1();retAttr->opCode = _opCode;break;}
        case 0x49:{ retAttr = new dstore_2();retAttr->opCode = _opCode;break;}
        case 0x4A:{ retAttr = new dstore_3();retAttr->opCode = _opCode;break;}
        case 0x4B:{ retAttr = new astore_0();retAttr->opCode = _opCode;break;}
        case 0x4C:{ retAttr = new astore_1();retAttr->opCode = _opCode;break;}
        case 0x4D:{ retAttr = new astore_2();retAttr->opCode = _opCode;break;}
        case 0x4E:{ retAttr = new astore_3();retAttr->opCode = _opCode;break;}
        case 0x4F:{ retAttr = new iastore();retAttr->opCode = _opCode;break;}
        case 0x50:{ retAttr = new lastore();retAttr->opCode = _opCode;break;}
        case 0x51:{ retAttr = new fastore();retAttr->opCode = _opCode;break;}
        case 0x52:{ retAttr = new dastore();retAttr->opCode = _opCode;break;}
        case 0x53:{ retAttr = new aastore();retAttr->opCode = _opCode;break;}
        case 0x54:{ retAttr = new bastore();retAttr->opCode = _opCode;break;}
        case 0x55:{ retAttr = new castore();retAttr->opCode = _opCode;break;}
        case 0x56:{ retAttr = new sastore();retAttr->opCode = _opCode;break;}
        case 0x57:{ retAttr = new pop();retAttr->opCode = _opCode;break;}
        case 0x58:{ retAttr = new pop2();retAttr->opCode = _opCode;break;}
        case 0x59:{ retAttr = new dup();retAttr->opCode = _opCode;break;}
        case 0x5A:{ retAttr = new dup_x1();retAttr->opCode = _opCode;break;}
        case 0x5B:{ retAttr = new dup_x2();retAttr->opCode = _opCode;break;}
        case 0x5C:{ retAttr = new dup2();retAttr->opCode = _opCode;break;}
        case 0x5D:{ retAttr = new dup2_x1();retAttr->opCode = _opCode;break;}
        case 0x5E:{ retAttr = new dup2_x2();retAttr->opCode = _opCode;break;}
        case 0x5F:{ retAttr = new swap();retAttr->opCode = _opCode;break;}
        case 0x60:{ retAttr = new iadd();retAttr->opCode = _opCode;break;}
        case 0x61:{ retAttr = new ladd();retAttr->opCode = _opCode;break;}
        case 0x62:{ retAttr = new fadd();retAttr->opCode = _opCode;break;}
        case 0x63:{ retAttr = new dadd();retAttr->opCode = _opCode;break;}
        case 0x64:{ retAttr = new isub();retAttr->opCode = _opCode;break;}
        case 0x65:{ retAttr = new lsub();retAttr->opCode = _opCode;break;}
        case 0x66:{ retAttr = new fsub();retAttr->opCode = _opCode;break;}
        case 0x67:{ retAttr = new dsub();retAttr->opCode = _opCode;break;}
        case 0x68:{ retAttr = new imul();retAttr->opCode = _opCode;break;}
        case 0x69:{ retAttr = new lmul();retAttr->opCode = _opCode;break;}
        case 0x6A:{ retAttr = new fmul();retAttr->opCode = _opCode;break;}
        case 0x6B:{ retAttr = new dmul();retAttr->opCode = _opCode;break;}
        case 0x6C:{ retAttr = new idiv();retAttr->opCode = _opCode;break;}
        case 0x6D:{ retAttr = new ldiv_();retAttr->opCode = _opCode;break;}
        case 0x6E:{ retAttr = new fdiv();retAttr->opCode = _opCode;break;}
        case 0x6F:{ retAttr = new ddiv();retAttr->opCode = _opCode;break;}
        case 0x70:{ retAttr = new irem();retAttr->opCode = _opCode;break;}
        case 0x71:{ retAttr = new lrem();retAttr->opCode = _opCode;break;}
        case 0x72:{ retAttr = new frem();retAttr->opCode = _opCode;break;}
        case 0x73:{ retAttr = new drem();retAttr->opCode = _opCode;break;}
        case 0x74:{ retAttr = new ineg();retAttr->opCode = _opCode;break;}
        case 0x75:{ retAttr = new lneg();retAttr->opCode = _opCode;break;}
        case 0x76:{ retAttr = new fneg();retAttr->opCode = _opCode;break;}
        case 0x77:{ retAttr = new dneg();retAttr->opCode = _opCode;break;}
        case 0x78:{ retAttr = new ishl();retAttr->opCode = _opCode;break;}
        case 0x79:{ retAttr = new lshl();retAttr->opCode = _opCode;break;}
        case 0x7A:{ retAttr = new ishr();retAttr->opCode = _opCode;break;}
        case 0x7B:{ retAttr = new lshr();retAttr->opCode = _opCode;break;}
        case 0x7C:{ retAttr = new iushr();retAttr->opCode = _opCode;break;}
        case 0x7D:{ retAttr = new lushr();retAttr->opCode = _opCode;break;}
        case 0x7E:{ retAttr = new iand();retAttr->opCode = _opCode;break;}
        case 0x7F:{ retAttr = new land();retAttr->opCode = _opCode;break;}
        case 0x80:{ retAttr = new ior();retAttr->opCode = _opCode;break;}
        case 0x81:{ retAttr = new lor();retAttr->opCode = _opCode;break;}
        case 0x82:{ retAttr = new ixor();retAttr->opCode = _opCode;break;}
        case 0x83:{ retAttr = new lxor();retAttr->opCode = _opCode;break;}
        case 0x84:{ retAttr = new iinc();retAttr->opCode = _opCode;break;}
        case 0x85:{ retAttr = new i2l();retAttr->opCode = _opCode;break;}
        case 0x86:{ retAttr = new i2f();retAttr->opCode = _opCode;break;}
        case 0x87:{ retAttr = new i2d();retAttr->opCode = _opCode;break;}
        case 0x88:{ retAttr = new l2i();retAttr->opCode = _opCode;break;}
        case 0x89:{ retAttr = new l2f();retAttr->opCode = _opCode;break;}
        case 0x8A:{ retAttr = new l2d();retAttr->opCode = _opCode;break;}
        case 0x8B:{ retAttr = new f2i();retAttr->opCode = _opCode;break;}
        case 0x8C:{ retAttr = new f2l();retAttr->opCode = _opCode;break;}
        case 0x8D:{ retAttr = new f2d();retAttr->opCode = _opCode;break;}
        case 0x8E:{ retAttr = new d2i();retAttr->opCode = _opCode;break;}
        case 0x8F:{ retAttr = new d2l();retAttr->opCode = _opCode;break;}
        case 0x90:{ retAttr = new d2f();retAttr->opCode = _opCode;break;}
        case 0x91:{ retAttr = new i2b();retAttr->opCode = _opCode;break;}
        case 0x92:{ retAttr = new i2c();retAttr->opCode = _opCode;break;}
        case 0x93:{ retAttr = new i2s();retAttr->opCode = _opCode;break;}
        case 0x94:{ retAttr = new lcmp();retAttr->opCode = _opCode;break;}
        case 0x95:{ retAttr = new fcmpl();retAttr->opCode = _opCode;break;}
        case 0x96:{ retAttr = new fcmpg();retAttr->opCode = _opCode;break;}
        case 0x97:{ retAttr = new dcmpl();retAttr->opCode = _opCode;break;}
        case 0x98:{ retAttr = new dcmpg();retAttr->opCode = _opCode;break;}
        case 0x99:{ retAttr = new ifeq();retAttr->opCode = _opCode;break;}
        case 0x9A:{ retAttr = new ifne();retAttr->opCode = _opCode;break;}
        case 0x9B:{ retAttr = new iflt();retAttr->opCode = _opCode;break;}
        case 0x9C:{ retAttr = new ifge();retAttr->opCode = _opCode;break;}
        case 0x9D:{ retAttr = new ifgt();retAttr->opCode = _opCode;break;}
        case 0x9E:{ retAttr = new ifle();retAttr->opCode = _opCode;break;}
        case 0x9F:{ retAttr = new if_icmpeq();retAttr->opCode = _opCode;break;}
        case 0xA0:{ retAttr = new if_icmpne();retAttr->opCode = _opCode;break;}
        case 0xA1:{ retAttr = new if_icmplt();retAttr->opCode = _opCode;break;}
        case 0xA2:{ retAttr = new if_icmpge();retAttr->opCode = _opCode;break;}
        case 0xA3:{ retAttr = new if_icmpgt();retAttr->opCode = _opCode;break;}
        case 0xA4:{ retAttr = new if_icmple();retAttr->opCode = _opCode;break;}
        case 0xA5:{ retAttr = new if_acmpeq();retAttr->opCode = _opCode;break;}
        case 0xA6:{ retAttr = new if_acmpne();retAttr->opCode = _opCode;break;}
        case 0xA7:{ retAttr = new goto_();retAttr->opCode = _opCode;break;}
        case 0xA8:{ retAttr = new jsr();retAttr->opCode = _opCode;break;}
        case 0xA9:{ retAttr = new ret();retAttr->opCode = _opCode;break;}
        case 0xAA:{ retAttr = new tableswitch();retAttr->opCode = _opCode;break;}
        case 0xAB:{ retAttr = new lookupswitch();retAttr->opCode = _opCode;break;}
        case 0xAC:{ retAttr = new ireturn();retAttr->opCode = _opCode;break;}
        case 0xAD:{ retAttr = new lreturn();retAttr->opCode = _opCode;break;}
        case 0xAE:{ retAttr = new freturn();retAttr->opCode = _opCode;break;}
        case 0xAF:{ retAttr = new dreturn();retAttr->opCode = _opCode;break;}
        case 0xB0:{ retAttr = new areturn();retAttr->opCode = _opCode;break;}
        case 0xB1:{ retAttr = new return_();retAttr->opCode = _opCode;break;}
        case 0xB2:{ retAttr = new getstatic();retAttr->opCode = _opCode;break;}
        case 0xB3:{ retAttr = new putstatic();retAttr->opCode = _opCode;break;}
        case 0xB4:{ retAttr = new getfield();retAttr->opCode = _opCode;break;}
        case 0xB5:{ retAttr = new putfield();retAttr->opCode = _opCode;break;}
        case 0xB6:{ retAttr = new invokevirtual();retAttr->opCode = _opCode;break;}
        case 0xB7:{ retAttr = new invokespecial();retAttr->opCode = _opCode;break;}
        case 0xB8:{ retAttr = new invokestatic();retAttr->opCode = _opCode;break;}
        case 0xB9:{ retAttr = new invokeinterface();retAttr->opCode = _opCode;break;}
        case 0xBB:{ retAttr = new new_();retAttr->opCode = _opCode;break;}
        case 0xBC:{ retAttr = new newarray();retAttr->opCode = _opCode;break;}
        case 0xBD:{ retAttr = new anewarray();retAttr->opCode = _opCode;break;}
        case 0xBE:{ retAttr = new arraylength();retAttr->opCode = _opCode;break;}
        case 0xBF:{ retAttr = new athrow();retAttr->opCode = _opCode;break;}
        case 0xC0:{ retAttr = new checkcast();retAttr->opCode = _opCode;break;}
        case 0xC1:{ retAttr = new instanceof();retAttr->opCode = _opCode;break;}
        case 0xC2:{ retAttr = new monitorenter();retAttr->opCode = _opCode;break;}
        case 0xC3:{ retAttr = new monitiorexit();retAttr->opCode = _opCode;break;}
        case 0xC4:{ retAttr = new wide();retAttr->opCode = _opCode;break;}
        case 0xC5:{ retAttr = new multianewarray();retAttr->opCode = _opCode;break;}
        case 0xC6:{ retAttr = new ifnull();retAttr->opCode = _opCode;break;}
        case 0xC7:{ retAttr = new ifnonnull();retAttr->opCode = _opCode;break;}
        case 0xC8:{ retAttr = new goto_w();retAttr->opCode = _opCode;break;}
        case 0xC9:{ retAttr = new jsr_w();retAttr->opCode = _opCode;break;}
        case 0xCA:{ retAttr = new breakpoint();retAttr->opCode = _opCode;break;}
        case 0xFE:{ retAttr = new impdep1();retAttr->opCode = _opCode;break;}
        case 0xFF:{ retAttr = new impdep2();retAttr->opCode = _opCode;break;}
        default:{
            printf("no such opCode: 0x%02x",_opCode);
            exit(1);
        }
    }
    return retAttr;
}

