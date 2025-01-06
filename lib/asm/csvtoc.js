import { readFileSync as read, writeFileSync as write } from "fs";

/**
 * Written like a piece of shit with no optimizations but still runs in like a couple milliseconds so I don't care
 * References:
 * 	- Vex Instruction Construction:
 * 		- Codegen.hs:1320
 * Notes:
 * 	- Provide special cases for LHS, LSS, and LGS in the first for loop that expands the opcodes
 */

// Putting anything in for the first argument disables descriptions.
const desc_strings = !process.argv[2];
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
		if(a === "r" && b.startsWith("m")) return "R" + b.slice(1) + " | " + "M" + b.slice(1);
		// console.log("expanding", a, b);
		// The "|" is fine because most of the instructions that have something like m16 (requiring pref66) are usually SSE or VEX, which don't have a prefix 66
		return operand_types(a) + " | " + operand_types(b); // Recursively expands reg and mm if needed.
	}
	if(str === "<xmm0>") return "XMM_0";
	let mm = str.match(/^([xy]?)mm/)?.[1];
	if(mm !== undefined) return mm.toUpperCase() + "MM";
	if(str.startsWith("m16") && (str[3] === "&" || str[3] === ":")) return "FARPTR16" + str.slice(4);
	if(str.startsWith("m512")) return "M512";
	if(str.startsWith("m80") || str.startsWith("m108")) return "X64_ALLMEMMASK"
	if(str.startsWith("m") && str.endsWith("byte")) return "M32";
	if(str === "mem" || str === "m") return "X64_ALLMEMMASK";
	if(str === "reg") return "R64 | R32";
	if(str === "r8") return ["RH", "R8"];
	if(str === "1") return "ONE";
	// let m = str.match(/^m(\d+)$/)?.[1];
	// if(m !== undefined) return "M" + m;
	if(str.startsWith("vm")) str = str.slice(1);
	let m = str.match(/^([mr])(\d+).*/)?.slice?.(1, 3);
	if(m !== undefined) return m[0].toUpperCase() + m[1];
	if(str === "p66") return "PREF66";
	if(str === "pw") return "PREFREX_W";
	if(str === "cr0-cr7") return "CR0_7";
	if(str === "dr0-dr7") return "DREG";
	if(str === "st(0)") return "ST_0";
	if(str === "st(i)") return "ST";
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
	// if(row[0][0] === "V") continue;

	let name = row[1].split(" ")[0];
	let operands = row[1].slice(name.length).trim() ? row[1].slice(name.length + 1).split(",").map(s => s.trim().toLowerCase()) : [];
	
	
	// Skip rows with fake REX+ requirements (It was just optional for them, which we already handle)
	if(row[0].includes("REX+") && !["LSS", "LFS", "LGS"].includes(name)) continue;
	
	if(operands[0]) insert_ins(row, name, operands);
	else instruction_variants[name] = row;
}
// console.log(Object.fromEntries(Object.entries(instruction_variants).slice(130, 150)));

