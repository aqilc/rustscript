#include "tests.h"
#undef FAR
#define VEC_H_IMPLEMENTATION
#include <vec.h>
#include <asm/asm_x86.h>

TEST("Assemble: `mov al, 3`") {
	x64 code = {
		MOV, {al, imm(3)}
	};
	
	char* ret = vnew();
	vpushn(ret, 14, 0);
	u32 len = x64emit(code, ret);

	// assertstreq(ret, (char[]) { 0xB0, 0x03, 0 });
	// asserteq(len, 2);
	asserteq(ret[0], 0x0);
	asserteq(len, 0);
}

TEST("Assemble: `push {rax}`") {
	x64 code = {
		PUSH, {rax}
	};
	
	char* ret = vnew();
	vpushn(ret, 14, 0);
	u32 len = x64emit(code, ret);

	// asserteq(ret[0], 0x50);
	// asserteq(len, 1);
	asserteq(ret[0], 0x0);
	asserteq(len, 0);
}

TEST("Assemble an actual ins: `das`") {
	x64 code = {
		DAS, {}
	};
	
	char* ret = vnew();
	vpushn(ret, 14, 0);
	u32 len = x64emit(code, ret);

	asserteq(ret[0], 0x2F);
	asserteq(len, 1);
}

#include "tests_end.h"