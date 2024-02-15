#include <stdio.h>
#include <util.h>
#include <vec.h>
#include "asm_x86.h"

// https://github.com/StanfordPL/x64asm

/**
 * Goal: Run this assembly program.

default rel

extern printf

segment .rdata
		msg db `Hello world!\r\n`, 0

segment .text

global main
main:
		sub     rsp, 40

		lea     rcx, [msg]
		call    printf

		xor     rax, rax
		add     rsp, 40
		ret

*/

// https://l-m.dev/cs/jitcalc/#:~:text=make%20it%20executable%3F-,C%20Territory,-V%20does%20not

#define ismem(x) (x > M8 && x < FARPTR1664)

static inline x64LookupActualIns* identify(x64Ins* ins) {
	const x64LookupGeneralIns* unresins = x64Table + (ins->op - 1);
	x64LookupActualIns* primary = NULL;
	x64LookupActualIns* secondary = NULL;
	bool secondaryprefferred = false;

	u32 operandnum = 0;
	while(ins->params[operandnum].type)
		operandnum ++;

	// ---------------------- Instruction resolution and Validation ---------------------- //
	
	for(u32 i = 0; i < unresins->numactualins; i ++) {
		if(unresins->ins[i].arglen != operandnum) continue;
		enum { NOTMATCH, PRIMARY, SECONDARY } match = PRIMARY;
		for(u32 j = 0; j < operandnum; j ++)
			// For instructions that have compatible operands but not the exact ones
			if (unresins->ins[i].args[j] != ins->params[j].type && unresins->ins[i].args[j] & ins->params[j].type) match = SECONDARY;
			else if (unresins->ins[i].args[j] != ins->params[j].type) { match = NOTMATCH; break; }
		if(match == PRIMARY) {
			// if(primary) printf("ERROR: Found two primary instructions for %s with %d arguments: `%s`(`%s`) and `%s`(`%s`)", unresins->name, operandnum, primary->orig_ins, primary->orig_opcode, unresins->ins[i].orig_ins, unresins->ins[i].orig_opcode);
			primary = unresins->ins + i;
		} else if(match == SECONDARY) {
			if(secondaryprefferred && !unresins->ins[i].preffered) continue;
			// if(secondary) printf("ERROR: Found two secondary instructions for %s with %d arguments: `%s`(`%s`) and `%s`(`%s`)", unresins->name, operandnum, secondary->orig_ins, secondary->orig_opcode, unresins->ins[i].orig_ins, unresins->ins[i].orig_opcode);
			secondary = unresins->ins + i;
			if(secondary->preffered) secondaryprefferred = true;
		}
	}

	if(!primary) {
		if(!secondary) {
			printf("No matching instruction for %s with %d arguments", unresins->name, operandnum);
			return 0;
		}
		// else printf("No primary instruction for %s with %d arguments, using `%s` secondary", unresins->name, operandnum, secondary->orig_ins);
		primary = secondary;
	}
	// else printf("Using primary instruction for %s with %d arguments, which is %lld in the array and has %d opcode(s).", unresins->name, operandnum, primary - unresins->ins, primary->oplen);

	return primary;
}


// Instructions to keep note of: MOVS mem, mem on line 1203
u32 x64emit(x64Ins* ins, char* opcode_dest) {
	if(ins->op == 0) return 0;
	x64LookupActualIns* res = identify(ins);
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

	// Prefixes
	if(res->prefixes) {
		if(res->prefixes < 0x100) *opcode_dest = res->prefixes, opcode_dest ++;
		else *(u16*) opcode_dest = res->prefixes, opcode_dest += 2;
	}

	// Segment Register for memory operands
	if(res->mem_operand && ins->params[res->mem_operand].type & ((u64) 0x7 << 56))
		*opcode_dest = ((char[]) { 0x26, 0x2e, 0x36, 0x3e, 0x64, 0x65 })[((ins->params[res->mem_operand].type >> 56) & 0x7) - 1], opcode_dest ++; 
	
	// 66H prefix
	if(res->pref66) *opcode_dest = 0x66, opcode_dest ++;

	// 67H prefix
	if(res->mem_operand && (ins->params[res->mem_operand - 1].value & ((u64) 0x1 << 60)))
		printf("Actual value: %llX", ins->params[res->mem_operand - 1].value),
		*opcode_dest = 0x67, opcode_dest ++;

	// REX prefix
	u8 rex = res->rex;
	if(res->reg_operand)
		if((ins->params[res->reg_operand - 1].value & 0x8) ? 0x44 : 0) {
			if(!res->mem_operand) rex |= 0x41;
			else rex |= 0x44;
		}
	if(res->mem_operand)
		if((ins->params[res->mem_operand - 1].value & 0x8) ? 0x44 : 0) {
			if(!res->reg_operand) rex |= 0x41;
			else rex |= 0x44;
		}
	if(rex) *opcode_dest = rex, opcode_dest ++;

	// opcode
	memcpy(opcode_dest, res->opcode, res->oplen);
	opcode_dest += res->oplen; res->oplen;

	if(!res->modrmreq && res->reg_operand)
		// printf("reg operand: %d, value: %lld", res->reg_operand, ins->params[res->reg_operand - 1].value),
		*(opcode_dest - 1) |= (ins->params[res->reg_operand - 1].value & 0x7);

	// ModR/M
	if(res->modrmreq) {
		u8 modrm = res->modrm;
		if(ismem(ins->params[res->mem_operand - 1].type)) {
			// TODO
		} else {
			modrm |= 0xC0 | ins->params[res->mem_operand - 1].value & 0x7;
			if(res->modrmreg)
				modrm |= (ins->params[res->reg_operand - 1].value & 0x7) << 3;
		}
		// if(!res->modrmreg) {
			
		// 	// Only take care of non-memory operands for now
		// 	if(!res->mem_operand)
		// 		modrm |= 0xC0, modrm |= ins->params[res->reg_operand - 1].value & 0x7;
			

		// 	// if(res->reg_operand) modrm |= (ins->params[res->reg_operand - 1].value & 0x7) << 3;
		// } else {

		// }
		*opcode_dest = modrm; opcode_dest ++;
	}

	// Immediate
	if(res->immediate) {
		u32 size = ins->params[res->immediate - 1].type >> 1;
		switch(size) {
			case 1: *       opcode_dest = ins->params[res->immediate - 1].value; break;
			case 2: *(u16*) opcode_dest = ins->params[res->immediate - 1].value; break;
			case 4: *(u32*) opcode_dest = ins->params[res->immediate - 1].value; break;
			case 8: *(u64*) opcode_dest = ins->params[res->immediate - 1].value; break;
		}
		opcode_dest += size;
	}

	return opcode_dest - opcode_dest_start;
}

char* x64as(x64 p, u32* len) {
	char* code = malloc(14);
	u32 ins = 0;

	while (p[ins].op) {
		u32 curlen = x64emit(p + ins, code + *len);
		if(!curlen) {
			free(code);
			*len = 0;
			return NULL;
		}
		*len += curlen;
		code = realloc(code, *len + 14);
		ins ++;
	}
	return code;
}

