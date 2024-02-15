import { readFileSync as read, writeFileSync as write } from "fs";

/**
 * References:
 * 	- Vex Instruction Construction:
 * 		- Codegen.hs:1320
 * Notes:
 * 	- Provide special cases for LHS, LSS, and LGS in the first for loop that expands the opcodes
 */

let file = (read("x86.csv") + '')
	.split("\r\n").filter(s => s.trim());
// [0] Opcode  [1] Instruction  [2] Op/En  [3] Properties  [4] Implicit Read  [5] Implicit Write  [6] Implicit Undef  [7] Useful  [8] Protected  [9] 64-bit Mode  [10] Compat/32-bit-Legacy Mode  [11] CPUID Feature Flags  [12] AT&T Mnemonic  [13] Preferred  [14] Description

const rows = file.slice(1).map(s => s.split("\t"));
// const atntnames = new Set(rows.filter(s => s[12]).map(s => ['b', 'w', 'l', 'q'].includes(s[12][s[12].length - 1]) ? s[12].slice(0, -1) : s[12]));
const instruction_variants = {};

let const_prefixes = new Set(["F2", "F3", "9B"]);

const operand_types = str => {
	if(Array.isArray(str)) return str;
	if(str.includes("/")) {
		let [a, b] = str.split("/");
		if(a === "r" && b.startsWith("m")) return ["R" + b.slice(1), "M" + b.slice(1)];
		return [operand_types(a), operand_types(b)]; // Recursively expands reg and mm if needed.
	}
	if(str === "<xmm0>") return "XMM_0";
	let mm = str.match(/^([xy]?)mm/)?.[1];
	if(mm !== undefined) return mm.toUpperCase() + "MM";
	if(str === "mem" || str === "m") return ["M64", "M32", "M16"];
	if(str === "reg") return ["R64", "R32"];
	if(str === "r8") return ["RH", "R8"];
	if(str.startsWith("m16:")) return "FARPTR16" + str.slice(4);
	if(str === "p66") return "PREF66";
	if(str === "pw") return "PREFREX_W";
	if(str === "cr0-cr7") return "CR0_7";
	if(str === "dr0-dr7") return "DREG";
	if(str === "1") return "ONE";
	if(str === "" + (+str)) return false;
	return str.toUpperCase();
}

function insert_ins(row, name, operands) {
	let actualops = [];
	for(let j = 0; j < operands.length; j++) {
		let oper = operand_types(operands[j]);
		if(!oper) { /*console.log("Skipping encoding instruction " + name + " with operands " + operands); */ return; }
		if(name === "ENTER" && !oper.startsWith("IMM")) { /*console.log("Skipping ENTER with operands ", operands); */ return; }
		if(Array.isArray(oper)) {
			oper = oper.flat();
			oper.slice(1).forEach(o => insert_ins(row, name, [...operands.slice(0, j), o, ...operands.slice(j + 1)]));
			actualops.push(operands[j] = oper[0]);
		} else actualops.push(operands[j] = oper);
	}
	// Skip rows that have an invalid REX.W+ prefix for RH operands
	// if(row[0].includes("REX.W+") && operands.includes("RH")) return;
	let insname = name + " " + actualops.join(", ");
	if(instruction_variants[insname]) {
		if(instruction_variants[insname][0] !== row[0])
			insname = "1_" + insname; //= insname.slice(0, insname.indexOf(" ")) + "_1" + insname.slice(insname.indexOf(" "));
		else console.log("Overwriting row: " + insname, instruction_variants[insname], row);
	}
	instruction_variants[insname] = [...row, actualops];
}

// Expand opcodes that have multiple variants
for(let i = 0; i < rows.length; i++) {
	let row = rows[i];

	// Skip instructions that are invalid in 64-bit mode
	row[9] = row[9].trim();
	if(row[9] === "I"/*Invalid*/ || row[9] === "NE"/*Not Encodable*/ || row[9] === "NS"/*Not Supported*/) continue;

	// Skip VEX instructions
	if(row[0][0] === "V") continue;

	// Skip instructions with ST
	if(row[1].match(/ST/)) continue;

	
	let name = row[1].split(" ")[0];
	let operands = row[1].slice(name.length + 1).split(",").map(s => s.trim().toLowerCase());
	
	// Skip rows with fake REX+ requirements (It was just optional for them, which we already handle)
	if(row[0].includes("REX+") && !["LSS", "LFS", "LGS"].includes(name)) continue;
	
	if(operands[0])
		insert_ins(row, name, operands);
	else instruction_variants[name] = row;
}
// console.log(Object.fromEntries(Object.entries(instruction_variants).slice(130, 150)));

