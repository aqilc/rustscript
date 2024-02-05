#pragma once
#include <stdint.h>
#include <hash.h>
#include "util.h"

enum x64OperandType {
	NONE = 0, //for an operand constructed without a type

  HINT = 0x1,

  // IMMEDIATES
  IMM64 = 0x2, IMM32 = 0x4, IMM16 = 0x8, IMM8 = 0x2,
  ZERO = 0x20, ONE = 0x40, THREE = 0x80, // For the enter/leave instructions

  LABEL = 0x100,

  M8 = 0x200, M16 = 0x400, M32 = 0x800, M64 = 0x1000, M128 = 0x2000, M256 = 0x4000, M16_INT = 0x8000, M32_INT = 0x10000,
  M64_INT = 0x20000, M32_FP = 0x40000, M64_FP = 0x80000, M80_FP = 0x100000, M80_BCD = 0x200000, M2_BYTE = 0x400000,
  M28_BYTE = 0x800000, M108_BYTE = 0x1000000, M512_BYTE = 0x2000000,
  FAR_PTR_16_16 = 0x4000000, FAR_PTR_16_32 = 0x8000000, FAR_PTR_16_64 = 0x10000000,
  
  MM = 0x20000000,

  PREF66 = 0x40000000,
  PREFREX_W = 0x80000000,
  FAR = 0x100000000,

  MOFFS8 = 0x200000000, MOFFS16 = 0x400000000, MOFFS32 = 0x800000000, MOFFS64 = 0x1000000000,

  R8 = 0x2000000000, RH = 0x4000000000, AL = 0x8000000000, CL = 0x10000000000,
  R16 = 0x20000000000, AX = 0x40000000000, DX = 0x80000000000,
  R32 = 0x100000000000, EAX = 0x200000000000,
  R64 = 0x400000000000, RAX = 0x800000000000,

  REL8 = 0x1000000000000,
  REL32 = 0x2000000000000,

  SEGMENT_REG = 0x4000000000000, FS = 0x8000000000000, GS = 0x10000000000000,

  ST = 0x20000000000000, ST_0 = 0x40000000000000,

  XMM = 0x80000000000000, XMM_0 = 0x100000000000000,
  YMM = 0x200000000000000 // EXACTLY ENOUGH TO FIT IN A 64-BIT INTEGER LETS FUCKING GO
};
typedef enum x64OperandType x64OperandType;

enum x64OperandSize { BYTE, WORD, LONG, QUAD };
typedef enum x64OperandSize x64OperandSize;

enum x64Op {
	AAA, AAD, AAM, AAS, ARPL, BOUND, CALL, CLTS, DAA, DAS, DEC, F2XM1, FABS, FADDP, FCHS, FCLEX, FNCLEX, FCOM, FCOMP, FCOMPP, FCOS, FDECSTP, FDIVP, FDIVRP, FINCSTP, FINIT, FNINIT, FLD1, FLDL2T, FLDL2E, FLDPI, FLDLG2, FLDLN2, FLDZ, FMULP, FNOP, FPATAN, FPREM, FPREM1, FPTAN, FRNDINT, FSCALE, FSIN, FSINCOS, FSQRT, FSTSW, FNSTSW, FSUBP, FSUBRP, FTST, FUCOM, FUCOMP, FUCOMPP, FXAM, FXCH, FXTRACT, FYL2X, FYL2XP1, HLT, INC, INTO, INVD, INVPCID, JCXZ, JA, JAE, JB, JBE, JC, JE, JG, JGE, JL, JLE, JNA, JNAE, JNB, JNBE, JNC, JNE, JNG, JNGE, JNL, JNLE, JNO, JNP, JNS, JNZ, JO, JP, JPE, JPO, JS, JZ, JMP, LDS, LES, LEAVE, MOV, PINSRQ, POP, POPA, POPAD, POPFD, PUSH, PUSHA, PUSHAD, PUSHFD, RDMSR, RDPMC, RDTSC, RDTSCP, RSM, WBINVD, WRMSR, XSETBV
};
typedef enum x64Op x64Op;


struct x64PrefGroup {
	enum { PREF_GROUP_1, PREF_GROUP_2, PREF_GROUP_3, PREF_GROUP_4 } group;
};
typedef struct x64PrefGroup x64PrefGroup;

struct x64Operand {
  x64OperandType type;
  u64 value;
};
typedef struct x64Operand x64Operand;

struct x64Ins {
	x64Op op;
	x64Operand params[4];
};
typedef struct x64Ins x64Ins;
typedef x64Ins x64[];

