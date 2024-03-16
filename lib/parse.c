#include <stdlib.h>

#define VEC_H_STATIC_INLINE
#include <vec.h>
#include "tok.h"
#include "parse.h"
#include "error.h"

#define error(...) error_at(st->src, st->toks[st->ind].place, st->file, __VA_ARGS__)

static void parse_stmt(struct RS_ParserState*);
static RS_Expr* parse_expr(struct RS_ParserState*);
static RS_Type* parse_type(struct RS_ParserState*);
static RS_FuncArg* parse_funcarg(struct RS_ParserState*);

struct RS_ParserState* parse(char* file, char* str) {
	RS_Token* toks = tokenize(str);

	if(vlast(toks)->type == TT_ERROR) {
		error_at(str, vlast(toks)->place, file, "%s", vlast(toks)->data);
		return NULL;
	}

	struct RS_ParserState* state = malloc(sizeof(struct RS_ParserState));
	*state = (struct RS_ParserState) {
		.ast = vnew(),
		.expressions = vnew(),
		.types = vnew(),

		.file = file,
		.src = str,
		.toks = toks,
		.ind = 0
	};

	while(state->toks[state->ind].type != TT_EOF) parse_stmt(state);
	vpush(state->ast, { .type = ST_EOF });
	return state;
}

static void parse_stmt(struct RS_ParserState* st) {
	switch(st->toks[st->ind++].type) {
		case TT_PSEMICOLON: return;
		case TT_KRETURN:
			vpush(st->ast, { .type = ST_RETURN, .ret = parse_expr(st) });
			return;
		default:
			st->ind--;
			vpush(st->ast, { .type = ST_EXPR, .expr = parse_expr(st) });
			return;
	}
}

static RS_Expr* parse_expr(struct RS_ParserState* st) {
	switch(st->toks[st->ind++].type) {
		case TT_POPENPAR: {
			RS_Expr* ret = parse_expr(st);
			if(st->toks[st->ind++].type != TT_PCLOSEPAR) error("Expected ')'");
			st->ind++;
			if(st->toks[st->ind].type == TT_POPENPAR) {
				vpush(st->expressions, { .type = EX_CALL, .func = ret, .args = vnew() });
				ret = vlast(st->expressions);
				// NOLINTNEXTLINE(bugprone-sizeof-expression)
				while(st->toks[st->ind].type != TT_PCLOSEPAR) vpush(ret->args, parse_expr(st));
			}
			return ret;
		}
		case TT_STRING:
		case TT_FLOAT:
		case TT_INT:
			vpush(st->expressions, { .type = EX_PRIM, .tok = st->ind - 1,  });
			return vlast(st->expressions);
		default: error("Unexpected token"); return NULL;
	}
}



static RS_Type* parse_type(struct RS_ParserState* st) {
	switch(st->toks[st->ind++].type) {
		default: error("Unexpected token"); return NULL;
	}
}