let final_variants = {};
for(let i in instruction_variants) {
	let name = i.split(" ")[0];
	let alt = false;
	if(name.startsWith("1_")) alt = true, name = name.slice(2);
	let row = instruction_variants[i];

	let opcode = row[0].split(" ");
	let variant = "{";
	let prefixes = "";
	let bytes = ""
	let prefdone = false;
	let firstdone = false;

	for(let i of opcode) {
		if(!prefdone && const_prefixes.has(i))
			prefixes += i;
		else if(!prefdone && (i === "PREF.66+" || i === "66"))
			variant += (firstdone ? "" : "\n\t\t") + ".pref66 = true, ", firstdone = true;
		else if (!prefdone && i.startsWith("REX")) {
			if(row[15]?.includes("RH")) console.log("uhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh why did this happen");
			if(i[3] === "+")
				variant += (firstdone ? "" : "\n\t\t") + ".rex = 0x40, ", firstdone = true;
			else if(i[4] === "W")
				variant += (firstdone ? "" : "\n\t\t") + ".rex = 0x48, ", firstdone = true;
			else if(i[4] === "R")
				variant += (firstdone ? "" : "\n\t\t") + ".rex = 0x44, ", firstdone = true;
		}
		else if(i.match(/[\dA-F][\dA-F]/))
			bytes += "0x" + i + ", ", prefdone = true;
		else if (i.match(/\/[r01234567]/)) {
			variant += (firstdone ? "" : "\n\t\t") + ".modrmreq = true, ", firstdone = true;
			if(i[1] === "r") variant += ".modrmreg = true, ";
			else variant += ".modrm = 0x" + (+i[1] << 3).toString(16) + ", ";
		}// else if ((i === "ib" || i === "iw" || i === "id" || i === "iq") && !variant.includes("immediate"))
		// 	variant += "\n\t\t.immediate = " + (row[15].findIndex(o => o.startsWith("IMM")) + 1) + ",";
	}
	
	let operands = row[15];
	if(operands?.[0]) {
		if(name !== "ENTER" && name !== "FSTSW" && name !== "FNSTSW" && name !== "LDDQU" && name !== "LEA" && i !== "MOV SREG, R16" &&
			name !== "PINSRW" && name !== "RET" && name !== "VERR" && i !== "MOVSX R32, R16" && i !== "MOVSX R64, R16" && i !== "MOVSX R32, M16" &&
			i !== "MOVSX R64, M16" && i !== "MOVZX R32, R16" && i !== "MOVZX R64, R16" && i !== "MOVZX R32, M16" && i !== "MOVZX R64, M16" &&
			!variant.includes("pref66") &&
			(operands.includes("M16") || operands.includes("R16") || operands.includes("AX") || operands.includes("IMM16"))) variant += ".pref66 = true, ";
		variant += "\n\t\t.args = { " + operands.join(", ")+ " }, .arglen = " + operands.length + ",";
		let imm = operands.findIndex(o => o.startsWith("IMM")) + 1;
		if(imm) variant += " .immediate = " + imm + ",";
		if(row[2].includes("M")) variant += " .mem_operand = " + (row[2].indexOf("M") + 1) + ",";
		if(row[2].includes("R")) variant += " .reg_operand = " + (row[2].indexOf("R") + 1) + ",";
		else if (row[2].includes("O")) variant += " .reg_operand = " + (row[2].indexOf("O") + 1) + ",";
	}
	

	variant += "\n\t\t.orig_ins = \"" + row[1] + "\", .orig_opcode = \"" + row[0] + "\",";
	variant += "\n\t\t.desc = \"" + row[14].replaceAll('"', "\\\"") + "\",";
	variant += "\n\t\t";
	if(prefixes) variant += ".prefixes = 0x" + prefixes + ", ";
	variant += ".opcode = { " + bytes.slice(0, -2) + " }, .oplen = " + (bytes.split(", ").length - 1) + ",";
	if(row[13] === "YES") variant += "\n\t\t.preffered = true,";
  variant += "\n\t}";
	
	if(!final_variants[name])
		final_variants[name] = [];
	final_variants[name].push(variant);
}

