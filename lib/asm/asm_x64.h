/*
 * asm_x64.h v1.1.0 - Aqil Contractor @aqilc 2025
 * Dual Licenced under MIT and Public Domain.
 *
 * This file includes all of the headers for the "chasm" library macros and functions.
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>

enum x64OperandType: uint64_t {
	NONE = 0, //for an operand constructed without a type

	HINT = 0x1,

	// IMMEDIATES
	IMM8 = 0x2, IMM16 = 0x4, IMM32 = 0x8, IMM64 = 0x10,
	
	X64_LABEL_REF = 0x20,

	M8 = 0x40, M16 = 0x80, M32 = 0x100, M64 = 0x200, M128 = 0x400, M256 = 0x800, M512 = 0x1000,
	FARPTR1616 = 0x2000, FARPTR1632 = 0x4000, FARPTR1664 = 0x8000,
	
	MM = 0x10000,

	PREF66 = 0x20000,
	PREFREX_W = 0x40000,
	FAR = 0x80000,

	MOFFS8 = 0x100000, MOFFS16 = 0x200000, MOFFS32 = 0x400000, MOFFS64 = 0x800000,

	R8 = 0x1000000, RH = 0x2000000, AL = 0x4000000, CL = 0x8000000,
	R16 = 0x10000000, AX = 0x20000000, DX = 0x40000000,
	R32 = 0x80000000, EAX = 0x100000000,
	R64 = 0x200000000, RAX = 0x400000000,

	REL8 = 0x800000000,
	REL32 = 0x1000000000,

	SREG = 0x2000000000, FS = 0x4000000000, GS = 0x8000000000,

	ST = 0x10000000000, ST_0 = 0x20000000000,

	XMM = 0x40000000000, XMM_0 = 0x80000000000,
	YMM = 0x100000000000,
	ZMM = 0x200000000000,
	
	CR0_7 = 0x400000000000, CR8 = 0x800000000000,
	DREG = 0x1000000000000,
	
	ONE = 0x2000000000000
};
typedef enum x64OperandType x64OperandType;


#define X64_ALLMEMMASK (M8 | M16 | M32 | M64 | M128 | M256 | M512)
#define X64_GPR (R8 | R16 | R32 | R64)
#define X64_ALLREGMASK (R8 | RH | R16 | R32 | R64 | MM | XMM | YMM | ZMM | SREG | CR0_7 | DREG | CR8)

enum x64Op: uint32_t {
	END_ASM, ADC, ADD, ADDPD, VADDPD, ADDPS, VADDPS, ADDSD, VADDSD, ADDSS, VADDSS, ADDSUBPD, VADDSUBPD, ADDSUBPS, VADDSUBPS, AESDEC, VAESDEC, AESDECLAST, VAESDECLAST, AESENC, VAESENC, AESENCLAST, VAESENCLAST, AESIMC, VAESIMC, AESKEYGENASSIST, VAESKEYGENASSIST, AND, ANDN, ANDPD, VANDPD, ANDPS, VANDPS, ANDNPD, VANDNPD, ANDNPS, VANDNPS, BLENDPD, VBLENDPD, BEXTR, BLENDPS, VBLENDPS, BLENDVPD, VBLENDVPD, BLENDVPS, VBLENDVPS, BLSI, BLSMSK, BLSR, BSF, BSR, BSWAP, BT, BTC, BTR, BTS, BZHI, CALL, CBW, CWDE, CDQE, CLC, CLD, CLFLUSH, CLI, CLTS, CMC, CMOVA, CMOVAE, CMOVB, CMOVBE, CMOVC, CMOVE, CMOVG, CMOVGE, CMOVL, CMOVLE, CMOVNA, CMOVNAE, CMOVNB, CMOVNBE, CMOVNC, CMOVNE, CMOVNG, CMOVNGE, CMOVNL, CMOVNLE, CMOVNO, CMOVNP, CMOVNS, CMOVNZ, CMOVO, CMOVP, CMOVPE, CMOVPO, CMOVS, CMOVZ, CMP, CMPPD, VCMPPD, CMPPS, VCMPPS, CMPS, CMPSB, CMPSW, CMPSD, CMPSQ, VCMPSD, CMPSS, VCMPSS, CMPXCHG, CMPXCHG8B, CMPXCHG16B, COMISD, VCOMISD, COMISS, VCOMISS, CPUID, CRC32, CVTDQ2PD, VCVTDQ2PD, CVTDQ2PS, VCVTDQ2PS, CVTPD2DQ, VCVTPD2DQ, CVTPD2PI, CVTPD2PS, VCVTPD2PS, CVTPI2PD, CVTPI2PS, CVTPS2DQ, VCVTPS2DQ, CVTPS2PD, VCVTPS2PD, CVTPS2PI, CVTSD2SI, VCVTSD2SI, CVTSD2SS, VCVTSD2SS, CVTSI2SD, VCVTSI2SD, CVTSI2SS, VCVTSI2SS, CVTSS2SD, VCVTSS2SD, CVTSS2SI, VCVTSS2SI, CVTTPD2DQ, VCVTTPD2DQ, CVTTPD2PI, CVTTPS2DQ, VCVTTPS2DQ, CVTTPS2PI, CVTTSD2SI, VCVTTSD2SI, CVTTSS2SI, VCVTTSS2SI, CWD, CDQ, CQO, DEC, DIV, DIVPD, VDIVPD, DIVPS, VDIVPS, DIVSD, VDIVSD, DIVSS, VDIVSS, DPPD, VDPPD, DPPS, VDPPS, EMMS, ENTER, EXTRACTPS, VEXTRACTPS, F2XM1, FABS, FADD, FADDP, FIADD, FBLD, FBSTP, FCHS, FCLEX, FNCLEX, FCMOVB, FCMOVE, FCMOVBE, FCMOVU, FCMOVNB, FCMOVNE, FCMOVNBE, FCMOVNU, FCOM, FCOMP, FCOMPP, FCOMI, FCOMIP, FUCOMI, FUCOMIP, FCOS, FDECSTP, FDIV, FDIVP, FIDIV, FDIVR, FDIVRP, FIDIVR, FFREE, FICOM, FICOMP, FILD, FINCSTP, FINIT, FNINIT, FIST, FISTP, FISTTP, FLD, FLD1, FLDL2T, FLDL2E, FLDPI, FLDLG2, FLDLN2, FLDZ, FLDCW, FLDENV, FMUL, FMULP, FIMUL, FNOP, FPATAN, FPREM, FPREM1, FPTAN, FRNDINT, FRSTOR, FSAVE, FNSAVE, FSCALE, FSIN, FSINCOS, FSQRT, FST, FSTP, FSTCW, FNSTCW, FSTENV, FNSTENV, FSTSW, FNSTSW, FSUB, FSUBP, FISUB, FSUBR, FSUBRP, FISUBR, FTST, FUCOM, FUCOMP, FUCOMPP, FXAM, FXCH, FXRSTOR, FXRSTOR64, FXSAVE, FXSAVE64, FXTRACT, FYL2X, FYL2XP1, HADDPD, VHADDPD, HADDPS, VHADDPS, HLT, HSUBPD, VHSUBPD, HSUBPS, VHSUBPS, IDIV, IMUL, IN, INC, INS, INSB, INSW, INSD, INSERTPS, VINSERTPS, INT3, INT1, INT, INVD, INVLPG, INVPCID, IRET, IRETD, IRETQ, JA, JAE, JB, JBE, JC, JECXZ, JRCXZ, JE, JG, JGE, JL, JLE, JNA, JNAE, JNB, JNBE, JNC, JNE, JNG, JNGE, JNL, JNLE, JNO, JNP, JNS, JNZ, JO, JP, JPE, JPO, JS, JZ, JMP, LAHF, LAR, LDDQU, VLDDQU, LDMXCSR, VLDMXCSR, LSS, LFS, LGS, LEA, LEAVE, LFENCE, LGDT, LIDT, LLDT, LMSW, LOCK, LODS, LODSB, LODSW, LODSD, LODSQ, LOOP, LOOPE, LOOPNE, LSL, LTR, LZCNT, MASKMOVDQU, VMASKMOVDQU, MASKMOVQ, MAXPD, VMAXPD, MAXPS, VMAXPS, MAXSD, VMAXSD, MAXSS, VMAXSS, MFENCE, MINPD, VMINPD, MINPS, VMINPS, MINSD, VMINSD, MINSS, VMINSS, MONITOR, MOV, MOVAPD, VMOVAPD, MOVAPS, VMOVAPS, MOVBE, MOVD, MOVQ, VMOVD, VMOVQ, MOVDDUP, VMOVDDUP, MOVDQA, VMOVDQA, MOVDQU, VMOVDQU, MOVDQ2Q, MOVHLPS, VMOVHLPS, MOVHPD, VMOVHPD, MOVHPS, VMOVHPS, MOVLHPS, VMOVLHPS, MOVLPD, VMOVLPD, MOVLPS, VMOVLPS, MOVMSKPD, VMOVMSKPD, MOVMSKPS, VMOVMSKPS, MOVNTDQA, VMOVNTDQA, MOVNTDQ, VMOVNTDQ, MOVNTI, MOVNTPD, VMOVNTPD, MOVNTPS, VMOVNTPS, MOVNTQ, MOVQ2DQ, MOVS, MOVSB, MOVSW, MOVSD, MOVSQ, VMOVSD, MOVSHDUP, VMOVSHDUP, MOVSLDUP, VMOVSLDUP, MOVSS, VMOVSS, MOVSX, MOVSXD, MOVUPD, VMOVUPD, MOVUPS, VMOVUPS, MOVZX, MPSADBW, VMPSADBW, MUL, MULPD, VMULPD, MULPS, VMULPS, MULSD, VMULSD, MULSS, VMULSS, MULX, MWAIT, NEG, NOP, NOT, OR, ORPD, VORPD, ORPS, VORPS, OUT, OUTS, OUTSB, OUTSW, OUTSD, PABSB, PABSW, PABSD, VPABSB, VPABSW, VPABSD, PACKSSWB, PACKSSDW, VPACKSSWB, VPACKSSDW, PACKUSDW, VPACKUSDW, PACKUSWB, VPACKUSWB, PADDB, PADDW, PADDD, VPADDB, VPADDW, VPADDD, PADDQ, VPADDQ, PADDSB, PADDSW, VPADDSB, VPADDSW, PADDUSB, PADDUSW, VPADDUSB, VPADDUSW, PALIGNR, VPALIGNR, PAND, VPAND, PANDN, VPANDN, PAUSE, PAVGB, PAVGW, VPAVGB, VPAVGW, PBLENDVB, VPBLENDVB, PBLENDW, VPBLENDW, PCLMULQDQ, VPCLMULQDQ, PCMPEQB, PCMPEQW, PCMPEQD, VPCMPEQB, VPCMPEQW, VPCMPEQD, PCMPEQQ, VPCMPEQQ, PCMPESTRI, VPCMPESTRI, PCMPESTRM, VPCMPESTRM, PCMPGTB, PCMPGTW, PCMPGTD, VPCMPGTB, VPCMPGTW, VPCMPGTD, PCMPGTQ, VPCMPGTQ, PCMPISTRI, VPCMPISTRI, PCMPISTRM, VPCMPISTRM, PDEP, PEXT, PEXTRB, PEXTRD, PEXTRQ, VPEXTRB, VPEXTRD, VPEXTRQ, PEXTRW, VPEXTRW, PHADDW, PHADDD, VPHADDW, VPHADDD, PHADDSW, VPHADDSW, PHMINPOSUW, VPHMINPOSUW, PHSUBW, PHSUBD, VPHSUBW, VPHSUBD, PHSUBSW, VPHSUBSW, PINSRB, PINSRD, VPINSRB, VPINSRD, VPINSRQ, PINSRW, VPINSRW, PMADDUBSW, VPMADDUBSW, PMADDWD, VPMADDWD, PMAXSB, VPMAXSB, PMAXSD, VPMAXSD, PMAXSW, VPMAXSW, PMAXUB, VPMAXUB, PMAXUD, VPMAXUD, PMAXUW, VPMAXUW, PMINSB, VPMINSB, PMINSD, VPMINSD, PMINSW, VPMINSW, PMINUB, VPMINUB, PMINUD, VPMINUD, PMINUW, VPMINUW, PMOVMSKB, VPMOVMSKB, PMOVSXBW, PMOVSXBD, PMOVSXBQ, PMOVSXWD, PMOVSXWQ, PMOVSXDQ, VPMOVSXBW, VPMOVSXBD, VPMOVSXBQ, VPMOVSXWD, VPMOVSXWQ, VPMOVSXDQ, PMOVZXBW, PMOVZXBD, PMOVZXBQ, PMOVZXWD, PMOVZXWQ, PMOVZXDQ, VPMOVZXBW, VPMOVZXBD, VPMOVZXBQ, VPMOVZXWD, VPMOVZXWQ, VPMOVZXDQ, PMULDQ, VPMULDQ, PMULHRSW, VPMULHRSW, PMULHUW, VPMULHUW, PMULHW, VPMULHW, PMULLD, VPMULLD, PMULLW, VPMULLW, PMULUDQ, VPMULUDQ, POP, POPCNT, POPF, POPFQ, POR, VPOR, PREFETCHT0, PREFETCHT1, PREFETCHT2, PREFETCHNTA, PSADBW, VPSADBW, PSHUFB, VPSHUFB, PSHUFD, VPSHUFD, PSHUFHW, VPSHUFHW, PSHUFLW, VPSHUFLW, PSHUFW, PSIGNB, PSIGNW, PSIGND, VPSIGNB, VPSIGNW, VPSIGND, PSLLDQ, VPSLLDQ, PSLLW, PSLLD, PSLLQ, VPSLLW, VPSLLD, VPSLLQ, PSRAW, PSRAD, VPSRAW, VPSRAD, PSRLDQ, VPSRLDQ, PSRLW, PSRLD, PSRLQ, VPSRLW, VPSRLD, VPSRLQ, PSUBB, PSUBW, PSUBD, VPSUBB, VPSUBW, VPSUBD, PSUBQ, VPSUBQ, PSUBSB, PSUBSW, VPSUBSB, VPSUBSW, PSUBUSB, PSUBUSW, VPSUBUSB, VPSUBUSW, PTEST, VPTEST, PUNPCKHBW, PUNPCKHWD, PUNPCKHDQ, PUNPCKHQDQ, VPUNPCKHBW, VPUNPCKHWD, VPUNPCKHDQ, VPUNPCKHQDQ, PUNPCKLBW, PUNPCKLWD, PUNPCKLDQ, PUNPCKLQDQ, VPUNPCKLBW, VPUNPCKLWD, VPUNPCKLDQ, VPUNPCKLQDQ, PUSH, PUSHQ, PUSHW, PUSHF, PUSHFQ, PXOR, VPXOR, RCL, RCR, ROL, ROR, RCPPS, VRCPPS, RCPSS, VRCPSS, RDFSBASE, RDGSBASE, RDMSR, RDPMC, RDRAND, RDTSC, RDTSCP, REP_INS, REP_MOVS, REP_OUTS, REP_LODS, REP_STOS, REPE_CMPS, REPE_SCAS, REPNE_CMPS, REPNE_SCAS, RET, RORX, ROUNDPD, VROUNDPD, ROUNDPS, VROUNDPS, ROUNDSD, VROUNDSD, ROUNDSS, VROUNDSS, RSQRTPS, VRSQRTPS, RSQRTSS, VRSQRTSS, SAHF, SAL, SAR, SHL, SHR, SARX, SHLX, SHRX, SBB, SCAS, SCASB, SCASW, SCASD, SCASQ, SETA, SETAE, SETB, SETBE, SETC, SETE, SETG, SETGE, SETL, SETLE, SETNA, SETNAE, SETNB, SETNBE, SETNC, SETNE, SETNG, SETNGE, SETNL, SETNLE, SETNO, SETNP, SETNS, SETNZ, SETO, SETP, SETPE, SETPO, SETS, SETZ, SFENCE, SGDT, SHLD, SHRD, SHUFPD, VSHUFPD, SHUFPS, VSHUFPS, SIDT, SLDT, SMSW, SQRTPD, VSQRTPD, SQRTPS, VSQRTPS, SQRTSD, VSQRTSD, SQRTSS, VSQRTSS, STC, STD, STI, STMXCSR, VSTMXCSR, STOS, STOSB, STOSW, STOSD, STOSQ, STR, SUB, SUBPD, VSUBPD, SUBPS, VSUBPS, SUBSD, VSUBSD, SUBSS, VSUBSS, SWAPGS, SYSCALL, SYSENTER, SYSEXIT, SYSRET, TEST, TZCNT, UCOMISD, VUCOMISD, UCOMISS, VUCOMISS, UD2, UNPCKHPD, VUNPCKHPD, UNPCKHPS, VUNPCKHPS, UNPCKLPD, VUNPCKLPD, UNPCKLPS, VUNPCKLPS, VBROADCASTSS, VBROADCASTSD, VBROADCASTF128, VCVTPH2PS, VCVTPS2PH, VERR, VERW, VEXTRACTF128, VEXTRACTI128, VFMADD132PD, VFMADD213PD, VFMADD231PD, VFMADD132PS, VFMADD213PS, VFMADD231PS, VFMADD132SD, VFMADD213SD, VFMADD231SD, VFMADD132SS, VFMADD213SS, VFMADD231SS, VFMADDSUB132PD, VFMADDSUB213PD, VFMADDSUB231PD, VFMADDSUB132PS, VFMADDSUB213PS, VFMADDSUB231PS, VFMSUBADD132PD, VFMSUBADD213PD, VFMSUBADD231PD, VFMSUBADD132PS, VFMSUBADD213PS, VFMSUBADD231PS, VFMSUB132PD, VFMSUB213PD, VFMSUB231PD, VFMSUB132PS, VFMSUB213PS, VFMSUB231PS, VFMSUB132SD, VFMSUB213SD, VFMSUB231SD, VFMSUB132SS, VFMSUB213SS, VFMSUB231SS, VFNMADD132PD, VFNMADD213PD, VFNMADD231PD, VFNMADD132PS, VFNMADD213PS, VFNMADD231PS, VFNMADD132SD, VFNMADD213SD, VFNMADD231SD, VFNMADD132SS, VFNMADD213SS, VFNMADD231SS, VFNMSUB132PD, VFNMSUB213PD, VFNMSUB231PD, VFNMSUB132PS, VFNMSUB213PS, VFNMSUB231PS, VFNMSUB132SD, VFNMSUB213SD, VFNMSUB231SD, VFNMSUB132SS, VFNMSUB213SS, VFNMSUB231SS, VGATHERDPD, VGATHERQPD, VGATHERDPS, VGATHERQPS, VPGATHERDD, VPGATHERQD, VPGATHERDQ, VPGATHERQQ, VINSERTF128, VINSERTI128, VMASKMOVPS, VMASKMOVPD, VPBLENDD, VPBROADCASTB, VPBROADCASTW, VPBROADCASTD, VPBROADCASTQ, VBROADCASTI128, VPERMD, VPERMPD, VPERMPS, VPERMQ, VPERM2I128, VPERMILPD, VPERMILPS, VPERM2F128, VPMASKMOVD, VPMASKMOVQ, VPSLLVD, VPSLLVQ, VPSRAVD, VPSRLVD, VPSRLVQ, VTESTPS, VTESTPD, VZEROALL, VZEROUPPER, WAIT, FWAIT, WBINVD, WRFSBASE, WRGSBASE, WRMSR, XACQUIRE, XRELEASE, XABORT, XADD, XBEGIN, XCHG, XEND, XGETBV, XLAT, XLATB, XOR, XORPD, VXORPD, XORPS, VXORPS, XRSTOR, XRSTOR64, XSAVE, XSAVE64, XSAVEOPT, XSAVEOPT64, XSETBV, XTEST, X64_LABEL_DEF
};
typedef enum x64Op x64Op;

struct x64Operand {
	x64OperandType type;
	int64_t value;
#ifdef __cplusplus
	constexpr x64Operand() : type(NONE), value(0) {}
	constexpr x64Operand(uint64_t t): type(static_cast<x64OperandType>(t)), value(0) {}
	constexpr x64Operand(uint64_t t, uint64_t v): type(static_cast<x64OperandType>(t)), value(v) {}
#endif
};
typedef struct x64Operand x64Operand;

struct x64Ins {
	x64Op op;
	x64Operand params[4];
#ifdef __cplusplus
	constexpr x64Ins(x64Op o, x64Operand p1, x64Operand p2, x64Operand p3, x64Operand p4) : op(o), params { p1, p2, p3, p4 } {}
	constexpr x64Ins(x64Op o, x64Operand p1, x64Operand p2, x64Operand p3) : op(o), params { p1, p2, p3 } {}
	constexpr x64Ins(x64Op o, x64Operand p1, x64Operand p2) : op(o), params { p1, p2 } {}
	constexpr x64Ins(x64Op o, x64Operand p1) : op(o), params { p1 } {}
	constexpr x64Ins(x64Op o) : op(o) {}
#endif
};
typedef struct x64Ins x64Ins;
typedef x64Ins x64[];

struct x64LookupGeneralIns {
	char* name;
	unsigned int numactualins;
	struct x64LookupActualIns {
		uint8_t mem_oper; // Index of memory operand if there is one + 1
		uint8_t reg_oper; // Index of register operand if there is one + 1
		uint8_t rel_oper; // Index of relative jump operand if there is one + 1
		uint8_t vex_oper; // Index of VEX operand if there is one + 1
    uint8_t imm_oper; // Index of immediate operand if there is one + 1
    uint8_t is4_oper; // Index of 4-byte immediate operand if there is one + 1
		uint8_t rex;
		uint8_t oplen;
		uint8_t preflen;
		uint8_t vex; // opcode_map if specified
		uint8_t vex_byte;
    uint8_t modrm;
		bool modrmreq;
		bool modrmreg;
		bool preffered;
		// uint8_t base_size;
		uint8_t arglen;
		uint32_t opcode;
		uint32_t prefixes;
		x64OperandType args[4];
	}* ins;
};
typedef struct x64LookupActualIns x64LookupActualIns;
typedef struct x64LookupGeneralIns x64LookupGeneralIns;

static const x64LookupGeneralIns x64Table[] = {
	{ "adc", 21, (struct x64LookupActualIns[]) { {
		.args = { AL, IMM8 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x14, .oplen = 1,
	}, {
		.args = { AX, IMM16 }, .arglen = 2, .imm_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x15, .oplen = 1,
	}, {
		.args = { EAX, IMM32 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x15, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { RAX, IMM32 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x15, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { R8 | M8, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x80, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { R16 | M16, IMM16 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x81, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { R32 | M32, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x81, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x10,
		.args = { R64 | M64, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x81, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x10,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, R8 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x10, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, RH }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x10, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16 | M16, R16 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x11, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x11, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x11, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x12, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { RH, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x12, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x13, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x13, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x13, .oplen = 1,
	} } },
	{ "add", 21, (struct x64LookupActualIns[]) { {
		.args = { AL, IMM8 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x04, .oplen = 1,
	}, {
		.args = { AX, IMM16 }, .arglen = 2, .imm_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x05, .oplen = 1,
	}, {
		.args = { EAX, IMM32 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x05, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { RAX, IMM32 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x05, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x80, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R16 | M16, IMM16 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x81, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R32 | M32, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x81, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x0,
		.args = { R64 | M64, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x81, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x0,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, R8 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x00, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, RH }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x00, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16 | M16, R16 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x01, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x01, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x01, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x02, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { RH, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x02, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x03, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x03, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x03, .oplen = 1,
	} } },
	{ "addpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x580F, .oplen = 2,
	} } },
	{ "vaddpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x58, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x58, .oplen = 1,
	} } },
	{ "addps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x580F, .oplen = 2,
	} } },
	{ "vaddps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x58, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x58, .oplen = 1,
	} } },
	{ "addsd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x580F, .oplen = 2,
	} } },
	{ "vaddsd", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x58, .oplen = 1,
	} } },
	{ "addss", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x580F, .oplen = 2,
	} } },
	{ "vaddss", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x58, .oplen = 1,
	} } },
	{ "addsubpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xD00F, .oplen = 2,
	} } },
	{ "vaddsubpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xD0, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xD0, .oplen = 1,
	} } },
	{ "addsubps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0xD00F, .oplen = 2,
	} } },
	{ "vaddsubps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xD0, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7f, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xD0, .oplen = 1,
	} } },
	{ "aesdec", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDE380F, .oplen = 3,
	} } },
	{ "vaesdec", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xDE, .oplen = 1,
	} } },
	{ "aesdeclast", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDF380F, .oplen = 3,
	} } },
	{ "vaesdeclast", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xDF, .oplen = 1,
	} } },
	{ "aesenc", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDC380F, .oplen = 3,
	} } },
	{ "vaesenc", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xDC, .oplen = 1,
	} } },
	{ "aesenclast", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDD380F, .oplen = 3,
	} } },
	{ "vaesenclast", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xDD, .oplen = 1,
	} } },
	{ "aesimc", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDB380F, .oplen = 3,
	} } },
	{ "vaesimc", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xDB, .oplen = 1,
	} } },
	{ "aeskeygenassist", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDF3A0F, .oplen = 3,
	} } },
	{ "vaeskeygenassist", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xDF, .oplen = 1,
	} } },
	{ "and", 21, (struct x64LookupActualIns[]) { {
		.args = { AL, IMM8 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x24, .oplen = 1,
	}, {
		.args = { AX, IMM16 }, .arglen = 2, .imm_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x25, .oplen = 1,
	}, {
		.args = { EAX, IMM32 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x25, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { RAX, IMM32 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x25, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R8 | M8, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x80, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R16 | M16, IMM16 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x81, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R32 | M32, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x81, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x20,
		.args = { R64 | M64, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x81, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x20,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, R8 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x20, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, RH }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x20, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16 | M16, R16 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x21, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x21, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x21, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x22, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { RH, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x22, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x23, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x23, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x23, .oplen = 1,
	} } },
	{ "andn", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { R32, R32, R32 | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF2, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xf8, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64, R64 | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF2, .oplen = 1,
	} } },
	{ "andpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x540F, .oplen = 2,
	} } },
	{ "vandpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x54, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x54, .oplen = 1,
	} } },
	{ "andps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x540F, .oplen = 2,
	} } },
	{ "vandps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x54, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x54, .oplen = 1,
	} } },
	{ "andnpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x550F, .oplen = 2,
	} } },
	{ "vandnpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x55, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x55, .oplen = 1,
	} } },
	{ "andnps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x550F, .oplen = 2,
	} } },
	{ "vandnps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x55, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x55, .oplen = 1,
	} } },
	{ "blendpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x0D3A0F, .oplen = 3,
	} } },
	{ "vblendpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x0D, .oplen = 1,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x0D, .oplen = 1,
	} } },
	{ "bextr", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32, R32 }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xf8, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64, R64 }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0xF7, .oplen = 1,
	} } },
	{ "blendps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x0C3A0F, .oplen = 3,
	} } },
	{ "vblendps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x0C, .oplen = 1,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x0C, .oplen = 1,
	} } },
	{ "blendvpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, XMM_0 }, .arglen = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x15380F, .oplen = 3,
	} } },
	{ "vblendvpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128, XMM }, .arglen = 4, .mem_oper = 3, .reg_oper = 1, .is4_oper = 4, .vex_oper = 2,
		.opcode = 0x4B, .oplen = 1,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256, YMM }, .arglen = 4, .mem_oper = 3, .reg_oper = 1, .is4_oper = 4, .vex_oper = 2,
		.opcode = 0x4B, .oplen = 1,
	} } },
	{ "blendvps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, XMM_0 }, .arglen = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x14380F, .oplen = 3,
	} } },
	{ "vblendvps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128, XMM }, .arglen = 4, .mem_oper = 3, .reg_oper = 1, .is4_oper = 4, .vex_oper = 2,
		.opcode = 0x4A, .oplen = 1,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256, YMM }, .arglen = 4, .mem_oper = 3, .reg_oper = 1, .is4_oper = 4, .vex_oper = 2,
		.opcode = 0x4A, .oplen = 1,
	} } },
	{ "blsi", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x78, .modrmreq = true, .modrm = 0x18,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0xF3, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xf8, .modrmreq = true, .modrm = 0x18,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0xF3, .oplen = 1,
	} } },
	{ "blsmsk", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x78, .modrmreq = true, .modrm = 0x10,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0xF3, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xf8, .modrmreq = true, .modrm = 0x10,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0xF3, .oplen = 1,
	} } },
	{ "blsr", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x78, .modrmreq = true, .modrm = 0x8,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0xF3, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xf8, .modrmreq = true, .modrm = 0x8,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0xF3, .oplen = 1,
	} } },
	{ "bsf", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xBC0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xBC0F, .oplen = 2,
	}, {
		.rex = 0x48,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xBC0F, .oplen = 2,
	} } },
	{ "bsr", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xBD0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xBD0F, .oplen = 2,
	}, {
		.rex = 0x48,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xBD0F, .oplen = 2,
	} } },
	{ "bswap", 2, (struct x64LookupActualIns[]) { {
		.args = { R32 }, .arglen = 1, .reg_oper = 1,
		.opcode = 0xC80F, .oplen = 2,
	}, {
		.rex = 0x48,
		.args = { R64 }, .arglen = 1, .reg_oper = 1,
		.opcode = 0xC80F, .oplen = 2,
	} } },
	{ "bt", 6, (struct x64LookupActualIns[]) { {
		.args = { R16 | M16, R16 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xA30F, .oplen = 2,
	}, {
		.args = { R32 | M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xA30F, .oplen = 2,
	}, {
		.rex = 0x48,
		.args = { R64 | M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xA30F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xBA0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xBA0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x20,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xBA0F, .oplen = 2,
	} } },
	{ "btc", 6, (struct x64LookupActualIns[]) { {
		.args = { R16 | M16, R16 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xBB0F, .oplen = 2,
	}, {
		.args = { R32 | M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xBB0F, .oplen = 2,
	}, {
		.rex = 0x48,
		.args = { R64 | M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xBB0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xBA0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xBA0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x38,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xBA0F, .oplen = 2,
	} } },
	{ "btr", 6, (struct x64LookupActualIns[]) { {
		.args = { R16 | M16, R16 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xB30F, .oplen = 2,
	}, {
		.args = { R32 | M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xB30F, .oplen = 2,
	}, {
		.rex = 0x48,
		.args = { R64 | M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xB30F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xBA0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xBA0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x30,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xBA0F, .oplen = 2,
	} } },
	{ "bts", 6, (struct x64LookupActualIns[]) { {
		.args = { R16 | M16, R16 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xAB0F, .oplen = 2,
	}, {
		.args = { R32 | M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xAB0F, .oplen = 2,
	}, {
		.rex = 0x48,
		.args = { R64 | M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xAB0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xBA0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xBA0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x28,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xBA0F, .oplen = 2,
	} } },
	{ "bzhi", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32, R32 }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0xF5, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xf8, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64, R64 }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0xF5, .oplen = 1,
	} } },
	{ "call", 5, (struct x64LookupActualIns[]) { {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0xE8, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { R64 | M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xFF, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { FARPTR1616 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xFF, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { FARPTR1632 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xFF, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x18,
		.args = { FARPTR1664 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xFF, .oplen = 1,
	} } },
	{ "cbw", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0x66, .preflen = 1, .opcode = 0x98, .oplen = 1,
	} } },
	{ "cwde", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x98, .oplen = 1,
	} } },
	{ "cdqe", 1, (struct x64LookupActualIns[]) { {
		.rex = 0x48,
		.opcode = 0x98, .oplen = 1,
	} } },
	{ "clc", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF8, .oplen = 1,
	} } },
	{ "cld", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xFC, .oplen = 1,
	} } },
	{ "clflush", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x38,
		.args = { M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xAE0F, .oplen = 2,
	} } },
	{ "cli", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xFA, .oplen = 1,
	} } },
	{ "clts", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x060F, .oplen = 2,
	} } },
	{ "cmc", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF5, .oplen = 1,
	} } },
	{ "cmova", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x470F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x470F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x470F, .oplen = 2,
	} } },
	{ "cmovae", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x430F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x430F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x430F, .oplen = 2,
	} } },
	{ "cmovb", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x420F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x420F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x420F, .oplen = 2,
	} } },
	{ "cmovbe", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x460F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x460F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x460F, .oplen = 2,
	} } },
	{ "cmovc", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x420F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x420F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x420F, .oplen = 2,
	} } },
	{ "cmove", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x440F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x440F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x440F, .oplen = 2,
	} } },
	{ "cmovg", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x4F0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4F0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4F0F, .oplen = 2,
	} } },
	{ "cmovge", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x4D0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4D0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4D0F, .oplen = 2,
	} } },
	{ "cmovl", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x4C0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4C0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4C0F, .oplen = 2,
	} } },
	{ "cmovle", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x4E0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4E0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4E0F, .oplen = 2,
	} } },
	{ "cmovna", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x460F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x460F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x460F, .oplen = 2,
	} } },
	{ "cmovnae", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x420F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x420F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x420F, .oplen = 2,
	} } },
	{ "cmovnb", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x430F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x430F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x430F, .oplen = 2,
	} } },
	{ "cmovnbe", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x470F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x470F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x470F, .oplen = 2,
	} } },
	{ "cmovnc", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x430F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x430F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x430F, .oplen = 2,
	} } },
	{ "cmovne", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x450F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x450F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x450F, .oplen = 2,
	} } },
	{ "cmovng", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x4E0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4E0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4E0F, .oplen = 2,
	} } },
	{ "cmovnge", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x4C0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4C0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4C0F, .oplen = 2,
	} } },
	{ "cmovnl", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x4D0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4D0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4D0F, .oplen = 2,
	} } },
	{ "cmovnle", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x4F0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4F0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4F0F, .oplen = 2,
	} } },
	{ "cmovno", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x410F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x410F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x410F, .oplen = 2,
	} } },
	{ "cmovnp", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x4B0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4B0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4B0F, .oplen = 2,
	} } },
	{ "cmovns", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x490F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x490F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x490F, .oplen = 2,
	} } },
	{ "cmovnz", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x450F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x450F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x450F, .oplen = 2,
	} } },
	{ "cmovo", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x400F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x400F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x400F, .oplen = 2,
	} } },
	{ "cmovp", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x4A0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4A0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4A0F, .oplen = 2,
	} } },
	{ "cmovpe", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x4A0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4A0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4A0F, .oplen = 2,
	} } },
	{ "cmovpo", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x4B0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4B0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x4B0F, .oplen = 2,
	} } },
	{ "cmovs", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x480F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x480F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x480F, .oplen = 2,
	} } },
	{ "cmovz", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x440F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x440F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x440F, .oplen = 2,
	} } },
	{ "cmp", 21, (struct x64LookupActualIns[]) { {
		.args = { AL, IMM8 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x3C, .oplen = 1,
	}, {
		.args = { AX, IMM16 }, .arglen = 2, .imm_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x3D, .oplen = 1,
	}, {
		.args = { EAX, IMM32 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x3D, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { RAX, IMM32 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x3D, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { R8 | M8, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x80, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { R16 | M16, IMM16 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x81, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { R32 | M32, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x81, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x38,
		.args = { R64 | M64, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x81, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x38,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, R8 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x38, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, RH }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x38, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16 | M16, R16 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x39, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x39, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x39, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x3A, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { RH, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x3A, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x3B, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x3B, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x3B, .oplen = 1,
	} } },
	{ "cmppd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xC20F, .oplen = 2,
	} } },
	{ "vcmppd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xC2, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xC2, .oplen = 1,
	} } },
	{ "cmpps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xC20F, .oplen = 2,
	} } },
	{ "vcmpps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xC2, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xC2, .oplen = 1,
	} } },
	{ "cmps", 4, (struct x64LookupActualIns[]) { {
		.args = { M8, M8 }, .arglen = 2,
		.opcode = 0xA6, .oplen = 1,
	}, {
		.args = { M16, M16 }, .arglen = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xA7, .oplen = 1,
	}, {
		.args = { M32, M32 }, .arglen = 2,
		.opcode = 0xA7, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { M64, M64 }, .arglen = 2,
		.opcode = 0xA7, .oplen = 1,
	} } },
	{ "cmpsb", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xA6, .oplen = 1,
	} } },
	{ "cmpsw", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0x66, .preflen = 1, .opcode = 0xA7, .oplen = 1,
	} } },
	{ "cmpsd", 2, (struct x64LookupActualIns[]) { {
		.opcode = 0xA7, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0xC20F, .oplen = 2,
	} } },
	{ "cmpsq", 1, (struct x64LookupActualIns[]) { {
		.rex = 0x48,
		.opcode = 0xA7, .oplen = 1,
	} } },
	{ "vcmpsd", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xC2, .oplen = 1,
	} } },
	{ "cmpss", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xC20F, .oplen = 2,
	} } },
	{ "vcmpss", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xC2, .oplen = 1,
	} } },
	{ "cmpxchg", 5, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, R8 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xB00F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, RH }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xB00F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16 | M16, R16 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xB10F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xB10F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xB10F, .oplen = 2,
	} } },
	{ "cmpxchg8b", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x8,
		.args = { M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xC70F, .oplen = 2,
	} } },
	{ "cmpxchg16b", 1, (struct x64LookupActualIns[]) { {
		.rex = 0x48, .modrmreq = true, .modrm = 0x8,
		.args = { M128 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xC70F, .oplen = 2,
	} } },
	{ "comisd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x2F0F, .oplen = 2,
	} } },
	{ "vcomisd", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2F, .oplen = 1,
	} } },
	{ "comiss", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2F0F, .oplen = 2,
	} } },
	{ "vcomiss", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2F, .oplen = 1,
	} } },
	{ "cpuid", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xA20F, .oplen = 2,
	} } },
	{ "crc32", 5, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0xF0380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0xF1380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0xF1380F, .oplen = 3,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0xF0380F, .oplen = 3,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0xF1380F, .oplen = 3,
	} } },
	{ "cvtdq2pd", 1, (struct x64LookupActualIns[]) { {
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xE60F, .oplen = 2,
	} } },
	{ "vcvtdq2pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xE6, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7e, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xE6, .oplen = 1,
	} } },
	{ "cvtdq2ps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x5B0F, .oplen = 2,
	} } },
	{ "vcvtdq2ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x5B, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x5B, .oplen = 1,
	} } },
	{ "cvtpd2dq", 1, (struct x64LookupActualIns[]) { {
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0xE60F, .oplen = 2,
	} } },
	{ "vcvtpd2dq", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xE6, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7f, .modrmreq = true, .modrmreg = true,
		.args = { XMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xE6, .oplen = 1,
	} } },
	{ "cvtpd2pi", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x2D0F, .oplen = 2,
	} } },
	{ "cvtpd2ps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x5A0F, .oplen = 2,
	} } },
	{ "vcvtpd2ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x5A, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { XMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x5A, .oplen = 1,
	} } },
	{ "cvtpi2pd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x2A0F, .oplen = 2,
	} } },
	{ "cvtpi2ps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2A0F, .oplen = 2,
	} } },
	{ "cvtps2dq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x5B0F, .oplen = 2,
	} } },
	{ "vcvtps2dq", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x5B, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x5B, .oplen = 1,
	} } },
	{ "cvtps2pd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x5A0F, .oplen = 2,
	} } },
	{ "vcvtps2pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x5A, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x5A, .oplen = 1,
	} } },
	{ "cvtps2pi", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2D0F, .oplen = 2,
	} } },
	{ "cvtsd2si", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x2D0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x2D0F, .oplen = 2,
	} } },
	{ "vcvtsd2si", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { R32, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2D, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0xfb, .modrmreq = true, .modrmreg = true,
		.args = { R64, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2D, .oplen = 1,
	} } },
	{ "cvtsd2ss", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x5A0F, .oplen = 2,
	} } },
	{ "vcvtsd2ss", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5A, .oplen = 1,
	} } },
	{ "cvtsi2sd", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x2A0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { XMM, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x2A0F, .oplen = 2,
	} } },
	{ "vcvtsi2sd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, R32 | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x2A, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0xfb, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, R64 | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x2A, .oplen = 1,
	} } },
	{ "cvtsi2ss", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x2A0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { XMM, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x2A0F, .oplen = 2,
	} } },
	{ "vcvtsi2ss", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, R32 | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x2A, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0xfa, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, R64 | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x2A, .oplen = 1,
	} } },
	{ "cvtss2sd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x5A0F, .oplen = 2,
	} } },
	{ "vcvtss2sd", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5A, .oplen = 1,
	} } },
	{ "cvtss2si", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x2D0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x2D0F, .oplen = 2,
	} } },
	{ "vcvtss2si", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { R32, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2D, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0xfa, .modrmreq = true, .modrmreg = true,
		.args = { R64, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2D, .oplen = 1,
	} } },
	{ "cvttpd2dq", 1, (struct x64LookupActualIns[]) { {
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xE60F, .oplen = 2,
	} } },
	{ "vcvttpd2dq", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xE6, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { XMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xE6, .oplen = 1,
	} } },
	{ "cvttpd2pi", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x2C0F, .oplen = 2,
	} } },
	{ "cvttps2dq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x5B0F, .oplen = 2,
	} } },
	{ "vcvttps2dq", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x5B, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7e, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x5B, .oplen = 1,
	} } },
	{ "cvttps2pi", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2C0F, .oplen = 2,
	} } },
	{ "cvttsd2si", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x2C0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x2C0F, .oplen = 2,
	} } },
	{ "vcvttsd2si", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { R32, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2C, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0xfb, .modrmreq = true, .modrmreg = true,
		.args = { R64, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2C, .oplen = 1,
	} } },
	{ "cvttss2si", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x2C0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x2C0F, .oplen = 2,
	} } },
	{ "vcvttss2si", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { R32, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2C, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0xfa, .modrmreq = true, .modrmreg = true,
		.args = { R64, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2C, .oplen = 1,
	} } },
	{ "cwd", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0x66, .preflen = 1, .opcode = 0x99, .oplen = 1,
	} } },
	{ "cdq", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x99, .oplen = 1,
	} } },
	{ "cqo", 1, (struct x64LookupActualIns[]) { {
		.rex = 0x48,
		.opcode = 0x99, .oplen = 1,
	} } },
	{ "dec", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x8,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xFE, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { R16 | M16 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xFF, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { R32 | M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xFF, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x8,
		.args = { R64 | M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xFF, .oplen = 1,
	} } },
	{ "div", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x30,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF6, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { R16 | M16 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { R32 | M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x30,
		.args = { R64 | M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	} } },
	{ "divpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x5E0F, .oplen = 2,
	} } },
	{ "vdivpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5E, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5E, .oplen = 1,
	} } },
	{ "divps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x5E0F, .oplen = 2,
	} } },
	{ "vdivps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5E, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5E, .oplen = 1,
	} } },
	{ "divsd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x5E0F, .oplen = 2,
	} } },
	{ "vdivsd", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5E, .oplen = 1,
	} } },
	{ "divss", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x5E0F, .oplen = 2,
	} } },
	{ "vdivss", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5E, .oplen = 1,
	} } },
	{ "dppd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x413A0F, .oplen = 3,
	} } },
	{ "vdppd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x41, .oplen = 1,
	} } },
	{ "dpps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x403A0F, .oplen = 3,
	} } },
	{ "vdpps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x40, .oplen = 1,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x40, .oplen = 1,
	} } },
	{ "emms", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x770F, .oplen = 2,
	} } },
	{ "enter", 1, (struct x64LookupActualIns[]) { {
		.args = { IMM16, IMM8 }, .arglen = 2, .imm_oper = 1,
		.opcode = 0xC8, .oplen = 1,
	} } },
	{ "extractps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R64 | R32 | M32, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x173A0F, .oplen = 3,
	} } },
	{ "vextractps", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x17, .oplen = 1,
	} } },
	{ "f2xm1", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF0D9, .oplen = 2,
	} } },
	{ "fabs", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xE1D9, .oplen = 2,
	} } },
	{ "fadd", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xD8, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDC, .oplen = 1,
	}, {
		.args = { ST_0, ST }, .arglen = 2, .reg_oper = 2,
		.opcode = 0xC0D8, .oplen = 2,
	}, {
		.args = { ST, ST_0 }, .arglen = 2, .reg_oper = 1,
		.opcode = 0xC0DC, .oplen = 2,
	} } },
	{ "faddp", 2, (struct x64LookupActualIns[]) { {
		.args = { ST, ST_0 }, .arglen = 2, .reg_oper = 1,
		.opcode = 0xC0DE, .oplen = 2,
	}, {
		.opcode = 0xC1DE, .oplen = 2,
	} } },
	{ "fiadd", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDA, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { M16 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDE, .oplen = 1,
	} } },
	{ "fbld", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x20,
		.args = { X64_ALLMEMMASK }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDF, .oplen = 1,
	} } },
	{ "fbstp", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x30,
		.args = { X64_ALLMEMMASK }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDF, .oplen = 1,
	} } },
	{ "fchs", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xE0D9, .oplen = 2,
	} } },
	{ "fclex", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0x9B, .preflen = 1, .opcode = 0xE2DB, .oplen = 2,
	} } },
	{ "fnclex", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xE2DB, .oplen = 2,
	} } },
	{ "fcmovb", 1, (struct x64LookupActualIns[]) { {
		.args = { ST_0, ST }, .arglen = 2, .reg_oper = 2,
		.opcode = 0xC0DA, .oplen = 2,
	} } },
	{ "fcmove", 1, (struct x64LookupActualIns[]) { {
		.args = { ST_0, ST }, .arglen = 2, .reg_oper = 2,
		.opcode = 0xC8DA, .oplen = 2,
	} } },
	{ "fcmovbe", 1, (struct x64LookupActualIns[]) { {
		.args = { ST_0, ST }, .arglen = 2, .reg_oper = 2,
		.opcode = 0xD0DA, .oplen = 2,
	} } },
	{ "fcmovu", 1, (struct x64LookupActualIns[]) { {
		.args = { ST_0, ST }, .arglen = 2, .reg_oper = 2,
		.opcode = 0xD8DA, .oplen = 2,
	} } },
	{ "fcmovnb", 1, (struct x64LookupActualIns[]) { {
		.args = { ST_0, ST }, .arglen = 2, .reg_oper = 2,
		.opcode = 0xC0DB, .oplen = 2,
	} } },
	{ "fcmovne", 1, (struct x64LookupActualIns[]) { {
		.args = { ST_0, ST }, .arglen = 2, .reg_oper = 2,
		.opcode = 0xC8DB, .oplen = 2,
	} } },
	{ "fcmovnbe", 1, (struct x64LookupActualIns[]) { {
		.args = { ST_0, ST }, .arglen = 2, .reg_oper = 2,
		.opcode = 0xD0DB, .oplen = 2,
	} } },
	{ "fcmovnu", 1, (struct x64LookupActualIns[]) { {
		.args = { ST_0, ST }, .arglen = 2, .reg_oper = 2,
		.opcode = 0xD8DB, .oplen = 2,
	} } },
	{ "fcom", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x10,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xD8, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDC, .oplen = 1,
	}, {
		.args = { ST }, .arglen = 1, .reg_oper = 1,
		.opcode = 0xD0D8, .oplen = 2,
	}, {
		.opcode = 0xD1D8, .oplen = 2,
	} } },
	{ "fcomp", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x18,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xD8, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDC, .oplen = 1,
	}, {
		.args = { ST }, .arglen = 1, .reg_oper = 1,
		.opcode = 0xD8D8, .oplen = 2,
	}, {
		.opcode = 0xD9D8, .oplen = 2,
	} } },
	{ "fcompp", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xD9DE, .oplen = 2,
	} } },
	{ "fcomi", 1, (struct x64LookupActualIns[]) { {
		.args = { ST, ST }, .arglen = 2, .reg_oper = 2,
		.opcode = 0xF0DB, .oplen = 2,
	} } },
	{ "fcomip", 1, (struct x64LookupActualIns[]) { {
		.args = { ST, ST }, .arglen = 2, .reg_oper = 2,
		.opcode = 0xF0DF, .oplen = 2,
	} } },
	{ "fucomi", 1, (struct x64LookupActualIns[]) { {
		.args = { ST, ST }, .arglen = 2, .reg_oper = 2,
		.opcode = 0xE8DB, .oplen = 2,
	} } },
	{ "fucomip", 1, (struct x64LookupActualIns[]) { {
		.args = { ST, ST }, .arglen = 2, .reg_oper = 2,
		.opcode = 0xE8DF, .oplen = 2,
	} } },
	{ "fcos", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xFFD9, .oplen = 2,
	} } },
	{ "fdecstp", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF6D9, .oplen = 2,
	} } },
	{ "fdiv", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x30,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xD8, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDC, .oplen = 1,
	}, {
		.args = { ST_0, ST }, .arglen = 2, .reg_oper = 2,
		.opcode = 0xF0D8, .oplen = 2,
	}, {
		.args = { ST, ST_0 }, .arglen = 2, .reg_oper = 1,
		.opcode = 0xF0DC, .oplen = 2,
	} } },
	{ "fdivp", 2, (struct x64LookupActualIns[]) { {
		.args = { ST, ST_0 }, .arglen = 2, .reg_oper = 1,
		.opcode = 0xF0DE, .oplen = 2,
	}, {
		.opcode = 0xF1DE, .oplen = 2,
	} } },
	{ "fidiv", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x30,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDA, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { M16 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDE, .oplen = 1,
	} } },
	{ "fdivr", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x38,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xD8, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDC, .oplen = 1,
	}, {
		.args = { ST_0, ST }, .arglen = 2, .reg_oper = 2,
		.opcode = 0xF8D8, .oplen = 2,
	}, {
		.args = { ST, ST_0 }, .arglen = 2, .reg_oper = 1,
		.opcode = 0xF8DC, .oplen = 2,
	} } },
	{ "fdivrp", 2, (struct x64LookupActualIns[]) { {
		.args = { ST, ST_0 }, .arglen = 2, .reg_oper = 1,
		.opcode = 0xF8DE, .oplen = 2,
	}, {
		.opcode = 0xF9DE, .oplen = 2,
	} } },
	{ "fidivr", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x38,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDA, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { M16 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDE, .oplen = 1,
	} } },
	{ "ffree", 1, (struct x64LookupActualIns[]) { {
		.args = { ST }, .arglen = 1, .reg_oper = 1,
		.opcode = 0xC0DD, .oplen = 2,
	} } },
	{ "ficom", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x10,
		.args = { M16 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDE, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDA, .oplen = 1,
	} } },
	{ "ficomp", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x18,
		.args = { M16 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDE, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDA, .oplen = 1,
	} } },
	{ "fild", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { M16 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDF, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDB, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDF, .oplen = 1,
	} } },
	{ "fincstp", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF7D9, .oplen = 2,
	} } },
	{ "finit", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0x9B, .preflen = 1, .opcode = 0xE3DB, .oplen = 2,
	} } },
	{ "fninit", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xE3DB, .oplen = 2,
	} } },
	{ "fist", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x10,
		.args = { M16 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDF, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDB, .oplen = 1,
	} } },
	{ "fistp", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x18,
		.args = { M16 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDF, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDB, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDF, .oplen = 1,
	} } },
	{ "fisttp", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x8,
		.args = { M16 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDF, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDB, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDD, .oplen = 1,
	} } },
	{ "fld", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xD9, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDD, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { X64_ALLMEMMASK }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDB, .oplen = 1,
	}, {
		.args = { ST }, .arglen = 1, .reg_oper = 1,
		.opcode = 0xC0D9, .oplen = 2,
	} } },
	{ "fld1", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xE8D9, .oplen = 2,
	} } },
	{ "fldl2t", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xE9D9, .oplen = 2,
	} } },
	{ "fldl2e", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xEAD9, .oplen = 2,
	} } },
	{ "fldpi", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xEBD9, .oplen = 2,
	} } },
	{ "fldlg2", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xECD9, .oplen = 2,
	} } },
	{ "fldln2", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xEDD9, .oplen = 2,
	} } },
	{ "fldz", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xEED9, .oplen = 2,
	} } },
	{ "fldcw", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x28,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xD9, .oplen = 1,
	} } },
	{ "fldenv", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x20,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xD9, .oplen = 1,
	} } },
	{ "fmul", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x8,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xD8, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDC, .oplen = 1,
	}, {
		.args = { ST_0, ST }, .arglen = 2, .reg_oper = 2,
		.opcode = 0xC8D8, .oplen = 2,
	}, {
		.args = { ST, ST_0 }, .arglen = 2, .reg_oper = 1,
		.opcode = 0xC8DC, .oplen = 2,
	} } },
	{ "fmulp", 2, (struct x64LookupActualIns[]) { {
		.args = { ST, ST_0 }, .arglen = 2, .reg_oper = 1,
		.opcode = 0xC8DE, .oplen = 2,
	}, {
		.opcode = 0xC9DE, .oplen = 2,
	} } },
	{ "fimul", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x8,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDA, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { M16 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDE, .oplen = 1,
	} } },
	{ "fnop", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xD0D9, .oplen = 2,
	} } },
	{ "fpatan", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF3D9, .oplen = 2,
	} } },
	{ "fprem", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF8D9, .oplen = 2,
	} } },
	{ "fprem1", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF5D9, .oplen = 2,
	} } },
	{ "fptan", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF2D9, .oplen = 2,
	} } },
	{ "frndint", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xFCD9, .oplen = 2,
	} } },
	{ "frstor", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x20,
		.args = { X64_ALLMEMMASK }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDD, .oplen = 1,
	} } },
	{ "fsave", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x30,
		.args = { X64_ALLMEMMASK }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0x9B, .preflen = 1, .opcode = 0xDD, .oplen = 1,
	} } },
	{ "fnsave", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x30,
		.args = { X64_ALLMEMMASK }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDD, .oplen = 1,
	} } },
	{ "fscale", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xFDD9, .oplen = 2,
	} } },
	{ "fsin", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xFED9, .oplen = 2,
	} } },
	{ "fsincos", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xFBD9, .oplen = 2,
	} } },
	{ "fsqrt", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xFAD9, .oplen = 2,
	} } },
	{ "fst", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x10,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xD9, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDD, .oplen = 1,
	}, {
		.args = { ST }, .arglen = 1, .reg_oper = 1,
		.opcode = 0xD0DD, .oplen = 2,
	} } },
	{ "fstp", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x18,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xD9, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDD, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { X64_ALLMEMMASK }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDB, .oplen = 1,
	}, {
		.args = { ST }, .arglen = 1, .reg_oper = 1,
		.opcode = 0xD8DD, .oplen = 2,
	} } },
	{ "fstcw", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x38,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0x9B, .preflen = 1, .opcode = 0xD9, .oplen = 1,
	} } },
	{ "fnstcw", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x38,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xD9, .oplen = 1,
	} } },
	{ "fstenv", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x30,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0x9B, .preflen = 1, .opcode = 0xD9, .oplen = 1,
	} } },
	{ "fnstenv", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x30,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xD9, .oplen = 1,
	} } },
	{ "fstsw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x38,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0x9B, .preflen = 1, .opcode = 0xDD, .oplen = 1,
	}, {
		.args = { AX }, .arglen = 1,
		.prefixes = 0x9B, .preflen = 1, .opcode = 0xE0DF, .oplen = 2,
	} } },
	{ "fnstsw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x38,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDD, .oplen = 1,
	}, {
		.args = { AX }, .arglen = 1,
		.opcode = 0xE0DF, .oplen = 2,
	} } },
	{ "fsub", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x20,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xD8, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDC, .oplen = 1,
	}, {
		.args = { ST_0, ST }, .arglen = 2, .reg_oper = 2,
		.opcode = 0xE0D8, .oplen = 2,
	}, {
		.args = { ST, ST_0 }, .arglen = 2, .reg_oper = 1,
		.opcode = 0xE0DC, .oplen = 2,
	} } },
	{ "fsubp", 2, (struct x64LookupActualIns[]) { {
		.args = { ST, ST_0 }, .arglen = 2, .reg_oper = 1,
		.opcode = 0xE0DE, .oplen = 2,
	}, {
		.opcode = 0xE1DE, .oplen = 2,
	} } },
	{ "fisub", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x20,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDA, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { M16 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDE, .oplen = 1,
	} } },
	{ "fsubr", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x28,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xD8, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDC, .oplen = 1,
	}, {
		.args = { ST_0, ST }, .arglen = 2, .reg_oper = 2,
		.opcode = 0xE8D8, .oplen = 2,
	}, {
		.args = { ST, ST_0 }, .arglen = 2, .reg_oper = 1,
		.opcode = 0xE8DC, .oplen = 2,
	} } },
	{ "fsubrp", 2, (struct x64LookupActualIns[]) { {
		.args = { ST, ST_0 }, .arglen = 2, .reg_oper = 1,
		.opcode = 0xE8DE, .oplen = 2,
	}, {
		.opcode = 0xE9DE, .oplen = 2,
	} } },
	{ "fisubr", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x28,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xDA, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { M16 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDE, .oplen = 1,
	} } },
	{ "ftst", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xE4D9, .oplen = 2,
	} } },
	{ "fucom", 2, (struct x64LookupActualIns[]) { {
		.args = { ST }, .arglen = 1, .reg_oper = 1,
		.opcode = 0xE0DD, .oplen = 2,
	}, {
		.opcode = 0xE1DD, .oplen = 2,
	} } },
	{ "fucomp", 2, (struct x64LookupActualIns[]) { {
		.args = { ST }, .arglen = 1, .reg_oper = 1,
		.opcode = 0xE8DD, .oplen = 2,
	}, {
		.opcode = 0xE9DD, .oplen = 2,
	} } },
	{ "fucompp", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xE9DA, .oplen = 2,
	} } },
	{ "fxam", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xE5D9, .oplen = 2,
	} } },
	{ "fxch", 2, (struct x64LookupActualIns[]) { {
		.args = { ST }, .arglen = 1, .reg_oper = 1,
		.opcode = 0xC8D9, .oplen = 2,
	}, {
		.opcode = 0xC9D9, .oplen = 2,
	} } },
	{ "fxrstor", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x8,
		.args = { M512 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xAE0F, .oplen = 2,
	} } },
	{ "fxrstor64", 1, (struct x64LookupActualIns[]) { {
		.rex = 0x48, .modrmreq = true, .modrm = 0x8,
		.args = { M512 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xAE0F, .oplen = 2,
	} } },
	{ "fxsave", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { M512 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xAE0F, .oplen = 2,
	} } },
	{ "fxsave64", 1, (struct x64LookupActualIns[]) { {
		.rex = 0x48, .modrmreq = true, .modrm = 0x0,
		.args = { M512 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xAE0F, .oplen = 2,
	} } },
	{ "fxtract", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF4D9, .oplen = 2,
	} } },
	{ "fyl2x", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF1D9, .oplen = 2,
	} } },
	{ "fyl2xp1", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF9D9, .oplen = 2,
	} } },
	{ "haddpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x7C0F, .oplen = 2,
	} } },
	{ "vhaddpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x7C, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x7C, .oplen = 1,
	} } },
	{ "haddps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x7C0F, .oplen = 2,
	} } },
	{ "vhaddps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x7C, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7f, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x7C, .oplen = 1,
	} } },
	{ "hlt", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF4, .oplen = 1,
	} } },
	{ "hsubpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x7D0F, .oplen = 2,
	} } },
	{ "vhsubpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x7D, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x7D, .oplen = 1,
	} } },
	{ "hsubps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x7D0F, .oplen = 2,
	} } },
	{ "vhsubps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x7D, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7f, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x7D, .oplen = 1,
	} } },
	{ "idiv", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x38,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF6, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { R16 | M16 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { R32 | M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x38,
		.args = { R64 | M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	} } },
	{ "imul", 13, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x28,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF6, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { R16 | M16 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { R32 | M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x28,
		.args = { R64 | M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xAF0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xAF0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xAF0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x6B, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x6B, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x6B, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16, IMM16 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x69, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32, IMM32 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x69, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64, IMM32 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x69, .oplen = 1,
	} } },
	{ "in", 6, (struct x64LookupActualIns[]) { {
		.args = { AL, IMM8 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0xE4, .oplen = 1,
	}, {
		.args = { AX, IMM8 }, .arglen = 2, .imm_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xE5, .oplen = 1,
	}, {
		.args = { EAX, IMM8 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0xE5, .oplen = 1,
	}, {
		.args = { AL, DX }, .arglen = 2,
		.opcode = 0xEC, .oplen = 1,
	}, {
		.args = { AX, DX }, .arglen = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xED, .oplen = 1,
	}, {
		.args = { EAX, DX }, .arglen = 2,
		.opcode = 0xED, .oplen = 1,
	} } },
	{ "inc", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xFE, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R16 | M16 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xFF, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R32 | M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xFF, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x0,
		.args = { R64 | M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xFF, .oplen = 1,
	} } },
	{ "ins", 3, (struct x64LookupActualIns[]) { {
		.args = { M8, DX }, .arglen = 2,
		.opcode = 0x6C, .oplen = 1,
	}, {
		.args = { M16, DX }, .arglen = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x6D, .oplen = 1,
	}, {
		.args = { M32, DX }, .arglen = 2,
		.opcode = 0x6D, .oplen = 1,
	} } },
	{ "insb", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x6C, .oplen = 1,
	} } },
	{ "insw", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0x66, .preflen = 1, .opcode = 0x6D, .oplen = 1,
	} } },
	{ "insd", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x6D, .oplen = 1,
	} } },
	{ "insertps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x213A0F, .oplen = 3,
	} } },
	{ "vinsertps", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x21, .oplen = 1,
	} } },
	{ "int3", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xCC, .oplen = 1,
	} } },
	{ "int1", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF1, .oplen = 1,
	} } },
	{ "int", 1, (struct x64LookupActualIns[]) { {
		.args = { IMM8 }, .arglen = 1, .imm_oper = 1,
		.opcode = 0xCD, .oplen = 1,
	} } },
	{ "invd", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x080F, .oplen = 2,
	} } },
	{ "invlpg", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x38,
		.args = { X64_ALLMEMMASK }, .arglen = 1,
		.opcode = 0x010F, .oplen = 2,
	} } },
	{ "invpcid", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R64, M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x82380F, .oplen = 3,
	} } },
	{ "iret", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0x66, .preflen = 1, .opcode = 0xCF, .oplen = 1,
	} } },
	{ "iretd", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xCF, .oplen = 1,
	} } },
	{ "iretq", 1, (struct x64LookupActualIns[]) { {
		.rex = 0x48,
		.opcode = 0xCF, .oplen = 1,
	} } },
	{ "ja", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x77, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x870F, .oplen = 2,
	} } },
	{ "jae", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x73, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x830F, .oplen = 2,
	} } },
	{ "jb", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x72, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x820F, .oplen = 2,
	} } },
	{ "jbe", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x76, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x860F, .oplen = 2,
	} } },
	{ "jc", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x72, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x820F, .oplen = 2,
	} } },
	{ "jecxz", 1, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0xE3, .oplen = 1,
	} } },
	{ "jrcxz", 1, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0xE3, .oplen = 1,
	} } },
	{ "je", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x74, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x840F, .oplen = 2,
	} } },
	{ "jg", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x7F, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x8F0F, .oplen = 2,
	} } },
	{ "jge", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x7D, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x8D0F, .oplen = 2,
	} } },
	{ "jl", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x7C, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x8C0F, .oplen = 2,
	} } },
	{ "jle", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x7E, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x8E0F, .oplen = 2,
	} } },
	{ "jna", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x76, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x860F, .oplen = 2,
	} } },
	{ "jnae", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x72, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x820F, .oplen = 2,
	} } },
	{ "jnb", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x73, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x830F, .oplen = 2,
	} } },
	{ "jnbe", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x77, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x870F, .oplen = 2,
	} } },
	{ "jnc", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x73, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x830F, .oplen = 2,
	} } },
	{ "jne", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x75, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x850F, .oplen = 2,
	} } },
	{ "jng", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x7E, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x8E0F, .oplen = 2,
	} } },
	{ "jnge", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x7C, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x8C0F, .oplen = 2,
	} } },
	{ "jnl", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x7D, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x8D0F, .oplen = 2,
	} } },
	{ "jnle", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x7F, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x8F0F, .oplen = 2,
	} } },
	{ "jno", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x71, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x810F, .oplen = 2,
	} } },
	{ "jnp", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x7B, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x8B0F, .oplen = 2,
	} } },
	{ "jns", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x79, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x890F, .oplen = 2,
	} } },
	{ "jnz", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x75, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x850F, .oplen = 2,
	} } },
	{ "jo", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x70, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x800F, .oplen = 2,
	} } },
	{ "jp", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x7A, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x8A0F, .oplen = 2,
	} } },
	{ "jpe", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x7A, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x8A0F, .oplen = 2,
	} } },
	{ "jpo", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x7B, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x8B0F, .oplen = 2,
	} } },
	{ "js", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x78, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x880F, .oplen = 2,
	} } },
	{ "jz", 2, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x74, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0x840F, .oplen = 2,
	} } },
	{ "jmp", 6, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0xEB, .oplen = 1,
	}, {
		.args = { REL32 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0xE9, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R64 | M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xFF, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { FARPTR1616 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0xFF, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { FARPTR1632 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0xFF, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x28,
		.args = { FARPTR1664 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0xFF, .oplen = 1,
	} } },
	{ "lahf", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x9F, .oplen = 1,
	} } },
	{ "lar", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x020F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x020F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R32 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x020F, .oplen = 2,
	} } },
	{ "lddqu", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0xF00F, .oplen = 2,
	} } },
	{ "vlddqu", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xF0, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7f, .modrmreq = true, .modrmreg = true,
		.args = { YMM, M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xF0, .oplen = 1,
	} } },
	{ "ldmxcsr", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x10,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xAE0F, .oplen = 2,
	} } },
	{ "vldmxcsr", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrm = 0x10,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xAE, .oplen = 1,
	} } },
	{ "lss", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, FARPTR1616 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xB20F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, FARPTR1632 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xB20F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, FARPTR1664 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xB20F, .oplen = 2,
	} } },
	{ "lfs", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, FARPTR1616 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xB40F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, FARPTR1632 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xB40F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, FARPTR1664 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xB40F, .oplen = 2,
	} } },
	{ "lgs", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, FARPTR1616 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xB50F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, FARPTR1632 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xB50F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, FARPTR1664 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xB50F, .oplen = 2,
	} } },
	{ "lea", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, X64_ALLMEMMASK }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x8D, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, X64_ALLMEMMASK }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x8D, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, X64_ALLMEMMASK }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x8D, .oplen = 1,
	} } },
	{ "leave", 2, (struct x64LookupActualIns[]) { {
		.args = { PREF66 }, .arglen = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xC9, .oplen = 1,
	}, {
		.opcode = 0xC9, .oplen = 1,
	} } },
	{ "lfence", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xE8AE0F, .oplen = 3,
	} } },
	{ "lgdt", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x10,
		.args = { FARPTR1664 }, .arglen = 1,
		.opcode = 0x010F, .oplen = 2,
	} } },
	{ "lidt", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x18,
		.args = { FARPTR1664 }, .arglen = 1,
		.opcode = 0x010F, .oplen = 2,
	} } },
	{ "lldt", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x10,
		.args = { R16 | M16 }, .arglen = 1,
		.opcode = 0x000F, .oplen = 2,
	} } },
	{ "lmsw", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x30,
		.args = { R16 | M16 }, .arglen = 1,
		.opcode = 0x010F, .oplen = 2,
	} } },
	{ "lock", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF0, .oplen = 1,
	} } },
	{ "lods", 4, (struct x64LookupActualIns[]) { {
		.args = { M8 }, .arglen = 1,
		.opcode = 0xAC, .oplen = 1,
	}, {
		.args = { M16 }, .arglen = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xAD, .oplen = 1,
	}, {
		.args = { M32 }, .arglen = 1,
		.opcode = 0xAD, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { M64 }, .arglen = 1,
		.opcode = 0xAD, .oplen = 1,
	} } },
	{ "lodsb", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xAC, .oplen = 1,
	} } },
	{ "lodsw", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0x66, .preflen = 1, .opcode = 0xAD, .oplen = 1,
	} } },
	{ "lodsd", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xAD, .oplen = 1,
	} } },
	{ "lodsq", 1, (struct x64LookupActualIns[]) { {
		.rex = 0x48,
		.opcode = 0xAD, .oplen = 1,
	} } },
	{ "loop", 1, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0xE2, .oplen = 1,
	} } },
	{ "loope", 1, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0xE0, .oplen = 1,
	} } },
	{ "loopne", 1, (struct x64LookupActualIns[]) { {
		.args = { REL8 }, .arglen = 1, .rel_oper = 1,
		.opcode = 0xE0, .oplen = 1,
	} } },
	{ "lsl", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x030F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x030F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R32 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x030F, .oplen = 2,
	} } },
	{ "ltr", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x18,
		.args = { R16 | M16 }, .arglen = 1,
		.opcode = 0x000F, .oplen = 2,
	} } },
	{ "lzcnt", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF366, .preflen = 2, .opcode = 0xBD0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xBD0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xBD0F, .oplen = 2,
	} } },
	{ "maskmovdqu", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xF70F, .oplen = 2,
	} } },
	{ "vmaskmovdqu", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	} } },
	{ "maskmovq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xF70F, .oplen = 2,
	} } },
	{ "maxpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x5F0F, .oplen = 2,
	} } },
	{ "vmaxpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5F, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5F, .oplen = 1,
	} } },
	{ "maxps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x5F0F, .oplen = 2,
	} } },
	{ "vmaxps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5F, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5F, .oplen = 1,
	} } },
	{ "maxsd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x5F0F, .oplen = 2,
	} } },
	{ "vmaxsd", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5F, .oplen = 1,
	} } },
	{ "maxss", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x5F0F, .oplen = 2,
	} } },
	{ "vmaxss", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5F, .oplen = 1,
	} } },
	{ "mfence", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF0AE0F, .oplen = 3,
	} } },
	{ "minpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x5D0F, .oplen = 2,
	} } },
	{ "vminpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5D, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5D, .oplen = 1,
	} } },
	{ "minps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x5D0F, .oplen = 2,
	} } },
	{ "vminps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5D, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5D, .oplen = 1,
	} } },
	{ "minsd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x5D0F, .oplen = 2,
	} } },
	{ "vminsd", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5D, .oplen = 1,
	} } },
	{ "minss", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x5D0F, .oplen = 2,
	} } },
	{ "vminss", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5D, .oplen = 1,
	} } },
	{ "monitor", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xC8010F, .oplen = 3,
	} } },
	{ "mov", 39, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, R8 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x88, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, RH }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x88, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16 | M16, R16 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x89, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x89, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x89, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x8A, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { RH, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x8A, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x8B, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x8B, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x8B, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16 | M16, SREG }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x8C, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, SREG }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x8C, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { SREG, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x8E, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { SREG, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x8E, .oplen = 1,
	}, {
		.args = { AL, MOFFS8 }, .arglen = 2, .rel_oper = 2,
		.opcode = 0xA0, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { AL, MOFFS8, PREFREX_W }, .arglen = 3, .rel_oper = 2,
		.opcode = 0xA0, .oplen = 1,
	}, {
		.args = { AX, MOFFS16 }, .arglen = 2, .rel_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xA1, .oplen = 1,
	}, {
		.args = { EAX, MOFFS32 }, .arglen = 2, .rel_oper = 2,
		.opcode = 0xA1, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { RAX, MOFFS64 }, .arglen = 2, .rel_oper = 2,
		.opcode = 0xA1, .oplen = 1,
	}, {
		.args = { MOFFS8, AL }, .arglen = 2, .rel_oper = 2,
		.opcode = 0xA2, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { MOFFS8, AL, PREFREX_W }, .arglen = 3, .rel_oper = 2,
		.opcode = 0xA2, .oplen = 1,
	}, {
		.args = { MOFFS16, AX }, .arglen = 2, .rel_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xA3, .oplen = 1,
	}, {
		.args = { MOFFS32, EAX }, .arglen = 2, .rel_oper = 2,
		.opcode = 0xA3, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { MOFFS64, RAX }, .arglen = 2, .rel_oper = 2,
		.opcode = 0xA3, .oplen = 1,
	}, {
		.args = { R8, IMM8 }, .arglen = 2, .imm_oper = 2, .reg_oper = 1,
		.opcode = 0xB0, .oplen = 1,
		.preffered = true,
	}, {
		.args = { RH, IMM8 }, .arglen = 2, .imm_oper = 2, .reg_oper = 1,
		.opcode = 0xB0, .oplen = 1,
		.preffered = true,
	}, {
		.args = { R16, IMM16 }, .arglen = 2, .imm_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xB8, .oplen = 1,
		.preffered = true,
	}, {
		.args = { R32, IMM32 }, .arglen = 2, .imm_oper = 2, .reg_oper = 1,
		.opcode = 0xB8, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { R64, IMM64 }, .arglen = 2, .imm_oper = 2, .reg_oper = 1,
		.opcode = 0xB8, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC6, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R16 | M16, IMM16 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xC7, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R32 | M32, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC7, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x0,
		.args = { R64 | M64, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC7, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R64, CR0_7 }, .arglen = 2,
		.opcode = 0x200F, .oplen = 2,
	}, {
		.rex = 0x44,
		.args = { R64, CR8 }, .arglen = 2,
		.opcode = 0x200F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { CR0_7, R64 }, .arglen = 2,
		.opcode = 0x220F, .oplen = 2,
	}, {
		.rex = 0x44,
		.args = { CR8, R64 }, .arglen = 2,
		.opcode = 0x220F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R64, DREG }, .arglen = 2,
		.opcode = 0x210F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { DREG, R64 }, .arglen = 2,
		.opcode = 0x230F, .oplen = 2,
	} } },
	{ "movapd", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x280F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM | M128, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x290F, .oplen = 2,
		.preffered = true,
	} } },
	{ "vmovapd", 4, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x28, .oplen = 1,
		.preffered = true,
	}, {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM | M128, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x29, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x28, .oplen = 1,
		.preffered = true,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM | M256, YMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x29, .oplen = 1,
	} } },
	{ "movaps", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x280F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM | M128, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x290F, .oplen = 2,
		.preffered = true,
	} } },
	{ "vmovaps", 4, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x28, .oplen = 1,
		.preffered = true,
	}, {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM | M128, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x29, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x28, .oplen = 1,
		.preffered = true,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM | M256, YMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x29, .oplen = 1,
	} } },
	{ "movbe", 6, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xF0380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xF0380F, .oplen = 3,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xF0380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { M16, R16 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xF1380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xF1380F, .oplen = 3,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xF1380F, .oplen = 3,
	} } },
	{ "movd", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x6E0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, MM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x7E0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x6E0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x7E0F, .oplen = 2,
	} } },
	{ "movq", 8, (struct x64LookupActualIns[]) { {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { MM, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x6E0F, .oplen = 2,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, MM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x7E0F, .oplen = 2,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { XMM, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x6E0F, .oplen = 2,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x7E0F, .oplen = 2,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x6F0F, .oplen = 2,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { MM | M64, MM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x7F0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x7E0F, .oplen = 2,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM | M64, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xD60F, .oplen = 2,
	} } },
	{ "vmovd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x6E, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x7E, .oplen = 1,
	} } },
	{ "vmovq", 5, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 1, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x6E, .oplen = 1,
		.preffered = true,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x7E, .oplen = 1,
		.preffered = true,
	}, {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x7E, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x7E, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM | M64, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xD6, .oplen = 1,
		.preffered = true,
	} } },
	{ "movddup", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x120F, .oplen = 2,
	} } },
	{ "vmovddup", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x12, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7f, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x12, .oplen = 1,
	} } },
	{ "movdqa", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x6F0F, .oplen = 2,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM | M128, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x7F0F, .oplen = 2,
	} } },
	{ "vmovdqa", 4, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x6F, .oplen = 1,
		.preffered = true,
	}, {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM | M128, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x7F, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x6F, .oplen = 1,
		.preffered = true,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM | M256, YMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x7F, .oplen = 1,
	} } },
	{ "movdqu", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x6F0F, .oplen = 2,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM | M128, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x7F0F, .oplen = 2,
	} } },
	{ "vmovdqu", 4, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x6F, .oplen = 1,
		.preffered = true,
	}, {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM | M128, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x7F, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7e, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x6F, .oplen = 1,
		.preffered = true,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7e, .modrmreq = true, .modrmreg = true,
		.args = { YMM | M256, YMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x7F, .oplen = 1,
	} } },
	{ "movdq2q", 1, (struct x64LookupActualIns[]) { {
		.args = { MM, XMM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0xD60F, .oplen = 2,
	} } },
	{ "movhlps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x120F, .oplen = 2,
	} } },
	{ "vmovhlps", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x12, .oplen = 1,
	} } },
	{ "movhpd", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x160F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { M64, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x170F, .oplen = 2,
	} } },
	{ "vmovhpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x16, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { M64, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x17, .oplen = 1,
	} } },
	{ "movhps", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x160F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { M64, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x170F, .oplen = 2,
	} } },
	{ "vmovhps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x16, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { M64, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x17, .oplen = 1,
	} } },
	{ "movlhps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x160F, .oplen = 2,
	} } },
	{ "vmovlhps", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x16, .oplen = 1,
	} } },
	{ "movlpd", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x120F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { M64, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x130F, .oplen = 2,
	} } },
	{ "vmovlpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x12, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { M64, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x13, .oplen = 1,
	} } },
	{ "movlps", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x120F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { M64, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x130F, .oplen = 2,
	} } },
	{ "vmovlps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x12, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { M64, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x13, .oplen = 1,
	} } },
	{ "movmskpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R64 | R32, XMM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x500F, .oplen = 2,
	} } },
	{ "vmovmskpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { R64 | R32, XMM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x50, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { R64 | R32, YMM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x50, .oplen = 1,
	} } },
	{ "movmskps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R64 | R32, XMM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x500F, .oplen = 2,
	} } },
	{ "vmovmskps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { R64 | R32, XMM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x50, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { R64 | R32, YMM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x50, .oplen = 1,
	} } },
	{ "movntdqa", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x2A380F, .oplen = 3,
	} } },
	{ "vmovntdqa", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2A, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2A, .oplen = 1,
	} } },
	{ "movntdq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { M128, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xE70F, .oplen = 2,
	} } },
	{ "vmovntdq", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { M128, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xE7, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { M256, YMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xE7, .oplen = 1,
	} } },
	{ "movnti", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xC30F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xC30F, .oplen = 2,
	} } },
	{ "movntpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { M128, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x2B0F, .oplen = 2,
	} } },
	{ "vmovntpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { M128, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x2B, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { M256, YMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x2B, .oplen = 1,
	} } },
	{ "movntps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { M128, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x2B0F, .oplen = 2,
	} } },
	{ "vmovntps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { M128, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x2B, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { M256, YMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x2B, .oplen = 1,
	} } },
	{ "movntq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { M64, MM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xE70F, .oplen = 2,
	} } },
	{ "movq2dq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, MM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xD60F, .oplen = 2,
	} } },
	{ "movs", 4, (struct x64LookupActualIns[]) { {
		.args = { M8, M8 }, .arglen = 2,
		.opcode = 0xA4, .oplen = 1,
	}, {
		.args = { M16, M16 }, .arglen = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xA5, .oplen = 1,
	}, {
		.args = { M32, M32 }, .arglen = 2,
		.opcode = 0xA5, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { M64, M64 }, .arglen = 2,
		.opcode = 0xA5, .oplen = 1,
	} } },
	{ "movsb", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xA4, .oplen = 1,
	} } },
	{ "movsw", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0x66, .preflen = 1, .opcode = 0xA5, .oplen = 1,
	} } },
	{ "movsd", 3, (struct x64LookupActualIns[]) { {
		.opcode = 0xA5, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x100F, .oplen = 2,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM | M64, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x110F, .oplen = 2,
	} } },
	{ "movsq", 1, (struct x64LookupActualIns[]) { {
		.rex = 0x48,
		.opcode = 0xA5, .oplen = 1,
	} } },
	{ "vmovsd", 4, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x10, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x10, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM }, .arglen = 3, .mem_oper = 1, .reg_oper = 3, .vex_oper = 2,
		.opcode = 0x11, .oplen = 1,
		.preffered = true,
	}, {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { M64, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x11, .oplen = 1,
	} } },
	{ "movshdup", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x160F, .oplen = 2,
	} } },
	{ "vmovshdup", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x16, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7e, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x16, .oplen = 1,
	} } },
	{ "movsldup", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x120F, .oplen = 2,
	} } },
	{ "vmovsldup", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x12, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7e, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x12, .oplen = 1,
	} } },
	{ "movss", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x100F, .oplen = 2,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM | M32, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x110F, .oplen = 2,
	} } },
	{ "vmovss", 4, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x10, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x10, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM }, .arglen = 3, .mem_oper = 1, .reg_oper = 3, .vex_oper = 2,
		.opcode = 0x11, .oplen = 1,
		.preffered = true,
	}, {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { M32, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x11, .oplen = 1,
	} } },
	{ "movsx", 5, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xBE0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xBE0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xBE0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xBF0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xBF0F, .oplen = 2,
	} } },
	{ "movsxd", 1, (struct x64LookupActualIns[]) { {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x63, .oplen = 1,
	} } },
	{ "movupd", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x100F, .oplen = 2,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM | M128, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x110F, .oplen = 2,
	} } },
	{ "vmovupd", 4, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x10, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x10, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM | M128, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x11, .oplen = 1,
		.preffered = true,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM | M256, YMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x11, .oplen = 1,
		.preffered = true,
	} } },
	{ "movups", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x100F, .oplen = 2,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM | M128, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x110F, .oplen = 2,
	} } },
	{ "vmovups", 4, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x10, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x10, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM | M128, XMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x11, .oplen = 1,
		.preffered = true,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM | M256, YMM }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x11, .oplen = 1,
		.preffered = true,
	} } },
	{ "movzx", 5, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xB60F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xB60F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xB60F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xB70F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xB70F, .oplen = 2,
	} } },
	{ "mpsadbw", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x423A0F, .oplen = 3,
	} } },
	{ "vmpsadbw", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x42, .oplen = 1,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x42, .oplen = 1,
	} } },
	{ "mul", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x20,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF6, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R16 | M16 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R32 | M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x20,
		.args = { R64 | M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	} } },
	{ "mulpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x590F, .oplen = 2,
	} } },
	{ "vmulpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x59, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x59, .oplen = 1,
	} } },
	{ "mulps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x590F, .oplen = 2,
	} } },
	{ "vmulps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x59, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x59, .oplen = 1,
	} } },
	{ "mulsd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x590F, .oplen = 2,
	} } },
	{ "vmulsd", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x59, .oplen = 1,
	} } },
	{ "mulss", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x590F, .oplen = 2,
	} } },
	{ "vmulss", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x59, .oplen = 1,
	} } },
	{ "mulx", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { R32, R32, R32 | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF6, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfb, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64, R64 | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF6, .oplen = 1,
	} } },
	{ "mwait", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xC9010F, .oplen = 3,
	} } },
	{ "neg", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x18,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF6, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { R16 | M16 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { R32 | M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x18,
		.args = { R64 | M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	} } },
	{ "nop", 3, (struct x64LookupActualIns[]) { {
		.opcode = 0x90, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R16 | M16 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x1F0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R32 | M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x1F0F, .oplen = 2,
	} } },
	{ "not", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x10,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF6, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { R16 | M16 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { R32 | M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x10,
		.args = { R64 | M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	} } },
	{ "or", 21, (struct x64LookupActualIns[]) { {
		.args = { AL, IMM8 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x0C, .oplen = 1,
	}, {
		.args = { AX, IMM16 }, .arglen = 2, .imm_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x0D, .oplen = 1,
	}, {
		.args = { EAX, IMM32 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x0D, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { RAX, IMM32 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x0D, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { R8 | M8, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x80, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { R16 | M16, IMM16 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x81, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { R32 | M32, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x81, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x8,
		.args = { R64 | M64, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x81, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x8,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, R8 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x08, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, RH }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x08, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16 | M16, R16 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x09, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x09, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x09, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x0A, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { RH, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x0A, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x0B, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x0B, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x0B, .oplen = 1,
	} } },
	{ "orpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x560F, .oplen = 2,
	} } },
	{ "vorpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x56, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x56, .oplen = 1,
	} } },
	{ "orps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x560F, .oplen = 2,
	} } },
	{ "vorps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x56, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x56, .oplen = 1,
	} } },
	{ "out", 6, (struct x64LookupActualIns[]) { {
		.args = { IMM8, AL }, .arglen = 2, .imm_oper = 1,
		.opcode = 0xE6, .oplen = 1,
	}, {
		.args = { IMM8, AX }, .arglen = 2, .imm_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xE7, .oplen = 1,
	}, {
		.args = { IMM8, EAX }, .arglen = 2, .imm_oper = 1,
		.opcode = 0xE7, .oplen = 1,
	}, {
		.args = { DX, AL }, .arglen = 2,
		.opcode = 0xEE, .oplen = 1,
	}, {
		.args = { DX, AX }, .arglen = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xEF, .oplen = 1,
	}, {
		.args = { DX, EAX }, .arglen = 2,
		.opcode = 0xEF, .oplen = 1,
	} } },
	{ "outs", 3, (struct x64LookupActualIns[]) { {
		.args = { DX, M8 }, .arglen = 2,
		.opcode = 0x6E, .oplen = 1,
	}, {
		.args = { DX, M16 }, .arglen = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x6F, .oplen = 1,
	}, {
		.args = { DX, M32 }, .arglen = 2,
		.opcode = 0x6F, .oplen = 1,
	} } },
	{ "outsb", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x6E, .oplen = 1,
	} } },
	{ "outsw", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0x66, .preflen = 1, .opcode = 0x6F, .oplen = 1,
	} } },
	{ "outsd", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x6F, .oplen = 1,
	} } },
	{ "pabsb", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x1C380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x1C380F, .oplen = 3,
	} } },
	{ "pabsw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x1D380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x1D380F, .oplen = 3,
	} } },
	{ "pabsd", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x1E380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x1E380F, .oplen = 3,
	} } },
	{ "vpabsb", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x1C, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x1C, .oplen = 1,
	} } },
	{ "vpabsw", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x1D, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x1D, .oplen = 1,
	} } },
	{ "vpabsd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x1E, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x1E, .oplen = 1,
	} } },
	{ "packsswb", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x630F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x630F, .oplen = 2,
	} } },
	{ "packssdw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x6B0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x6B0F, .oplen = 2,
	} } },
	{ "vpacksswb", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x63, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x63, .oplen = 1,
	} } },
	{ "vpackssdw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x6B, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x6B, .oplen = 1,
	} } },
	{ "packusdw", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x2B380F, .oplen = 3,
	} } },
	{ "vpackusdw", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x2B, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x2B, .oplen = 1,
	} } },
	{ "packuswb", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x670F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x670F, .oplen = 2,
	} } },
	{ "vpackuswb", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x67, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x67, .oplen = 1,
	} } },
	{ "paddb", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xFC0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xFC0F, .oplen = 2,
	} } },
	{ "paddw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xFD0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xFD0F, .oplen = 2,
	} } },
	{ "paddd", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xFE0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xFE0F, .oplen = 2,
	} } },
	{ "vpaddb", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xFC, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xFC, .oplen = 1,
	} } },
	{ "vpaddw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xFD, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xFD, .oplen = 1,
	} } },
	{ "vpaddd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xFE, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xFE, .oplen = 1,
	} } },
	{ "paddq", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xD40F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xD40F, .oplen = 2,
	} } },
	{ "vpaddq", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xD4, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xD4, .oplen = 1,
	} } },
	{ "paddsb", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xEC0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xEC0F, .oplen = 2,
	} } },
	{ "paddsw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xED0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xED0F, .oplen = 2,
	} } },
	{ "vpaddsb", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xEC, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xEC, .oplen = 1,
	} } },
	{ "vpaddsw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xED, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xED, .oplen = 1,
	} } },
	{ "paddusb", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xDC0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDC0F, .oplen = 2,
	} } },
	{ "paddusw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xDD0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDD0F, .oplen = 2,
	} } },
	{ "vpaddusb", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xDC, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xDC, .oplen = 1,
	} } },
	{ "vpaddusw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xDD, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xDD, .oplen = 1,
	} } },
	{ "palignr", 2, (struct x64LookupActualIns[]) { {
		.args = { MM, MM | M64, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x0F3A0F, .oplen = 3,
	}, {
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x0F3A0F, .oplen = 3,
	} } },
	{ "vpalignr", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x0F, .oplen = 1,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x0F, .oplen = 1,
	} } },
	{ "pand", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xDB0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDB0F, .oplen = 2,
	} } },
	{ "vpand", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xDB, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xDB, .oplen = 1,
	} } },
	{ "pandn", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xDF0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDF0F, .oplen = 2,
	} } },
	{ "vpandn", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xDF, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xDF, .oplen = 1,
	} } },
	{ "pause", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x90, .oplen = 1,
	} } },
	{ "pavgb", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xE00F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xE00F, .oplen = 2,
	} } },
	{ "pavgw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xE30F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xE30F, .oplen = 2,
	} } },
	{ "vpavgb", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xE0, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xE0, .oplen = 1,
	} } },
	{ "vpavgw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xE3, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xE3, .oplen = 1,
	} } },
	{ "pblendvb", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, XMM_0 }, .arglen = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x10380F, .oplen = 3,
	} } },
	{ "vpblendvb", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128, XMM }, .arglen = 4, .mem_oper = 3, .reg_oper = 1, .is4_oper = 4, .vex_oper = 2,
		.opcode = 0x4C, .oplen = 1,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256, YMM }, .arglen = 4, .mem_oper = 3, .reg_oper = 1, .is4_oper = 4, .vex_oper = 2,
		.opcode = 0x4C, .oplen = 1,
	} } },
	{ "pblendw", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x0E3A0F, .oplen = 3,
	} } },
	{ "vpblendw", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x0E, .oplen = 1,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x0E, .oplen = 1,
	} } },
	{ "pclmulqdq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x443A0F, .oplen = 3,
	} } },
	{ "vpclmulqdq", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x44, .oplen = 1,
	} } },
	{ "pcmpeqb", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x740F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x740F, .oplen = 2,
	} } },
	{ "pcmpeqw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x750F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x750F, .oplen = 2,
	} } },
	{ "pcmpeqd", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x760F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x760F, .oplen = 2,
	} } },
	{ "vpcmpeqb", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x74, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x74, .oplen = 1,
	} } },
	{ "vpcmpeqw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x75, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x75, .oplen = 1,
	} } },
	{ "vpcmpeqd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x76, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x76, .oplen = 1,
	} } },
	{ "pcmpeqq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x29380F, .oplen = 3,
	} } },
	{ "vpcmpeqq", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x29, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x29, .oplen = 1,
	} } },
	{ "pcmpestri", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x613A0F, .oplen = 3,
	} } },
	{ "vpcmpestri", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x61, .oplen = 1,
	} } },
	{ "pcmpestrm", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x603A0F, .oplen = 3,
	} } },
	{ "vpcmpestrm", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x60, .oplen = 1,
	} } },
	{ "pcmpgtb", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x640F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x640F, .oplen = 2,
	} } },
	{ "pcmpgtw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x650F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x650F, .oplen = 2,
	} } },
	{ "pcmpgtd", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x660F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x660F, .oplen = 2,
	} } },
	{ "vpcmpgtb", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x64, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x64, .oplen = 1,
	} } },
	{ "vpcmpgtw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x65, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x65, .oplen = 1,
	} } },
	{ "vpcmpgtd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x66, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x66, .oplen = 1,
	} } },
	{ "pcmpgtq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x37380F, .oplen = 3,
	} } },
	{ "vpcmpgtq", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x37, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x37, .oplen = 1,
	} } },
	{ "pcmpistri", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x633A0F, .oplen = 3,
	} } },
	{ "vpcmpistri", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x63, .oplen = 1,
	} } },
	{ "pcmpistrm", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x623A0F, .oplen = 3,
	} } },
	{ "vpcmpistrm", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x62, .oplen = 1,
	} } },
	{ "pdep", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { R32, R32, R32 | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF5, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfb, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64, R64 | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF5, .oplen = 1,
	} } },
	{ "pext", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { R32, R32, R32 | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF5, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfa, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64, R64 | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF5, .oplen = 1,
	} } },
	{ "pextrb", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R64 | R32 | M8, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x143A0F, .oplen = 3,
	} } },
	{ "pextrd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x163A0F, .oplen = 3,
	} } },
	{ "pextrq", 1, (struct x64LookupActualIns[]) { {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x163A0F, .oplen = 3,
	} } },
	{ "vpextrb", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { R64 | R32 | M8, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x14, .oplen = 1,
	} } },
	{ "vpextrd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x16, .oplen = 1,
	} } },
	{ "vpextrq", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x16, .oplen = 1,
	} } },
	{ "pextrw", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R64 | R32, MM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xC50F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R64 | R32, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xC50F, .oplen = 2,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R64 | R32 | M16, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x153A0F, .oplen = 3,
	} } },
	{ "vpextrw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { R64 | R32, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xC5, .oplen = 1,
		.preffered = true,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { R64 | R32 | M16, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x15, .oplen = 1,
	} } },
	{ "phaddw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x01380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x01380F, .oplen = 3,
	} } },
	{ "phaddd", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x02380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x02380F, .oplen = 3,
	} } },
	{ "vphaddw", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x01, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x01, .oplen = 1,
	} } },
	{ "vphaddd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x02, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x02, .oplen = 1,
	} } },
	{ "phaddsw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x03380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x03380F, .oplen = 3,
	} } },
	{ "vphaddsw", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x03, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x03, .oplen = 1,
	} } },
	{ "phminposuw", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x41380F, .oplen = 3,
	} } },
	{ "vphminposuw", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x41, .oplen = 1,
	} } },
	{ "phsubw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x05380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x05380F, .oplen = 3,
	} } },
	{ "phsubd", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x06380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x06380F, .oplen = 3,
	} } },
	{ "vphsubw", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x05, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x05, .oplen = 1,
	} } },
	{ "vphsubd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x06, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x06, .oplen = 1,
	} } },
	{ "phsubsw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x07380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x07380F, .oplen = 3,
	} } },
	{ "vphsubsw", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x07, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x07, .oplen = 1,
	} } },
	{ "pinsrb", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, R32 | M8, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x203A0F, .oplen = 3,
	} } },
	{ "pinsrd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, R32 | M32, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x223A0F, .oplen = 3,
	} } },
	{ "vpinsrb", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, R32 | M8, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x20, .oplen = 1,
	} } },
	{ "vpinsrd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, R32 | M32, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x22, .oplen = 1,
	} } },
	{ "vpinsrq", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, R64 | M64, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x22, .oplen = 1,
	} } },
	{ "pinsrw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, R32 | M16, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xC40F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, R32 | M16, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xC40F, .oplen = 2,
	} } },
	{ "vpinsrw", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, R32 | M16, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xC4, .oplen = 1,
	} } },
	{ "pmaddubsw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x04380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x04380F, .oplen = 3,
	} } },
	{ "vpmaddubsw", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x04, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x04, .oplen = 1,
	} } },
	{ "pmaddwd", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xF50F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xF50F, .oplen = 2,
	} } },
	{ "vpmaddwd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF5, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF5, .oplen = 1,
	} } },
	{ "pmaxsb", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x3C380F, .oplen = 3,
	} } },
	{ "vpmaxsb", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x3C, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x3C, .oplen = 1,
	} } },
	{ "pmaxsd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x3D380F, .oplen = 3,
	} } },
	{ "vpmaxsd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x3D, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x3D, .oplen = 1,
	} } },
	{ "pmaxsw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xEE0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xEE0F, .oplen = 2,
	} } },
	{ "vpmaxsw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xEE, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xEE, .oplen = 1,
	} } },
	{ "pmaxub", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xDE0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDE0F, .oplen = 2,
	} } },
	{ "vpmaxub", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xDE, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xDE, .oplen = 1,
	} } },
	{ "pmaxud", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x3F380F, .oplen = 3,
	} } },
	{ "vpmaxud", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x3F, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x3F, .oplen = 1,
	} } },
	{ "pmaxuw", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x3E380F, .oplen = 3,
	} } },
	{ "vpmaxuw", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x3E, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x3E, .oplen = 1,
	} } },
	{ "pminsb", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x38380F, .oplen = 3,
	} } },
	{ "vpminsb", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x38, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x38, .oplen = 1,
	} } },
	{ "pminsd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x39380F, .oplen = 3,
	} } },
	{ "vpminsd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x39, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x39, .oplen = 1,
	} } },
	{ "pminsw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xEA0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xEA0F, .oplen = 2,
	} } },
	{ "vpminsw", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xEA, .oplen = 1,
	} } },
	{ "pminub", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xDA0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xDA0F, .oplen = 2,
	} } },
	{ "vpminub", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xDA, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xDA, .oplen = 1,
	} } },
	{ "pminud", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x3B380F, .oplen = 3,
	} } },
	{ "vpminud", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x3B, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x3B, .oplen = 1,
	} } },
	{ "pminuw", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x3A380F, .oplen = 3,
	} } },
	{ "vpminuw", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x3A, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x3A, .oplen = 1,
	} } },
	{ "pmovmskb", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R64 | R32, MM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xD70F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R64 | R32, XMM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xD70F, .oplen = 2,
	} } },
	{ "vpmovmskb", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { R64 | R32, XMM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xD7, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { R64 | R32, YMM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xD7, .oplen = 1,
	} } },
	{ "pmovsxbw", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x2038, .oplen = 2,
	} } },
	{ "pmovsxbd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x2138, .oplen = 2,
	} } },
	{ "pmovsxbq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x2238, .oplen = 2,
	} } },
	{ "pmovsxwd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x2338, .oplen = 2,
	} } },
	{ "pmovsxwq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x2438, .oplen = 2,
	} } },
	{ "pmovsxdq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x2538, .oplen = 2,
	} } },
	{ "vpmovsxbw", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x20, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x20, .oplen = 1,
	} } },
	{ "vpmovsxbd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x21, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x21, .oplen = 1,
	} } },
	{ "vpmovsxbq", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x22, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x22, .oplen = 1,
	} } },
	{ "vpmovsxwd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x23, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x23, .oplen = 1,
	} } },
	{ "vpmovsxwq", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x24, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x24, .oplen = 1,
	} } },
	{ "vpmovsxdq", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x25, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x25, .oplen = 1,
	} } },
	{ "pmovzxbw", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x3038, .oplen = 2,
	} } },
	{ "pmovzxbd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x3138, .oplen = 2,
	} } },
	{ "pmovzxbq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x3238, .oplen = 2,
	} } },
	{ "pmovzxwd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x3338, .oplen = 2,
	} } },
	{ "pmovzxwq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x3438, .oplen = 2,
	} } },
	{ "pmovzxdq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x3538, .oplen = 2,
	} } },
	{ "vpmovzxbw", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x30, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x30, .oplen = 1,
	} } },
	{ "vpmovzxbd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x31, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x31, .oplen = 1,
	} } },
	{ "vpmovzxbq", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x32, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x32, .oplen = 1,
	} } },
	{ "vpmovzxwd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x33, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x33, .oplen = 1,
	} } },
	{ "vpmovzxwq", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x34, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x34, .oplen = 1,
	} } },
	{ "vpmovzxdq", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x35, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x35, .oplen = 1,
	} } },
	{ "pmuldq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x28380F, .oplen = 3,
	} } },
	{ "vpmuldq", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x28, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x28, .oplen = 1,
	} } },
	{ "pmulhrsw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x0B380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x0B380F, .oplen = 3,
	} } },
	{ "vpmulhrsw", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x0B, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x0B, .oplen = 1,
	} } },
	{ "pmulhuw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xE40F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xE40F, .oplen = 2,
	} } },
	{ "vpmulhuw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xE4, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xE4, .oplen = 1,
	} } },
	{ "pmulhw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xE50F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xE50F, .oplen = 2,
	} } },
	{ "vpmulhw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xE5, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xE5, .oplen = 1,
	} } },
	{ "pmulld", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x40380F, .oplen = 3,
	} } },
	{ "vpmulld", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x40, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x40, .oplen = 1,
	} } },
	{ "pmullw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xD50F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xD50F, .oplen = 2,
	} } },
	{ "vpmullw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xD5, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xD5, .oplen = 1,
	} } },
	{ "pmuludq", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xF40F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xF40F, .oplen = 2,
	} } },
	{ "vpmuludq", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF4, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF4, .oplen = 1,
	} } },
	{ "pop", 8, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R16 | M16 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x8F, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R64 | M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x8F, .oplen = 1,
	}, {
		.args = { R16 }, .arglen = 1, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x58, .oplen = 1,
		.preffered = true,
	}, {
		.args = { R64 }, .arglen = 1, .reg_oper = 1,
		.opcode = 0x58, .oplen = 1,
		.preffered = true,
	}, {
		.args = { FS, PREF66 }, .arglen = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xA10F, .oplen = 2,
	}, {
		.args = { FS }, .arglen = 1,
		.opcode = 0xA10F, .oplen = 2,
	}, {
		.args = { GS, PREF66 }, .arglen = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xA90F, .oplen = 2,
	}, {
		.args = { GS }, .arglen = 1,
		.opcode = 0xA90F, .oplen = 2,
	} } },
	{ "popcnt", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF366, .preflen = 2, .opcode = 0xB80F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xB80F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xB80F, .oplen = 2,
	} } },
	{ "popf", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0x66, .preflen = 1, .opcode = 0x9D, .oplen = 1,
	} } },
	{ "popfq", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x9D, .oplen = 1,
	} } },
	{ "por", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xEB0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xEB0F, .oplen = 2,
	} } },
	{ "vpor", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xEB, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xEB, .oplen = 1,
	} } },
	{ "prefetcht0", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x8,
		.args = { M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x180F, .oplen = 2,
	} } },
	{ "prefetcht1", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x10,
		.args = { M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x180F, .oplen = 2,
	} } },
	{ "prefetcht2", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x18,
		.args = { M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x180F, .oplen = 2,
	} } },
	{ "prefetchnta", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x180F, .oplen = 2,
	} } },
	{ "psadbw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xF60F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xF60F, .oplen = 2,
	} } },
	{ "vpsadbw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF6, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF6, .oplen = 1,
	} } },
	{ "pshufb", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x00380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x00380F, .oplen = 3,
	} } },
	{ "vpshufb", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x00, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x00, .oplen = 1,
	} } },
	{ "pshufd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x700F, .oplen = 2,
	} } },
	{ "vpshufd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x70, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x70, .oplen = 1,
	} } },
	{ "pshufhw", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x700F, .oplen = 2,
	} } },
	{ "vpshufhw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x70, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7e, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x70, .oplen = 1,
	} } },
	{ "pshuflw", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x700F, .oplen = 2,
	} } },
	{ "vpshuflw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x70, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7f, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x70, .oplen = 1,
	} } },
	{ "pshufw", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x700F, .oplen = 2,
	} } },
	{ "psignb", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x08380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x08380F, .oplen = 3,
	} } },
	{ "psignw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x09380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x09380F, .oplen = 3,
	} } },
	{ "psignd", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x0A380F, .oplen = 3,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x0A380F, .oplen = 3,
	} } },
	{ "vpsignb", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x08, .oplen = 1,
	} } },
	{ "vpsignw", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x09, .oplen = 1,
	} } },
	{ "vpsignd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x0A, .oplen = 1,
	} } },
	{ "pslldq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x38,
		.args = { XMM, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x730F, .oplen = 2,
	} } },
	{ "vpslldq", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrm = 0x38,
		.args = { XMM, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x73, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrm = 0x38,
		.args = { YMM, YMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x73, .oplen = 1,
	} } },
	{ "psllw", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xF10F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xF10F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { MM, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x710F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { XMM, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x710F, .oplen = 2,
		.preffered = true,
	} } },
	{ "pslld", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xF20F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xF20F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { MM, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x720F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { XMM, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x720F, .oplen = 2,
	} } },
	{ "psllq", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xF30F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xF30F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { MM, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x730F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { XMM, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x730F, .oplen = 2,
	} } },
	{ "vpsllw", 4, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF1, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrm = 0x30,
		.args = { XMM, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x71, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF1, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrm = 0x30,
		.args = { YMM, YMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x71, .oplen = 1,
	} } },
	{ "vpslld", 4, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF2, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrm = 0x30,
		.args = { XMM, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x72, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF2, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrm = 0x30,
		.args = { YMM, YMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x72, .oplen = 1,
	} } },
	{ "vpsllq", 4, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF3, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrm = 0x30,
		.args = { XMM, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x73, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF3, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrm = 0x30,
		.args = { YMM, YMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x73, .oplen = 1,
	} } },
	{ "psraw", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xE10F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xE10F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { MM, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x710F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { XMM, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x710F, .oplen = 2,
	} } },
	{ "psrad", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xE20F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xE20F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { MM, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x720F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { XMM, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x720F, .oplen = 2,
	} } },
	{ "vpsraw", 4, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xE1, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrm = 0x20,
		.args = { XMM, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x71, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xE1, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrm = 0x20,
		.args = { YMM, YMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x71, .oplen = 1,
	} } },
	{ "vpsrad", 4, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xE2, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrm = 0x20,
		.args = { XMM, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x72, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xE2, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrm = 0x20,
		.args = { YMM, YMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x72, .oplen = 1,
	} } },
	{ "psrldq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x18,
		.args = { XMM, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x730F, .oplen = 2,
	} } },
	{ "vpsrldq", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrm = 0x18,
		.args = { XMM, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x73, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrm = 0x18,
		.args = { YMM, YMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x73, .oplen = 1,
	} } },
	{ "psrlw", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xD10F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xD10F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { MM, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x710F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { XMM, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x710F, .oplen = 2,
	} } },
	{ "psrld", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xD20F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xD20F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { MM, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x720F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { XMM, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x720F, .oplen = 2,
	} } },
	{ "psrlq", 4, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xD30F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xD30F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { MM, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x730F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { XMM, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x730F, .oplen = 2,
	} } },
	{ "vpsrlw", 4, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrm = 0x10,
		.args = { XMM, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x71, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrm = 0x10,
		.args = { YMM, YMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x71, .oplen = 1,
	} } },
	{ "vpsrld", 4, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xD2, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrm = 0x10,
		.args = { XMM, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x72, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xD2, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrm = 0x10,
		.args = { YMM, YMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x72, .oplen = 1,
	} } },
	{ "vpsrlq", 4, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrm = 0x10,
		.args = { XMM, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x73, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrm = 0x10,
		.args = { YMM, YMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .vex_oper = 1,
		.opcode = 0x73, .oplen = 1,
	} } },
	{ "psubb", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xF80F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xF80F, .oplen = 2,
	} } },
	{ "psubw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xF90F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xF90F, .oplen = 2,
	} } },
	{ "psubd", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xFA0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xFA0F, .oplen = 2,
	} } },
	{ "vpsubb", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF8, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF8, .oplen = 1,
	} } },
	{ "vpsubw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF9, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xF9, .oplen = 1,
	} } },
	{ "vpsubd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xFA, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xFA, .oplen = 1,
	} } },
	{ "psubq", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xFB0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xFB0F, .oplen = 2,
	} } },
	{ "vpsubq", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xFB, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xFB, .oplen = 1,
	} } },
	{ "psubsb", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xE80F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xE80F, .oplen = 2,
	} } },
	{ "psubsw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xE90F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xE90F, .oplen = 2,
	} } },
	{ "vpsubsb", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xE8, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xE8, .oplen = 1,
	} } },
	{ "vpsubsw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xE9, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xE9, .oplen = 1,
	} } },
	{ "psubusb", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xD80F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xD80F, .oplen = 2,
	} } },
	{ "psubusw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xD90F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xD90F, .oplen = 2,
	} } },
	{ "vpsubusb", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xD8, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xD8, .oplen = 1,
	} } },
	{ "vpsubusw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xD9, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xD9, .oplen = 1,
	} } },
	{ "ptest", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x17380F, .oplen = 3,
	} } },
	{ "vptest", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x17, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x17, .oplen = 1,
	} } },
	{ "punpckhbw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x680F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x680F, .oplen = 2,
	} } },
	{ "punpckhwd", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x690F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x690F, .oplen = 2,
	} } },
	{ "punpckhdq", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x6A0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x6A0F, .oplen = 2,
	} } },
	{ "punpckhqdq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x6D0F, .oplen = 2,
	} } },
	{ "vpunpckhbw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x68, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x68, .oplen = 1,
	} } },
	{ "vpunpckhwd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x69, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x69, .oplen = 1,
	} } },
	{ "vpunpckhdq", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x6A, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x6A, .oplen = 1,
	} } },
	{ "vpunpckhqdq", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x6D, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x6D, .oplen = 1,
	} } },
	{ "punpcklbw", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x600F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x600F, .oplen = 2,
	} } },
	{ "punpcklwd", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x610F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x610F, .oplen = 2,
	} } },
	{ "punpckldq", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x620F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x620F, .oplen = 2,
	} } },
	{ "punpcklqdq", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x6C0F, .oplen = 2,
	} } },
	{ "vpunpcklbw", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x60, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x60, .oplen = 1,
	} } },
	{ "vpunpcklwd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x61, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x61, .oplen = 1,
	} } },
	{ "vpunpckldq", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x62, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x62, .oplen = 1,
	} } },
	{ "vpunpcklqdq", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x6C, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x6C, .oplen = 1,
	} } },
	{ "push", 6, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x30,
		.args = { R16 | M16 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xFF, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { R64 | M64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xFF, .oplen = 1,
	}, {
		.args = { R16 }, .arglen = 1, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x50, .oplen = 1,
		.preffered = true,
	}, {
		.args = { R64 }, .arglen = 1, .reg_oper = 1,
		.opcode = 0x50, .oplen = 1,
		.preffered = true,
	}, {
		.args = { FS }, .arglen = 1,
		.opcode = 0xA00F, .oplen = 2,
	}, {
		.args = { GS }, .arglen = 1,
		.opcode = 0xA80F, .oplen = 2,
	} } },
	{ "pushq", 3, (struct x64LookupActualIns[]) { {
		.args = { IMM8 }, .arglen = 1, .imm_oper = 1,
		.opcode = 0x6A, .oplen = 1,
	}, {
		.args = { IMM16 }, .arglen = 1, .imm_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x68, .oplen = 1,
	}, {
		.args = { IMM32 }, .arglen = 1, .imm_oper = 1,
		.opcode = 0x68, .oplen = 1,
	} } },
	{ "pushw", 2, (struct x64LookupActualIns[]) { {
		.args = { IMM8 }, .arglen = 1, .imm_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x6A, .oplen = 1,
	}, {
		.args = { IMM16 }, .arglen = 1, .imm_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x68, .oplen = 1,
	} } },
	{ "pushf", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0x66, .preflen = 1, .opcode = 0x9C, .oplen = 1,
	} } },
	{ "pushfq", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x9C, .oplen = 1,
	} } },
	{ "pxor", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { MM, MM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xEF0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xEF0F, .oplen = 2,
	} } },
	{ "vpxor", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xEF, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xEF, .oplen = 1,
	} } },
	{ "rcl", 12, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x10,
		.args = { R8 | M8, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD0, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { R8 | M8, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD2, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { R8 | M8, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC0, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { R16 | M16, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { R16 | M16, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { R32 | M32, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x10,
		.args = { R64 | M64, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { R32 | M32, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x10,
		.args = { R64 | M64, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x10,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x10,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	} } },
	{ "rcr", 12, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x18,
		.args = { R8 | M8, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD0, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { R8 | M8, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD2, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { R8 | M8, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC0, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { R16 | M16, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { R16 | M16, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { R32 | M32, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x18,
		.args = { R64 | M64, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { R32 | M32, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x18,
		.args = { R64 | M64, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x18,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	} } },
	{ "rol", 12, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD0, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD2, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC0, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R16 | M16, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R16 | M16, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R32 | M32, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x0,
		.args = { R64 | M64, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R32 | M32, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x0,
		.args = { R64 | M64, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x0,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	} } },
	{ "ror", 12, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x8,
		.args = { R8 | M8, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD0, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { R8 | M8, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD2, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { R8 | M8, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC0, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { R16 | M16, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { R16 | M16, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { R32 | M32, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x8,
		.args = { R64 | M64, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { R32 | M32, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x8,
		.args = { R64 | M64, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x8,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x8,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	} } },
	{ "rcpps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x530F, .oplen = 2,
	} } },
	{ "vrcpps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x53, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x53, .oplen = 1,
	} } },
	{ "rcpss", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x530F, .oplen = 2,
	} } },
	{ "vrcpss", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x53, .oplen = 1,
	} } },
	{ "rdfsbase", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R32 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAE0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x0,
		.args = { R64 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAE0F, .oplen = 2,
	} } },
	{ "rdgsbase", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x8,
		.args = { R32 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAE0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x8,
		.args = { R64 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAE0F, .oplen = 2,
	} } },
	{ "rdmsr", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x320F, .oplen = 2,
	} } },
	{ "rdpmc", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x330F, .oplen = 2,
	} } },
	{ "rdrand", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x30,
		.args = { R16 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xC70F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { R32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xC70F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x30,
		.args = { R64 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xC70F, .oplen = 2,
	} } },
	{ "rdtsc", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x310F, .oplen = 2,
	} } },
	{ "rdtscp", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF9010F, .oplen = 3,
	} } },
	{ "rep ins", 5, (struct x64LookupActualIns[]) { {
		.args = { M8, DX }, .arglen = 2,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x6C, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { M8, DX }, .arglen = 2,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x6C, .oplen = 1,
	}, {
		.args = { M16, DX }, .arglen = 2,
		.prefixes = 0xF366, .preflen = 2, .opcode = 0x6D, .oplen = 1,
		.preffered = true,
	}, {
		.args = { M32, DX }, .arglen = 2,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x6D, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { M64, DX }, .arglen = 2,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x6D, .oplen = 1,
	} } },
	{ "rep movs", 5, (struct x64LookupActualIns[]) { {
		.args = { M8, M8 }, .arglen = 2,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xA4, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { M8, M8 }, .arglen = 2,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xA4, .oplen = 1,
	}, {
		.args = { M16, M16 }, .arglen = 2,
		.prefixes = 0xF366, .preflen = 2, .opcode = 0xA5, .oplen = 1,
		.preffered = true,
	}, {
		.args = { M32, M32 }, .arglen = 2,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xA5, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { M64, M64 }, .arglen = 2,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xA5, .oplen = 1,
	} } },
	{ "rep outs", 5, (struct x64LookupActualIns[]) { {
		.args = { DX, M8 }, .arglen = 2,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x6E, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { DX, M8 }, .arglen = 2,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x6E, .oplen = 1,
	}, {
		.args = { DX, M16 }, .arglen = 2,
		.prefixes = 0xF366, .preflen = 2, .opcode = 0x6F, .oplen = 1,
		.preffered = true,
	}, {
		.args = { DX, M32 }, .arglen = 2,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x6F, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { DX, M64 }, .arglen = 2,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x6F, .oplen = 1,
	} } },
	{ "rep lods", 5, (struct x64LookupActualIns[]) { {
		.args = { AL }, .arglen = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAC, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { AL }, .arglen = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAC, .oplen = 1,
	}, {
		.args = { AX }, .arglen = 1,
		.prefixes = 0xF366, .preflen = 2, .opcode = 0xAD, .oplen = 1,
		.preffered = true,
	}, {
		.args = { EAX }, .arglen = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAD, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { RAX }, .arglen = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAD, .oplen = 1,
	} } },
	{ "rep stos", 5, (struct x64LookupActualIns[]) { {
		.args = { M8 }, .arglen = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAA, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { M8 }, .arglen = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAA, .oplen = 1,
	}, {
		.args = { M16 }, .arglen = 1,
		.prefixes = 0xF366, .preflen = 2, .opcode = 0xAB, .oplen = 1,
		.preffered = true,
	}, {
		.args = { M32 }, .arglen = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAB, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { M64 }, .arglen = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAB, .oplen = 1,
	} } },
	{ "repe cmps", 5, (struct x64LookupActualIns[]) { {
		.args = { M8, M8 }, .arglen = 2,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xA6, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { M8, M8 }, .arglen = 2,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xA6, .oplen = 1,
	}, {
		.args = { M16, M16 }, .arglen = 2,
		.prefixes = 0xF366, .preflen = 2, .opcode = 0xA7, .oplen = 1,
		.preffered = true,
	}, {
		.args = { M32, M32 }, .arglen = 2,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xA7, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { M64, M64 }, .arglen = 2,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xA7, .oplen = 1,
	} } },
	{ "repe scas", 5, (struct x64LookupActualIns[]) { {
		.args = { M8 }, .arglen = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAE, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { M8 }, .arglen = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAE, .oplen = 1,
	}, {
		.args = { M16 }, .arglen = 1,
		.prefixes = 0xF366, .preflen = 2, .opcode = 0xAF, .oplen = 1,
		.preffered = true,
	}, {
		.args = { M32 }, .arglen = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAF, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { M64 }, .arglen = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAF, .oplen = 1,
	} } },
	{ "repne cmps", 5, (struct x64LookupActualIns[]) { {
		.args = { M8, M8 }, .arglen = 2,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0xA6, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { M8, M8 }, .arglen = 2,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0xA6, .oplen = 1,
	}, {
		.args = { M16, M16 }, .arglen = 2,
		.prefixes = 0xF266, .preflen = 2, .opcode = 0xA7, .oplen = 1,
		.preffered = true,
	}, {
		.args = { M32, M32 }, .arglen = 2,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0xA7, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { M64, M64 }, .arglen = 2,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0xA7, .oplen = 1,
	} } },
	{ "repne scas", 5, (struct x64LookupActualIns[]) { {
		.args = { M8 }, .arglen = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0xAE, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { M8 }, .arglen = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0xAE, .oplen = 1,
	}, {
		.args = { M16 }, .arglen = 1,
		.prefixes = 0xF266, .preflen = 2, .opcode = 0xAF, .oplen = 1,
		.preffered = true,
	}, {
		.args = { M32 }, .arglen = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0xAF, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48,
		.args = { M64 }, .arglen = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0xAF, .oplen = 1,
	} } },
	{ "ret", 4, (struct x64LookupActualIns[]) { {
		.opcode = 0xC3, .oplen = 1,
	}, {
		.args = { FAR }, .arglen = 1,
		.opcode = 0xCB, .oplen = 1,
	}, {
		.args = { IMM16 }, .arglen = 1, .imm_oper = 1,
		.opcode = 0xC2, .oplen = 1,
	}, {
		.args = { IMM16, FAR }, .arglen = 2, .imm_oper = 1,
		.opcode = 0xCA, .oplen = 1,
	} } },
	{ "rorx", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xF0, .oplen = 1,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0xfb, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xF0, .oplen = 1,
	} } },
	{ "roundpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x093A0F, .oplen = 3,
	} } },
	{ "vroundpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x09, .oplen = 1,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x09, .oplen = 1,
	} } },
	{ "roundps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x083A0F, .oplen = 3,
	} } },
	{ "vroundps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x08, .oplen = 1,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x08, .oplen = 1,
	} } },
	{ "roundsd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x0B3A0F, .oplen = 3,
	} } },
	{ "vroundsd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x0B, .oplen = 1,
	} } },
	{ "roundss", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x0A3A0F, .oplen = 3,
	} } },
	{ "vroundss", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79,
		.args = { XMM, XMM, XMM | M32, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x0A, .oplen = 1,
	} } },
	{ "rsqrtps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x520F, .oplen = 2,
	} } },
	{ "vrsqrtps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x52, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x52, .oplen = 1,
	} } },
	{ "rsqrtss", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x520F, .oplen = 2,
	} } },
	{ "vrsqrtss", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x52, .oplen = 1,
	} } },
	{ "sahf", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x9E, .oplen = 1,
	} } },
	{ "sal", 12, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x20,
		.args = { R8 | M8, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD0, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R8 | M8, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD2, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R8 | M8, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC0, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R16 | M16, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R16 | M16, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R32 | M32, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x20,
		.args = { R64 | M64, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R32 | M32, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x20,
		.args = { R64 | M64, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x20,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	} } },
	{ "sar", 12, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x38,
		.args = { R8 | M8, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD0, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { R8 | M8, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD2, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { R8 | M8, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC0, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { R16 | M16, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { R16 | M16, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { R32 | M32, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x38,
		.args = { R64 | M64, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { R32 | M32, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x38,
		.args = { R64 | M64, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x38,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x38,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	} } },
	{ "shl", 12, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x20,
		.args = { R8 | M8, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD0, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R8 | M8, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD2, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R8 | M8, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC0, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R16 | M16, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R16 | M16, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R32 | M32, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x20,
		.args = { R64 | M64, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R32 | M32, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x20,
		.args = { R64 | M64, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x20,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	} } },
	{ "shr", 12, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x28,
		.args = { R8 | M8, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD0, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { R8 | M8, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD2, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { R8 | M8, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC0, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { R16 | M16, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { R16 | M16, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { R32 | M32, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x28,
		.args = { R64 | M64, ONE }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD1, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { R32 | M32, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x28,
		.args = { R64 | M64, CL }, .arglen = 2, .mem_oper = 1,
		.opcode = 0xD3, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x28,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xC1, .oplen = 1,
	} } },
	{ "sarx", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32, R32 }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfa, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64, R64 }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0xF7, .oplen = 1,
	} } },
	{ "shlx", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32, R32 }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64, R64 }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0xF7, .oplen = 1,
	} } },
	{ "shrx", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32, R32 }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfb, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64, R64 }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0xF7, .oplen = 1,
	} } },
	{ "sbb", 21, (struct x64LookupActualIns[]) { {
		.args = { AL, IMM8 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x1C, .oplen = 1,
	}, {
		.args = { AX, IMM16 }, .arglen = 2, .imm_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x1D, .oplen = 1,
	}, {
		.args = { EAX, IMM32 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x1D, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { RAX, IMM32 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x1D, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { R8 | M8, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x80, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { R16 | M16, IMM16 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x81, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { R32 | M32, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x81, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x18,
		.args = { R64 | M64, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x81, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrm = 0x18,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x18,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, R8 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x18, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, RH }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x18, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16 | M16, R16 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x19, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x19, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x19, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x1A, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { RH, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x1A, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x1B, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x1B, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x1B, .oplen = 1,
	} } },
	{ "scas", 4, (struct x64LookupActualIns[]) { {
		.args = { M8 }, .arglen = 1,
		.opcode = 0xAE, .oplen = 1,
	}, {
		.args = { M16 }, .arglen = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xAF, .oplen = 1,
	}, {
		.args = { M32 }, .arglen = 1,
		.opcode = 0xAF, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { M64 }, .arglen = 1,
		.opcode = 0xAF, .oplen = 1,
	} } },
	{ "scasb", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xAE, .oplen = 1,
	} } },
	{ "scasw", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0x66, .preflen = 1, .opcode = 0xAF, .oplen = 1,
	} } },
	{ "scasd", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xAF, .oplen = 1,
	} } },
	{ "scasq", 1, (struct x64LookupActualIns[]) { {
		.rex = 0x48,
		.opcode = 0xAF, .oplen = 1,
	} } },
	{ "seta", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x970F, .oplen = 2,
	} } },
	{ "setae", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x930F, .oplen = 2,
	} } },
	{ "setb", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x920F, .oplen = 2,
	} } },
	{ "setbe", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x960F, .oplen = 2,
	} } },
	{ "setc", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x920F, .oplen = 2,
	} } },
	{ "sete", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x940F, .oplen = 2,
	} } },
	{ "setg", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x9F0F, .oplen = 2,
	} } },
	{ "setge", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x9D0F, .oplen = 2,
	} } },
	{ "setl", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x9C0F, .oplen = 2,
	} } },
	{ "setle", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x9E0F, .oplen = 2,
	} } },
	{ "setna", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x960F, .oplen = 2,
	} } },
	{ "setnae", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x920F, .oplen = 2,
	} } },
	{ "setnb", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x930F, .oplen = 2,
	} } },
	{ "setnbe", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x970F, .oplen = 2,
	} } },
	{ "setnc", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x930F, .oplen = 2,
	} } },
	{ "setne", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x950F, .oplen = 2,
	} } },
	{ "setng", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x9E0F, .oplen = 2,
	} } },
	{ "setnge", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x9C0F, .oplen = 2,
	} } },
	{ "setnl", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x9D0F, .oplen = 2,
	} } },
	{ "setnle", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x9F0F, .oplen = 2,
	} } },
	{ "setno", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x910F, .oplen = 2,
	} } },
	{ "setnp", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x9B0F, .oplen = 2,
	} } },
	{ "setns", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x990F, .oplen = 2,
	} } },
	{ "setnz", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x950F, .oplen = 2,
	} } },
	{ "seto", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x900F, .oplen = 2,
	} } },
	{ "setp", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x9A0F, .oplen = 2,
	} } },
	{ "setpe", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x9A0F, .oplen = 2,
	} } },
	{ "setpo", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x9B0F, .oplen = 2,
	} } },
	{ "sets", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x980F, .oplen = 2,
	} } },
	{ "setz", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x940F, .oplen = 2,
	} } },
	{ "sfence", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF8AE0F, .oplen = 3,
	} } },
	{ "sgdt", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { X64_ALLMEMMASK }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x010F, .oplen = 2,
	} } },
	{ "shld", 6, (struct x64LookupActualIns[]) { {
		.args = { R16 | M16, R16, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xA40F, .oplen = 2,
	}, {
		.args = { R16 | M16, R16, CL }, .arglen = 3, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xA50F, .oplen = 2,
	}, {
		.args = { R32 | M32, R32, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xA40F, .oplen = 2,
	}, {
		.rex = 0x48,
		.args = { R64 | M64, R64, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xA40F, .oplen = 2,
	}, {
		.args = { R32 | M32, R32, CL }, .arglen = 3, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xA50F, .oplen = 2,
	}, {
		.rex = 0x48,
		.args = { R64 | M64, R64, CL }, .arglen = 3, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xA50F, .oplen = 2,
	} } },
	{ "shrd", 6, (struct x64LookupActualIns[]) { {
		.args = { R16 | M16, R16, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xAC0F, .oplen = 2,
	}, {
		.args = { R16 | M16, R16, CL }, .arglen = 3, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xAD0F, .oplen = 2,
	}, {
		.args = { R32 | M32, R32, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xAC0F, .oplen = 2,
	}, {
		.rex = 0x48,
		.args = { R64 | M64, R64, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xAC0F, .oplen = 2,
	}, {
		.args = { R32 | M32, R32, CL }, .arglen = 3, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xAD0F, .oplen = 2,
	}, {
		.rex = 0x48,
		.args = { R64 | M64, R64, CL }, .arglen = 3, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xAD0F, .oplen = 2,
	} } },
	{ "shufpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xC60F, .oplen = 2,
	} } },
	{ "vshufpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xC6, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xC6, .oplen = 1,
	} } },
	{ "shufps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0xC60F, .oplen = 2,
	} } },
	{ "vshufps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xC6, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xC6, .oplen = 1,
	} } },
	{ "sidt", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x8,
		.args = { X64_ALLMEMMASK }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x010F, .oplen = 2,
	} } },
	{ "sldt", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x0,
		.args = { R16 | M16 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x000F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x0,
		.args = { R64 | M16 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x000F, .oplen = 2,
	} } },
	{ "smsw", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x20,
		.args = { R16 | M16 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x010F, .oplen = 2,
	}, {
		.modrmreq = true, .modrm = 0x20,
		.args = { R32 | M16 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x010F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x20,
		.args = { R64 | M16 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x010F, .oplen = 2,
	} } },
	{ "sqrtpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x510F, .oplen = 2,
	} } },
	{ "vsqrtpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x51, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x51, .oplen = 1,
	} } },
	{ "sqrtps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x510F, .oplen = 2,
	} } },
	{ "vsqrtps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x51, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x51, .oplen = 1,
	} } },
	{ "sqrtsd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x510F, .oplen = 2,
	} } },
	{ "vsqrtsd", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x51, .oplen = 1,
	} } },
	{ "sqrtss", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x510F, .oplen = 2,
	} } },
	{ "vsqrtss", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x51, .oplen = 1,
	} } },
	{ "stc", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF9, .oplen = 1,
	} } },
	{ "std", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xFD, .oplen = 1,
	} } },
	{ "sti", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xFB, .oplen = 1,
	} } },
	{ "stmxcsr", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x18,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xAE0F, .oplen = 2,
	} } },
	{ "vstmxcsr", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrm = 0x18,
		.args = { M32 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xAE, .oplen = 1,
	} } },
	{ "stos", 4, (struct x64LookupActualIns[]) { {
		.args = { M8 }, .arglen = 1,
		.opcode = 0xAA, .oplen = 1,
	}, {
		.args = { M16 }, .arglen = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xAB, .oplen = 1,
	}, {
		.args = { M32 }, .arglen = 1,
		.opcode = 0xAB, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { M64 }, .arglen = 1,
		.opcode = 0xAB, .oplen = 1,
	} } },
	{ "stosb", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xAA, .oplen = 1,
	} } },
	{ "stosw", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0x66, .preflen = 1, .opcode = 0xAB, .oplen = 1,
	} } },
	{ "stosd", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xAB, .oplen = 1,
	} } },
	{ "stosq", 1, (struct x64LookupActualIns[]) { {
		.rex = 0x48,
		.opcode = 0xAB, .oplen = 1,
	} } },
	{ "str", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x8,
		.args = { R16 | M16 }, .arglen = 1,
		.opcode = 0x000F, .oplen = 2,
	} } },
	{ "sub", 21, (struct x64LookupActualIns[]) { {
		.args = { AL, IMM8 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x2C, .oplen = 1,
	}, {
		.args = { AX, IMM16 }, .arglen = 2, .imm_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x2D, .oplen = 1,
	}, {
		.args = { EAX, IMM32 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x2D, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { RAX, IMM32 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x2D, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { R8 | M8, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x80, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { R16 | M16, IMM16 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x81, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { R32 | M32, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x81, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x28,
		.args = { R64 | M64, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x81, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrm = 0x28,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x28,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, R8 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x28, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, RH }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x28, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16 | M16, R16 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x29, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x29, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x29, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2A, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { RH, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2A, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x2B, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2B, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2B, .oplen = 1,
	} } },
	{ "subpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x5C0F, .oplen = 2,
	} } },
	{ "vsubpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5C, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5C, .oplen = 1,
	} } },
	{ "subps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x5C0F, .oplen = 2,
	} } },
	{ "vsubps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5C, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5C, .oplen = 1,
	} } },
	{ "subsd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x5C0F, .oplen = 2,
	} } },
	{ "vsubsd", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7b, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5C, .oplen = 1,
	} } },
	{ "subss", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x5C0F, .oplen = 2,
	} } },
	{ "vsubss", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x7a, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x5C, .oplen = 1,
	} } },
	{ "swapgs", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xF8010F, .oplen = 3,
	} } },
	{ "syscall", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x050F, .oplen = 2,
	} } },
	{ "sysenter", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x340F, .oplen = 2,
	} } },
	{ "sysexit", 2, (struct x64LookupActualIns[]) { {
		.opcode = 0x350F, .oplen = 2,
	}, {
		.rex = 0x48,
		.args = { PREFREX_W }, .arglen = 1,
		.opcode = 0x350F, .oplen = 2,
	} } },
	{ "sysret", 2, (struct x64LookupActualIns[]) { {
		.opcode = 0x070F, .oplen = 2,
	}, {
		.rex = 0x48,
		.args = { PREFREX_W }, .arglen = 1,
		.opcode = 0x070F, .oplen = 2,
	} } },
	{ "test", 13, (struct x64LookupActualIns[]) { {
		.args = { AL, IMM8 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0xA8, .oplen = 1,
	}, {
		.args = { AX, IMM16 }, .arglen = 2, .imm_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xA9, .oplen = 1,
	}, {
		.args = { EAX, IMM32 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0xA9, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { RAX, IMM32 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0xA9, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R8 | M8, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xF6, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R16 | M16, IMM16 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xF7, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x0,
		.args = { R32 | M32, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x0,
		.args = { R64 | M64, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0xF7, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, R8 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x84, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, RH }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x84, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16 | M16, R16 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x85, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x85, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x85, .oplen = 1,
	} } },
	{ "tzcnt", 3, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF366, .preflen = 2, .opcode = 0xBC0F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xBC0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xBC0F, .oplen = 2,
	} } },
	{ "ucomisd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x2E0F, .oplen = 2,
	} } },
	{ "vucomisd", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2E, .oplen = 1,
	} } },
	{ "ucomiss", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2E0F, .oplen = 2,
	} } },
	{ "vucomiss", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x2E, .oplen = 1,
	} } },
	{ "ud2", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x0B0F, .oplen = 2,
	} } },
	{ "unpckhpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x150F, .oplen = 2,
	} } },
	{ "vunpckhpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x15, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x15, .oplen = 1,
	} } },
	{ "unpckhps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x150F, .oplen = 2,
	} } },
	{ "vunpckhps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x15, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x15, .oplen = 1,
	} } },
	{ "unpcklpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x140F, .oplen = 2,
	} } },
	{ "vunpcklpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x14, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x14, .oplen = 1,
	} } },
	{ "unpcklps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x140F, .oplen = 2,
	} } },
	{ "vunpcklps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x14, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x14, .oplen = 1,
	} } },
	{ "vbroadcastss", 4, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x18, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x18, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x18, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x18, .oplen = 1,
	} } },
	{ "vbroadcastsd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x19, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x19, .oplen = 1,
	} } },
	{ "vbroadcastf128", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x1A, .oplen = 1,
	} } },
	{ "vcvtph2ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x13, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x13, .oplen = 1,
	} } },
	{ "vcvtps2ph", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { XMM | M128, YMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x1D, .oplen = 1,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM | M64, XMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x1D, .oplen = 1,
	} } },
	{ "verr", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x20,
		.args = { R16 | M16 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x000F, .oplen = 2,
	} } },
	{ "verw", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x28,
		.args = { R16 | M16 }, .arglen = 1, .mem_oper = 1,
		.opcode = 0x000F, .oplen = 2,
	} } },
	{ "vextractf128", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { XMM | M128, YMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x19, .oplen = 1,
	} } },
	{ "vextracti128", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { XMM | M128, YMM, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x39, .oplen = 1,
	} } },
	{ "vfmadd132pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x98, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x98, .oplen = 1,
	} } },
	{ "vfmadd213pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xA8, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xA8, .oplen = 1,
	} } },
	{ "vfmadd231pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xB8, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xB8, .oplen = 1,
	} } },
	{ "vfmadd132ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x98, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x98, .oplen = 1,
	} } },
	{ "vfmadd213ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xA8, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xA8, .oplen = 1,
	} } },
	{ "vfmadd231ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xB8, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xB8, .oplen = 1,
	} } },
	{ "vfmadd132sd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x99, .oplen = 1,
	} } },
	{ "vfmadd213sd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xA9, .oplen = 1,
	} } },
	{ "vfmadd231sd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xB9, .oplen = 1,
	} } },
	{ "vfmadd132ss", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x99, .oplen = 1,
	} } },
	{ "vfmadd213ss", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xA9, .oplen = 1,
	} } },
	{ "vfmadd231ss", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xB9, .oplen = 1,
	} } },
	{ "vfmaddsub132pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x96, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x96, .oplen = 1,
	} } },
	{ "vfmaddsub213pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xA6, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xA6, .oplen = 1,
	} } },
	{ "vfmaddsub231pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xB6, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xB6, .oplen = 1,
	} } },
	{ "vfmaddsub132ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x96, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x96, .oplen = 1,
	} } },
	{ "vfmaddsub213ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xA6, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xA6, .oplen = 1,
	} } },
	{ "vfmaddsub231ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xB6, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xB6, .oplen = 1,
	} } },
	{ "vfmsubadd132pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x97, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x97, .oplen = 1,
	} } },
	{ "vfmsubadd213pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xA7, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xA7, .oplen = 1,
	} } },
	{ "vfmsubadd231pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xB7, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xB7, .oplen = 1,
	} } },
	{ "vfmsubadd132ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x97, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x97, .oplen = 1,
	} } },
	{ "vfmsubadd213ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xA7, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xA7, .oplen = 1,
	} } },
	{ "vfmsubadd231ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xB7, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xB7, .oplen = 1,
	} } },
	{ "vfmsub132pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x9A, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x9A, .oplen = 1,
	} } },
	{ "vfmsub213pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xAA, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xAA, .oplen = 1,
	} } },
	{ "vfmsub231pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xBA, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xBA, .oplen = 1,
	} } },
	{ "vfmsub132ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x9A, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x9A, .oplen = 1,
	} } },
	{ "vfmsub213ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xAA, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xAA, .oplen = 1,
	} } },
	{ "vfmsub231ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xBA, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xBA, .oplen = 1,
	} } },
	{ "vfmsub132sd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x9B, .oplen = 1,
	} } },
	{ "vfmsub213sd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xAB, .oplen = 1,
	} } },
	{ "vfmsub231sd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xBB, .oplen = 1,
	} } },
	{ "vfmsub132ss", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x9B, .oplen = 1,
	} } },
	{ "vfmsub213ss", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xAB, .oplen = 1,
	} } },
	{ "vfmsub231ss", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xBB, .oplen = 1,
	} } },
	{ "vfnmadd132pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x9C, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x9C, .oplen = 1,
	} } },
	{ "vfnmadd213pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xAC, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xAC, .oplen = 1,
	} } },
	{ "vfnmadd231pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xBC, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xBC, .oplen = 1,
	} } },
	{ "vfnmadd132ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x9C, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x9C, .oplen = 1,
	} } },
	{ "vfnmadd213ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xAC, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xAC, .oplen = 1,
	} } },
	{ "vfnmadd231ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xBC, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xBC, .oplen = 1,
	} } },
	{ "vfnmadd132sd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x9D, .oplen = 1,
	} } },
	{ "vfnmadd213sd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xAD, .oplen = 1,
	} } },
	{ "vfnmadd231sd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xBD, .oplen = 1,
	} } },
	{ "vfnmadd132ss", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x9D, .oplen = 1,
	} } },
	{ "vfnmadd213ss", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xAD, .oplen = 1,
	} } },
	{ "vfnmadd231ss", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xBD, .oplen = 1,
	} } },
	{ "vfnmsub132pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x9E, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x9E, .oplen = 1,
	} } },
	{ "vfnmsub213pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xAE, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xAE, .oplen = 1,
	} } },
	{ "vfnmsub231pd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xBE, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xBE, .oplen = 1,
	} } },
	{ "vfnmsub132ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x9E, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x9E, .oplen = 1,
	} } },
	{ "vfnmsub213ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xAE, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xAE, .oplen = 1,
	} } },
	{ "vfnmsub231ps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xBE, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xBE, .oplen = 1,
	} } },
	{ "vfnmsub132sd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x9F, .oplen = 1,
	} } },
	{ "vfnmsub213sd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xAF, .oplen = 1,
	} } },
	{ "vfnmsub231sd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M64 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xBF, .oplen = 1,
	} } },
	{ "vfnmsub132ss", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x9F, .oplen = 1,
	} } },
	{ "vfnmsub213ss", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xAF, .oplen = 1,
	} } },
	{ "vfnmsub231ss", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M32 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0xBF, .oplen = 1,
	} } },
	{ "vgatherdpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, M32, XMM }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0x92, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, M32, YMM }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0x92, .oplen = 1,
	} } },
	{ "vgatherqpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, M64, XMM }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0x93, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, M64, YMM }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0x93, .oplen = 1,
	} } },
	{ "vgatherdps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, M32, XMM }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0x92, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, M32, YMM }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0x92, .oplen = 1,
	} } },
	{ "vgatherqps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, M64, XMM }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0x93, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { XMM, M64, XMM }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0x93, .oplen = 1,
	} } },
	{ "vpgatherdd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, M32, XMM }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0x90, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, M32, YMM }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0x90, .oplen = 1,
	} } },
	{ "vpgatherqd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, M64, XMM }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0x91, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { XMM, M64, XMM }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0x91, .oplen = 1,
	} } },
	{ "vpgatherdq", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, M32, XMM }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0x90, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, M32, YMM }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0x90, .oplen = 1,
	} } },
	{ "vpgatherqq", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, M64, XMM }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0x91, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, M64, YMM }, .arglen = 3, .mem_oper = 2, .reg_oper = 1, .vex_oper = 3,
		.opcode = 0x91, .oplen = 1,
	} } },
	{ "vinsertf128", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, XMM | M128, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x18, .oplen = 1,
	} } },
	{ "vinserti128", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, XMM | M128, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x38, .oplen = 1,
	} } },
	{ "vmaskmovps", 4, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x2C, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x2C, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { M128, XMM, XMM }, .arglen = 3, .mem_oper = 1, .reg_oper = 3, .vex_oper = 2,
		.opcode = 0x2E, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { M256, YMM, YMM }, .arglen = 3, .mem_oper = 1, .reg_oper = 3, .vex_oper = 2,
		.opcode = 0x2E, .oplen = 1,
	} } },
	{ "vmaskmovpd", 4, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x2D, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x2D, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { M128, XMM, XMM }, .arglen = 3, .mem_oper = 1, .reg_oper = 3, .vex_oper = 2,
		.opcode = 0x2F, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { M256, YMM, YMM }, .arglen = 3, .mem_oper = 1, .reg_oper = 3, .vex_oper = 2,
		.opcode = 0x2F, .oplen = 1,
	} } },
	{ "vpblendd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x02, .oplen = 1,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x02, .oplen = 1,
	} } },
	{ "vpbroadcastb", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x78, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x78, .oplen = 1,
	} } },
	{ "vpbroadcastw", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x79, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x79, .oplen = 1,
	} } },
	{ "vpbroadcastd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x58, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x58, .oplen = 1,
	} } },
	{ "vpbroadcastq", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x59, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, XMM | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x59, .oplen = 1,
	} } },
	{ "vbroadcasti128", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x5A, .oplen = 1,
	} } },
	{ "vpermd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x36, .oplen = 1,
	} } },
	{ "vpermpd", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x01, .oplen = 1,
	} } },
	{ "vpermps", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x16, .oplen = 1,
	} } },
	{ "vpermq", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x00, .oplen = 1,
	} } },
	{ "vperm2i128", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x46, .oplen = 1,
	} } },
	{ "vpermilpd", 4, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x0D, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x0D, .oplen = 1,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x05, .oplen = 1,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x05, .oplen = 1,
	} } },
	{ "vpermilps", 4, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x0C, .oplen = 1,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x04, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x0C, .oplen = 1,
	}, {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256, IMM8 }, .arglen = 3, .imm_oper = 3, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x04, .oplen = 1,
	} } },
	{ "vperm2f128", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 3, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256, IMM8 }, .arglen = 4, .imm_oper = 4, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x06, .oplen = 1,
	} } },
	{ "vpmaskmovd", 4, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x8C, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x8C, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { M128, XMM, XMM }, .arglen = 3, .mem_oper = 1, .reg_oper = 3, .vex_oper = 2,
		.opcode = 0x8E, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { M256, YMM, YMM }, .arglen = 3, .mem_oper = 1, .reg_oper = 3, .vex_oper = 2,
		.opcode = 0x8E, .oplen = 1,
	} } },
	{ "vpmaskmovq", 4, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x8C, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x8C, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { M128, XMM, XMM }, .arglen = 3, .mem_oper = 1, .reg_oper = 3, .vex_oper = 2,
		.opcode = 0x8E, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { M256, YMM, YMM }, .arglen = 3, .mem_oper = 1, .reg_oper = 3, .vex_oper = 2,
		.opcode = 0x8E, .oplen = 1,
	} } },
	{ "vpsllvd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x47, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x47, .oplen = 1,
	} } },
	{ "vpsllvq", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x47, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x47, .oplen = 1,
	} } },
	{ "vpsravd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x46, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x46, .oplen = 1,
	} } },
	{ "vpsrlvd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x45, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x45, .oplen = 1,
	} } },
	{ "vpsrlvq", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0xf9, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x45, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0xfd, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x45, .oplen = 1,
	} } },
	{ "vtestps", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x0E, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x0E, .oplen = 1,
	} } },
	{ "vtestpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 2, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x0F, .oplen = 1,
	}, {
		.vex = 0x80 | 2, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM | M256 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x0F, .oplen = 1,
	} } },
	{ "vzeroall", 1, (struct x64LookupActualIns[]) { {
		.vex = 0x80 | 1, .vex_byte = 0x7c,
		.opcode = 0x77, .oplen = 1,
	} } },
	{ "vzeroupper", 1, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78,
		.opcode = 0x77, .oplen = 1,
	} } },
	{ "wait", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0x9B, .preflen = 1, .opcode = 0x0, .oplen = 0,
	} } },
	{ "fwait", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0x9B, .preflen = 1, .opcode = 0x0, .oplen = 0,
	} } },
	{ "wbinvd", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x090F, .oplen = 2,
	} } },
	{ "wrfsbase", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x10,
		.args = { R32 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAE0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x10,
		.args = { R64 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAE0F, .oplen = 2,
	} } },
	{ "wrgsbase", 2, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x18,
		.args = { R32 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAE0F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x18,
		.args = { R64 }, .arglen = 1, .mem_oper = 1,
		.prefixes = 0xF3, .preflen = 1, .opcode = 0xAE0F, .oplen = 2,
	} } },
	{ "wrmsr", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0x300F, .oplen = 2,
	} } },
	{ "xacquire", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0xF2, .preflen = 1, .opcode = 0x0, .oplen = 0,
	} } },
	{ "xrelease", 1, (struct x64LookupActualIns[]) { {
		.prefixes = 0xF3, .preflen = 1, .opcode = 0x0, .oplen = 0,
	} } },
	{ "xabort", 1, (struct x64LookupActualIns[]) { {
		.args = { IMM8 }, .arglen = 1, .imm_oper = 1,
		.opcode = 0xF8C6, .oplen = 2,
	} } },
	{ "xadd", 5, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, R8 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xC00F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, RH }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xC00F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16 | M16, R16 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0xC10F, .oplen = 2,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xC10F, .oplen = 2,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0xC10F, .oplen = 2,
	} } },
	{ "xbegin", 1, (struct x64LookupActualIns[]) { {
		.args = { REL32 }, .arglen = 1,
		.opcode = 0xF8C7, .oplen = 2,
	} } },
	{ "xchg", 16, (struct x64LookupActualIns[]) { {
		.args = { AX, R16 }, .arglen = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x90, .oplen = 1,
	}, {
		.args = { R16, AX }, .arglen = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x90, .oplen = 1,
	}, {
		.args = { EAX, R32 }, .arglen = 2, .reg_oper = 1,
		.opcode = 0x90, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { RAX, R64 }, .arglen = 2, .reg_oper = 1,
		.opcode = 0x90, .oplen = 1,
	}, {
		.args = { R32, EAX }, .arglen = 2, .reg_oper = 1,
		.opcode = 0x90, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { R64, RAX }, .arglen = 2, .reg_oper = 1,
		.opcode = 0x90, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, R8 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x86, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, RH }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x86, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x86, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { RH, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x86, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16 | M16, R16 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x87, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x87, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x87, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x87, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x87, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x87, .oplen = 1,
	} } },
	{ "xend", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xD5010F, .oplen = 3,
	} } },
	{ "xgetbv", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xD0010F, .oplen = 3,
	} } },
	{ "xlat", 1, (struct x64LookupActualIns[]) { {
		.args = { M8 }, .arglen = 1,
		.opcode = 0xD7, .oplen = 1,
	} } },
	{ "xlatb", 1, (struct x64LookupActualIns[]) { {
		.rex = 0x48,
		.opcode = 0xD7, .oplen = 1,
	} } },
	{ "xor", 21, (struct x64LookupActualIns[]) { {
		.args = { AL, IMM8 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x34, .oplen = 1,
	}, {
		.args = { AX, IMM16 }, .arglen = 2, .imm_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x35, .oplen = 1,
	}, {
		.args = { EAX, IMM32 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x35, .oplen = 1,
	}, {
		.rex = 0x48,
		.args = { RAX, IMM32 }, .arglen = 2, .imm_oper = 2,
		.opcode = 0x35, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { R8 | M8, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x80, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { R16 | M16, IMM16 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x81, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { R32 | M32, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x81, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x30,
		.args = { R64 | M64, IMM32 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x81, .oplen = 1,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { R16 | M16, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrm = 0x30,
		.args = { R32 | M32, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrm = 0x30,
		.args = { R64 | M64, IMM8 }, .arglen = 2, .imm_oper = 2, .mem_oper = 1,
		.opcode = 0x83, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, R8 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x30, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8 | M8, RH }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x30, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16 | M16, R16 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x31, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32 | M32, R32 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x31, .oplen = 1,
		.preffered = true,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64 | M64, R64 }, .arglen = 2, .mem_oper = 1, .reg_oper = 2,
		.opcode = 0x31, .oplen = 1,
		.preffered = true,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R8, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x32, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { RH, R8 | M8 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x32, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R16, R16 | M16 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x33, .oplen = 1,
	}, {
		.modrmreq = true, .modrmreg = true,
		.args = { R32, R32 | M32 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x33, .oplen = 1,
	}, {
		.rex = 0x48, .modrmreq = true, .modrmreg = true,
		.args = { R64, R64 | M64 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x33, .oplen = 1,
	} } },
	{ "xorpd", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.prefixes = 0x66, .preflen = 1, .opcode = 0x570F, .oplen = 2,
	} } },
	{ "vxorpd", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x79, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x57, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7d, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x57, .oplen = 1,
	} } },
	{ "xorps", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM | M128 }, .arglen = 2, .mem_oper = 2, .reg_oper = 1,
		.opcode = 0x570F, .oplen = 2,
	} } },
	{ "vxorps", 2, (struct x64LookupActualIns[]) { {
		.vex = 1, .vex_byte = 0x78, .modrmreq = true, .modrmreg = true,
		.args = { XMM, XMM, XMM | M128 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x57, .oplen = 1,
	}, {
		.vex = 0x80 | 1, .vex_byte = 0x7c, .modrmreq = true, .modrmreg = true,
		.args = { YMM, YMM, YMM | M256 }, .arglen = 3, .mem_oper = 3, .reg_oper = 1, .vex_oper = 2,
		.opcode = 0x57, .oplen = 1,
	} } },
	{ "xrstor", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x28,
		.args = { X64_ALLMEMMASK }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xAE0F, .oplen = 2,
	} } },
	{ "xrstor64", 1, (struct x64LookupActualIns[]) { {
		.rex = 0x48, .modrmreq = true, .modrm = 0x28,
		.args = { X64_ALLMEMMASK }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xAE0F, .oplen = 2,
	} } },
	{ "xsave", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x20,
		.args = { X64_ALLMEMMASK }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xAE0F, .oplen = 2,
	} } },
	{ "xsave64", 1, (struct x64LookupActualIns[]) { {
		.rex = 0x48, .modrmreq = true, .modrm = 0x20,
		.args = { X64_ALLMEMMASK }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xAE0F, .oplen = 2,
	} } },
	{ "xsaveopt", 1, (struct x64LookupActualIns[]) { {
		.modrmreq = true, .modrm = 0x30,
		.args = { X64_ALLMEMMASK }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xAE0F, .oplen = 2,
	} } },
	{ "xsaveopt64", 1, (struct x64LookupActualIns[]) { {
		.rex = 0x48, .modrmreq = true, .modrm = 0x30,
		.args = { X64_ALLMEMMASK }, .arglen = 1, .mem_oper = 1,
		.opcode = 0xAE0F, .oplen = 2,
	} } },
	{ "xsetbv", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xD1010F, .oplen = 3,
	} } },
	{ "xtest", 1, (struct x64LookupActualIns[]) { {
		.opcode = 0xD6010F, .oplen = 3,
	} } }
};

#ifdef __cplusplus
#define X64OPERAND_CAST(...) x64Operand(__VA_ARGS__)
#else
#define X64OPERAND_CAST(...) (x64Operand) { __VA_ARGS__ }
#endif

#define imm(value) X64OPERAND_CAST( ((value) == 1 ? ONE : 0) | IMM8 | IMM16 | IMM32 | IMM64, (value) )
#define im64(value) X64OPERAND_CAST( ((value) == 1 ? ONE : 0) | IMM64, (value) )
#define im32(value) X64OPERAND_CAST( ((value) == 1 ? ONE : 0) | IMM32, (value) )
#define im16(value) X64OPERAND_CAST( ((value) == 1 ? ONE : 0) | IMM16, (value) )
#define im8(value) X64OPERAND_CAST( ((value) == 1 ? ONE : 0) | IMM8, (value) )
#define imptr(value) X64OPERAND_CAST( IMM64, (uint64_t)(void*)(value) )

#define al X64OPERAND_CAST( AL | R8 )
#define cl X64OPERAND_CAST( CL | R8, 1 )
#define dl X64OPERAND_CAST( R8, 2 )
#define bl X64OPERAND_CAST( R8, 3 )

#define bpl X64OPERAND_CAST( R8, 4 )
#define spl X64OPERAND_CAST( R8, 5 )
#define sil X64OPERAND_CAST( R8, 6 )
#define dil X64OPERAND_CAST( R8, 7 )
#define r8b X64OPERAND_CAST( R8, 8 )
#define r9b X64OPERAND_CAST( R8, 9 )
#define r10b X64OPERAND_CAST( R8, 10 )
#define r11b X64OPERAND_CAST( R8, 11 )
#define r12b X64OPERAND_CAST( R8, 12 )
#define r13b X64OPERAND_CAST( R8, 13 )
#define r14b X64OPERAND_CAST( R8, 14 )
#define r15b X64OPERAND_CAST( R8, 15 )

#define ah X64OPERAND_CAST( RH, 4 )
#define ch X64OPERAND_CAST( RH, 5 )
#define dh X64OPERAND_CAST( RH, 6 )
#define bh X64OPERAND_CAST( RH, 7 )

#define ax X64OPERAND_CAST( AX | R16 )
#define cx X64OPERAND_CAST( R16, 1 )
#define dx X64OPERAND_CAST( DX | R16, 2 )
#define bx X64OPERAND_CAST( R16, 3 )

#define si X64OPERAND_CAST( R16, 4 )
#define di X64OPERAND_CAST( R16, 5 )
#define bp X64OPERAND_CAST( R16, 6 )
#define sp X64OPERAND_CAST( R16, 7 )
#define r8w X64OPERAND_CAST( R16, 8 )
#define r9w X64OPERAND_CAST( R16, 9 )
#define r10w X64OPERAND_CAST( R16, 10 )
#define r11w X64OPERAND_CAST( R16, 11 )
#define r12w X64OPERAND_CAST( R16, 12 )
#define r13w X64OPERAND_CAST( R16, 13 )
#define r14w X64OPERAND_CAST( R16, 14 )
#define r15w X64OPERAND_CAST( R16, 15 )

enum x64RegisterReference: uint32_t {
	// DO NOT CHANGE THEIR ORDER
	$eax, $ecx, $edx, $ebx, $esp, $ebp, $esi, $edi, $r8d, $r9d, $r10d, $r11d, $r12d,
	$r13d, $r14d, $r15d, $rax, $rcx, $rdx, $rbx, $rsp, $rbp, $rsi, $rdi, $r8, $r9, $r10,
	$r11, $r12, $r13, $r14, $r15, $rip = 0x20, $es, $cs, $ss, $ds, $fs, $gs,
	
	$xmm0 = 0x800000, $xmm1 = 0x800001, $xmm2 = 0x800002, $xmm3 = 0x800003, $xmm4 = 0x800004, $xmm5 = 0x800005, $xmm6 = 0x800006, $xmm7 = 0x800007,
	$xmm8 = 0x800008, $xmm9 = 0x800009, $xmm10 = 0x80000A, $xmm11 = 0x80000B, $xmm12 = 0x80000C, $xmm13 = 0x80000D, $xmm14 = 0x80000E, $xmm15 = 0x80000F,
	$ymm0 = 0x800000, $ymm1 = 0x800001, $ymm2 = 0x800002, $ymm3 = 0x800003, $ymm4 = 0x800004, $ymm5 = 0x800005, $ymm6 = 0x800006, $ymm7 = 0x800007,
	$ymm8 = 0x800008, $ymm9 = 0x800009, $ymm10 = 0x80000A, $ymm11 = 0x80000B, $ymm12 = 0x80000C, $ymm13 = 0x80000D, $ymm14 = 0x80000E, $ymm15 = 0x80000F,
	$riprel = 0x30, $none = 0xFFF0
};

#define eax X64OPERAND_CAST( EAX | R32, $eax )
#define ecx X64OPERAND_CAST( R32, $ecx )
#define edx X64OPERAND_CAST( R32, $edx )
#define ebx X64OPERAND_CAST( R32, $ebx )
#define esp X64OPERAND_CAST( R32, $esp )
#define ebp X64OPERAND_CAST( R32, $ebp )
#define esi X64OPERAND_CAST( R32, $esi )
#define edi X64OPERAND_CAST( R32, $edi )
#define r8d X64OPERAND_CAST( R32, $r8d )
#define r9d X64OPERAND_CAST( R32, $r9d )
#define r10d X64OPERAND_CAST( R32, $r10d )
#define r11d X64OPERAND_CAST( R32, $r11d )
#define r12d X64OPERAND_CAST( R32, $r12d )
#define r13d X64OPERAND_CAST( R32, $r13d )
#define r14d X64OPERAND_CAST( R32, $r14d )
#define r15d X64OPERAND_CAST( R32, $r15d )

#define rax X64OPERAND_CAST( RAX | R64, 0x0 )
#define rcx X64OPERAND_CAST( R64, 0x1 )
#define rdx X64OPERAND_CAST( R64, 0x2 )
#define rbx X64OPERAND_CAST( R64, 0x3 )
#define rsp X64OPERAND_CAST( R64, 0x4 )
#define rbp X64OPERAND_CAST( R64, 0x5 )
#define rsi X64OPERAND_CAST( R64, 0x6 )
#define rdi X64OPERAND_CAST( R64, 0x7 )
#define r8 X64OPERAND_CAST( R64, 0x8 )
#define r9 X64OPERAND_CAST( R64, 0x9 )
#define r10 X64OPERAND_CAST( R64, 0xA )
#define r11 X64OPERAND_CAST( R64, 0xB )
#define r12 X64OPERAND_CAST( R64, 0xC )
#define r13 X64OPERAND_CAST( R64, 0xD )
#define r14 X64OPERAND_CAST( R64, 0xE )
#define r15 X64OPERAND_CAST( R64, 0xF )

// SSE and AVX registers
#define xmm0 X64OPERAND_CAST( XMM_0 | XMM, 0 )
#define xmm1 X64OPERAND_CAST( XMM, 1 )
#define xmm2 X64OPERAND_CAST( XMM, 2 )
#define xmm3 X64OPERAND_CAST( XMM, 3 )
#define xmm4 X64OPERAND_CAST( XMM, 4 )
#define xmm5 X64OPERAND_CAST( XMM, 5 )
#define xmm6 X64OPERAND_CAST( XMM, 6 )
#define xmm7 X64OPERAND_CAST( XMM, 7 )
#define xmm8 X64OPERAND_CAST( XMM, 8 )
#define xmm9 X64OPERAND_CAST( XMM, 9 )
#define xmm10 X64OPERAND_CAST( XMM, 10 )
#define xmm11 X64OPERAND_CAST( XMM, 11 )
#define xmm12 X64OPERAND_CAST( XMM, 12 )
#define xmm13 X64OPERAND_CAST( XMM, 13 )
#define xmm14 X64OPERAND_CAST( XMM, 14 )
#define xmm15 X64OPERAND_CAST( XMM, 15 )
#define xmm16 X64OPERAND_CAST( XMM, 16 )
#define xmm17 X64OPERAND_CAST( XMM, 17 )
#define xmm18 X64OPERAND_CAST( XMM, 18 )
#define xmm19 X64OPERAND_CAST( XMM, 19 )
#define xmm20 X64OPERAND_CAST( XMM, 20 )
#define xmm21 X64OPERAND_CAST( XMM, 21 )
#define xmm22 X64OPERAND_CAST( XMM, 22 )
#define xmm23 X64OPERAND_CAST( XMM, 23 )
#define xmm24 X64OPERAND_CAST( XMM, 24 )
#define xmm25 X64OPERAND_CAST( XMM, 25 )
#define xmm26 X64OPERAND_CAST( XMM, 26 )
#define xmm27 X64OPERAND_CAST( XMM, 27 )
#define xmm28 X64OPERAND_CAST( XMM, 28 )
#define xmm29 X64OPERAND_CAST( XMM, 29 )
#define xmm30 X64OPERAND_CAST( XMM, 30 )
#define xmm31 X64OPERAND_CAST( XMM, 31 )

#define ymm0 X64OPERAND_CAST( YMM, 0 )
#define ymm1 X64OPERAND_CAST( YMM, 1 )
#define ymm2 X64OPERAND_CAST( YMM, 2 )
#define ymm3 X64OPERAND_CAST( YMM, 3 )
#define ymm4 X64OPERAND_CAST( YMM, 4 )
#define ymm5 X64OPERAND_CAST( YMM, 5 )
#define ymm6 X64OPERAND_CAST( YMM, 6 )
#define ymm7 X64OPERAND_CAST( YMM, 7 )
#define ymm8 X64OPERAND_CAST( YMM, 8 )
#define ymm9 X64OPERAND_CAST( YMM, 9 )
#define ymm10 X64OPERAND_CAST( YMM, 10 )
#define ymm11 X64OPERAND_CAST( YMM, 11 )
#define ymm12 X64OPERAND_CAST( YMM, 12 )
#define ymm13 X64OPERAND_CAST( YMM, 13 )
#define ymm14 X64OPERAND_CAST( YMM, 14 )
#define ymm15 X64OPERAND_CAST( YMM, 15 )
#define ymm16 X64OPERAND_CAST( YMM, 16 )
#define ymm17 X64OPERAND_CAST( YMM, 17 )
#define ymm18 X64OPERAND_CAST( YMM, 18 )
#define ymm19 X64OPERAND_CAST( YMM, 19 )
#define ymm20 X64OPERAND_CAST( YMM, 20 )
#define ymm21 X64OPERAND_CAST( YMM, 21 )
#define ymm22 X64OPERAND_CAST( YMM, 22 )
#define ymm23 X64OPERAND_CAST( YMM, 23 )
#define ymm24 X64OPERAND_CAST( YMM, 24 )
#define ymm25 X64OPERAND_CAST( YMM, 25 )
#define ymm26 X64OPERAND_CAST( YMM, 26 )
#define ymm27 X64OPERAND_CAST( YMM, 27 )
#define ymm28 X64OPERAND_CAST( YMM, 28 )
#define ymm29 X64OPERAND_CAST( YMM, 29 )
#define ymm30 X64OPERAND_CAST( YMM, 30 )
#define ymm31 X64OPERAND_CAST( YMM, 31 )

#define zmm0 X64OPERAND_CAST( ZMM, 0 )
#define zmm1 X64OPERAND_CAST( ZMM, 1 )
#define zmm2 X64OPERAND_CAST( ZMM, 2 )
#define zmm3 X64OPERAND_CAST( ZMM, 3 )
#define zmm4 X64OPERAND_CAST( ZMM, 4 )
#define zmm5 X64OPERAND_CAST( ZMM, 5 )
#define zmm6 X64OPERAND_CAST( ZMM, 6 )
#define zmm7 X64OPERAND_CAST( ZMM, 7 )
#define zmm8 X64OPERAND_CAST( ZMM, 8 )
#define zmm9 X64OPERAND_CAST( ZMM, 9 )
#define zmm10 X64OPERAND_CAST( ZMM, 10 )
#define zmm11 X64OPERAND_CAST( ZMM, 11 )
#define zmm12 X64OPERAND_CAST( ZMM, 12 )
#define zmm13 X64OPERAND_CAST( ZMM, 13 )
#define zmm14 X64OPERAND_CAST( ZMM, 14 )
#define zmm15 X64OPERAND_CAST( ZMM, 15 )
#define zmm16 X64OPERAND_CAST( ZMM, 16 )
#define zmm17 X64OPERAND_CAST( ZMM, 17 )
#define zmm18 X64OPERAND_CAST( ZMM, 18 )
#define zmm19 X64OPERAND_CAST( ZMM, 19 )
#define zmm20 X64OPERAND_CAST( ZMM, 20 )
#define zmm21 X64OPERAND_CAST( ZMM, 21 )
#define zmm22 X64OPERAND_CAST( ZMM, 22 )
#define zmm23 X64OPERAND_CAST( ZMM, 23 )
#define zmm24 X64OPERAND_CAST( ZMM, 24 )
#define zmm25 X64OPERAND_CAST( ZMM, 25 )
#define zmm26 X64OPERAND_CAST( ZMM, 26 )
#define zmm27 X64OPERAND_CAST( ZMM, 27 )
#define zmm28 X64OPERAND_CAST( ZMM, 28 )
#define zmm29 X64OPERAND_CAST( ZMM, 29 )
#define zmm30 X64OPERAND_CAST( ZMM, 30 )
#define zmm31 X64OPERAND_CAST( ZMM, 31 )

// mm registers
#define mm0 X64OPERAND_CAST( MM, 0 )
#define mm1 X64OPERAND_CAST( MM, 1 )
#define mm2 X64OPERAND_CAST( MM, 2 )
#define mm3 X64OPERAND_CAST( MM, 3 )
#define mm4 X64OPERAND_CAST( MM, 4 )
#define mm5 X64OPERAND_CAST( MM, 5 )
#define mm6 X64OPERAND_CAST( MM, 6 )
#define mm7 X64OPERAND_CAST( MM, 7 )

// control registers
#define cr0 X64OPERAND_CAST( CR0_7, 0 )
#define cr1 X64OPERAND_CAST( CR0_7, 1 )
#define cr2 X64OPERAND_CAST( CR0_7, 2 )
#define cr3 X64OPERAND_CAST( CR0_7, 3 )
#define cr4 X64OPERAND_CAST( CR0_7, 4 )
#define cr5 X64OPERAND_CAST( CR0_7, 5 )
#define cr6 X64OPERAND_CAST( CR0_7, 6 )
#define cr7 X64OPERAND_CAST( CR0_7, 7 )
#define cr8 X64OPERAND_CAST( CR8, 8 )

// debug registers
#define dr0 X64OPERAND_CAST( DREG, 0 )
#define dr1 X64OPERAND_CAST( DREG, 1 )
#define dr2 X64OPERAND_CAST( DREG, 2 )
#define dr3 X64OPERAND_CAST( DREG, 3 )
#define dr4 X64OPERAND_CAST( DREG, 4 )
#define dr5 X64OPERAND_CAST( DREG, 5 )
#define dr6 X64OPERAND_CAST( DREG, 6 )
#define dr7 X64OPERAND_CAST( DREG, 7 )

// FPU registers
#define st0 X64OPERAND_CAST( ST_0 | ST, 0 )
#define st1 X64OPERAND_CAST( ST, 1 )
#define st2 X64OPERAND_CAST( ST, 2 )
#define st3 X64OPERAND_CAST( ST, 3 )
#define st4 X64OPERAND_CAST( ST, 4 )
#define st5 X64OPERAND_CAST( ST, 5 )
#define st6 X64OPERAND_CAST( ST, 6 )
#define st7 X64OPERAND_CAST( ST, 7 )


// segment registers
#define es X64OPERAND_CAST( SREG, 1 )
#define cs X64OPERAND_CAST( SREG, 2 )
#define ss X64OPERAND_CAST( SREG, 3 )
#define ds X64OPERAND_CAST( SREG, 4 )
#define fs X64OPERAND_CAST( FS | SREG, 5 )
#define gs X64OPERAND_CAST( GS | SREG, 6 )

// #define lb(l) X64OPERAND_CAST( X64_LABEL_REF | REL32 | REL8, .label_name = l )
// #define lb_def(l) (x64Ins) { X64_LABEL_DEF, .label_name = l }

#define rel(insns) X64OPERAND_CAST( REL32 | REL8, insns )

// DISP    : 0x00000000ffffffff bit 0-31
// BASE    : 0x0000001f00000000 bit 32-36
// INDEX   : 0x00001f0000000000 bit 40-44
// SCALE   : 0x0003000000000000 bit 48-49
// SEG     : 0x0700000000000000 bit 56-58
// ADDR_OR : 0x1000000000000000 bit 60
// RIP     : 0x2000000000000000 bit 61
// RIPREL  : 0x4000000000000000 bit 62
// VSIB    : 0x8000000000000000 bit 63


//hi = (disp, base) => (disp & 0xffffffffn | ((base) & 0x30n ? ( (BigInt((base) == 0x20n) && (1n << 61n)) | (BigInt((base) == 0xfff0n) && (0x1n << 36n)) | BigInt((base & 0xfn) << 32n) ) : (0x1n << 60n) | ((base) & 0xfn) << 32n))


#define X64MEM_1_ARGS(base)                      (((base) & 0x30 ?																										( ((uint64_t) ((base) == $rip) ? ((uint64_t) 0x1 << 61) : 0) | ((uint64_t) ((base) == $riprel) ? ((uint64_t) 0x3 << 61) : 0) | ((uint64_t) ((base) == $none) ? ((uint64_t) 0x1 << 36) : 0) | ((uint64_t) ((base) & 0xf) << 32) ) :																										((uint64_t) 0x1 << 60) | (uint64_t) ((base) & 0xf) << 32) |																									(uint64_t) 0x10 << 40)
#define X64MEM_2_ARGS(base, disp)               (disp & 0xffffffff | X64MEM_1_ARGS(base))
#define X64MEM_3_ARGS(base, disp, index)        (disp & 0xffffffff | ((base) & 0x30 ?																										( ((uint64_t) ((base) == $rip) ? ((uint64_t) 0x1 << 61) : 0) | ((uint64_t) ((base) == $riprel) ? ((uint64_t) 0x3 << 61) : 0) | ((uint64_t) ((base) == $none) ? ((uint64_t) 0x1 << 36) : 0) | ((uint64_t) ((base) & 0xf) << 32) ) :																										((uint64_t) 0x1 << 60) | (uint64_t) ((base) & 0xf) << 32) |																									(uint64_t) ((index) == $none ? 0x10 : (index) & 0x80000F) << 40)
#define X64MEM_4_ARGS(base, disp, index, scale) (X64MEM_3_ARGS(base, disp, index) | (uint64_t) ((scale) <= 1 ? 0b00 : (scale) == 2 ? 0b01 : (scale) == 4 ? 0b10 : 0b11) << 48)
#define X64MEM_5_ARGS(base, disp, index, scale, segment) (disp & 0xffffffff	| ((base) & 0x30 ? /*If the operand is more than 32 bits wide or is equal to the RIP register, set mode to wide addressing and set base register, or RIP addressing*/			( ((uint64_t) ((base) == $rip) ? ((uint64_t) 0x1 << 61) : 0) | ((uint64_t) ((base) == $riprel) ? ((uint64_t) 0x3 << 61) : 0) | ((uint64_t) ((base) == $none) ? ((uint64_t) 0x1 << 36) : 0) | ((uint64_t) ((base) & 0xf) << 32) ) :			((uint64_t) 0x1 << 60) | (uint64_t) ((base) & 0xf) << 32)	| (uint64_t) ((index) == $none ? 0x10 : (index) & 0x80000F) << 40	| (uint64_t) ((scale) <= 1 ? 0b00 : (scale) == 2 ? 0b01 : (scale) == 4 ? 0b10 : 0b11) << 48	| (uint64_t) (((segment) - $rip) & (uint64_t) 0x7) << 56) /* minusing from $rip, because segment registers are 1 + their value for simplification. */

