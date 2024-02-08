import { readFileSync as read, writeFileSync as write } from "fs";

/**
 * References:
 * 	- Vex Instruction Construction:
 * 		- Codegen.hs:1320
 */

let file = (read("x86.csv") + '')
	.split("\r\n").filter(s => s.trim());
// [0] Opcode  [1] Instruction  [2] Op/En  [3] Properties  [4] Implicit Read  [5] Implicit Write  [6] Implicit Undef  [7] Useful  [8] Protected  [9] 64-bit Mode  [10] Compat/32-bit-Legacy Mode  [11] CPUID Feature Flags  [12] AT&T Mnemonic  [13] Preferred  [14] Description

const rows = file.slice(1).filter(s => s.trim()).map(s => s.split("\t"));
// const atntnames = new Set(rows.filter(s => s[12]).map(s => ['b', 'w', 'l', 'q'].includes(s[12][s[12].length - 1]) ? s[12].slice(0, -1) : s[12]));
const instruction_variants = {};
let const_prefixes = {
	"PREF.66+": "0x66",
	"66": "0x66",
	"F2": "0xF2",
	"F3": "0xF3",
	"9B": "0x9B",
};

let size_mappings = {
	b: "SIZE_BYTE",
	w: "SIZE_WORD",
	d: "SIZE_DWORD",
	q: "SIZE_QUAD",
}

const operand_types = str => {
	if(str === "<xmm0>") return "XMM_0";
	let mm = str.match(/^([xy]?)mm/)?.[1];
	if(mm !== undefined) return mm.toUpperCase() + "MM";
	if(str === "m" || str === "mem" || str === "reg" || str === "r") return str[0].toUpperCase() + "64 | " + str[0].toUpperCase() + "32";
	if(str.includes("/")) {
		let [a, b] = str.split("/");
		if(a === "r" && b.startsWith("m")) return "R" + b.slice(1) + " | M" + b.slice(1);
		return operand_types(a) + " | " + operand_types(b);
	}
	if(str.startsWith("m16:")) return "FARPTR16" + str.slice(4);
	if(str === "p66") return "PREF66";
	if(str === "pw") return "PREFREX_W";
	if(str === "cr0-cr7") return "CR0_7";
	if(str === "dr0-dr7") return "DREG";
	return str.toUpperCase();
}

outerloop:
for(let row of rows) {
	// const name = row[12].replace(" ", "_");

	// Op/En not yet supported
	// if(row[2]?.trim() && row[2] !== "ZO") continue;

	// Skip instructions that are invalid in 64-bit mode
	row[9] = row[9].trim();
	if(row[9] === "I"/*Invalid*/ || row[9] === "NE"/*Not Encodable*/ || row[9] === "NS"/*Not Supported*/) continue;

	// Skip VEX instructions
	if(row[0][0] === "V") continue;

	// Skip instructions with displacement or a modrm byte
	// if(row[0].match(/\/\d/)) continue;

	// Skip instructions with +rw and other stuff
	// if(row[0].match(/\+\w+/)) continue;

	// Skip instructions with ST
	if(row[1].match(/ST/)) continue;

	const name = row[1].split(" ")[0]
	
	// Decode opcodes in the format of "REX+ 80 /4 ib"
	let opcode = row[0].split(" ");
	let variant = { text: "{", ref: row };
  let bytes = "";
	let prefixes = "";
	for(let i of opcode)
		if(const_prefixes[i])
			prefixes += const_prefixes[i] + ", ";
		else if(i.match(/[\dA-F][\dA-F]/))
			bytes += "0x" + i + ", ";
		else if (i.startsWith("REX")) {
			if(i[3] === "+")
				variant.text += "\n\t\t.rex = 0x40, ";
			else if(i[4] === "W")
				variant.text += "\n\t\t.rex = 0x48, ";
			else if(i[4] === "R")
				variant.text += "\n\t\t.rex = 0x44, ";
		}
		else if (i.match(/\/[r01234567]/))
			variant.text += "\n\t\t.modrm = 0x" + (i[1] === "r" ? "C0" : "C8") + ",";
		else if ((i === "ib" || i === "iw" || i === "id" || i === "iq") && !variant.text.includes("immediate"))
			variant.text += "\n\t\t.immediate = " + size_mappings[i[1]] + ",";

	variant.text += "\n\t\t.orig_ins = \"" + row[1] + "\", .orig_opcode = \"" + row[0] + "\",";
	variant.text += "\n\t\t.desc = \"" + row[14].replaceAll('"', "\\\"") + "\",";
	if(row[2].includes("M")) variant.text += "\n\t\t.mem_operand = " + (row[2].indexOf("M") + 1) + ",";
	if(row[2].includes("R")) variant.text += "\n\t\t.reg_operand = " + (row[2].indexOf("R") + 1) + ",";
	if(prefixes) variant.text += "\n\t\t.prefixes = { " + prefixes.slice(0, -2) + " }, .preflen = " + (prefixes.split(", ").length - 1) + ",";
	variant.text += "\n\t\t.opcode = { " + bytes.slice(0, -2) + " }, .oplen = " + (bytes.split(", ").length - 1) + ",";

	const operands = row[1].slice(name.length).trim().split(",");
	if(operands[0]) {
		variant.text += "\n\t\t.args = { "
		for(let i = 0; i < operands.length; i++) {
			let oper = operands[i].trim().toLowerCase();
			// if(oper.includes("/")) { console.log(row[0], row[1], operands, oper); continue outerloop; }// throw new Error("Shouldn't have these...");

			variant.text += operand_types(oper);
			if(i < operands.length - 1) variant.text += ", ";

			// variant.text += ((oper.includes("/") ? operand_types[oper[0] + oper.slice(3)] + " | " + operand_types[oper[2] + oper.slice(3)] : operand_types[oper]) || "NONE") + ", ";
		}
		variant.text += " }, .arglen = " + operands.length + ",";
	}

  variant.text += "\n\t}";
	
	if(!instruction_variants[name])
		instruction_variants[name] = [];
	instruction_variants[name].push(variant);
}
// console.log("{\n" + file.slice(40, 50).map(s => "\t{ " + s.split("\t").map(s => s || "0").join(", ") + " }").join(",\n") + "\n}");
// console.log("{\n" + Object.values(instruction_variants).filter(v => v[0].ref[1].includes(",")).map(s => "\t{ " + s[0].ref.map(s => s || "0").join(", ") + " }").join(",\n") + "\n}");
console.log("Parsed Instructions: " + Object.keys(instruction_variants).length);
// console.log(Object.fromEntries(Object.entries(instruction_variants).slice(0, 10)));
// console.log(Object.values(instruction_variants).reduce((a, b) => a < b.length ? b.length : a, 0) + " variants");
// Instruction decoder:
// Decodes instructions like "REX+ 80 /4 ib" this and returns a value in the form of the struct

