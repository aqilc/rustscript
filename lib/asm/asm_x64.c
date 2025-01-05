/*
 * asm_x64.c v1.0.0 - Aqil Contractor @AqilC 2023
 * Licenced under Attribution-NonCommercial-ShareAlike 3.0
 *
 * This file includes all of the source for the "chasm" library macros and functions.
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <malloc.h>
#include "asm_x64.h"


typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// INSERT TABLE HERE

/**
 * TODO: Add support for VEX and EVEX instructions.
 * TODO: Error messages for using a 32 bit register to address on a mem64 operand.
 * TODO: 32 Bit support?
 */

// https://github.com/StanfordPL/x64asm

/**
 * Cool resources:
 * - https://stackoverflow.com/questions/31853189/x86-64-assembly-why-displacement-not-64-bits
 * - https://nixhacker.com/segmentation-in-intel-64-bit/
 * - https://stackoverflow.com/questions/58182616/assembler-use-of-segment-register
 * - https://stackoverflow.com/questions/41573502/why-doesnt-gcc-use-partial-registers
 * - https://stackoverflow.com/questions/52522544/rbp-not-allowed-as-sib-base
 * - https://blog.yossarian.net/2020/11/30/How-many-registers-does-an-x86-64-cpu-have
 * - https://stackoverflow.com/a/54895495/10013227   # x86 instruction prefix decoding
 * - https://www.cs.virginia.edu/~evans/cs216/guides/x86.html # instruction guide, handy
 * - https://www.cs.put.poznan.pl/tzok/public/cawllp-04-asm.html#:~:text=default%20rel%20instructs%20to%20use,16%2D%20or%2032%2Dbit%20number # Various examples
 * - https://www.felixcloutier.com/x86/ # x86 instruction set reference
 * - https://learn.microsoft.com/en-us/cpp/cpp/argument-passing-and-naming-conventions?view=msvc-170
 * - https://wiki.osdev.org/Calling_Conventions
 * - https://chromium.googlesource.com/v8/v8.git/+/refs/heads/main/src/codegen/x64/assembler-x64.h # V8's x64 assembler
 * - https://zhu45.org/posts/2017/Jul/30/understanding-how-function-call-works/#google_vignette
 * - https://www.computerenhance.com/p/how-does-queryperformancecounter
 * - https://github.com/llvm/llvm-project/blob/main/llvm/lib/Target/X86/Disassembler/X86Disassembler.cpp#L335 # LLVM's x86 disassembler
 *
 * - What each operand name means (Note: Reg = DST, Mem = Src in op/en):
 *   - https://stackoverflow.com/questions/15017659/how-to-read-the-intel-opcode-notation/41616657#41616657:~:text=%E2%80%A2-,m16%2632%2C%20m16%2616%2C%20m32%2632%2C%20m16%2664%20%E2%80%94%20A%20memory,load%20the%20base%20field%20of%20the%20corresponding%20GDTR%20and%20IDTR%20registers.,-%E2%80%A2%20moffs8%2C%20moffs16%2C%20moffs32
 *
 * - https://gist.github.com/mikesmullin/6259449 # Mike's x86 assembly notes
 *   - https://gist.github.com/mikesmullin/6259449#appendix-reverse-engineering--malware-analysis
 *   - https://gist.github.com/mikesmullin/6259449#appendix-writing-a-compiler
 *
 * - Register Allocator docs: https://cfallin.org/blog/2021/03/15/cranelift-isel-3/
 */

// https://l-m.dev/cs/jitcalc/#:~:text=make%20it%20executable%3F-,C%20Territory,-V%20does%20not

static u32 encode(const x64Ins* ins, x64LookupActualIns* res, u8* opcode_dest);

#define ismem(x) (x & X64_ALLMEMMASK)
#define membase(x)  ((x >> 32) & 0x1f)
#define memindex(x) ((x >> 40) & 0x1f)
#define memscale(x) ((x >> 48) & 0x3)

_Thread_local struct AssemblyError {
  bool error;
  char buf[100];
  enum AssemblyErrorType {
    ASMERR_INVALID_INS,
    ASMERR_INVALID_REG_TYPE,
    ASMERR_INS_ARGUMENT_MISMATCH,
    ASMERR_ESPRSP_USED_AS_INDEX,
    ASMERR_REL_OUT_OF_RANGE,
    ASMERR_LABEL_NOT_FOUND
    // More to come
  } error_type;
} cur_error;

static inline u32 error(enum AssemblyErrorType type, char* fmt, ...) {
  cur_error.error = true;
  cur_error.error_type = type;
  va_list args;
  va_start(args, fmt);
  vsnprintf(cur_error.buf, 100, fmt, args);
  va_end(args);
  return 0;
}