#define GET_4TH_ARG(arg1, arg2, arg3, arg4, arg5, arg6, ...) arg6
#define X64MEM_MACRO_CHOOSER(...)     GET_4TH_ARG(__VA_ARGS__, X64MEM_5_ARGS, X64MEM_4_ARGS, X64MEM_3_ARGS,                 X64MEM_2_ARGS, X64MEM_1_ARGS, )

#define x64mem(...) X64MEM_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

#define m8(...) X64OPERAND_CAST( M8, x64mem(__VA_ARGS__) )
#define m16(...) X64OPERAND_CAST( M16, x64mem(__VA_ARGS__) )
#define m32(...) X64OPERAND_CAST( M32, x64mem(__VA_ARGS__) )
#define m64(...) X64OPERAND_CAST( M64, x64mem(__VA_ARGS__) )
#define m128(...) X64OPERAND_CAST( M128, x64mem(__VA_ARGS__) )
#define m256(...) X64OPERAND_CAST( M256, x64mem(__VA_ARGS__) )
#define m512(...) X64OPERAND_CAST( M512, x64mem(__VA_ARGS__) )
#define mem(...) X64OPERAND_CAST( M8 | M16 | M32 | M64 | M128 | M256 | M512, x64mem(__VA_ARGS__) )

#ifdef __cplusplus 
extern "C" {
#endif

// Emits code and links rip relatives, labels, and jumps after.
uint8_t* x64as(const x64 p, uint32_t num, uint32_t* len);

// Emits 1 instruction.
uint32_t x64emit(const x64Ins* ins, uint8_t* opcode_dest);

// Stringifies the IR.
char* x64stringify(const x64 p, uint32_t num);

// Runs the assembled output.
void (*x64exec(void* mem, uint32_t size))();
void x64exec_free(void* buf, uint32_t size);

// Gets last emitted error code and string.
char* x64error(int* errcode);

#ifdef __cplusplus 
}
#endif
