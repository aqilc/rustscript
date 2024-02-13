#include <stdio.h>
#include <util.h>
#include <vec.h>
#include "asm_x86.h"

// https://github.com/StanfordPL/x64asm

/*
Dump of assembler code for function htget:
push: Pushes a value onto the stack.
mov: Moves data from one location to another.
sub: Subtracts one value from another and stores the result.
test: Performs a bitwise AND operation on two values and sets flags based on the result.
jne: Jumps to a specified location if the zero flag is not set (i.e., if the result of the previous test or cmp instruction was not zero).
jmp: Unconditionally jumps to a specified location.
call: Calls a subroutine (i.e., jumps to a specified location and saves the return address on the stack).
div: Divides one value by another and stores the result.
add: Adds two values together and stores the result.
shl: Shifts a value to the left by a specified number of bits.
je: Jumps to a specified location if the zero flag is set (i.e., if the result of the previous test or cmp instruction was zero).
cmpb: Compares two values and sets flags based on the result.
pop: Pops a value off of the stack.
ret: Returns from a subroutine (i.e., pops the return address off of the stack and jumps to it).
	<+0>:     push   %rbp
	<+1>:     mov    %rsp,%rbp
	<+4>:     sub    $0x30,%rsp
	<+8>:     mov    %rcx,0x10(%rbp)
	<+12>:    mov    %rdx,0x18(%rbp)
	<+16>:    mov    %r8d,0x20(%rbp)
	<+20>:    mov    %r9d,%eax
	<+23>:    mov    %al,0x28(%rbp)
	<+26>:    mov    0x10(%rbp),%rax
	<+30>:    mov    0x4(%rax),%eax
	<+33>:    test   %eax,%eax
	<+35>:    jne    0x1400039c0 <htget+47>
	<+37>:    mov    $0x0,%eax
	<+42>:    jmp    0x140003a8d <htget+252>
	<+47>:    mov    0x20(%rbp),%edx
	<+50>:    mov    0x18(%rbp),%rax
	<+54>:    mov    %rax,%rcx
	<+57>:    call   0x140008d56 <hash>
	<+62>:    mov    0x10(%rbp),%rdx
	<+66>:    mov    0x4(%rdx),%edx
	<+69>:    mov    %edx,%ecx
	<+71>:    mov    $0x0,%edx
	<+76>:    div    %ecx
	<+78>:    mov    %edx,%eax
	<+80>:    mov    %eax,-0xc(%rbp)
	<+83>:    mov    0x10(%rbp),%rax
	<+87>:    mov    0x18(%rax),%rcx
	<+91>:    mov    -0xc(%rbp),%eax
	<+94>:    movslq %eax,%rdx
	<+97>:    mov    %rdx,%rax
	<+100>:   add    %rax,%rax
	<+103>:   add    %rdx,%rax
	<+106>:   shl    $0x3,%rax
	<+110>:   add    %rcx,%rax
	<+113>:   mov    %rax,-0x8(%rbp)
	<+117>:   mov    -0x8(%rbp),%rax
	<+121>:   mov    (%rax),%rax
	<+124>:   test   %rax,%rax
	<+127>:   je     0x140003a88 <htget+247>
	<+129>:   cmpb   $0x0,0x28(%rbp)
	<+133>:   je     0x140003a4e <htget+189>
	<+135>:   mov    -0x8(%rbp),%rax
	<+139>:   mov    (%rax),%rax
	<+142>:   mov    0x18(%rbp),%rdx
	<+146>:   mov    %rax,%rcx
	<+149>:   call   0x140010da0 <strcmp>
	<+154>:   test   %eax,%eax
	<+156>:   jne    0x140003a39 <htget+168>
	<+158>:   mov    -0x8(%rbp),%rax
	<+162>:   mov    0x8(%rax),%rax
	<+166>:   jmp    0x140003a8d <htget+252>
	<+168>:   mov    -0x8(%rbp),%rax
	<+172>:   mov    0x10(%rax),%rax
	<+176>:   mov    %rax,-0x8(%rbp)
	<+180>:   cmpq   $0x0,-0x8(%rbp)
	<+185>:   jne    0x140003a18 <htget+135>
	<+187>:   jmp    0x140003a88 <htget+247>
	<+189>:   mov    0x20(%rbp),%ecx
	<+192>:   mov    -0x8(%rbp),%rax
	<+196>:   mov    (%rax),%rax
	<+199>:   mov    0x18(%rbp),%rdx
	<+203>:   mov    %rcx,%r8
	<+206>:   mov    %rax,%rcx
	<+209>:   call   0x140010d58 <memcmp>
	<+214>:   test   %eax,%eax
	<+216>:   jne    0x140003a75 <htget+228>
	<+218>:   mov    -0x8(%rbp),%rax
	<+222>:   mov    0x8(%rax),%rax
	<+226>:   jmp    0x140003a8d <htget+252>
	<+228>:   mov    -0x8(%rbp),%rax
	<+232>:   mov    0x10(%rax),%rax
	<+236>:   mov    %rax,-0x8(%rbp)
	<+240>:   cmpq   $0x0,-0x8(%rbp)
	<+245>:   jne    0x140003a4e <htget+189>
	<+247>:   mov    $0x0,%eax
	<+252>:   add    $0x30,%rsp
	<+256>:   pop    %rbp
	<+257>:   ret
*/


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
	u32 len = 0;

	// Prefixes
	if(res->preflen) {
		memcpy(opcode_dest, res->prefixes, res->preflen);
		*opcode_dest += res->preflen; len += res->preflen;
	}
	
	// 66H prefix
	if(res->pref66) *opcode_dest = 0x66, opcode_dest ++, len ++;

	// 67H prefix
	if(res->mem_operand && ins->params[res->mem_operand].value & ((u64) 1 << 61))
		*opcode_dest = 0x67, opcode_dest ++, len ++;

	// REX prefix
	u8 rex = res->rex | ((res->reg_operand && ins->params[res->reg_operand - 1].value & 0x8) ? 0x44 : 0);
	if(rex) *opcode_dest = rex, opcode_dest ++, len ++;

	// opcode
	memcpy(opcode_dest, res->opcode, res->oplen);
	opcode_dest += res->oplen; len += res->oplen;

	if(!res->modrm && res->reg_operand)
		// printf("reg operand: %d, value: %lld", res->reg_operand, ins->params[res->reg_operand - 1].value),
		*(opcode_dest - 1) |= (ins->params[res->reg_operand - 1].value & 0x7);

	// Immediate
	if(res->immediate) {
		u32 size = ins->params[res->immediate - 1].type >> 1;
		// printf("Immediate: %d\n", res->immediate);
		switch(size) {
			case 1: *opcode_dest = ins->params[res->immediate - 1].value; break;
			case 2: *(u16*) opcode_dest = ins->params[res->immediate - 1].value; break;
			case 4: *(u32*) opcode_dest = ins->params[res->immediate - 1].value; break;
			case 8: *(u64*) opcode_dest = ins->params[res->immediate - 1].value; break;
		}
		opcode_dest += size; len += size;
	}

	return len;
}

char* x64as(x64 p, u32* len) {
	char* code = malloc(14);
	u32 ins = 0;
	u32 emitted = 0;

	while (p[ins].op) {
		u32 curlen = x64emit(p + ins, code + emitted);
		if(!curlen) {
			free(code);
			return NULL;
		}
		emitted += curlen;
		ins ++;
	}
	return code;
}