let asmh = `#pragma once
#include <hash.h>
#include "util.h"

enum x64OperandType {
	NONE = 0, //for an operand constructed without a type

	HINT = 0x1,

	// IMMEDIATES
	IMM64 = 0x2, IMM32 = 0x4, IMM16 = 0x8, IMM8 = 0x10,
	
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
	DREG = 0x200000000000000 // EXACTLY ENOUGH TO FIT IN A 64-BIT INTEGER LETS FUCKING GO
};
typedef enum x64OperandType x64OperandType;

enum x64OperandSize { SIZE_BYTE = 1, SIZE_WORD, SIZE_DWORD, SIZE_QUAD };
typedef enum x64OperandSize x64OperandSize;

enum x64Op {
	ADC = 1, ${Object.keys(instruction_variants).slice(1).map(s => s.toUpperCase().replace(" ", "_")).join(", ")}, LABEL_DEF
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
	struct { // Displacement encoding, puts the SIB right there.
		u8 SIB : 8;
		u64 discard : 48;
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
		u8 prefixes[2];
		u8 preflen;
		u8 rex;
		u8 opcode[4];
		u8 oplen;
    u8 modrm;
		x64OperandSize displacement;
    x64OperandSize immediate;
		x64OperandType args[4];
		u32 arglen;
	}* ins;
};
typedef struct x64LookupActualIns x64LookupActualIns;
typedef struct x64LookupGeneralIns x64LookupGeneralIns;

static const x64LookupGeneralIns x64Table[] = {
${Object.entries(instruction_variants).map(([name, variants]) => `\t{ "${name.toLowerCase().replace("_", " ")}", ${variants.length}, (struct x64LookupActualIns[]) { ${variants.map(v => v.text).join(", ")} } }`).join(",\n")}
};


#define imm(value) (x64Operand) { IMM64, value }
#define im64(value) (x64Operand) { IMM64, value }
#define im32(value) (x64Operand) { IMM32, value }
#define im16(value) (x64Operand) { IMM16, value }
#define im8(value) (x64Operand) { IMM8, value }

#define rh (x64Operand) { RH | R8 }
#define al (x64Operand) { AL | R8 }
#define cl (x64Operand) { CL | R8, 1 }
#define dl (x64Operand) { R8, 2 }
#define bl (x64Operand) { R8, 3 }
#define ah (x64Operand) { R8, 4 }
#define ch (x64Operand) { R8, 5 }
#define dh (x64Operand) { R8, 6 }
#define bh (x64Operand) { R8, 7 }

#define dx (x64Operand) { DX | R16 }
#define ax (x64Operand) { AX | R16 }

#define eax (x64Operand) { EAX | R32 }
#define ecx (x64Operand) { R32, 1 }
#define edx (x64Operand) { R32, 2 }
#define ebx (x64Operand) { R32, 3 }
#define esp (x64Operand) { R32, 4 }
#define ebp (x64Operand) { R32, 5 }
#define esi (x64Operand) { R32, 6 }
#define edi (x64Operand) { R32, 7 }
#define r8d (x64Operand) { R32, 8 }
#define r9d (x64Operand) { R32, 9 }
#define r10d (x64Operand) { R32, 10 }
#define r11d (x64Operand) { R32, 11 }
#define r12d (x64Operand) { R32, 12 }
#define r13d (x64Operand) { R32, 13 }
#define r14d (x64Operand) { R32, 14 }
#define r15d (x64Operand) { R32, 15 }


#define rax (x64Operand) { RAX | R64 }
#define rcx (x64Operand) { R64, 1 }
#define rdx (x64Operand) { R64, 2 }
#define rbx (x64Operand) { R64, 3 }
#define rsp (x64Operand) { R64, 4 }
#define rbp (x64Operand) { R64, 5 }
#define rsi (x64Operand) { R64, 6 }
#define rdi (x64Operand) { R64, 7 }
#define r8 (x64Operand) { R64, 8 }
#define r9 (x64Operand) { R64, 9 }
#define r10 (x64Operand) { R64, 10 }
#define r11 (x64Operand) { R64, 11 }
#define r12 (x64Operand) { R64, 12 }
#define r13 (x64Operand) { R64, 13 }
#define r14 (x64Operand) { R64, 14 }
#define r15 (x64Operand) { R64, 15 }

#define lb(l) (x64Operand) { LABEL, #l }

u64 label(char* name);
u32 x64emit(x64Ins* ins, char* opcode_dest);
char* x64assemble(x64 p);
void (*prog(void* mem, u32 size))(void);
`;

write(`asm_x86.h`, asmh);