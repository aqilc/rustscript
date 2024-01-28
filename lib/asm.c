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

enum AssFn {
	AF_RET, AF_CALL, AF_PUSH, AF_POP,
	
	AF_MOV,
	
	AF_LEA,
	
	AF_XOR, AF_ADD, AF_SUB,
};
typedef enum AssFn AssFn;

struct Instruction {
	AssFn f;
	char* name;
	
};
