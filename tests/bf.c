#define INT BRUH_WHY_FUCK_YOU
#include "tests.h"
#undef FAR
#undef IN
#undef INT
#undef OUT
#include <asm/asm_x64.h>

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
	
#ifdef _WIN32
	x64Operand arg1 = rcx, arg2 = rdx;
#else
	x64Operand arg1 = rdi, arg2 = rsi;
#endif
	
	vpusharr(ret, {
		{ PUSH, rbp },
		{ MOV, rbp, rsp },
		{ MOV, rax, arg1 },
		{ PUSH, arg1 } // RCX = argument 1. 
	});

	bool raxoverwritten = false;

	while(*in) {
		switch(*in) {
		case '>':
		case '<':
			vpush(ret, { *in == '>' ? INC : DEC, m64($rbp, -8) });
			
			if(!raxoverwritten)
				vpush(ret, { *in == '>' ? INC : DEC, rax });
			break;
		case '+':
		case '-': {
			if(raxoverwritten) {
				vpush(ret, { MOV, rax, m64($rbp, -8) });
				raxoverwritten = false;
			}

			vpush(ret, { *in == '+' ? INC : DEC, m8($rax) });
			break;
		}
		case '[':
			vpusharr(ret, {
				{ LEA, rsi, m64($riprel, 0) }, // 0 here means $+0 or the current instruction
				{ PUSH, rsi }
			});
			raxoverwritten = true; // Because ] overwrites rax, so it's probably overwritten and if it's not, nothing bad happens.
			break;
		case '.':
			raxoverwritten = true;
			vpusharr(ret, {
				{ TEST, arg2, arg2 }, // If there's no putchar function passed in, just skip.
				{ JZ, rel(6) },
				{ MOV, rax, mem($rbp, -8) },
				{ MOV, rcx, mem($rax) },
				{ SUB, rsp, imm(64) }, // Should investigate aligining the stack to 16 bytes but this works for now(what msvc does).
				{ MOV, rax, arg2 },
				{ CALL, rax },
				{ ADD, rsp, imm(64) },
			});
			break;
		case ']':
			raxoverwritten = true;
			vpusharr(ret, {
				{ MOV, rax, mem($rbp, -8) },
				{ CMP, m8($rax), imm(0) },
				{ JZ, rel(3) },
				{ POP, rax },
				{ JMP, rax },
			});
		default: break;
		}
		in++;
	}

	vpusharr(ret, {
		{ MOV, rsp, rbp },
		{ POP, rbp },
		{ RET },
	});
	return ret;
}


char buf[200] = {};
void custom_putchar(int c) {
	buf[strlen(buf)] = c;
}

void (*hi)(char* buf, void* printfn);
TEST("Print a letter: Compile") {
	x64Ins* ins = bf_compile("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.");
	uint32_t len;
	void* compiled = x64as(ins, vlen(ins), &len);
	hi = (void*) x64_exec(compiled, len);
}

TEST("Print a letter: Run") {
	char buf[2] = {};
	hi(buf);
	expectstreq(buf, "s");
}


TEST("Print hello world: Compile") {
	x64Ins* ins = bf_compile(prog1);
	uint32_t len = 0;
	void* compiled = x64as(ins, vlen(ins), &len);
	hi = (void*) x64_exec(compiled, len);
}

TEST("Print hello world: Run") {
	char buf[20] = {0};
	hi(buf);
	expectstreq(buf, "Hello World!");
}

#include "tests_end.h"
