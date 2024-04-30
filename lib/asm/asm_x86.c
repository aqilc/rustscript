/*
 * asm_x86.c v1.0.0 - Aqil Contractor @AqilC 2023
 * Licenced under Attribution-NonCommercial-ShareAlike 3.0
 *
 * This file includes all of the source for the "chasm" library macros and functions.
 * WARNING: CURRENTLY NOT FULLY THREAD SAFE. Use with caution when using in thread safe code!
 */

#include <stdio.h>
#include <string.h>
#include <util.h>
#include <stdarg.h>
#include <malloc.h>
#include "asm_x86.h"

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

 * - https://gist.github.com/mikesmullin/6259449 # Mike's x86 assembly notes
 *   - https://gist.github.com/mikesmullin/6259449#appendix-reverse-engineering--malware-analysis
 *   - https://gist.github.com/mikesmullin/6259449#appendix-writing-a-compiler
 */

// https://l-m.dev/cs/jitcalc/#:~:text=make%20it%20executable%3F-,C%20Territory,-V%20does%20not

static u32 encode(x64Ins* ins, x64LookupActualIns* res, char* opcode_dest);

#define ismem(x) (x >= M8 && x <= FARPTR1664)
#define membase(x) ((x >> 32) & 0x1f)
#define memindex(x) ((x >> 40) & 0x1f)
#define memscale(x) ((x >> 48) & 0x3)