let final_variants = {};
for(let i in instruction_variants) {
	let name = i.split(" ")[0];
	if(name.startsWith("1_")) name = name.slice(2);
	
	let row = instruction_variants[i];

	let opcode = row[0].split(" ");
	let variant = "{";
	let prefixes = "";
	let bytes = [];
	let prefdone = false;
	let firstdone = false;
	let pref66 = false;

	if(opcode[0].startsWith("VEX")) {
		const vex_op = opcode[0].slice(4).split(".");
		const prefixes = ["66", "F3", "F2"];
		const maps = ["0F", "0F38", "0F3A"];
		
		let vex_w = 0;
		let opcode_map = 1;
		let prefix = 0;
		let long = 0;
		
		for(let op of vex_op) {
			if(op === "256") long = 1;
			else if(op === "W1") vex_w = 1;
			else if(maps.includes(op)) opcode_map = maps.indexOf(op) + 1;
			else if(prefixes.includes(op)) prefix = prefixes.indexOf(op) + 1;
		}

		if(opcode_map > 1 || vex_w || long)
			variant += "\n\t\t.vex = 0x80 | " + opcode_map + ",";
		else variant += "\n\t\t.vex = " + opcode_map + ",";
		variant += " .vex_byte = 0x" + (long << 2 | vex_w << 7 | prefix | 0b01111000).toString(16) + ",";
		opcode = opcode.slice(1);
		prefdone = true;
		firstdone = true;
	}

	for(let i of opcode) {
		if(!prefdone && const_prefixes.has(i))
			prefixes += i;
		else if(!prefdone && (i === "PREF.66+" || i === "66"))
			pref66 = true;
		else if (!prefdone && i.startsWith("REX")) {
			// if(row[15]?.includes("RH")) console.log("uhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh why did this happen");
			if(i[3] === "+")
				variant += (firstdone ? " " : "\n\t\t") + ".rex = 0x40,", firstdone = true;
			else if(i[4] === "W")
				variant += (firstdone ? " " : "\n\t\t") + ".rex = 0x48,", firstdone = true;
			else if(i[4] === "R")
				variant += (firstdone ? " " : "\n\t\t") + ".rex = 0x44,", firstdone = true;
		}
		else if(i.match(/[\dA-F][\dA-F]/))
			bytes.push(i), prefdone = true;
		else if (i.match(/\/[r01234567]/)) {
			variant += (firstdone ? " " : "\n\t\t") + ".modrmreq = true,", firstdone = true;
			if(i[1] === "r") variant += " .modrmreg = true,";
			else variant += " .modrm = 0x" + (+i[1] << 3).toString(16) + ",";
		}// else if ((i === "ib" || i === "iw" || i === "id" || i === "iq") && !variant.includes("immediate"))
		// 	variant += "\n\t\t.immediate = " + (row[15].findIndex(o => o.startsWith("IMM")) + 1) + ",";
	}
	
	let operands = row[15];
	let rel_oper = 0;
	let imm = 0;
	if(operands?.[0]) {
		if(name !== "ENTER" && name !== "FSTSW" && name !== "FNSTSW" && name !== "LDDQU" && name !== "LEA" && i !== "MOV SREG, R16" &&
			name !== "PINSRW" && name !== "RET" && name !== "VERR" && i !== "MOVSX R32, R16" && i !== "MOVSX R64, R16" && i !== "MOVSX R32, M16" &&
			i !== "MOVSX R64, M16" && i !== "MOVZX R32, R16" && i !== "MOVZX R64, R16" && i !== "MOVZX R32, M16" && i !== "MOVZX R64, M16" &&
			(operands.includes("M16") || operands.includes("R16") || operands.includes("AX") || operands.includes("IMM16"))) // Exhaustive list of instructions that don't require a 66 prefix
				pref66 = true;
		variant += "\n\t\t.args = { " + operands.join(", ")+ " }, .arglen = " + operands.length + ",";
		imm = operands.findIndex(o => o.startsWith("IMM")) + 1;
		if(imm) variant += " .imm_oper = " + imm + ",";
		if(row[2].includes("D")) variant += " .rel_oper = " + (rel_oper = row[2].indexOf("D") + 1) + ",";
		if(row[2].includes("M")) variant += " .mem_oper = " + (row[2].indexOf("M") + 1) + ",";
		if(row[2].includes("R") || row[2] === "XM"/*what the fuck intel*/) variant += " .reg_oper = " + (row[2].indexOf("R") + 1 + row[2].indexOf("X") + 1) + ",";
		else if(row[2].includes("O")) variant += " .reg_oper = " + (row[2].indexOf("O") + 1) + ","; // THIS IS NOT RELATIVE, THIS IS GODDAMN THE +rd WHATEVER THING THAT GOES ON TOP OF THE OPCODE
		if(row[0].includes("/is4")) variant += " .is4_oper = " + (row[2].lastIndexOf("R") + 1) + ",";
		if(row[2].includes("V")) variant += " .vex_oper = " + (row[2].indexOf("V") + 1) + ",";
	}
	
	if(desc_strings) {
		variant += "\n\t\t.orig_ins = \"" + row[1] + "\", .orig_opcode = \"" + row[0] + "\",";
		variant += "\n\t\t.desc = \"" + row[14].replaceAll('"', "\\\"") + "\",";
	}
	
	variant += "\n\t\t";
	if(pref66) prefixes += "66"; // Prefix 66 is usually before the other prefixes like FWAIT
	if(prefixes) variant += ".prefixes = 0x" + prefixes + ", ";
	variant += ".opcode = 0x" + (bytes.reverse().join("") || 0) + ", .oplen = " + (bytes.length) + ",";
	if(row[13] === "YES") variant += "\n\t\t.preffered = true,";
	
	// variant += "\n\t\t.base_size = " + (((prefixes.length / 2) + (bytes.length)) +
	// 																		(rel_oper && (operands[rel_oper - 1] == "REL32" ? 4 : 1)) +
	// 																		(imm ? 2 ** (["IMM8", "IMM16", "IMM32", "IMM64"].indexOf(operands[imm - 1])) : 0)) + ",";
  variant += "\n\t}";
	
	if(!final_variants[name])
		final_variants[name] = [];
	final_variants[name].push(variant);
}