char* get_error(int* errcode) {
  if(cur_error.error) {
    cur_error.error = false;
    if(errcode) *errcode = cur_error.error_type;
    return cur_error.buf;
  }
  return NULL;
}

static inline x64LookupActualIns* identify(const x64Ins* ins) {
  if (ins->op > sizeof(x64Table) / sizeof(x64LookupGeneralIns) || ins->op < 1) {
    error(ASMERR_INVALID_INS, "Invalid instruction: %d.", ins->op);
    return NULL;
  }

  const x64LookupGeneralIns* unresins = x64Table + (ins->op - 1);
  x64LookupActualIns* resolved = NULL;
  bool preferred = false;

  u64 insoperands[] = { ins->params[0].type, ins->params[1].type, ins->params[2].type, ins->params[3].type };

  u32 operandnum = 0;
  while(insoperands[operandnum] && operandnum < 4)
    operandnum ++;

  // Specifies bigger, more specific sizes for MOV based on the immediate value. Basically, picks the right instruction when there's an ambiguous immediate value.
  if(ins->op == MOV) {
    u8 immplace = 0;
    if(insoperands[1] & (IMM8 | IMM16 | IMM32 | IMM64)) immplace = 2;
    else immplace = 1;
    
    // If there's no ambiguity in the immediate value, and it does not go into the RAX-R15 registers, there's no point
    if ((insoperands[immplace - 1] & IMM64) == 0 || (insoperands[immplace - 1] & IMM32) == 0 ||
        (insoperands[2 - immplace] & R64) == 0) goto next;
    
    if(ins->params[immplace - 1].value > 0x100000000) insoperands[immplace - 1] = IMM64;
    else if(ins->params[immplace - 1].value > 0x10000) insoperands[immplace - 1] = IMM32 | IMM8 | IMM16;
  }
  // Adds more specificity to the ambiguous rel() macro's REL32 | REL8
  else if(ins->op >= JA && ins->op <= JMP && insoperands[0] & REL8) {
    if((i32) ins->params[0].value > 127 || (i32) ins->params[0].value < -128) insoperands[0] = REL32;
    else insoperands[0] = REL8;
  }
next:
  
  // ---------------------- Instruction resolution and Validation ---------------------- //

  for(u32 i = 0; i < unresins->numactualins; i ++) {
    if(unresins->ins[i].arglen != operandnum) continue;
    x64LookupActualIns* currentins = unresins->ins + i;

    bool morespecific = false;
    for(u32 j = 0; j < operandnum; j ++)
      if(!(currentins->args[j] & insoperands[j])) goto cont;
      else if(resolved && (
          resolved->args[j] < (currentins->args[j] & insoperands[j]) || // Generally, more specific arguments have a higher set bit than less specific ones.
          (resolved->modrmreq && !currentins->modrmreq))) morespecific = true;
    
    if(preferred && !currentins->preffered) continue;
    else if(currentins->preffered) preferred = true; // this order is necessary, since the first if validates there's no preference, and the last if only works if there's no preference
    else if(resolved && !morespecific) continue;
    resolved = currentins;
cont:
    continue;
  }

  if(!resolved) {
    error(ASMERR_INS_ARGUMENT_MISMATCH, "Argument mismatch for %s.", x64stringify(ins, 1));
    return NULL;
  }

  return resolved;
}

// static inline u32 ins_size(x64LookupActualIns* res, x64Ins* ins) {
//   bool rex = res->rex || (res->reg_oper && ins->params[res->reg_oper - 1].value & 0x8);
//   int modrm = res->modrmreq;
//   if(modrm) {
//     x64Operand* rm = ins->params + res->mem_oper - 1;
    
//     if(ismem(rm->type)) {
//       if(rm->value & 0x2000000000000000) modrm = 5;
//       else if(membase(rm->value) & 0x10) modrm = 6; // THIS IS WRONG, IT CAN HAVE SIZE 2 BASED ON HAVING A DISPLACEMENT OR NOT
//       else {
//         if((membase(rm->value) | memindex(rm->value)) & 0x8) rex = true;
//         if (rm->value) {
//           modrm += ((i32) rm->value > 127 || (i32) rm->value < -128) * 3 + 1;
//           if(memindex(rm->value) != 0x10) modrm += 1;
//         }
//       }
//     }
//   }
//   return rex + modrm + res->base_size;
// }