struct x64LookupGeneralIns {
	char* name;
	unsigned int numactualins;
	struct x64LookupActualIns {
		x64PrefGroup pref_groups[4];
		char opcode[4];
    bool modrm;
		x64OperandSize displacement;
    x64OperandSize immediate;
		x64OperandType args[4];
	}* ins;
};
typedef struct x64LookupGeneralIns x64LookupGeneralIns;

x64LookupGeneralIns x64Table[] = {
	{ "aaa", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "aad", 2, (struct x64LookupActualIns[]) { {  }, {  } } },
	{ "aam", 2, (struct x64LookupActualIns[]) { {  }, {  } } },
	{ "aas", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "arpl", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "bound", 2, (struct x64LookupActualIns[]) { {  }, {  } } },
	{ "call", 3, (struct x64LookupActualIns[]) { {  }, {  }, {  } } },
	{ "clts", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "daa", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "das", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "dec", 2, (struct x64LookupActualIns[]) { {  }, {  } } },
	{ "f2xm1", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fabs", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "faddp", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fchs", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fclex", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fnclex", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fcom", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fcomp", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fcompp", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fcos", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fdecstp", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fdivp", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fdivrp", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fincstp", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "finit", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fninit", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fld1", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fldl2t", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fldl2e", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fldpi", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fldlg2", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fldln2", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fldz", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fmulp", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fnop", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fpatan", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fprem", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fprem1", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fptan", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "frndint", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fscale", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fsin", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fsincos", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fsqrt", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fstsw", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fnstsw", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fsubp", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fsubrp", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "ftst", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fucom", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fucomp", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fucompp", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fxam", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fxch", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fxtract", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fyl2x", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "fyl2xp1", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "hlt", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "inc", 2, (struct x64LookupActualIns[]) { {  }, {  } } },
	{ "into", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "invd", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "invpcid", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jcxz", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "ja", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jae", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jb", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jbe", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jc", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "je", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jg", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jge", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jl", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jle", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jna", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jnae", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jnb", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jnbe", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jnc", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jne", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jng", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jnge", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jnl", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jnle", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jno", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jnp", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jns", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jnz", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jo", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jp", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jpe", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jpo", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "js", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jz", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "jmp", 3, (struct x64LookupActualIns[]) { {  }, {  }, {  } } },
	{ "lds", 2, (struct x64LookupActualIns[]) { {  }, {  } } },
	{ "les", 2, (struct x64LookupActualIns[]) { {  }, {  } } },
	{ "leave", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "mov", 10, (struct x64LookupActualIns[]) { {  }, {  }, {  }, {  }, {  }, {  }, {  }, {  }, {  }, {  } } },
	{ "pinsrq", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "pop", 6, (struct x64LookupActualIns[]) { {  }, {  }, {  }, {  }, {  }, {  } } },
	{ "popa", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "popad", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "popfd", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "push", 5, (struct x64LookupActualIns[]) { {  }, {  }, {  }, {  }, {  } } },
	{ "pusha", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "pushad", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "pushfd", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "rdmsr", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "rdpmc", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "rdtsc", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "rdtscp", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "rsm", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "wbinvd", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "wrmsr", 1, (struct x64LookupActualIns[]) { {  } } },
	{ "xsetbv", 1, (struct x64LookupActualIns[]) { {  } } }
};


#define imm(value) (x64Operand) { (((value) < 0x100) ? IMM8 : ((value) < 0x10000) ? IMM16 : ((value) < 0x100000000) ? IMM32 : IMM64), value }

#define eax { EAX | R32 }
#define ecx { R32, 1 }
#define edx { R32, 2 }
#define ebx { R32, 3 }
#define esp { R32, 4 }
#define ebp { R32, 5 }
#define esi { R32, 6 }
#define edi { R32, 7 }
#define r8d { R32, 8 }
#define r9d { R32, 9 }
#define r10d { R32, 10 }
#define r11d { R32, 11 }
#define r12d { R32, 12 }
#define r13d { R32, 13 }
#define r14d { R32, 14 }
#define r15d { R32, 15 }


#define rax { RAX | R64 }
#define rcx { R64, 1 }
#define rdx { R64, 2 }
#define rbx { R64, 3 }
#define rsp { R64, 4 }
#define rbp { R64, 5 }
#define rsi { R64, 6 }
#define rdi { R64, 7 }
#define r8 { R64, 8 }
#define r9 { R64, 9 }
#define r10 { R64, 10 }
#define r11 { R64, 11 }
#define r12 { R64, 12 }
#define r13 { R64, 13 }
#define r14 { R64, 14 }
#define r15 { R64, 15 }

