// #define NO_PRINT
#define INT WINDOWS_INT
#include "tests.h"
#undef FAR
#undef IN
#undef INT
#undef OUT
#include <asm/asm_x64.h>

int instructionlen;
int expectedinslen;
x64Ins curins;

#define INSTEST(bytes, ...) \
	curins = (x64Ins) { __VA_ARGS__ };\
	SUB(#__VA_ARGS__ " => " #bytes) {\
		instructionlen = x64emit(&curins, buf);\
		expectedinslen = sizeof(#bytes) / 5;\
		if(instructionlen == 0) puts(x64error(NULL));\
		expecteq(instructionlen, expectedinslen);
#define INSTESTMEMEQ(...) expectbyteseq(buf, { __VA_ARGS__ }); } SUBBENCH() { x64emit(&curins, buf); }

TEST("Assemble push instructions (1 argument, with optional REX and Addressing Overrides)") {
	uint8_t buf[3] = {0};

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
	uint8_t buf[7] = {0};

	INSTEST(0xFF 0xD0, CALL, rax);
	INSTESTMEMEQ(0xFF, 0xD0);

	INSTEST(0x41 0xFF 0xD0, CALL, r8);
	INSTESTMEMEQ(0x41, 0xFF, 0xD0);
}

TEST("Assemble mov instructions (2 arguments, with optional REX and Immediates)") {
	uint8_t buf[10] = {0};
	
	INSTEST(0xB0 0x03, MOV, al, imm(3));
	INSTESTMEMEQ(0xB0, 0x03);

	INSTEST(0x67 0x8A 0x4B 0x03, MOV, cl, mem($ebx, 3));
	INSTESTMEMEQ(0x67, 0x8A, 0x4B, 0x03);

	INSTEST(0x48 0xC7 0xC0 0x04 0x00 0x00 0x00, MOV, rax, imm(4));
	INSTESTMEMEQ(0x48, 0xC7, 0xC0, 0x04, 0x00, 0x00, 0x00);

	INSTEST(0x4C 0x89 0xC0, MOV, rax, r8);
	INSTESTMEMEQ(0x4C, 0x89, 0xC0);

	INSTEST(0x4D 0x89 0xEC, MOV, r12, r13);
	INSTESTMEMEQ(0x4D, 0x89, 0xEC);

	INSTEST(0x48 0xBA 0x39 0x20 0x39 0x20 0x09 0x02 0x00 0x00, MOV, rdx, imm(0x20920392039));
	INSTESTMEMEQ(0x48, 0xBA, 0x39, 0x20, 0x39, 0x20, 0x09, 0x02, 0x00, 0x00);

	INSTEST(0xF3 0x44 0x0F 0x10 0x3C 0x48, MOVSS, xmm15, mem($rax, 0, $rcx, 2));
	INSTESTMEMEQ(0xF3, 0x44, 0x0F, 0x10, 0x3C, 0x48);

	INSTEST(0x67 0x66 0x0F 0x28 0x40 0x0A, MOVAPD, xmm0, mem($eax, 0xA));
	INSTESTMEMEQ(0x67, 0x66, 0x0f, 0x28, 0x40, 0x0A);
}

TEST("Assemble lea instructions (2 arguments, with optional REX and Immediates)") {
	uint8_t buf[10] = {0};

	INSTEST(0x49 0x8D 0x49 0x08, LEA, rcx, mem($r9, 8));
	INSTESTMEMEQ(0x49, 0x8D, 0x49, 0x08);

	INSTEST(0x67 0x41 0x8D 0x4B 0x08, LEA, ecx, mem($r11d, 8));
	INSTESTMEMEQ(0x67, 0x41, 0x8D, 0x4B, 0x08);

	INSTEST(0x48 0x8d 0x05 0x08 0x00 0x00 0x00, LEA, rax, mem($rip, 8));
	INSTESTMEMEQ(0x48, 0x8d, 0x05, 0x08, 0x00, 0x00, 0x00);
}

TEST("Assemble Special Instructions (1-2 arguments with different, FPU operand types)") {
	uint8_t buf[10] = {0};

	INSTEST(0xD9 0xC0, FLD, st0);
	INSTESTMEMEQ(0xD9, 0xC0);

	INSTEST(0xD9 0xE8, FLD1);
	INSTESTMEMEQ(0xD9, 0xE8);

	INSTEST(0xDD 0x04 0x25 0x02 0x00 0x00 0x00, FLD, m64($none, 2));
	INSTESTMEMEQ(0xDD, 0x04, 0x25, 0x02, 0x00, 0x00, 0x00);

	INSTEST(0xD8 0xCA, FMUL, st0, st2);
	INSTESTMEMEQ(0xD8, 0xCA);

	INSTEST(0xC3, RET);
	INSTESTMEMEQ(0xC3);
	
	INSTEST(0xCB, RET, { FAR });
	INSTESTMEMEQ(0xCB);

	INSTEST(0xAE, SCAS, m8($rdi));
	INSTESTMEMEQ(0xAE);

	INSTEST(0x9B, FWAIT);
	INSTESTMEMEQ(0x9B);

	INSTEST(0xC8 0x0A 0x00 0x01, ENTER, imm(10), imm(1));
	INSTESTMEMEQ(0xC8, 0x0A, 0x00, 0x01);

	INSTEST(0x67 0x0F 0x01 0x02, SGDT, mem($edx));
	INSTESTMEMEQ(0x67, 0x0F, 0x01, 0x02);

	INSTEST(0x0F 0x01 0x22, SMSW, mem($rdx));
	INSTESTMEMEQ(0x0F, 0x01, 0x22);
}

TEST("Assemble random SSE Instructions (2-3 arguments with many different prefixes)") {
	uint8_t buf[10] = {0};
	
	INSTEST(0x67 0xF3 0x0F 0x7E 0x40 0x08, MOVQ, xmm0, mem($eax, 8));
	INSTESTMEMEQ(0x67, 0xF3, 0x0F, 0x7E, 0x40, 0x08);

	INSTEST(0x66 0x0F 0x66 0xC1, PCMPGTD, xmm0, xmm1);
	INSTESTMEMEQ(0x66, 0x0F, 0x66, 0xC1);

	INSTEST(0x66 0x44 0x0F 0x10 0x72 0x0A, MOVUPD, xmm14, mem($rdx, 10));
	INSTESTMEMEQ(0x66, 0x44, 0x0F, 0x10, 0x72, 0x0A);

	INSTEST(0x0F 0x6F 0x4A 0x0A, MOVQ, mm1, mem($rdx, 10));
	INSTESTMEMEQ(0x0F, 0x6F, 0x4A, 0x0A);
}

TEST("Assemble AVX (VEX) Instructions (With the VEX Prefix)") {
	uint8_t buf[13] = {0};

	INSTEST(0xC5 0xF8 0x28 0xC6, VMOVAPS, xmm0, xmm6);
	INSTESTMEMEQ(0xC5, 0xF8, 0x28, 0xC6);

	INSTEST(0xC5 0xF9 0x6E 0xD0, VMOVD, xmm2, eax);
	INSTESTMEMEQ(0xC5, 0xF9, 0x6E, 0xD0);
	
	INSTEST(0xC5 0xF8 0x59 0xE6, VMULPS, xmm4, xmm0, xmm6);
	INSTESTMEMEQ(0xC5, 0xF8, 0x59, 0xE6);

	// Tests VSIB
	INSTEST(0xC4 0xE2 0xD5 0x93 0x54 0xD8 0x0A, VGATHERQPD, ymm2, mem($rax, 10, $ymm3, 8), ymm5);
	INSTESTMEMEQ(0xC4, 0xE2, 0xD5, 0x93, 0x54, 0xD8, 0x0A);

	INSTEST(0xC4 0xC1 0x58 0xC2 0x1C 0x10 0xFF, VCMPPS, xmm3, xmm4, mem($r8, 0, $rdx), imm(0xff));
	INSTESTMEMEQ(0xC4, 0xC1, 0x58, 0xC2, 0x1C, 0x10, 0xFF);

	INSTEST(0xC4 0xE3 0x75 0x4B 0x54 0x10 0x0A 0x50, VBLENDVPD, ymm2, ymm1, mem($rax, 10, $rdx), ymm5);
	INSTESTMEMEQ(0xC4, 0xE3, 0x75, 0x4B, 0x54, 0x10, 0x0A, 0x50);
}

TEST("Assemble instructions with extremely specific operands.") {
	uint8_t buf[10] = {0};

	INSTEST(0xD0 0xD0, RCL, al, imm(1));
	INSTESTMEMEQ(0xD0, 0xD0);

	INSTEST(0xD2 0xD0, RCL, al, cl);
	INSTESTMEMEQ(0xD2, 0xD0);

	INSTEST(0xD1 0x08, ROR, m32($rax), imm(1));
	INSTESTMEMEQ(0xD1, 0x08);

	INSTEST(0x48 0x15 0x0A 0x00 0x00 0x00, ADC, rax, im32(10))
	INSTESTMEMEQ(0x48, 0x15, 0x0A, 0x00, 0x00, 0x00);

	INSTEST(0x66 0x0F 0xA1, POP, fs, { PREF66 });
	INSTESTMEMEQ(0x66, 0x0F, 0xA1);

	INSTEST(0x0F 0xA9, POP, gs);
	INSTESTMEMEQ(0x0F, 0xA9)
}

TEST("Stringify instructions") {
	SUB("Stringify MOV, rax, rax => mov rax, rax")
		assertstreq(x64stringify((x64) { MOV, rax, rax }, 1), "mov rax, rax");

	SUB("Stringify MOV, rax, imm(0xABCDEF) => mov rax, 0xABCDEF")
		assertstreq(x64stringify((x64) { MOV, rax, imm(0xABCDEF) }, 1), "mov rax, 0xABCDEF");

	SUB("Stringify MOV, rax, mem($rax, 0xABCDEF, $r8, 2, $es) => mov rax, es:[rax + 0xABCDEF + r8 * 2]")
		assertstreq(x64stringify((x64) { MOV, rax, mem($rax, 0xABCDEF, $r8, 2, $es) }, 1), "mov rax, es:[rax + 0xABCDEF + r8 * 2]");

	SUB("Stringify LEA, rax, mem($riprel, 0xABCDEF) => lea rax, [$+11259375]")
		assertstreq(x64stringify((x64) { LEA, rax, mem($riprel, 0xABCDEF) }, 1), "lea rax, [$+11259375]");

	SUB("Stringify JMP, rel(1000) => jmp $+1000")
		assertstreq(x64stringify((x64) { JMP, rel(1000) }, 1), "jmp $+1000");

	SUB("Stringify VGATHERQPD, ymm3, mem($rax, 10, $ymm5, 8), ymm2 => vgatherqpd ymm3, [rax + 0xA + ymm5 * 8], ymm2")
		assertstreq(x64stringify((x64) { VGATHERQPD, ymm3, mem($rax, 10, $ymm5, 8), ymm2 }, 1), "vgatherqpd ymm3, [rax + 0xA + ymm5 * 8], ymm2");
}

#include "tests_end.h"