console.log("Parsed Instructions: " + Object.keys(instruction_variants).length);
// console.log(Object.values(instruction_variants).reduce((a, b) => a < b.length ? b.length : a, 0) + " variants");
// Instruction decoder:
// Decodes instructions like "REX+ 80 /4 ib" this and returns a value in the form of the struct

let asmh = `/*
 * asm_x64.h v1.1.0 - Aqil Contractor @aqilc 2025
 * Dual Licenced under MIT and Public Domain.
 *
 * This file includes all of the headers for the "chasm" library macros and functions.
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>

enum x64OperandType: uint64_t {
	NONE = 0, //for an operand constructed without a type

	HINT = 0x1,

	// IMMEDIATES
	IMM8 = 0x2, IMM16 = 0x4, IMM32 = 0x8, IMM64 = 0x10,
	
	X64_LABEL_REF = 0x20,

	M8 = 0x40, M16 = 0x80, M32 = 0x100, M64 = 0x200, M128 = 0x400, M256 = 0x800, M512 = 0x1000,
	FARPTR1616 = 0x2000, FARPTR1632 = 0x4000, FARPTR1664 = 0x8000,
	
	MM = 0x10000,

	PREF66 = 0x20000,
	PREFREX_W = 0x40000,
	FAR = 0x80000,

	MOFFS8 = 0x100000, MOFFS16 = 0x200000, MOFFS32 = 0x400000, MOFFS64 = 0x800000,

	R8 = 0x1000000, RH = 0x2000000, AL = 0x4000000, CL = 0x8000000,
	R16 = 0x10000000, AX = 0x20000000, DX = 0x40000000,
	R32 = 0x80000000, EAX = 0x100000000,
	R64 = 0x200000000, RAX = 0x400000000,

	REL8 = 0x800000000,
	REL32 = 0x1000000000,

	SREG = 0x2000000000, FS = 0x4000000000, GS = 0x8000000000,

	ST = 0x10000000000, ST_0 = 0x20000000000,

	XMM = 0x40000000000, XMM_0 = 0x80000000000,
	YMM = 0x100000000000,
	ZMM = 0x200000000000,
	
	CR0_7 = 0x400000000000, CR8 = 0x800000000000,
	DREG = 0x1000000000000,
	
	ONE = 0x2000000000000
};
typedef enum x64OperandType x64OperandType;


#define X64_ALLMEMMASK (M8 | M16 | M32 | M64 | M128 | M256 | M512)
#define X64_GPR (R8 | R16 | R32 | R64)
#define X64_ALLREGMASK (R8 | RH | R16 | R32 | R64 | MM | XMM | YMM | ZMM | SREG | CR0_7 | DREG | CR8)

enum x64Op: uint32_t {
	END_ASM, ${Object.keys(final_variants).map(s => s.toUpperCase().replace(" ", "_")).join(", ")}, X64_LABEL_DEF
};
typedef enum x64Op x64Op;

struct x64Operand {
	x64OperandType type;
	union {
		int64_t value;
		char* label_name;
	};
};
typedef struct x64Operand x64Operand;

struct x64Ins {
	x64Op op;
	union {
		x64Operand params[4];
		char* label_name;
	};
};
typedef struct x64Ins x64Ins;
typedef x64Ins x64[];

struct x64LookupGeneralIns {
	char* name;
	unsigned int numactualins;
	struct x64LookupActualIns {${desc_strings ? `
		char* orig_ins;
		char* orig_opcode;
		char* desc;` : ""}
		uint8_t mem_oper; // Index of memory operand if there is one + 1
		uint8_t reg_oper; // Index of register operand if there is one + 1
		uint8_t rel_oper; // Index of relative jump operand if there is one + 1
		uint8_t vex_oper; // Index of VEX operand if there is one + 1
    uint8_t imm_oper; // Index of immediate operand if there is one + 1
    uint8_t is4_oper; // Index of 4-byte immediate operand if there is one + 1
		uint8_t rex;
		uint8_t oplen;
		uint8_t vex; // opcode_map if specified
		uint8_t vex_byte;
    uint8_t modrm;
		bool modrmreq;
		bool modrmreg;
		bool preffered;
		uint8_t base_size;
		uint8_t arglen;
		uint32_t opcode;
		uint32_t prefixes;
		x64OperandType args[4];
	}* ins;
};
typedef struct x64LookupActualIns x64LookupActualIns;
typedef struct x64LookupGeneralIns x64LookupGeneralIns;

static const x64LookupGeneralIns x64Table[] = {
${Object.entries(final_variants).map(([name, variants]) => `\t{ "${name.toLowerCase().replace("_", " ")}", ${variants.length}, (struct x64LookupActualIns[]) { ${variants.join(", ")} } }`).join(",\n")}
};

#define imm(value) (x64Operand) { ((value) == 1 ? ONE : 0) | IMM8 | IMM16 | IMM32 | IMM64, (value) }
#define im64(value) (x64Operand) { ((value) == 1 ? ONE : 0) | IMM64, (value) }
#define im32(value) (x64Operand) { ((value) == 1 ? ONE : 0) | IMM32, (value) }
#define im16(value) (x64Operand) { ((value) == 1 ? ONE : 0) | IMM16, (value) }
#define im8(value) (x64Operand) { ((value) == 1 ? ONE : 0) | IMM8, (value) }
#define imptr(value) (x64Operand) { IMM64, (uint64_t)(void*)(value) }

#define al (x64Operand) { AL | R8 }
#define cl (x64Operand) { CL | R8, 1 }
#define dl (x64Operand) { R8, 2 }
#define bl (x64Operand) { R8, 3 }

#define bpl (x64Operand) { R8, 4 }
#define spl (x64Operand) { R8, 5 }
#define sil (x64Operand) { R8, 6 }
#define dil (x64Operand) { R8, 7 }
#define r8b (x64Operand) { R8, 8 }
#define r9b (x64Operand) { R8, 9 }
#define r10b (x64Operand) { R8, 10 }
#define r11b (x64Operand) { R8, 11 }
#define r12b (x64Operand) { R8, 12 }
#define r13b (x64Operand) { R8, 13 }
#define r14b (x64Operand) { R8, 14 }
#define r15b (x64Operand) { R8, 15 }

#define ah (x64Operand) { RH, 4 }
#define ch (x64Operand) { RH, 5 }
#define dh (x64Operand) { RH, 6 }
#define bh (x64Operand) { RH, 7 }

#define ax (x64Operand) { AX | R16 }
#define cx (x64Operand) { R16, 1 }
#define dx (x64Operand) { DX | R16, 2 }
#define bx (x64Operand) { R16, 3 }

#define si (x64Operand) { R16, 4 }
#define di (x64Operand) { R16, 5 }
#define bp (x64Operand) { R16, 6 }
#define sp (x64Operand) { R16, 7 }
#define r8w (x64Operand) { R16, 8 }
#define r9w (x64Operand) { R16, 9 }
#define r10w (x64Operand) { R16, 10 }
#define r11w (x64Operand) { R16, 11 }
#define r12w (x64Operand) { R16, 12 }
#define r13w (x64Operand) { R16, 13 }
#define r14w (x64Operand) { R16, 14 }
#define r15w (x64Operand) { R16, 15 }

enum x64RegisterReference: uint32_t {
	// DO NOT CHANGE THEIR ORDER
	$eax, $ecx, $edx, $ebx, $esp, $ebp, $esi, $edi, $r8d, $r9d, $r10d, $r11d, $r12d,
	$r13d, $r14d, $r15d, $rax, $rcx, $rdx, $rbx, $rsp, $rbp, $rsi, $rdi, $r8, $r9, $r10,
	$r11, $r12, $r13, $r14, $r15, $rip = 0x20, $es, $cs, $ss, $ds, $fs, $gs,
	
	$xmm0 = 0x800000, $xmm1 = 0x800001, $xmm2 = 0x800002, $xmm3 = 0x800003, $xmm4 = 0x800004, $xmm5 = 0x800005, $xmm6 = 0x800006, $xmm7 = 0x800007,
	$xmm8 = 0x800008, $xmm9 = 0x800009, $xmm10 = 0x80000A, $xmm11 = 0x80000B, $xmm12 = 0x80000C, $xmm13 = 0x80000D, $xmm14 = 0x80000E, $xmm15 = 0x80000F,
	$ymm0 = 0x800000, $ymm1 = 0x800001, $ymm2 = 0x800002, $ymm3 = 0x800003, $ymm4 = 0x800004, $ymm5 = 0x800005, $ymm6 = 0x800006, $ymm7 = 0x800007,
	$ymm8 = 0x800008, $ymm9 = 0x800009, $ymm10 = 0x80000A, $ymm11 = 0x80000B, $ymm12 = 0x80000C, $ymm13 = 0x80000D, $ymm14 = 0x80000E, $ymm15 = 0x80000F,
	$riprel = 0x30, $none = 0xFFF0
};

#define eax (x64Operand) { EAX | R32, $eax }
#define ecx (x64Operand) { R32, $ecx }
#define edx (x64Operand) { R32, $edx }
#define ebx (x64Operand) { R32, $ebx }
#define esp (x64Operand) { R32, $esp }
#define ebp (x64Operand) { R32, $ebp }
#define esi (x64Operand) { R32, $esi }
#define edi (x64Operand) { R32, $edi }
#define r8d (x64Operand) { R32, $r8d }
#define r9d (x64Operand) { R32, $r9d }
#define r10d (x64Operand) { R32, $r10d }
#define r11d (x64Operand) { R32, $r11d }
#define r12d (x64Operand) { R32, $r12d }
#define r13d (x64Operand) { R32, $r13d }
#define r14d (x64Operand) { R32, $r14d }
#define r15d (x64Operand) { R32, $r15d }

#define rax (x64Operand) { RAX | R64, 0x0 }
#define rcx (x64Operand) { R64, 0x1 }
#define rdx (x64Operand) { R64, 0x2 }
#define rbx (x64Operand) { R64, 0x3 }
#define rsp (x64Operand) { R64, 0x4 }
#define rbp (x64Operand) { R64, 0x5 }
#define rsi (x64Operand) { R64, 0x6 }
#define rdi (x64Operand) { R64, 0x7 }
#define r8 (x64Operand) { R64, 0x8 }
#define r9 (x64Operand) { R64, 0x9 }
#define r10 (x64Operand) { R64, 0xA }
#define r11 (x64Operand) { R64, 0xB }
#define r12 (x64Operand) { R64, 0xC }
#define r13 (x64Operand) { R64, 0xD }
#define r14 (x64Operand) { R64, 0xE }
#define r15 (x64Operand) { R64, 0xF }

// SSE and AVX registers
#define xmm0 (x64Operand) { XMM_0 | XMM, 0 }
#define xmm1 (x64Operand) { XMM, 1 }
#define xmm2 (x64Operand) { XMM, 2 }
#define xmm3 (x64Operand) { XMM, 3 }
#define xmm4 (x64Operand) { XMM, 4 }
#define xmm5 (x64Operand) { XMM, 5 }
#define xmm6 (x64Operand) { XMM, 6 }
#define xmm7 (x64Operand) { XMM, 7 }
#define xmm8 (x64Operand) { XMM, 8 }
#define xmm9 (x64Operand) { XMM, 9 }
#define xmm10 (x64Operand) { XMM, 10 }
#define xmm11 (x64Operand) { XMM, 11 }
#define xmm12 (x64Operand) { XMM, 12 }
#define xmm13 (x64Operand) { XMM, 13 }
#define xmm14 (x64Operand) { XMM, 14 }
#define xmm15 (x64Operand) { XMM, 15 }
#define xmm16 (x64Operand) { XMM, 16 }
#define xmm17 (x64Operand) { XMM, 17 }
#define xmm18 (x64Operand) { XMM, 18 }
#define xmm19 (x64Operand) { XMM, 19 }
#define xmm20 (x64Operand) { XMM, 20 }
#define xmm21 (x64Operand) { XMM, 21 }
#define xmm22 (x64Operand) { XMM, 22 }
#define xmm23 (x64Operand) { XMM, 23 }
#define xmm24 (x64Operand) { XMM, 24 }
#define xmm25 (x64Operand) { XMM, 25 }
#define xmm26 (x64Operand) { XMM, 26 }
#define xmm27 (x64Operand) { XMM, 27 }
#define xmm28 (x64Operand) { XMM, 28 }
#define xmm29 (x64Operand) { XMM, 29 }
#define xmm30 (x64Operand) { XMM, 30 }
#define xmm31 (x64Operand) { XMM, 31 }

#define ymm0 (x64Operand) { YMM, 0 }
#define ymm1 (x64Operand) { YMM, 1 }
#define ymm2 (x64Operand) { YMM, 2 }
#define ymm3 (x64Operand) { YMM, 3 }
#define ymm4 (x64Operand) { YMM, 4 }
#define ymm5 (x64Operand) { YMM, 5 }
#define ymm6 (x64Operand) { YMM, 6 }
#define ymm7 (x64Operand) { YMM, 7 }
#define ymm8 (x64Operand) { YMM, 8 }
#define ymm9 (x64Operand) { YMM, 9 }
#define ymm10 (x64Operand) { YMM, 10 }
#define ymm11 (x64Operand) { YMM, 11 }
#define ymm12 (x64Operand) { YMM, 12 }
#define ymm13 (x64Operand) { YMM, 13 }
#define ymm14 (x64Operand) { YMM, 14 }
#define ymm15 (x64Operand) { YMM, 15 }
#define ymm16 (x64Operand) { YMM, 16 }
#define ymm17 (x64Operand) { YMM, 17 }
#define ymm18 (x64Operand) { YMM, 18 }
#define ymm19 (x64Operand) { YMM, 19 }
#define ymm20 (x64Operand) { YMM, 20 }
#define ymm21 (x64Operand) { YMM, 21 }
#define ymm22 (x64Operand) { YMM, 22 }
#define ymm23 (x64Operand) { YMM, 23 }
#define ymm24 (x64Operand) { YMM, 24 }
#define ymm25 (x64Operand) { YMM, 25 }
#define ymm26 (x64Operand) { YMM, 26 }
#define ymm27 (x64Operand) { YMM, 27 }
#define ymm28 (x64Operand) { YMM, 28 }
#define ymm29 (x64Operand) { YMM, 29 }
#define ymm30 (x64Operand) { YMM, 30 }
#define ymm31 (x64Operand) { YMM, 31 }

#define zmm0 (x64Operand) { ZMM, 0 }
#define zmm1 (x64Operand) { ZMM, 1 }
#define zmm2 (x64Operand) { ZMM, 2 }
#define zmm3 (x64Operand) { ZMM, 3 }
#define zmm4 (x64Operand) { ZMM, 4 }
#define zmm5 (x64Operand) { ZMM, 5 }
#define zmm6 (x64Operand) { ZMM, 6 }
#define zmm7 (x64Operand) { ZMM, 7 }
#define zmm8 (x64Operand) { ZMM, 8 }
#define zmm9 (x64Operand) { ZMM, 9 }
#define zmm10 (x64Operand) { ZMM, 10 }
#define zmm11 (x64Operand) { ZMM, 11 }
#define zmm12 (x64Operand) { ZMM, 12 }
#define zmm13 (x64Operand) { ZMM, 13 }
#define zmm14 (x64Operand) { ZMM, 14 }
#define zmm15 (x64Operand) { ZMM, 15 }
#define zmm16 (x64Operand) { ZMM, 16 }
#define zmm17 (x64Operand) { ZMM, 17 }
#define zmm18 (x64Operand) { ZMM, 18 }
#define zmm19 (x64Operand) { ZMM, 19 }
#define zmm20 (x64Operand) { ZMM, 20 }
#define zmm21 (x64Operand) { ZMM, 21 }
#define zmm22 (x64Operand) { ZMM, 22 }
#define zmm23 (x64Operand) { ZMM, 23 }
#define zmm24 (x64Operand) { ZMM, 24 }
#define zmm25 (x64Operand) { ZMM, 25 }
#define zmm26 (x64Operand) { ZMM, 26 }
#define zmm27 (x64Operand) { ZMM, 27 }
#define zmm28 (x64Operand) { ZMM, 28 }
#define zmm29 (x64Operand) { ZMM, 29 }
#define zmm30 (x64Operand) { ZMM, 30 }
#define zmm31 (x64Operand) { ZMM, 31 }

// mm registers
#define mm0 (x64Operand) { MM, 0 }
#define mm1 (x64Operand) { MM, 1 }
#define mm2 (x64Operand) { MM, 2 }
#define mm3 (x64Operand) { MM, 3 }
#define mm4 (x64Operand) { MM, 4 }
#define mm5 (x64Operand) { MM, 5 }
#define mm6 (x64Operand) { MM, 6 }
#define mm7 (x64Operand) { MM, 7 }

// control registers
#define cr0 (x64Operand) { CR0_7, 0 }
#define cr1 (x64Operand) { CR0_7, 1 }
#define cr2 (x64Operand) { CR0_7, 2 }
#define cr3 (x64Operand) { CR0_7, 3 }
#define cr4 (x64Operand) { CR0_7, 4 }
#define cr5 (x64Operand) { CR0_7, 5 }
#define cr6 (x64Operand) { CR0_7, 6 }
#define cr7 (x64Operand) { CR0_7, 7 }
#define cr8 (x64Operand) { CR8, 8 }

// debug registers
#define dr0 (x64Operand) { DREG, 0 }
#define dr1 (x64Operand) { DREG, 1 }
#define dr2 (x64Operand) { DREG, 2 }
#define dr3 (x64Operand) { DREG, 3 }
#define dr4 (x64Operand) { DREG, 4 }
#define dr5 (x64Operand) { DREG, 5 }
#define dr6 (x64Operand) { DREG, 6 }
#define dr7 (x64Operand) { DREG, 7 }

// FPU registers
#define st0 (x64Operand) { ST_0 | ST, 0 }
#define st1 (x64Operand) { ST, 1 }
#define st2 (x64Operand) { ST, 2 }
#define st3 (x64Operand) { ST, 3 }
#define st4 (x64Operand) { ST, 4 }
#define st5 (x64Operand) { ST, 5 }
#define st6 (x64Operand) { ST, 6 }
#define st7 (x64Operand) { ST, 7 }


// segment registers
#define es (x64Operand) { SREG, 1 }
#define cs (x64Operand) { SREG, 2 }
#define ss (x64Operand) { SREG, 3 }
#define ds (x64Operand) { SREG, 4 }
#define fs (x64Operand) { FS | SREG, 5 }
#define gs (x64Operand) { GS | SREG, 6 }

// #define lb(l) (x64Operand) { X64_LABEL_REF | REL32 | REL8, .label_name = l }
// #define lb_def(l) (x64Ins) { X64_LABEL_DEF, .label_name = l }

#define rel(insns) (x64Operand) { REL32 | REL8, insns }

// DISP    : 0x00000000ffffffff bit 0-31
// BASE    : 0x0000001f00000000 bit 32-36
// INDEX   : 0x00001f0000000000 bit 40-44
// SCALE   : 0x0003000000000000 bit 48-49
// SEG     : 0x0700000000000000 bit 56-58
// ADDR_OR : 0x1000000000000000 bit 60
// RIP     : 0x2000000000000000 bit 61
// RIPREL  : 0x4000000000000000 bit 62
// VSIB    : 0x8000000000000000 bit 63


//hi = (disp, base) => (disp & 0xffffffffn | ((base) & 0x30n ? ( (BigInt((base) == 0x20n) && (1n << 61n)) | (BigInt((base) == 0xfff0n) && (0x1n << 36n)) | BigInt((base & 0xfn) << 32n) ) : (0x1n << 60n) | ((base) & 0xfn) << 32n))


#define X64MEM_1_ARGS(base)                      (((base) & 0x30 ?\\
																										( ((uint64_t) ((base) == $rip) ? ((uint64_t) 0x1 << 61) : 0) | ((uint64_t) ((base) == $riprel) ? ((uint64_t) 0x3 << 61) : 0) | ((uint64_t) ((base) == $none) ? ((uint64_t) 0x1 << 36) : 0) | ((uint64_t) ((base) & 0xf) << 32) ) :\\
																										((uint64_t) 0x1 << 60) | (uint64_t) ((base) & 0xf) << 32) |\\
																									(uint64_t) 0x10 << 40)
#define X64MEM_2_ARGS(base, disp)               (disp & 0xffffffff | X64MEM_1_ARGS(base))
#define X64MEM_3_ARGS(base, disp, index)        (disp & 0xffffffff | ((base) & 0x30 ?\\
																										( ((uint64_t) ((base) == $rip) ? ((uint64_t) 0x1 << 61) : 0) | ((uint64_t) ((base) == $riprel) ? ((uint64_t) 0x3 << 61) : 0) | ((uint64_t) ((base) == $none) ? ((uint64_t) 0x1 << 36) : 0) | ((uint64_t) ((base) & 0xf) << 32) ) :\\
																										((uint64_t) 0x1 << 60) | (uint64_t) ((base) & 0xf) << 32) |\\
																									(uint64_t) ((index) == $none ? 0x10 : (index) & 0x80000F) << 40)
#define X64MEM_4_ARGS(base, disp, index, scale) (X64MEM_3_ARGS(base, disp, index) | (uint64_t) ((scale) <= 1 ? 0b00 : (scale) == 2 ? 0b01 : (scale) == 4 ? 0b10 : 0b11) << 48)
#define X64MEM_5_ARGS(base, disp, index, scale, segment) (disp & 0xffffffff\\
	| ((base) & 0x30 ? /*If the operand is more than 32 bits wide or is equal to the RIP register, set mode to wide addressing and set base register, or RIP addressing*/\\
			( ((uint64_t) ((base) == $rip) ? ((uint64_t) 0x1 << 61) : 0) | ((uint64_t) ((base) == $riprel) ? ((uint64_t) 0x3 << 61) : 0) | ((uint64_t) ((base) == $none) ? ((uint64_t) 0x1 << 36) : 0) | ((uint64_t) ((base) & 0xf) << 32) ) :\\
			((uint64_t) 0x1 << 60) | (uint64_t) ((base) & 0xf) << 32)\\
	| (uint64_t) ((index) == $none ? 0x10 : (index) & 0x80000F) << 40\\
	| (uint64_t) ((scale) <= 1 ? 0b00 : (scale) == 2 ? 0b01 : (scale) == 4 ? 0b10 : 0b11) << 48\\
	| (uint64_t) (((segment) - $rip) & (uint64_t) 0x7) << 56) /* minusing from $rip, because segment registers are 1 + their value for simplification. */

#define GET_4TH_ARG(arg1, arg2, arg3, arg4, arg5, arg6, ...) arg6
#define X64MEM_MACRO_CHOOSER(...) \\
    GET_4TH_ARG(__VA_ARGS__, X64MEM_5_ARGS, X64MEM_4_ARGS, X64MEM_3_ARGS, \\
                X64MEM_2_ARGS, X64MEM_1_ARGS, )

#define x64mem(...) X64MEM_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

#define m8(...) (x64Operand) { M8, x64mem(__VA_ARGS__) }
#define m16(...) (x64Operand) { M16, x64mem(__VA_ARGS__) }
#define m32(...) (x64Operand) { M32, x64mem(__VA_ARGS__) }
#define m64(...) (x64Operand) { M64, x64mem(__VA_ARGS__) }
#define m128(...) (x64Operand) { M128, x64mem(__VA_ARGS__) }
#define m256(...) (x64Operand) { M256, x64mem(__VA_ARGS__) }
#define m512(...) (x64Operand) { M512, x64mem(__VA_ARGS__) }
#define mem(...) (x64Operand) { M8 | M16 | M32 | M64 | M128 | M256 | M512, x64mem(__VA_ARGS__) }


// Emits code and links rip relatives, labels, and jumps after.
uint8_t* x64as(const x64 p, uint32_t num, uint32_t* len);

// Emits 1 instruction.
uint32_t x64emit(const x64Ins* ins, uint8_t* opcode_dest);

// Stringifies the IR.
char* x64stringify(const x64 p, uint32_t num);

// Runs the assembled output.
void (*x64exec(void* mem, uint32_t size))();
void x64exec_free(void* buf, uint32_t size);

// Gets last emitted error code and string.
char* x64error(int* errcode);
`;

write(`asm_x64.h`, asmh);
