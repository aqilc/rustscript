import { readFileSync as read, writeFileSync as write } from "fs";

/**
 * TODO:
 * - Add system that removes instructions not yet supported.
 */

// console.log(process.argv);
let file = (read("x86.csv") + '')
	.split("\r\n").filter(s => s.trim());
console.log(file.slice(0, 1)[0]);
// [0] Opcode  [1] Instruction  [2] Op/En  [3] Properties  [4] Implicit Read  [5] Implicit Write  [6] Implicit Undef  [7] Useful  [8] Protected  [9] 64-bit Mode  [10] Compat/32-bit-Legacy Mode  [11] CPUID Feature Flags  [12] AT&T Mnemonic  [13] Preferred  [14] Description

const rows = file.slice(1).filter(s => s.trim()).map(s => s.split("\t"));
// const atntnames = new Set(rows.filter(s => s[12]).map(s => ['b', 'w', 'l', 'q'].includes(s[12][s[12].length - 1]) ? s[12].slice(0, -1) : s[12]));
const instruction_variants = {};
let prefixes = {
	"PREF.66+": "0x66",
	"66": "0x66",
	"F2": "0xF2",
	"F3": "0xF3",
}
for(let row of rows) {
	// const name = row[12].replace(" ", "_");

	// Op/En not yet supported
	if(row[2]) continue;

	// Skip VEX instructions
	if(row[0][0] === "V") continue;

	// Skip instructions with displacement
	if(row[0].match(/\/\d/)) continue;

	const name = row[1].split(" ")[0]
	if(!instruction_variants[name])
		instruction_variants[name] = [];

	// Decode opcodes in the format of "REX+ 80 /4 ib"
	let opcode = row[0].split(" ");
	let variant = "{ ";
  let bytes = "";
	for(let i of opcode);
  variant += " }";
	instruction_variants[name].push(variant);
}
// console.log("{\n" + file.slice(40, 50).map(s => "\t{ " + s.split("\t").map(s => s || "0").join(", ") + " }").join(",\n") + "\n}");
console.log(Object.fromEntries(Object.entries(instruction_variants).slice(0, 10)));
console.log(Object.values(instruction_variants).reduce((a, b) => a < b.length ? b.length : a, 0) + " variants");
// Instruction decoder:
// Decodes instructions like "REX+ 80 /4 ib" this and returns a value in the form of the struct

let asmh = `#pragma once
#include <stdint.h>
#include <hash.h>
#include "util.h"

enum x64OperandType {
	NONE = 0, //for an operand constructed without a type

  HINT = 0x1,

  // IMMEDIATES
  IMM64 = 0x2, IMM32 = 0x4, IMM16 = 0x8, IMM8 = 0x2,
  ZERO = 0x20, ONE = 0x40, THREE = 0x80, // For the enter/leave instructions

  LABEL = 0x100,

  M8 = 0x200, M16 = 0x400, M32 = 0x800, M64 = 0x1000, M128 = 0x2000, M256 = 0x4000, M16_INT = 0x8000, M32_INT = 0x10000,
  M64_INT = 0x20000, M32_FP = 0x40000, M64_FP = 0x80000, M80_FP = 0x100000, M80_BCD = 0x200000, M2_BYTE = 0x400000,
  M28_BYTE = 0x800000, M108_BYTE = 0x1000000, M512_BYTE = 0x2000000,
  FAR_PTR_16_16 = 0x4000000, FAR_PTR_16_32 = 0x8000000, FAR_PTR_16_64 = 0x10000000,
  
  MM = 0x20000000,

  PREF66 = 0x40000000,
  PREFREX_W = 0x80000000,
  FAR = 0x100000000,

  MOFFS8 = 0x200000000, MOFFS16 = 0x400000000, MOFFS32 = 0x800000000, MOFFS64 = 0x1000000000,

  R8 = 0x2000000000, RH = 0x4000000000, AL = 0x8000000000, CL = 0x10000000000,
  R16 = 0x20000000000, AX = 0x40000000000, DX = 0x80000000000,
  R32 = 0x100000000000, EAX = 0x200000000000,
  R64 = 0x400000000000, RAX = 0x800000000000,

  REL8 = 0x1000000000000,
  REL32 = 0x2000000000000,

  SEGMENT_REG = 0x4000000000000, FS = 0x8000000000000, GS = 0x10000000000000,

  ST = 0x20000000000000, ST_0 = 0x40000000000000,

  XMM = 0x80000000000000, XMM_0 = 0x100000000000000,
  YMM = 0x200000000000000 // EXACTLY ENOUGH TO FIT IN A 64-BIT INTEGER LETS FUCKING GO
};
typedef enum x64OperandType x64OperandType;

enum x64OperandSize { BYTE, WORD, LONG, QUAD };
typedef enum x64OperandSize x64OperandSize;

enum x64Op {
	${Object.keys(instruction_variants).map(s => s.toUpperCase().replace(" ", "_")).join(", ")}
};
typedef enum x64Op x64Op;


struct x64PrefGroup {
	enum { PREF_GROUP_1, PREF_GROUP_2, PREF_GROUP_3, PREF_GROUP_4 } group;
};
typedef struct x64PrefGroup x64PrefGroup;

struct x64Operand {
  x64OperandType type;
  u64 value;
};
typedef struct x64Operand x64Operand;

struct x64Ins {
	x64Op op;
	x64Operand params[4];
};
typedef struct x64Ins x64Ins;
typedef x64Ins x64[];

struct x64LookupGeneralIns {
	char* name;
	unsigned int numactualins;
	struct x64LookupActualIns {
		x64PrefGroup pref_groups[4];
		char opcode[4];
    bool modrm;
		x64OperandSize displacement;
    x64OperandSize immediate;
		x64OperandType args[4];
	}* ins;
};
typedef struct x64LookupGeneralIns x64LookupGeneralIns;

struct x64LookupGeneralIns x64Table[] = {
${Object.entries(instruction_variants).map(([name, variants]) => `\t{ "${name.toLowerCase().replace("_", " ")}", ${variants.length}, (struct x64LookupActualIns[]) { ${variants.join(", ")} } }`).join(",\n")}
};


#define imm(value) (x64Operand) { (((value) < 0x100) ? IMM8 : ((value) < 0x10000) ? IMM16 : ((value) < 0x100000000) ? IMM32 : IMM64), value }

#define eax { EAX | R32 }
#define ecx { R32, 1 }
#define edx { R32, 2 }
#define ebx { R32, 3 }
#define esp { R32, 4 }
#define ebp { R32, 5 }
#define esi { R32, 6 }
#define edi { R32, 7 }
#define r8d { R32, 8 }
#define r9d { R32, 9 }
#define r10d { R32, 10 }
#define r11d { R32, 11 }
#define r12d { R32, 12 }
#define r13d { R32, 13 }
#define r14d { R32, 14 }
#define r15d { R32, 15 }


#define rax { RAX | R64 }
#define rcx { R64, 1 }
#define rdx { R64, 2 }
#define rbx { R64, 3 }
#define rsp { R64, 4 }
#define rbp { R64, 5 }
#define rsi { R64, 6 }
#define rdi { R64, 7 }
#define r8 { R64, 8 }
#define r9 { R64, 9 }
#define r10 { R64, 10 }
#define r11 { R64, 11 }
#define r12 { R64, 12 }
#define r13 { R64, 13 }
#define r14 { R64, 14 }
#define r15 { R64, 15 }

`;

write(`asm_x86.h`, asmh);