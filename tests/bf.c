#define INT BRUH_WHY_FUCK_YOU
#include "tests.h"
#undef FAR
#undef IN
#undef INT
#undef OUT
#include <asm/asm_x86.h>

#define VEC_H_IMPLEMENTATION
#include <vec.h>

#define PROG(...) #__VA_ARGS__

char* prog1 = PROG(
+++++ +++++             initialize counter (cell #0) to 10
[                       use loop to set the next four cells to 70/100/30/10
	> +++++ ++              add  7 to cell #1
	> +++++ +++++           add 10 to cell #2 
	> +++                   add  3 to cell #3
	> +                     add  1 to cell #4
	<<<< -                  decrement counter (cell #0)
]                   
> ++ .                  print 'H'
> + .                   print 'e'
+++++ ++ .              print 'l'
.                       print 'l'
+++ .                   print 'o'
> ++ .                  print ' '
<< +++++ +++++ +++++ .  print 'W'
> .                     print 'o'
+++ .                   print 'r'
----- - .               print 'l'
----- --- .             print 'd'
> + .                   print '!'
> .                     print '\n'
);

x64Ins* bf_compile(char* in) {
	x64Ins* ret = vnew();
	vpusharr(ret, {
		{ PUSH, rbp },
		{ MOV, rbp, rsp },
		{ MOV, rcx, imm(256) },
		{ MOV, rax, im64((uint64_t)(void*)calloc)},
		{ CALL, rax },
		{ PUSH, rax },
	});

	while(*in) {
		switch(*in) {
		case '>': vpush(ret, { DEC, m64($rbp, -8) }); break;
		case '<': vpush(ret, { INC, m64($rbp, -8) }); break;
		case '+': vpusharr(ret, { { MOV, rax, m64($rbp, -8) }, { INC, m8($rax) } }); break;
		case '-': vpusharr(ret, { { MOV, rax, m64($rbp, -8) }, { DEC, m8($rax) } }); break;
		case '[': vpusharr(ret, { { LEA, rax, m64($riprel, -1) }, { PUSH, rax } }); break;
		case '.':
			vpusharr(ret, {
				{ MOV, rax, mem($rbp, -8) },
				{ MOV, rcx, mem($rax) },
				{ SUB, rsp, imm(64) },
				{ MOV, rax, im64((uint64_t)(void*)putchar) },
				{ CALL, rax },
				{ ADD, rsp, imm(64) },
			});
			break;
		case ']':
			vpusharr(ret, {
				{ MOV, rax, mem($rbp, -8) },
				{ CMP, m8($rax), imm(0) },
				{ JZ, rel(2) },
				{ POP, rax },
				{ JMP, rax },
			});
			break;
		default: break;
		}
		in ++;
	}

	vpusharr(ret, {
		{ MOV, rsp, rbp },
		{ POP, rbp },
		{ RET },
		{ 0 }
	});
	return ret;
}

TEST("Print a letter") {
	x64Ins* ins = bf_compile("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.");
	uint32_t len;
	void* program = x64as(vlen(ins), ins, &len);
	void (*hi)() = run(program, len);
	hi();
}

TEST("Print hello world") {
	x64Ins* ins = bf_compile(prog1);
	uint32_t len;
	void* program = x64as(vlen(ins), ins, &len);
	void (*hi)() = run(program, len);
	hi();
}

#include "tests_end.h"
