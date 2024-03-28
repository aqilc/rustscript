#pragma once
#include "util.h"
#include <hash.h>
#include <stdbool.h>
#include "tok.h"
typedef struct RS_Stmt RS_Stmt;
typedef struct RS_Type RS_Type;
typedef struct RS_Expr RS_Expr;


enum RS_TypeT {
	TY_U8, TY_U16, TY_U32, TY_U64,
	TY_I8, TY_I16, TY_I32, TY_I64,
	TY_BOOL
};

struct RS_Type {
	u32 tok; // TT_TX
	bool isptr;
	bool signedness;
};

struct RS_FuncArg { RS_Type type; char* name; };
typedef struct RS_FuncArg RS_FuncArg;

enum RS_ExprT { EX_CALL = 1, EX_REGULAR, EX_PRIM, EX_VAR };
typedef enum RS_ExprT RS_ExprT;

enum RS_StmtT { ST_EXPR = 1, ST_DECLARE, ST_RETURN, ST_IF, ST_ELSE, ST_WHILE, ST_FUNC, ST_EOF };
typedef enum RS_StmtT RS_StmtT;



struct RS_Variable {
	bool vcons;
	char* vname;
	RS_Expr* value;
}; // RS_Declare

struct RS_Scope {
	ht(char*, struct RS_Variable*) vars;
};


struct RS_Expr {
	RS_Token* tok; // TT_OPX
	RS_ExprT type;
	union {
		struct {
			RS_Expr* first;
			RS_Expr* second;
			RS_Expr* third;
		}; // Binary
		struct {
			RS_Expr* func;
			RS_Expr** args;
		}; // Call
	};
};


struct RS_Stmt {
	RS_StmtT type;
	union {
		struct {
			RS_Expr* ret;
		}; // RS_Return
		struct {
			RS_Expr* expr;
		}; // RS_Expr
		struct {
			RS_Expr* cond;
			RS_Stmt* body;
		}; // RS_If, RS_Else, RS_While
		struct {
			char* fname;
			RS_FuncArg* fargs;
			RS_Stmt* fvars;
			RS_Stmt* fbody;
		}; // RS_Func
	};
};

struct RS_ParserState {
	RS_Stmt* ast;
	RS_Expr* expressions;
	RS_Type* types;

	RS_Stmt* scope;

	char* file;
	char* src;
	RS_Token* toks;
	u32 ind;
};

typedef RS_Stmt* AST;

struct RS_ParserState* parse(char* file, char* str);
void debug_expr(RS_Expr* ex);
// void free_ast(AST ast);