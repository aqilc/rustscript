#include "util.h"

typedef enum RS_TokenType RS_TokenType;
typedef struct Token Token;

enum RS_TokenType {
	TT_KRETURN, TT_KLET, TT_KCONST, TT_KIF, TT_KELSE, TT_KFN, TT_KSTRUCT, TT_KTRAIT,
	
	TT_TU32, TT_TU8, TT_TU16, TT_TI32, TT_TI8, TT_TI16, TT_TBOOL,
	
	TT_POCBR, TT_PCCBR, TT_POPAR, TT_PCPAR, TT_POSBR, TT_PCSBR,
	
	TT_OPADD, TT_OPSUB, TT_OPMUL, TT_OPDIV, TT_OPMOD, TT_OPSET, // basic operations
	TT_OPADDSET, TT_OPSUBSET, TT_OPMULSET, TT_OPDIVSET, TT_OPMODSET, // operations with assignment
	TT_OPSHIFTRIGHT, TT_OPSHIFTLEFT, // bitshifts
	TT_OPXOR, TT_OPAND, TT_OPOR, // bitwise operations
	TT_OPPOW, // power
	TT_OPINCR, TT_OPDECR, // Increment and decrement
	TT_OPGREATER, TT_OPLESS, TT_OPEQ, TT_OPGREATEQ, TT_OPLESSEQ, TT_OPNOTEQ, // Comparisons

	TT_IDENT, TT_INT, TT_FLOAT,

	TT_EOF, TT_ERROR
};
struct Token {
	RS_TokenType type;
	char* data;
	u32 place;
	u32 len;
};

Token* tokenize(char* source);
void freetoks(Token* tok);
