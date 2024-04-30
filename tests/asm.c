// #define NO_PRINT
#define INT BRUH_WHY_FUCK_YOU
#include "tests.h"
#undef FAR
#undef IN
#undef INT
#undef OUT
#include <asm/asm_x86.h>

int instructionlen;
int expectedinslen;
x64Ins curins;
double hi;

#define INSTEST(bytes, ...) curins = (x64Ins) { __VA_ARGS__ }; SUB(#__VA_ARGS__ " => " #bytes) {\
	instructionlen = x64emit(&curins, buf);\
	expectedinslen = sizeof(#bytes) / 5;\
	expecteq(instructionlen, expectedinslen);
#define INSTESTMEMEQ(...) assertbyteseq(buf, { __VA_ARGS__ }); } SUBBENCH() { x64emit(&curins, buf); }

TEST("Assemble push instructions (1 argument, with optional REX and Addressing Overrides)") {
	char buf[3] = {0};

	benchiters(12345);

	INSTEST(0x50, PUSH, rax);
	INSTESTMEMEQ(0x50);

	INSTEST(0x52, PUSH, rdx);
	INSTESTMEMEQ(0x52);

	INSTEST(0x66 0x53, PUSH, bx);
	INSTESTMEMEQ(0x66, 0x53);

	INSTEST(0x41 0x50, PUSH, r8);
	INSTESTMEMEQ(0x41, 0x50);
}

TEST("Assemble call/jmp instructions (1 argument, with optional REX and Immediates)") {
	char buf[7] = {0};

	INSTEST(0xFF 0xD0, CALL, rax);
	INSTESTMEMEQ(0xFF, 0xD0);

	INSTEST(0x41 0xFF 0xD0, CALL, r8);
	INSTESTMEMEQ(0x41, 0xFF, 0xD0);
}

TEST("Assemble mov instructions (2 arguments, with optional REX and Immediates)") {
	char buf[10] = {0};
	
	INSTEST(0xB0 0x03, MOV, al, im8(3));
	INSTESTMEMEQ(0xB0, 0x03);

	INSTEST(0x48 0xC7 0xC0 0x04 0x00 0x00 0x00, MOV, rax, imm(4));
	INSTESTMEMEQ(0x48, 0xC7, 0xC0, 0x04, 0x00, 0x00, 0x00);

	INSTEST(0x4C 0x89 0xC0, MOV, rax, r8);
	INSTESTMEMEQ(0x4C, 0x89, 0xC0);

	INSTEST(0x67 0x8A 0x4B 0x03, MOV, cl, mem($ebx, 3));
	INSTESTMEMEQ(0x67, 0x8A, 0x4B, 0x03);

	INSTEST(0x67 0x66 0x0F 0x28 0x40 0x0A, MOVAPD, xmm0, mem($eax, 0xA));
	INSTESTMEMEQ(0x67, 0x66, 0x0f, 0x28, 0x40, 0x0A);
}

TEST("Assemble lea instructions (2 arguments, with optional REX and Immediates)") {
	char buf[10] = {0};

	INSTEST(0x49 0x8D 0x49 0x08, LEA, rcx, mem($r9, 8));
	INSTESTMEMEQ(0x49, 0x8D, 0x49, 0x08);

	INSTEST(0x67 0x41 0x8D 0x4B 0x08, LEA, ecx, mem($r11d, 8));
	INSTESTMEMEQ(0x67, 0x41, 0x8D, 0x4B, 0x08);

	INSTEST(0x48 0x8d 0x05 0x08 0x00 0x00 0x00, LEA, rax, mem($rip, 8));
	INSTESTMEMEQ(0x48, 0x8d, 0x05, 0x08, 0x00, 0x00, 0x00);
}

TEST("Assemble FPU Instructions (1-2 arguments with different, FPU operand types)") {
	char buf[10] = {0};

	INSTEST(0xD9 0xC0, FLD, st0);
	INSTESTMEMEQ(0xD9, 0xC0);

	INSTEST(0xDD 0x04 0x25 0x02 0x00 0x00 0x00, FLD, m64($none, 2));
	INSTESTMEMEQ(0xDD, 0x04, 0x25, 0x02, 0x00, 0x00, 0x00);

	INSTEST(0xD8 0xCA, FMUL, st0, st2);
	INSTESTMEMEQ(0xD8, 0xCA);

	INSTEST(0xD9 0xE8, FLD1);
	INSTESTMEMEQ(0xD9, 0xE8);

	INSTEST(0x9B, FWAIT);
	INSTESTMEMEQ(0x9B);
}

TEST("Assemble random SSE Instructions (2-3 arguments with many different prefixes)") {
	char buf[10] = {0};
	
	INSTEST(0x67 0xF3 0x0F 0x7E 0x40 0x08, MOVQ, xmm0, mem($eax, 8));
	INSTESTMEMEQ(0x67, 0xF3, 0x0F, 0x7E, 0x40, 0x08);

	INSTEST(0x66 0x0F 0x66 0xC1, PCMPGTD, xmm0, xmm1);
	INSTESTMEMEQ(0x66, 0x0F, 0x66, 0xC1);

	// INSTEST(0xC5 0xF8 0x59 0xE6, VMULPS, xmm4, xmm0, xmm6);
	// INSTESTMEMEQ(0xC5, 0xF8, 0x59, 0xE6);
}

TEST("Stringify instructions") {
	SUB("Stringify MOV, {rax, rax} => mov rax, rax")
		assertstreq(x64stringify((x64) { MOV, {rax, rax}, 0 }), "\tmov\trax, rax");

	SUB("Stringify MOV, {rax, imm(0xABCDEF)} => mov rax, 0xABCDEF")
		assertstreq(x64stringify((x64) { MOV, {rax, imm(0xABCDEF)}, 0 }), "\tmov\trax, 0xABCDEF");

	SUB("Stringify MOV, {rax, mem($rax, 0xABCDEF, $r8, 2, $es)} => mov rax, es:[rax + r8 * 2 + 0xABCDEF]")
		assertstreq(x64stringify((x64) { MOV, {rax, mem($rax, 0xABCDEF, $r8, 2, $es)}, 0 }), "\tmov\trax, es:[rax + 0xABCDEF + r8 * 2]");

	
}

#include "tests_end.h"