// Instructions to keep note of: MOVS mem, mem on line 1203, page 844 in the manual.
static u32 encode(const x64Ins* ins, x64LookupActualIns* res, u8* opcode_dest) {
  if(!res) return 0;

  // ------------------------------ Special Instructions ------------------------------ //

  // Enter is the weirdest instruction ever :'(
  if(ins->op == ENTER) {
    *(u32*) opcode_dest = 0xC8 << (8 * 3) | (u32) (ins->params[0].value & 0xFF) << (8 * 2) | (u16) ins->params[1].value;
    return 4;
  }

  // ----------------------------- Instruction encoding ----------------------------- //

  u8 *const opcode_dest_start = opcode_dest;

  if(res->vex) {
    u8 vex_map = res->vex & 0xf;
    
    u8 vex_byte = res->vex_byte;
    if(res->vex_oper) vex_byte &= ~(ins->params[res->vex_oper - 1].value << 3);
    
    u8 vex_r = 0x80, vex_x = 0x40, vex_b = 0x20;
    if(res->reg_oper && ins->params[res->reg_oper - 1].value & 0x8) res->modrmreg ? (vex_r = 0) : (vex_b = 0);
    if(res->mem_oper) {
      if(ismem(ins->params[res->mem_oper - 1].type)) {
        if(membase(ins->params[res->mem_oper - 1].value) & 0x8) vex_b = 0;
        if(memindex(ins->params[res->mem_oper - 1].value) & 0x8) vex_x = 0;
      } else if(ins->params[res->mem_oper - 1].value & 0x8) vex_b = 0;
    }
    
    // VEX 3 byte form
    //     7                           0       7                           0
    // +---+---+---+---+---+---+---+---+   +---+---+---+---+---+---+---+---+
    // |~R |~X |~B | map_select        |   |W/E|    ~vvvv      | L |   pp  |
    // +---+---+---+---+---+---+---+---+   +---+---+---+---+---+---+---+---+
    if((res->vex >> 4) || !vex_x || !vex_b) {
      *(u32*) opcode_dest = (u32) 0xC4 | ((vex_map | vex_r | vex_x | vex_b) << 8) | (vex_byte << 16);
      opcode_dest += 3;
    }
    // VEX 2 byte form
    //     7                           0
    // +---+---+---+---+---+---+---+---+
    // |~R |     ~vvvv     | L |   pp  |
    // +---+---+---+---+---+---+---+---+
    else {
      *(u16*) opcode_dest = (u16) 0xC5 | ((vex_byte | vex_r) << 8);
      opcode_dest += 2;
    }
  }
  // Segment Register for memory operands - Prefix group 2 (GCC Ordering)
  if(res->mem_oper && ins->params[res->mem_oper].type & ((u64) 0x7 << 56))
    *opcode_dest = ((u8[]) { 0x26, 0x2e, 0x36, 0x3e, 0x64, 0x65 })[((ins->params[res->mem_oper].type >> 56) & 0x7) - 1], opcode_dest ++;
  
  // 67H prefix - Prefix group 4 (GCC Ordering)
  if(res->mem_oper && (ins->params[res->mem_oper - 1].value & ((u64) 0x1 << 60)))
    *opcode_dest = 0x67, opcode_dest ++;

  // Only for Normal **NON** VEX and EVEX instructions
  if(!res->vex) {
    
    // 66H prefix - Prefix group 3 (GCC Ordering) + FWAIT and Prefix Group 1
    if(res->prefixes) {
      *(u32*) opcode_dest = res->prefixes;
      opcode_dest += 1 + (res->prefixes >= 0x100) + (res->prefixes >= 0x10000);
    }

    // REX prefix
    //     7                           0
    // +---+---+---+---+---+---+---+---+
    // | 0   1   0   0 | W | R | X | B |
    // +---+---+---+---+---+---+---+---+
    
    // Intel SDM 2.2.1.2: REX prefix: The REX prefix is used to access additional registers (R8-R15) and to extend most instructions to 64 bits.
    // W: 1 = 64 Bit Operand Size
    // R: Extension of the ModR/M reg field. REX.R modifies the ModR/M reg field when that field encodes a GPR, SSE, control or debug register.
    // X: Extension of the SIB index field.
    // B: Extension of the ModR/M r/m field, SIB base field, or Opcode reg field.
    // AMD APM Vol 3: 1.8.2 Figure 1-6: Encoding Examples Using REX R, X, and B Bits
    u8 rex = res->rex;
    if(res->reg_oper && ins->params[res->reg_oper - 1].value & 0x8) rex |= res->modrmreg ? 0x44 : 0x41;
    if(res->mem_oper) {
      if(ismem(ins->params[res->mem_oper - 1].type)) {
        if(membase(ins->params[res->mem_oper - 1].value) & 0x8) rex |= 0x41;
        if(memindex(ins->params[res->mem_oper - 1].value) & 0x8) rex |= 0x42;
      } else if(ins->params[res->mem_oper - 1].value & 0x8) rex |= 0x41;
    }
    if(rex) *opcode_dest = rex, opcode_dest ++;
  }

  // opcode
  *(u32*)opcode_dest = res->opcode;
  opcode_dest += res->oplen;

  // ModR/M | MOD = XX, REG = XXX, RM = XXX | https://wiki.osdev.org/X86-64_Instruction_Encoding#:~:text=r/m-,32/64%2Dbit%20addressing,-These%20are%20the
  if(res->modrmreq) {
    u8 modrm = res->modrm;
    const x64Operand* rm = ins->params + res->mem_oper - 1;

    // Need to watch out for VSIB
    // https://en.wikipedia.org/wiki/ModR/M#:~:text=of%20these%20exceptions.-,Special%20SIB%20byte%20addressing%20modes,-%5Bedit%5D

    if(res->modrmreg)
      modrm |= (ins->params[res->reg_oper - 1].value & 0x7) << 3;

    if(ismem(rm->type)) {
      if(rm->value & 0x2000000000000000) // RIP-relative addressing
        *opcode_dest = modrm | 0x05 /* MOD = 00, REG = XXX, RM = 101 (RIP) */, *(i32*)(opcode_dest + 1) = rm->value, opcode_dest += 5;

      else {
        // NOTE: RBP CANNOT BE A BASE REGISTER WHEN USING SIB! Use it to index instead! https://stackoverflow.com/a/52522744/10013227
        u16 base = membase(rm->value);
        u16 index = memindex(rm->value);
        const i32 value = (i32) rm->value;

        if(base & 0x10) { // No base register => SIB byte without base.
          u8 sib = (index | 0x10) ? 0x25/* Scale = 00, Index = 100, Base = 101, both null*/ : memscale(rm->value) << 6 | (index & 0x7) << 3 | 0x5;
          *opcode_dest = modrm | 0x04 /* MOD = 00, REG = XXX, RM = 100 */, *(opcode_dest + 1) = sib;
          *(i32*) (opcode_dest + 2) = value; // I don't know why, but when the base is null, there's always a 32 bit displacement encoded with the ModR/M + SIB byte.
          opcode_dest += 6;
          goto end;
        }

        base &= 0x7; // It doesn't matter if it's an r8-r13 register now, since we already took care of that in the REX prefix byte.        
        if(value || index != 0x10) {
          if(index & 0x10 && base != $esp) {// No SIB byte required!
            if(value < 128 && value >= -128) // 1 byte/8 bit displacement
              *opcode_dest = modrm | 0x40 | base /* MOD = 01, REG = XXX, RM = XXX */, *(opcode_dest + 1) = (i8) value, opcode_dest += 2;

            // 4 byte/32 bit displacement
            else *opcode_dest = modrm | 0x80 | base /* MOD = 10, REG = XXX, RM = XXX */, *(i32*) (opcode_dest + 1) = value, opcode_dest += 5;

          } else { // SIB required.
            if(index == $esp)
              return error(ASMERR_ESPRSP_USED_AS_INDEX, "ESP/RSP cannot be used as an index register for memory addressing! "
                                                        "If not using scale, switch the base and index(esp/rsp), making esp/rsp the base.");
            if(index & 0x10) index = 0x4; // Happens in the case of base being ESP/RSP, in which case we set the index to 0b100(ESP), which is no register for index in SIB.
            *(opcode_dest + 1) = memscale(rm->value) << 6 | index << 3 | base;

            // If using an index without a displacement
            if(!value) *opcode_dest = modrm | 0x04 /* MOD = 00, REG = XXX, RM = 100 */, opcode_dest += 2;

            else if(value < 128 && value >= -128) // 1 byte/8 bit displacement
              *opcode_dest = modrm | 0x44 /* MOD = 01, REG = XXX, RM = 100 */, *(opcode_dest + 2) = (i8) value, opcode_dest += 3;

            // 4 byte/32 bit displacement
            else *opcode_dest = modrm | 0x84 /* MOD = 10, REG = XXX, RM = 100 */, *(i32*) (opcode_dest + 2) = value, opcode_dest += 6;
          }
        }
        else if(base == $esp) // Special case for ESP/RSP without displacement since ESP as base for the RM means that SIB is used.
          *opcode_dest = modrm | 0x04 /* MOD = 00, REG = XXX, RM = 100 */, *(opcode_dest + 1) = 0x24 /* Scale = 00, Index = 100, Base = 100 */, opcode_dest += 2;
        else if(base == $ebp) // Special case for register EBP/R13 without displacement because with mod = 00, r13 = rip
          *opcode_dest = 0x45 /* MOD = 01, REG = XXX, RM = 101 */, *(opcode_dest + 1) = 0 /* 1 Byte/8 Bit Disp */, opcode_dest ++;
        else *opcode_dest = modrm | base, opcode_dest ++;
      }
    } else *opcode_dest = modrm | 0xC0 | (rm->value & 0x7) /* MOD = 11, REG = XXX, RM = XXX */, opcode_dest ++; // Is not a memory operand, so RM is the register number.
  }

  // For instructions that have +rw, +rd etc
  else if(res->reg_oper)
    *(opcode_dest - 1) |= (ins->params[res->reg_oper - 1].value & 0x7);

end:
  if(res->imm_oper) {
    u32 size = res->args[res->imm_oper - 1] >> 1;
    switch(size) {
    case 1: *       opcode_dest = ins->params[res->imm_oper - 1].value; break;
    case 2: *(i16*) opcode_dest = ins->params[res->imm_oper - 1].value; break;
    case 4: *(i32*) opcode_dest = ins->params[res->imm_oper - 1].value; break;
    case 8: *(i64*) opcode_dest = ins->params[res->imm_oper - 1].value; break;
    }
    opcode_dest += size;
  }

  // Relative displacement for instructions like JMP
  else if(res->rel_oper) {
    if(res->args[res->rel_oper - 1] == REL8) {
      *opcode_dest = ins->params[res->rel_oper - 1].value;
      opcode_dest ++;
    } else { // HAS to be Rel32 for x64.
      *(i32*) opcode_dest = ins->params[res->rel_oper - 1].value;
      opcode_dest += 4;
    }
  }

  else if(res->is4_oper)
    *opcode_dest = (u8) ins->params[res->is4_oper - 1].value << 4, opcode_dest ++;

  return opcode_dest - opcode_dest_start;
}


