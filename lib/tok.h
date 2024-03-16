#pragma once
#include <stdbool.h>
#include "util.h"


enum RS_TokenType {
	TT_KRETURN = 1, TT_KLET, TT_KCONST, TT_KIF, TT_KELSE, TT_KFN, TT_KSTRUCT, TT_KTRAIT,
	
	TT_POPENCBR, TT_PCLOSECBR, TT_POPENPAR, TT_PCLOSEPAR, TT_POPENSQBR, TT_PCLOSESQBR,
		TT_PARROW, TT_PCOMMA, TT_PSEMICOLON,
	
	TT_LAND, TT_LOR, TT_LTERNARY, TT_LNOT, // Logic
	TT_CGREATER, TT_CLESS, TT_CEQ, TT_CGREATEQ, TT_CLESSEQ, TT_CNOTEQ, // Comparisons

	TT_DNUOPSTART, // DO NOT USE, this represents the start of operator tokens to make it easy to check if a taken is an operator!

	// THESE MUST BE KEPT IN ORDER, THE ASSIGNMENT OPERATIONS MUST BE 13 ABOVE THEIR NORMAL COUNTERPARTS.
	TT_OPSET, TT_OPADD, TT_OPSUB, TT_OPMUL, TT_OPDIV, TT_OPMOD, TT_OPPOW, // basic operations
	TT_OPBXOR, TT_OPBOR, TT_OPBAND, TT_OPBNOT, // bitwise operations
	TT_OPBSHIFTRIGHT, TT_OPBSHIFTLEFT, // bitshifts
	TT_OPADDSET, TT_OPSUBSET, TT_OPMULSET, TT_OPDIVSET, TT_OPMODSET, TT_OPPOWSET,
		TT_OPBXORSET, TT_OPBORSET, TT_OPBANDSET, TT_OPBNOTSET, TT_OPBSHIFTRIGHTSET, TT_OPBSHIFTLEFTSET, // operations with assignment

	TT_OPDOT, TT_OPCOLON,
	TT_OPINCR, TT_OPDECR, // Increment and decrement
	
	TT_DNUOPEND, // DO NOT USE, this represents the end of operator tokens to make it easy to check if a taken is an operator!

	TT_TU8, TT_TU16, TT_TU32, TT_TU64, TT_TI8, TT_TI16, TT_TI32, TT_TI64,
		TT_TBOOL,

	TT_IDENT, TT_INT, TT_FLOAT, TT_STRING,

	TT_EOF, TT_ERROR
};
typedef enum RS_TokenType RS_TokenType;

struct RS_Token {
	union {
		char* data;
		u64 intv;
		double floatv;
	};
	u32 place;
	u32 len;
	RS_TokenType type;
};
typedef struct RS_Token RS_Token;

static inline const bool isop(RS_TokenType type) {
	return type > TT_DNUOPSTART && type < TT_DNUOPEND;
}

RS_Token* tokenize(char* source);
void freetoks(RS_Token* tok);