console.log("Parsed Instructions: " + Object.keys(instruction_variants).length);
// console.log(Object.values(instruction_variants).reduce((a, b) => a < b.length ? b.length : a, 0) + " variants");
// Instruction decoder:
// Decodes instructions like "REX+ 80 /4 ib" this and returns a value in the form of the struct

let asmh = `#pragma once
#include <hash.h>
#include "util.h"

enum x64OperandType: u64 {
	NONE = 0, //for an operand constructed without a type

	HINT = 0x1,

	// IMMEDIATES
	IMM8 = 0x2, IMM16 = 0x4, IMM32 = 0x8, IMM64 = 0x10,
	
	LABEL = 0x20,

	M8 = 0x40, M16 = 0x80, M32 = 0x100, M64 = 0x200, M128 = 0x400, M256 = 0x800, M16INT = 0x1000, M32INT = 0x2000,
	M64INT = 0x4000, M32FP = 0x8000, M64FP = 0x10000, M80FP = 0x20000, M80BCD = 0x40000, M2BYTE = 0x80000,
	M28BYTE = 0x100000, M108BYTE = 0x200000, M512BYTE = 0x400000,
	FARPTR1616 = 0x800000, FARPTR1632 = 0x1000000, FARPTR1664 = 0x2000000,
	
	MM = 0x4000000,

	PREF66 = 0x8000000,
	PREFREX_W = 0x10000000,
	FAR = 0x20000000,

	MOFFS8 = 0x40000000, MOFFS16 = 0x80000000, MOFFS32 = 0x100000000, MOFFS64 = 0x200000000,

	R8 = 0x400000000, RH = 0x800000000, AL = 0x1000000000, CL = 0x2000000000,
	R16 = 0x4000000000, AX = 0x8000000000, DX = 0x10000000000,
	R32 = 0x20000000000, EAX = 0x40000000000,
	R64 = 0x80000000000, RAX = 0x100000000000,

	REL8 = 0x200000000000,
	REL32 = 0x400000000000,

	SREG = 0x800000000000, FS = 0x1000000000000, GS = 0x2000000000000,

	ST = 0x4000000000000, ST_0 = 0x8000000000000,

	XMM = 0x10000000000000, XMM_0 = 0x20000000000000,
	YMM = 0x40000000000000,
	
	CR0_7 = 0x80000000000000, CR8 = 0x100000000000000,
	DREG = 0x200000000000000,
	
	ONE = 0x400000000000000 // EXACTLY ENOUGH TO FIT IN A 64-BIT INTEGER LETS FUCKING GO
	// 2 bytes + 2 bits for extra things that can't fit in \`value\`, like segment registers 😈
};
typedef enum x64OperandType x64OperandType;

// enum x64OperandSize { SIZE_BYTE = 1, SIZE_WORD, SIZE_DWORD, SIZE_QUAD };
// typedef enum x64OperandSize x64OperandSize;

enum x64Op {
	ADC = 1, ${Object.keys(final_variants).slice(1).map(s => s.toUpperCase().replace(" ", "_")).join(", ")}, LABEL_DEF
};
typedef enum x64Op x64Op;


struct x64PrefGroup {
	enum { PREF_GROUP_1, PREF_GROUP_2, PREF_GROUP_3, PREF_GROUP_4 } group;
};
typedef struct x64PrefGroup x64PrefGroup;

union x64Operand {
	struct {
		x64OperandType type;
		u64 value;
	};
};
typedef union x64Operand x64Operand;

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
		char* orig_ins;
		char* orig_opcode;
		char* desc;
		u8 mem_operand; // Index of memory operand if there is one + 1
		u8 reg_operand; // Index of register operand if there is one + 1
		u16 prefixes;
		u8 preflen;
		bool pref66;
		u8 rex;
		u8 opcode[4];
		u8 oplen;
		bool modrmreq;
		bool modrmreg;
    u8 modrm;
		u8 displacement;
    u8 immediate;
		x64OperandType args[4];
		u32 arglen;
		bool preffered;
	}* ins;
};
typedef struct x64LookupActualIns x64LookupActualIns;
typedef struct x64LookupGeneralIns x64LookupGeneralIns;

static const x64LookupGeneralIns x64Table[] = {
${Object.entries(final_variants).map(([name, variants]) => `\t{ "${name.toLowerCase().replace("_", " ")}", ${variants.length}, (struct x64LookupActualIns[]) { ${variants.join(", ")} } }`).join(",\n")}
};


#define imm(value) (x64Operand) { ((value) == 1 && ONE) | IMM8 | IMM16 | IMM32 | IMM64, (value) }
// #define imm(value) (x64Operand) { ((value) == 1 && ONE) | (value < 0x100 && IMM8) | (value < 0x10000 && IMM16) | (value < 0x100000000 && IMM32) | IMM64, (value) }
#define im64(value) (x64Operand) { ((value) == 1 && ONE) | IMM64, (value) }
#define im32(value) (x64Operand) { ((value) == 1 && ONE) | IMM32, (value) }
#define im16(value) (x64Operand) { ((value) == 1 && ONE) | IMM16, (value) }
#define im8(value) (x64Operand) { ((value) == 1 && ONE) | IMM8, (value) }

#define rh (x64Operand) { RH | R8 }
#define al (x64Operand) { AL | R8 }
#define cl (x64Operand) { CL | R8, 1 }
#define dl (x64Operand) { R8, 2 }
#define bl (x64Operand) { R8, 3 }
#define ah (x64Operand) { RH, 4 }
#define ch (x64Operand) { RH, 5 }
#define dh (x64Operand) { RH, 6 }
#define bh (x64Operand) { RH, 7 }

#define ax (x64Operand) { AX | R16 }
#define cx (x64Operand) { R16, 1 }
#define dx (x64Operand) { DX | R16, 2 }
#define bx (x64Operand) { R16, 3 }

#define $eax 0x0
#define eax (x64Operand) { EAX | R32, $eax }
#define $ecx 0x1
#define ecx (x64Operand) { R32, $ecx }
#define $edx 0x2
#define edx (x64Operand) { R32, $edx }
#define $ebx 0x3
#define ebx (x64Operand) { R32, $ebx }
#define $esp 0x4
#define esp (x64Operand) { R32, $esp }
#define $ebp 0x5
#define ebp (x64Operand) { R32, $ebp }
#define $esi 0x6
#define esi (x64Operand) { R32, $esi }
#define $edi 0x7
#define edi (x64Operand) { R32, $edi }
#define $r8d 0x8
#define r8d (x64Operand) { R32, $r8d }
#define $r9d 0x9
#define r9d (x64Operand) { R32, $r9d }
#define $r10d 0xA
#define r10d (x64Operand) { R32, $r10d }
#define $r11d 0xB
#define r11d (x64Operand) { R32, $r11d }
#define $r12d 0xC
#define r12d (x64Operand) { R32, $r12d }
#define $r13d 0xD
#define r13d (x64Operand) { R32, $r13d }
#define $r14d 0xE
#define r14d (x64Operand) { R32, $r14d }
#define $r15d 0xF
#define r15d (x64Operand) { R32, $r15d }

#define $none 0xffff
#define $rip 0x20
#define $rax 0x10
#define rax (x64Operand) { RAX | R64, 0x0 }
#define $rcx 0x11
#define rcx (x64Operand) { R64, 0x1 }
#define $rdx 0x12
#define rdx (x64Operand) { R64, 0x2 }
#define $rbx 0x13
#define rbx (x64Operand) { R64, 0x3 }
#define $rsp 0x14
#define rsp (x64Operand) { R64, 0x4 }
#define $rbp 0x15
#define rbp (x64Operand) { R64, 0x5 }
#define $rsi 0x16
#define rsi (x64Operand) { R64, 0x6 }
#define $rdi 0x17
#define rdi (x64Operand) { R64, 0x7 }
#define $r8 0x18
#define r8 (x64Operand) { R64, 0x8 }
#define $r9 0x19
#define r9 (x64Operand) { R64, 0x9 }
#define $r10 0x1A
#define r10 (x64Operand) { R64, 0xA }
#define $r11 0x1B
#define r11 (x64Operand) { R64, 0xB }
#define $r12 0x1C
#define r12 (x64Operand) { R64, 0xC }
#define $r13 0x1D
#define r13 (x64Operand) { R64, 0xD }
#define $r14 0x1E
#define r14 (x64Operand) { R64, 0xE }
#define $r15 0x1F
#define r15 (x64Operand) { R64, 0xF }

// segment registers
#define $es 1
#define es (x64Operand) { SEGREG, 1 }
#define $cs 2
#define cs (x64Operand) { SEGREG, 2 }
#define $ss 3
#define ss (x64Operand) { SEGREG, 3 }
#define $ds 4
#define ds (x64Operand) { SEGREG, 4 }
#define $fs 5
#define fs (x64Operand) { FS | SEGREG, 5 }
#define $gs 6
#define gs (x64Operand) { GS | SEGREG, 6 }

#define lb(l) (x64Operand) { LABEL, #l }

#define X64MEM_1_ARGS(disp)                     (disp & 0xffffffff | (u64) 0x1 << 36) /*0x10 << 32*/
#define X64MEM_2_ARGS(disp, base)               (disp & 0xffffffff | ((base) > 0xf ? (((u64) (base) == 0x20 && (0x1 << 61)) || ((u64) ((base) & 0xf) << 32)) : ((u64) 0x1 << 60) | (u64) ((base) & 0xf) << 32))
#define X64MEM_3_ARGS(disp, base, index)        (X64MEM_2_ARGS(disp, base) | (u64) ((index) & 0x1f) << 40)
#define X64MEM_4_ARGS(disp, base, index, scale) (X64MEM_3_ARGS(disp, base, index) | (u64) ((scale) == 1 ? 0b00 : (scale) == 2 ? 0b01 : (scale) == 4 ? 0b10 : 0b11) << 48)
#define X64MEM_5_ARGS(disp, base, index, scale, segment) (disp & 0xffffffff\\
	| ((base) > 0xf ? (((u64) (base) == 0x20 && (1 << 61)) || ((base) == 0xffff && ((u64) 0x1 << 36)) ((u64) ((base) & 0xf) << 32)) : ((u64) 1 << 60) | (u64) ((base) & 0xf) << 32)) /*If the operand is more than 32 bits wide or is equal to the RIP register,\\
	set mode to wide addressing and set base register, or RIP addressing*/\\
	| (u64) ((index) & 0x1f) << 40\\
	| (u64) ((scale) == 1 ? 0b00 : (scale) == 2 ? 0b01 : (scale) == 4 ? 0b10 : 0b11) << 48\\
	| (u64) ((segment) & (u64) 0x7) << 56)

#define GET_4TH_ARG(arg1, arg2, arg3, arg4, arg5, arg6, ...) arg6
#define X64MEM_MACRO_CHOOSER(...) \
    GET_4TH_ARG(__VA_ARGS__, X64MEM_5_ARGS, X64MEM_4_ARGS, X64MEM_3_ARGS, \
                X64MEM_2_ARGS, X64MEM_1_ARGS, )

#define x64mem(...) X64MEM_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)
#define m8(...) (x64Operand) { M8, x64mem(__VA_ARGS__) }
#define m16(...) (x64Operand) { M16, x64mem(__VA_ARGS__) }
#define m32(...) (x64Operand) { M32, x64mem(__VA_ARGS__) }
#define m64(...) (x64Operand) { M64, x64mem(__VA_ARGS__) }
#define m128(...) (x64Operand) { M128, x64mem(__VA_ARGS__) }
#define m256(...) (x64Operand) { M256, x64mem(__VA_ARGS__) }
#define mem(...) (x64Operand) { M8 | M16 | M32 | M64 | M128 | M256, x64mem(__VA_ARGS__) }

#define END RET, {0}, ((x64Ins) {0, {0}})

u64 label(char* name);
u32 x64emit(x64Ins* ins, char* opcode_dest);
char* x64as(x64 p, u32* len);
void (*run(void* mem, u32 size))();
`;

write(`asm_x86.h`, asmh);