u32 x64emit(const x64Ins* ins, u8* opcode_dest) {
  x64LookupActualIns* res = identify(ins);
  return encode(ins, res, opcode_dest);
}


static const char* reg_stringify(const x64Operand* reg) {
  if(reg->type & R8) return ((const char*[]){ "al", "cl", "dl", "bl", "sil", "dil", "bpl", "spl", "r8b", "r9b", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b" })[reg->value];
  if(reg->type & RH) return ((const char*[]){ "ah", "ch", "dh", "bh" })[reg->value];
  if(reg->type & R16) return ((const char*[]){ "ax", "cx", "dx", "bx", "sp", "bp", "si", "di", "bp", "sp", "r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w" })[reg->value];
  if(reg->type & R32) return ((const char*[]){ "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d" })[reg->value];
  if(reg->type & R64) return ((const char*[]){ "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" })[reg->value];
  if(reg->type & XMM) return ((const char*[]){ "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7", "xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15", "xmm16", "xmm17", "xmm18", "xmm19", "xmm20", "xmm21", "xmm22", "xmm23", "xmm24", "xmm25", "xmm26", "xmm27", "xmm28", "xmm29", "xmm30", "xmm31" })[reg->value];
  if(reg->type & YMM) return ((const char*[]){ "ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7", "ymm8", "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15", "ymm16", "ymm17", "ymm18", "ymm19", "ymm20", "ymm21", "ymm22", "ymm23", "ymm24", "ymm25", "ymm26", "ymm27", "ymm28", "ymm29", "ymm30", "ymm31" })[reg->value];
  if(reg->type & ZMM) return ((const char*[]){ "zmm0", "zmm1", "zmm2", "zmm3", "zmm4", "zmm5", "zmm6", "zmm7", "zmm8", "zmm9", "zmm10", "zmm11", "zmm12", "zmm13", "zmm14", "zmm15", "zmm16", "zmm17", "zmm18", "zmm19", "zmm20", "zmm21", "zmm22", "zmm23", "zmm24", "zmm25", "zmm26", "zmm27", "zmm28", "zmm29", "zmm30", "zmm31" })[reg->value];
  if(reg->type & MM) return ((const char*[]){ "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7" })[reg->value];
  if(reg->type & SREG) return ((const char*[]){ "es", "cs", "ss", "ds", "fs", "gs" })[reg->value];
  if(reg->type & CR0_7) return ((const char*[]){ "cr0", "cr1", "cr2", "cr3", "cr4", "cr5", "cr6", "cr7" })[reg->value];
  if(reg->type & CR8) return "cr8";
  if(reg->type & DREG) return ((const char*[]){ "dr0", "dr1", "dr2", "dr3", "dr4", "dr5", "dr6", "dr7" })[reg->value];
  if(reg->type & ST_0) return "st";
  else if(reg->type & ST) return ((const char*[]){ "st(0)", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)" })[reg->value];
  return NULL;
}

static const char* reg_ref_stringify(int reg) {
  if(reg == $none || reg > 40) return NULL;
  return ((const char*[]) { "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d", "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "rip", "es", "cs", "ss", "ds", "fs", "gs" })[reg];
}

enum: u64 {
  allregmask = R8 | RH | R16 | R32 | R64 | MM | XMM | YMM | ZMM | SREG | CR0_7 | DREG | CR8,
  allfarmask = FARPTR1616 | FARPTR1632 | FARPTR1664
};

char* x64stringify(const x64 p, u32 num) {
  if(!num) return "";
  
  u32 mallocsize = num * 20 + 50;
  char* code = malloc(mallocsize);
  u32 cursize = 0;
  u32 curins = 0;
  u8 tab;

  if(num == 1) tab = ' ';
  else {
    tab = code[cursize] = '\t';
    cursize ++;
  }

  while (num --) {
    if (p[curins].op > sizeof(x64Table) / sizeof(x64LookupGeneralIns) || p[curins].op < 1) {
      error(ASMERR_INVALID_INS, "Invalid instruction: %d.", p[curins].op);
      return NULL;
    }
    const x64LookupGeneralIns* ins = x64Table + (p[curins].op - 1);

    u32 inslen = strlen(ins->name);
    memcpy(code + cursize, ins->name, inslen);
    cursize += inslen;

    if(p[curins].params[0].type) {
      code[cursize] = tab;
      cursize ++;
    }

    for(u32 i = 0; i < 4; i ++) {
      if(!p[curins].params[i].type) break;
      if(i) {
        code[cursize] = ',';
        code[cursize + 1] = ' ';
        cursize += 2;
      }
      if(p[curins].params[i].type & allregmask) {
        const char* reg = reg_stringify(p[curins].params + i);
        if(!reg) {
          error(ASMERR_INVALID_REG_TYPE, "Invalid register type: %llX", p[curins].params[i].type);
          free(code);
          return NULL;
        }
        u32 reglen = strlen(reg);
        memcpy(code + cursize, reg, reglen);
        cursize += reglen;
      }
      else if(p[curins].params[i].type & (IMM8 | IMM16 | IMM32 | IMM64))
        cursize += sprintf(code + cursize, "0x%llX", p[curins].params[i].value);

      else if(p[curins].params[i].type & (REL8 | REL32))
        cursize += sprintf(code + cursize, "$%+d", (u32) p[curins].params[i].value);

      // Rip relative memory operand detection
      else if(p[curins].params[i].type & (X64_ALLMEMMASK | allfarmask) && p[curins].params[i].value & ((u64)1 << 62))
        cursize += sprintf(code + cursize, "[$%+d]", (u32) p[curins].params[i].value);

      else if(p[curins].params[i].type == X64_LABEL_REF)
        cursize += sprintf(code + cursize, "%s", p[curins].label_name);

      else if(p[curins].params[i].type & (X64_ALLMEMMASK | allfarmask)) {

        if(p[curins].params[i].type != X64_ALLMEMMASK) {
          const int type = p[curins].params[i].type;

          if(type & allfarmask) memcpy(code + cursize, "far ", 4), cursize += 4;
          else {
            const int ptrstrlen = ((u32 const[]) { 9, 9, 10, 10, 12, 12, 12 })[- (__builtin_clz(type) - 25)];
            memcpy(code + cursize, ((char const *const[]) { "byte ptr ", "word ptr ", "dword ptr ", "qword ptr ", "xmmword ptr ",
              "ymmword ptr ", "zmmword ptr " })[- (__builtin_clz(type) /* f(type) = 32 - log_2 type */ - 25 /* f(M8) */)], ptrstrlen);
            cursize += ptrstrlen;
          }
        }
        

        if(p[curins].params[i].value & 0x0700000000000000)
          cursize += sprintf(code + cursize, "%s:", reg_ref_stringify(((p[curins].params[i].value >> 48) & 0x7) - 1 + $es));

        code[cursize] = '[';
        cursize += 1;

        if(p[curins].params[i].value & 0x2000000000000000) {
          if(p[curins].params[i].value & 0x2000000000000000)
            cursize += sprintf(code + cursize, "rip + 0x%X", (u32) p[curins].params[i].value);

          // RIP-relative taking instructions into account
          else cursize += sprintf(code + cursize, "$%+d", (u32) p[curins].params[i].value);
          
        } else {
          u32 base = membase(p[curins].params[i].value);
          u32 index = memindex(p[curins].params[i].value);
          u32 scale = memscale(p[curins].params[i].value);
          u32 disp = (u32) p[curins].params[i].value;

          if(!(base & 0x10))
            cursize += sprintf(code + cursize, "%s", reg_ref_stringify(base + (p[curins].params[i].value & 0x1000000000000000 ? 0 : $rax)));

          if(disp) cursize += sprintf(code + cursize, " + 0x%X", disp);

          if(!(index & 0x10))
            cursize += sprintf(code + cursize, " + %s", reg_ref_stringify(index + (p[curins].params[i].value & 0x1000000000000000 ? 0 : $rax)));

          if(scale) cursize += sprintf(code + cursize, " * %d", 1 << scale);
        }
        code[cursize] = ']';
        cursize ++;
      }
    }

    // If there is a next instruction, add a newline.
    if(num > 0)
      *((u16*) code + cursize) = (u16) ('\n' << 8) | '\t', cursize += 2;

    if(cursize + 50 >= mallocsize) {
      mallocsize += 100 + num * 20;
      code = realloc(code, mallocsize);
    }
    curins ++;
  }

  code[cursize] = 0;
  return code;
}


struct x64_relative {
  u32 ins; bool relref; // regular relative or riprel
  u8 size; u8 param;
  x64LookupActualIns* res;
};

// static inline u32 fnv1a(const char* data) {
//   u32 hash = 0x811c9dc5;
//   while (*data) {
//     hash ^= *data++;
//     hash += (hash<<1) + (hash<<4) + (hash<<7) + (hash<<8) + (hash<<24);
//   }
//   return hash;
// }

// static inline u32 checksum(const char* data) {
//   u32 hash = 0;
//   while (*data) hash += *data++;
//   return hash;
// }


/**
Current Problems with label-based linking:
  - Need to completely change the original instruction and re-identify the instruction when trying to reduce the size of JMP / JCC instructions, since labels don't have a size.
  - Need to keep re-calculating all of the instruction distances when a jump instruction changes size, as there can be jumps inside the area jumped over.
  - Need to have a format that supports bringing different code together with different labels to allow them to link together

union x64MCode {
  u8 bytes[16];
  struct {
    u8 len;
    u8 data[15];
  };
};
typedef union x64MCode x64MCode;

struct x64AssemblyRes {
  x64MCode* code;
  u32 code_len;
  struct x64Relocatable {
    x64Op op;
    
  }* reloc;
};

So I just want to release this tech, I will hold off on label based linking and string storage.
*/

/**
*things to note in readme*

jmp rel8 vs jmp rel32
no labels for now
use x64emit to emit single instructions
highlight $riprel and rel()
geterror()
highlight that the mem() macro's scale only takes 1, 2, 4 or 8
add disclaimer/issue that vsib for instructions like vgatherqpd cannot be stringified with the current method
*/

u8* x64as(const x64 p, u32 num, u32* len) {
  u32 code_size = num * 15;// 15 is the maximum size of 1 instruction. Example: lwpval rax, cs:[rax+rbx*8+0x23829382], 100000000
  u32 indexes_size = num * sizeof(u16);
  u32 relref_size = (num / 2) * sizeof(struct x64_relative); // THIS SHOULD BE ENOUGH IN MOST CASES

  u8 *const encoding_arena = calloc(code_size + indexes_size + relref_size, 1);
  u8 *const code = encoding_arena;
  u16 *const indexes = (u16*) (encoding_arena + code_size);
  struct x64_relative *const relrefidxes = (struct x64_relative*) (encoding_arena + code_size + indexes_size);
  // 2048 * 15 + 200 * 8 + 2048 * 4 + 2048 * 8 + 1024 * 16 = 73280, about 35x more memory than instructions :skull:

  *len = 0;
  u32 codelen = 0;
  u32 index = 0;
  u32 relreflen = 0;
  
  while (num --) {
    x64LookupActualIns* res = identify(p + index);
    if(!res) goto error;
    int curlen = encode(p + index, res, code + codelen);
    if(!curlen) goto error;

    if(res->rel_oper) {
      i32 insns = p[index].params[res->rel_oper - 1].value;

      // we don't need relrefs if the value was negative
      if(insns <= 1) {
        if(insns + index < 0) {
          // error(ASMERR_REL_OUT_OF_RANGE, "Relative reference out of range on ins '%s'", x64stringify(p + index, 1));
          goto error;
        }

        i32 offset;

        if(insns == 1) offset = 0;
        else if (insns == 0) offset = -curlen;
        else offset = indexes[index + insns] - curlen;

        // printf("\nAssembling %s with an emission length of %d at index %d, referencing instruction %d away(%s), with offset %d\n", x64stringify(p + index, 1), curlen, index, insns, x64stringify(p + index + insns, 1), offset);
        if(res->args[res->rel_oper - 1] == REL32) *(int*) (code + codelen - 4) = offset;
        else code[codelen - 1] = (i8) offset;
      } else {
        relrefidxes[relreflen].ins = index;
        relrefidxes[relreflen].res = res;
        relrefidxes[relreflen].param = res->rel_oper - 1;
        relreflen ++;
      }
    }

    // Identify relrefs
    else if(res->mem_oper && p[index].params[res->mem_oper - 1].value & 0x4000000000000000) {
      i32 insns = p[index].params[res->mem_oper - 1].value;

      // If resolving offsets for instructions that were already resolved, including the current instruction, take this fast path before adding work to the other for loop
      if(insns <= 1) {
        if(insns + index < 0) {
          error(ASMERR_REL_OUT_OF_RANGE, "Relative reference out of range on ins '%s'", x64stringify(p + index, 1));
          goto error;
        }

        i32 offset;

        if(insns == 1) offset = 0;
        else if (insns == 0) offset = -curlen;
        else offset = indexes[index + insns] - codelen - curlen;
        
        // printf("\nAssembling %s with an emission length of %d at index %d, referencing instruction %d away(%s), with offset %d\n", x64stringify(p + index, 1), curlen, index, insns, x64stringify(p + index + insns, 1), offset);

        // Currently no better way other than to directly reencode.

        x64Ins ins = p[index];
        ins.params[res->mem_oper - 1].value &= ~((u64) 0xffffffff);
        ins.params[res->mem_oper - 1].value |= ((u64) offset) & 0xffffffff;
        encode(&ins, res, code + codelen);
      } else {
        relrefidxes[relreflen].ins = index;
        relrefidxes[relreflen].res = res;
        relrefidxes[relreflen].param = res->mem_oper - 1;
        relrefidxes[relreflen].relref = true;
        relreflen ++;
      }
    }

    indexes[index] = codelen;
    codelen += curlen;

    index ++;
  }

  for(u32 i = 0; i < relreflen; i ++) {

    // Index of current instruction in `indexes`
    u32 relidx = relrefidxes[i].ins;
    const i64* insoffset = &p[relidx].params[relrefidxes[i].param].value;
    i32 offset = indexes[relidx + /* The current instruction that is being resolved */ *(i32*) insoffset /* The offset of the relative */]
                 - indexes[relidx + 1]; /* Added 1 because the offset is added to a rip pointing to the next instruction */
    
        // printf("\nAssembling %s at index %d, referencing instruction %d away(%s), with offset %d\n", x64stringify(p + relidx, 1), relidx, *(i32*)insoffset, x64stringify(p + relidx + *insoffset, 1), offset);
    if(relrefidxes[i].relref) {
      // Currently no better way other than to directly reencode.
      x64Ins ins = p[relidx];
      ins.params[relrefidxes[i].param].value &= ~((u64) 0xffffffff);
      ins.params[relrefidxes[i].param].value |= ((u64) offset) & 0xffffffff;
      // printf("Assembling %s at index %d, referencing instruction %d away, with offset %d\n", x64stringify(p + relidx, 1), relidx, (i32) p[relidx].params[relrefidxes[i].param].value, offset);
      encode(&ins, relrefidxes[i].res, code + indexes[relidx]);
    } else {
      if(relrefidxes[i].size == 4) {
        *(int*) (code + indexes[relidx + 1] - 4) = offset;
      } else code[indexes[relidx + 1] - 1] = (i8) offset;
    }
  }

  *len = codelen;
  return encoding_arena;
error:
  free(encoding_arena);
  *len = 0;
  return NULL;
}

// Aligns to the next multiple of a, where a is a power of 2
static inline u32 align(u32 n, u32 a) { return (n + a - 1) & ~(a - 1); }

#if defined _WIN32 | defined __CYGWIN__

// https://learn.microsoft.com/en-us/windows/win32/memory/memory-protection-constants
#define PAGE_EXECUTE_READ 0x20
#define PAGE_READWRITE 0x4
// https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualalloc
#define MEM_COMMIT 0x00001000

__attribute((dllimport)) void* __attribute((stdcall)) VirtualAlloc(void* lpAddress, size_t dwSize, u32 flAllocationType, u32 flProtect);
__attribute((dllimport)) int __attribute((stdcall)) VirtualProtect(void* lpAddress, size_t dwSize, u32 flNewProtect, u32* lpflOldProtect);

void (*x64_exec(void* mem, u32 size))() {
	u32 pagesize = 4096;
	u32 alignedsize = align(size, pagesize);

	void* buf = VirtualAlloc(NULL, alignedsize, MEM_COMMIT, PAGE_READWRITE);
	memcpy(buf, mem, size);

	u32 old;
	VirtualProtect(buf, size, PAGE_EXECUTE_READ, &old);
	return buf;
}

#else
#include <sys/mman.h>
#include <unistd.h>

void (*x64_exec(void* mem, u32 size))() {
	u32 pagesize = sysconf(_SC_PAGESIZE);
	u32 alignedsize = align(size, pagesize);

	// printf("Page size: %d\n", pagesize);
	// printf("Original size: %d, new size: %d\n", size, alignedsize);

	void* buf = mmap(NULL, alignedsize, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON, -1, 0);
	memcpy(buf, mem, size);

	mprotect(buf, size, PROT_READ | PROT_EXEC);

	return buf;
}

#endif