_Thread_local struct AssemblyError {
	bool error;
	char buf[100];
	enum AssemblyErrorType {
		ASMERR_INVALID_INS,
		ASMERR_INVALID_REG_TYPE,
		ASMERR_NO_MATCHING_INS,
		ASMERR_ESPRSP_USED_AS_BASE,
		ASMERR_REL_OUT_OF_RANGE
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

static inline x64LookupActualIns* identify(x64Ins* ins) {
	if (ins->op > sizeof(x64Table) / sizeof(x64LookupGeneralIns)) {
		error(ASMERR_INVALID_INS, "Invalid instruction: %d", ins->op);
		return NULL;
	}

	const x64LookupGeneralIns* unresins = x64Table + (ins->op - 1);
	x64LookupActualIns* resolved = NULL;
	bool preferred = false;

	u64 insoperands[] = { ins->params[0].type, ins->params[1].type, ins->params[2].type, ins->params[3].type };

	u32 operandnum = 0;
	while(ins->params[operandnum].type)
		operandnum ++;

	// ---------------------- Instruction resolution and Validation ---------------------- //

	for(u32 i = 0; i < unresins->numactualins; i ++) {
		if(unresins->ins[i].arglen != operandnum) continue;
		x64LookupActualIns* actual = unresins->ins + i;

		bool match = true;
		bool morespecific = false;
		for(u32 j = 0; j < actual->arglen; j ++)
			if(!(actual->args[j] & insoperands[j])) { match = false; break; }
			else if(resolved && (
					resolved->args[j] < (actual->args[j] & insoperands[j]) || // Generally, more specific arguments have a higher set bit than less specific ones.
					// resolved->oplen + resolved->preflen + !!resolved->pref66 > actual->oplen + actual->preflen + !!actual->pref66 ||
					(resolved->modrmreq && !actual->modrmreq))) morespecific = true;
		if(!match || (preferred && !actual->preffered)) continue;
		else if(actual->preffered) preferred = true;
		else if(resolved && !morespecific) continue;
		resolved = actual;
	}

	if(!resolved) {
		error(ASMERR_NO_MATCHING_INS, "No matching instruction for %s", x64stringify(ins));
		return NULL;
	}

	return resolved;
}

// Instructions to keep note of: MOVS mem, mem on line 1203, page 844 in the manual.
static u32 encode(x64Ins* ins, x64LookupActualIns* res, char* opcode_dest) {
	if(!res) return 0;

	// ------------------------------ Special Instructions ------------------------------ //

	// Enter is the weirdest instruction ever :'(
	if(ins->op == ENTER) {
		memcpy(opcode_dest, (u8[]) { 0xC8,
			ins->params[0].value,
			ins->params[1].value >> 8,
			ins->params[1].value
		}, 1);
		return 4;
	}

	// ----------------------------- Instruction encoding ----------------------------- //

	char const* opcode_dest_start = opcode_dest;

	// Segment Register for memory operands - Prefix group 2 (GCC Ordering)
	if(res->mem_operand && ins->params[res->mem_operand].type & ((u64) 0x7 << 56))
		*opcode_dest = ((char[]) { 0x26, 0x2e, 0x36, 0x3e, 0x64, 0x65 })[((ins->params[res->mem_operand].type >> 56) & 0x7) - 1], opcode_dest ++;
	
	// 67H prefix - Prefix group 4 (GCC Ordering)
	if(res->mem_operand && (ins->params[res->mem_operand - 1].value & ((u64) 0x1 << 60)))
		*opcode_dest = 0x67, opcode_dest ++;

	// Only for Normal **NON** VEX and EVEX instructions
	if(!res->vexxopevex) {

		// 66H prefix - Prefix group 3 (GCC Ordering) + FWAIT and Prefix Group 1
		if(res->prefixes) {
			if(res->prefixes < 0x100) *opcode_dest = res->prefixes, opcode_dest ++;
			else if(res->prefixes < 0x10000) *(u16*) opcode_dest = res->prefixes, opcode_dest += 2;
			else *(u16*) opcode_dest = res->prefixes >> 8, *(u8*) (opcode_dest + 2) = res->prefixes & 0xff, opcode_dest += 3;
		}
	}

	// REX prefix
	u8 rex = res->rex;
	if(res->reg_operand && ins->params[res->reg_operand - 1].value & 0x8) rex |= res->modrmreg ? 0x44 : 0x41;
	if(res->mem_operand) {
		if(ismem(ins->params[res->mem_operand - 1].type)) {
			if(membase(ins->params[res->mem_operand - 1].value) & 0x8) rex |= 0x41;
			if(memindex(ins->params[res->mem_operand - 1].value) & 0x8) rex |= 0x42;
		} else if(ins->params[res->mem_operand - 1].value & 0x8) rex |= 0x41;
	}
	if(rex) *opcode_dest = rex, opcode_dest ++;

	// opcode
	memcpy(opcode_dest, res->opcode, res->oplen);
	opcode_dest += res->oplen;

	// ModR/M | MOD = XX, REG = XXX, RM = XXX | https://wiki.osdev.org/X86-64_Instruction_Encoding#:~:text=r/m-,32/64%2Dbit%20addressing,-These%20are%20the
	if(res->modrmreq) {
		u8 modrm = res->modrm;
		x64Operand* rm = ins->params + res->mem_operand - 1;

		if (res->modrmreg)
			modrm |= (ins->params[res->reg_operand - 1].value & 0x7) << 3;

		if(ismem(rm->type)) {
			if(rm->value & 0x2000000000000000) // RIP-relative addressing
				*opcode_dest = modrm | 0x05 /* MOD = 00, REG = XXX, RM = 101 (RIP) */, *(int*)(opcode_dest + 1) = rm->value, opcode_dest += 5;

			else {
				// NOTE: RBP CANNOT BE A BASE REGISTER WHEN USING SIB! Use it to index instead! https://stackoverflow.com/a/52522744/10013227
				u16 base = membase(rm->value);
				u16 index = memindex(rm->value);

				if(base & 0x10) { // No base register => SIB byte without base.
					u8 sib = (index | 0x10) ? 0x25/* Scale = 1, Index = 100, Base = 101, both null*/ : memscale(rm->value) << 6 | (index & 0x7) << 3 | 0x5;
					*opcode_dest = modrm | 0x04 /* MOD = 00, REG = XXX, RM = 100 */, *(opcode_dest + 1) = sib;
					*(int*) (opcode_dest + 2) = (int) rm->value; // I don't know why, but when the base is null, there's always a 32 bit displacement encoded with the ModR/M + SIB byte.
					opcode_dest += 6;
					goto end;
				}

				base &= 0x7; // It doesn't matter if it's an r8-r13 register now, since we already took care of that in the REX prefix byte.
				if((int) rm->value) {
					if(base == $esp)
						return error(ASMERR_ESPRSP_USED_AS_BASE, "ERROR: ESP/RSP cannot be used as a base register for memory!");

					if(index & 0x10) // No SIB byte required!

						if((int) rm->value <= 128 || (int) rm->value >= -128) // 1 byte/8 bit displacement
							*opcode_dest = modrm | 0x40 | base /* MOD = 01, REG = XXX, RM = XXX */, *(opcode_dest + 1) = (char) rm->value, opcode_dest += 2;

						// 4 byte/32 bit displacement
						else *opcode_dest = modrm | 0x80 | base /* MOD = 10, REG = XXX, RM = XXX */, *(int*) (opcode_dest + 1) = (int) rm->value, opcode_dest += 5;

					else { // SIB required.
						*(opcode_dest + 1) = memscale(rm->value) << 6 | index << 3 | base;

						if((int) rm->value <= 128 || (int) rm->value >= -128) // 1 byte/8 bit displacement
							*opcode_dest = modrm | 0x44 /* MOD = 01, REG = XXX, RM = 100 */, *(opcode_dest + 2) = (char) rm->value, opcode_dest += 3;

						// 4 byte/32 bit displacement
						else *opcode_dest = modrm | 0x84 /* MOD = 10, REG = XXX, RM = 100 */, *(int*) (opcode_dest + 2) = (int) rm->value, opcode_dest += 6;
					}
				}
				else if(base == $ebp) // Special case for register EBP/R13 without displacement because with mod = 00, r13 = rip
					*opcode_dest = 0x45 /* MOD = 01, REG = XXX, RM = 101 */, *(opcode_dest + 1) = (char) rm->value /* 1 Byte/8 Bit Disp */, opcode_dest ++;
				else *opcode_dest = modrm | base, opcode_dest ++;
			}
		} else *opcode_dest = modrm | 0xC0 | (rm->value & 0x7) /* MOD = 11, REG = XXX, RM = XXX */, opcode_dest ++; // Is not a memory operand, so RM is the register number.
	}

	// For instructions that have +rw, +rd etc
	else if(res->reg_operand)
		*(opcode_dest - 1) |= (ins->params[res->reg_operand - 1].value & 0x7);

end:
	// Immediate
	if(res->immediate) {
		u32 size = res->args[res->immediate - 1] >> 1;
		switch(size) {
			case 1: *       opcode_dest = ins->params[res->immediate - 1].value; break;
			case 2: *(u16*) opcode_dest = ins->params[res->immediate - 1].value; break;
			case 4: *(u32*) opcode_dest = ins->params[res->immediate - 1].value; break;
			case 8: *(u64*) opcode_dest = ins->params[res->immediate - 1].value; break;
		}
		opcode_dest += size;
		// if(immediatesize == 8 && 
	}

	// Relative displacement for instructions like JMP
	else if(res->rel_operand) {
		if(res->args[res->rel_operand - 1] == REL8) {
			*opcode_dest = ins->params[res->rel_operand - 1].value;
			opcode_dest ++;
		} else { // HAS to be Rel32 for x64.
			*(int*) opcode_dest = ins->params[res->rel_operand - 1].value;
			opcode_dest += 4;
		}
	}

	return opcode_dest - opcode_dest_start;
}


u32 x64emit(x64Ins* ins, char* opcode_dest) {
	if(ins->op == 0) return 0;
	x64LookupActualIns* res = identify(ins);
	return encode(ins, res, opcode_dest);
}


static const char* reg_stringify(x64Operand* reg) {
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

const u64 allregmask = R8 | RH | R16 | R32 | R64 | MM | XMM | YMM | ZMM | SREG | CR0_7 | DREG | CR8;
char* x64stringify(x64 p) {
	char* code = malloc(100);
	u32 mallocsize = 100;
	u32 cursize = 0;
	u32 curins = 0;

	while (p[curins].op) {
		const x64LookupGeneralIns* ins = x64Table + (p[curins].op - 1);

		code[cursize] = '\t';
		cursize ++;

		u32 inslen = strlen(ins->name);
		memcpy(code + cursize, ins->name, inslen);
		cursize += inslen;

		if(p[curins].params[0].type) {
			code[cursize] = '\t';
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

			else if(p[curins].params[i].type & (M8 | M16 | M32 | M64 | M128 | M256 | M512 | FARPTR1616 | FARPTR1632 | FARPTR1664)) {

				if(p[curins].params[i].value & 0x0700000000000000)
					cursize += sprintf(code + cursize, "%s:", reg_ref_stringify(((p[curins].params[i].value >> 48) & 0x7) - 1 + $es));

				code[cursize] = '[';
				cursize += 1;

				if(p[curins].params[i].value & 0x2000000000000000) {
					if(p[curins].params[i].value & 0x3000000000000000)
						cursize += sprintf(code + cursize, "rip %s 0x%X", p[curins].params[i].value < 0 ? "-" : "+", (i32) p[curins].params[i].value);

					// RIP-relative taking instructions into account
					else cursize += sprintf(code + cursize, "$%+d", (u32) p[curins].params[i].value);
					
				} else {
					u32 base = membase(p[curins].params[i].value);
					u32 index = memindex(p[curins].params[i].value);
					u32 scale = memscale(p[curins].params[i].value);

					if(!(base & 0x10))
						cursize += sprintf(code + cursize, "%s", reg_ref_stringify(base + (p[curins].params[i].value & 0x1000000000000000 ? 0 : $rax)));

					if(p[curins].params[i].value & 0xffffffff)
						cursize += sprintf(code + cursize, " + 0x%X", (u32) p[curins].params[i].value);

					if(!(index & 0x10))
						cursize += sprintf(code + cursize, " + %s", reg_ref_stringify(index + (p[curins].params[i].value & 0x1000000000000000 ? 0 : $rax)));

					if(scale)	cursize += sprintf(code + cursize, " * %d", 1 << scale);
				}
				code[cursize] = ']';
				cursize ++;
			}
		}

		// If there is a next instruction, add a newline.
		if(p[curins + 1].op)
			code[cursize] = '\n', cursize ++;

		if(cursize + 50 >= mallocsize) {
			mallocsize += 100;
			code = realloc(code, mallocsize);
		}
		curins ++;
	}

	code[cursize] = 0;
	return code;
}

char* x64as(u32 num, x64 p, u32* len) {
	u32 cap = num * 7 + 15;
	char* code = malloc(cap); // 15 is the maximum size of an instruction.
	// Example: lwpval rax, cs:[rax+rbx*8+0x23829382], 100000000
	u32 ins = 0;
	*len = 0;

	u16* indexes;
	bool indexmalloced = false;
	if(num > 96)
		indexes = malloc(sizeof(u16) * num), indexmalloced = true;
	else indexes = alloca(sizeof(u16) * num);

	static struct {
		u32 ins; bool relref; // Riprel or normal relative
		u8 size; u8 param;
		x64LookupActualIns* res; // no point in making anything a union because of alignment
	} relrefidxes[48];
	u32 relreflen = 0;

	while (p[ins].op) {
		x64LookupActualIns* res = identify(p + ins);
		int curlen = encode(p + ins, res, code + *len);
		if(!curlen) goto error;

		// Identify relrefs
		if(res->mem_operand && p[ins].params[res->mem_operand - 1].value & 0x4000000000000000) {
			i32 insns = p[ins].params[res->mem_operand - 1].value;
			if(insns < 0) {
				if(insns + ins < 0) {
					error(ASMERR_REL_OUT_OF_RANGE, "Relative reference out of range on ins '%s'", x64stringify(p + ins));
					goto error;
				}

				i32 offset = indexes[ins + offset] - indexes[ins] - curlen;

				// Currently no better way other than to directly reencode.
				p[ins].params[res->mem_operand - 1].value &= ~((u64) 0xffffffff);
				p[ins].params[res->mem_operand - 1].value |= ((u64) offset) & 0xffffffff;
				encode(p + ins, res, code + *len);
			} else {
				relrefidxes[relreflen].ins = ins;
				relrefidxes[relreflen].res = res;
				relrefidxes[relreflen].param = res->mem_operand - 1;
				relrefidxes[relreflen].relref = true;
				relreflen ++;
			}
		}

		if(res->rel_operand) {
			relrefidxes[relreflen].ins = ins;
			relrefidxes[relreflen].size = res->args[res->rel_operand - 1] == REL32 ? 4 : 1;
			relrefidxes[relreflen].param = res->rel_operand - 1;
			relreflen ++;
		}

		indexes[ins] = *len;
		*len += curlen;

		if(*len >= cap) code = realloc(code, (cap += (num - ins) * 15));
		ins ++;
	}

	for(u32 i = 0; i < relreflen; i ++) {
		u32 relidx = relrefidxes[i].ins;
		int offset = indexes[
			relidx + /* The current instruction that is being resolved */
			(i32) p[relidx].params[relrefidxes[i].param].value + /* The offset of the relative */
			1 /* because the offset is after the instruction has ended */
		] - indexes[relidx + 1]; /* Added 1 because the value is after the current rip of the instruction */
		
		if(relrefidxes[i].relref) {
			// Currently no better way other than to directly reencode.
			p[relrefidxes[i].ins].params[relrefidxes[i].param].value &= ~((u64) 0xffffffff);
			p[relrefidxes[i].ins].params[relrefidxes[i].param].value |= ((u64) offset) & 0xffffffff;
			encode(p + relrefidxes[i].ins, relrefidxes[i].res, code + indexes[relidx]);
		} else {
			if(relrefidxes[i].size == 4) {
				*(int*) (code + indexes[relidx + 1] - 4) = offset;
			} else code[indexes[relidx + 1] - 1] = offset;
		}
	}

	if(indexmalloced) free(indexes);
	return code;
error:
	free(code);
	if(indexmalloced) free(indexes);
	*len = 0;
	return NULL;
}

