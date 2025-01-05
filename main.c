#include <stdio.h>
#include "lib/asm/asm_x64.h"

int main() {
	char* str = "Hello World!";
	x64 code = {
		{ MOV, rax, imfn(puts) },
		{ MOV, rcx, imfn(str) },
		{ CALL, rax },
	};
	
	uint32_t len = 0;
	uint8_t* assembled = x64as(code, sizeof(code) / sizeof(code[0]), &len);
	if(!len) return 1;
	
	x64_exec(assembled, len)();
	return 0;
}
