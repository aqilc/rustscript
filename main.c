// Threading library
// https://github.com/tinycthread/tinycthread
#include <stdio.h>
#include "lib/asm/asm_x86.h"

void print() {
	printf("HI!!!");
}

int main() {
	x64 hi2 = {
		// INT3, {},
		MOV, {rax, im64((u64)(void*)print)},
		CALL, {rax},
		END
	};
	
	u32 len = 0;
	char* assembled = x64as(hi2, &len);
	run(assembled, len)(); // prints "HI!!!"

	return 0;
}
