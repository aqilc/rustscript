#include "tests.h"
#include "parse.h"

#define HASH_H_IMPLEMENTATION
#include <hash.h>

TEST("Parse a number?") {
	struct RS_ParserState* state = parse("test1.rc", "123");
	assert(state != NULL);
	expecteq(state->ast[0].type, ST_EXPR);
	expecteq(state->ast[0].expr->type, EX_PRIM);
	assert(state->ast[0].expr->tok != NULL);
	expecteq(state->ast[0].expr->tok->type, TT_INT);
	expecteq(state->ast[0].expr->tok->intv, 123);
	expecteq(state->ast[0].expr->tok->len, 3);
	expecteq(state->ast[1].type, ST_EOF);
}

TEST("Parse \"return 0;\"") {
	struct RS_ParserState* state = parse("test2.rc", "return 0;");
	assert(state != NULL);
	expecteq(state->ast[0].type, ST_RETURN);
	expecteq(state->ast[0].ret->type, EX_PRIM);
	expecteq(state->ast[0].ret->tok - state->toks, 1);
	expecteq(state->ast[0].ret->tok->type, TT_INT);
	expecteq(state->ast[0].ret->tok->intv, 0);
	expecteq(state->ast[0].ret->tok->len, 1);
	expecteq(state->ast[1].type, ST_EOF);
}

TEST("Parse \"return 1 + -2;\"") {
	struct RS_ParserState* state = parse("test2.rc", "return 1 + -2;");
	assert(state != NULL);
	RS_Stmt* stmt = &state->ast[0];
	// printf("\ndebug: ");
	// debug_expr(stmt->ret);
	// puts("");
	expecteq(stmt->type, ST_RETURN);
	expecteq(stmt->ret->type, EX_REGULAR);
	expecteq(stmt->ret->tok - state->toks, 2);
	expecteq(stmt->ret->tok->type, TT_OPADD);
	expecteq(stmt->ret->params[0]->type, EX_PRIM);
	expecteq(stmt->ret->params[0]->tok - state->toks, 1);
	expecteq(stmt->ret->params[0]->tok->type, TT_INT);
	expecteq(stmt->ret->params[0]->tok->intv, 1);
	expecteq(stmt->ret->params[1]->type, EX_PRIM);
	expecteq(stmt->ret->params[1]->tok - state->toks, 3);
	expecteq(stmt->ret->params[1]->tok->type, TT_INT);
	expecteq(stmt->ret->params[1]->tok->intv, -2);
	expecteq(state->ast[1].type, ST_EOF);
}

TEST("Parse \"return 1 - 2 * 0;\"") {
	struct RS_ParserState* state = parse("test2.rc", "return 1 - 2 * 0;");
	assert(state != NULL);
	RS_Stmt* stmt = &state->ast[0];
	// printf("\ndebug: ");
	// debug_expr(stmt->ret);
	// puts("");
	expecteq(stmt->type, ST_RETURN);
	expecteq(stmt->ret->type, EX_REGULAR);
	expecteq(stmt->ret->tok - state->toks, 2);
	expecteq(stmt->ret->tok->type, TT_OPSUB);
	expecteq(stmt->ret->params[0]->type, EX_PRIM);
	expecteq(stmt->ret->params[0]->tok - state->toks, 1);
	expecteq(stmt->ret->params[0]->tok->type, TT_INT);
	expecteq(stmt->ret->params[0]->tok->intv, 1);
	expecteq(stmt->ret->params[1]->type, EX_REGULAR);
	expecteq(stmt->ret->params[1]->tok - state->toks, 4);
	expecteq(stmt->ret->params[1]->tok->type, TT_OPMUL);
	expecteq(stmt->ret->params[1]->params[0]->type, EX_PRIM);
	expecteq(stmt->ret->params[1]->params[0]->tok - state->toks, 3);
	expecteq(stmt->ret->params[1]->params[0]->tok->type, TT_INT);
	expecteq(stmt->ret->params[1]->params[0]->tok->intv, 2);
	expecteq(stmt->ret->params[1]->params[1]->type, EX_PRIM);
	expecteq(stmt->ret->params[1]->params[1]->tok - state->toks, 5);
	expecteq(stmt->ret->params[1]->params[1]->tok->type, TT_INT);
	expecteq(stmt->ret->params[1]->params[1]->tok->intv, 0);
	expecteq(state->ast[1].type, ST_EOF);
}

TEST("Parse Problematic \"return 1 - 2 * 3 + 4 ^ 5 = 4\"") {
	struct RS_ParserState* state = parse("test2.rc", "return 1 - 2 * 3 + 4 ^ 5 = 6;");
	assert(state != NULL);
	RS_Stmt* stmt = &state->ast[0];
	// printf("\ndebug: ");
	// debug_expr(stmt->ret);
	// puts("");
	expecteq(stmt->type, ST_RETURN);
	expecteq(stmt->ret->type, EX_REGULAR);
	expecteq(stmt->ret->tok - state->toks, 10);
	expecteq(stmt->ret->tok->type, TT_OPSET);
	expecteq(stmt->ret->params[0]->type, EX_REGULAR);
	expecteq(stmt->ret->params[0]->tok - state->toks, 6);
	expecteq(stmt->ret->params[0]->tok->type, TT_OPADD);
	expecteq(stmt->ret->params[0]->params[0]->type, EX_REGULAR);
	expecteq(stmt->ret->params[0]->params[0]->tok - state->toks, 2);
	expecteq(stmt->ret->params[0]->params[0]->tok->type, TT_OPSUB);
	expecteq(stmt->ret->params[0]->params[0]->params[0]->type, EX_PRIM);
	expecteq(stmt->ret->params[0]->params[0]->params[0]->tok - state->toks, 1);
	expecteq(stmt->ret->params[0]->params[0]->params[0]->tok->type, TT_INT);
	expecteq(stmt->ret->params[0]->params[0]->params[0]->tok->intv, 1);
	expecteq(stmt->ret->params[0]->params[0]->params[1]->type, EX_REGULAR);
	expecteq(stmt->ret->params[0]->params[0]->params[1]->tok - state->toks, 4);
	expecteq(stmt->ret->params[0]->params[0]->params[1]->tok->type, TT_OPMUL);
	expecteq(stmt->ret->params[0]->params[0]->params[1]->params[0]->type, EX_PRIM);
	expecteq(stmt->ret->params[0]->params[0]->params[1]->params[0]->tok - state->toks, 3);
	expecteq(stmt->ret->params[0]->params[0]->params[1]->params[0]->tok->type, TT_INT);
	expecteq(stmt->ret->params[0]->params[0]->params[1]->params[0]->tok->intv, 2);
	expecteq(stmt->ret->params[0]->params[0]->params[1]->params[1]->type, EX_PRIM);
	expecteq(stmt->ret->params[0]->params[0]->params[1]->params[1]->tok - state->toks, 5);
	expecteq(stmt->ret->params[0]->params[0]->params[1]->params[1]->tok->type, TT_INT);
	expecteq(stmt->ret->params[0]->params[0]->params[1]->params[1]->tok->intv, 3);
	expecteq(stmt->ret->params[0]->params[1]->type, EX_REGULAR);
	expecteq(stmt->ret->params[0]->params[1]->tok - state->toks, 8);
	expecteq(stmt->ret->params[0]->params[1]->tok->type, TT_OPBXOR);
	expecteq(stmt->ret->params[0]->params[1]->params[0]->type, EX_PRIM);
	expecteq(stmt->ret->params[0]->params[1]->params[0]->tok - state->toks, 7);
	expecteq(stmt->ret->params[0]->params[1]->params[0]->tok->type, TT_INT);
	expecteq(stmt->ret->params[0]->params[1]->params[0]->tok->intv, 4);
	expecteq(stmt->ret->params[0]->params[1]->params[1]->type, EX_PRIM);
	expecteq(stmt->ret->params[0]->params[1]->params[1]->tok - state->toks, 9);
	expecteq(stmt->ret->params[0]->params[1]->params[1]->tok->type, TT_INT);
	expecteq(stmt->ret->params[0]->params[1]->params[1]->tok->intv, 5);
	expecteq(stmt->ret->params[1]->type, EX_PRIM);
	expecteq(stmt->ret->params[1]->tok - state->toks, 11);
	expecteq(stmt->ret->params[1]->tok->type, TT_INT);
	expecteq(stmt->ret->params[1]->tok->intv, 6);
	expecteq(state->ast[1].type, ST_EOF);
}

TEST("Parse Parenthesis \"return 1 + (2 - (3 >> (4) + 5))\"") {
	struct RS_ParserState* state = parse("test2.rc", "return 1 + (2 - (3 >> (4) + 5));");
	assert(state != NULL);
	RS_Stmt* stmt = &state->ast[0];
	printf("\ndebug: ");
	debug_expr(stmt->ret);
	puts("");
	expecteq(stmt->type, ST_RETURN);
	expecteq(stmt->ret->type, EX_REGULAR);
	expecteq(stmt->ret->tok - state->toks, 2);
	expecteq(stmt->ret->tok->type, TT_OPADD);
	expecteq(stmt->ret->params[0]->type, EX_PRIM);
	expecteq(stmt->ret->params[0]->tok - state->toks, 1);
	expecteq(stmt->ret->params[0]->tok->type, TT_INT);
	expecteq(stmt->ret->params[0]->tok->intv, 1);
	expecteq(stmt->ret->params[1]->type, EX_REGULAR);
	expecteq(stmt->ret->params[1]->tok - state->toks, 6);
	expecteq(stmt->ret->params[1]->tok->type, TT_OPSUB);
	expecteq(stmt->ret->params[1]->params[0]->type, EX_PRIM);
	expecteq(stmt->ret->params[1]->params[0]->tok - state->toks, 4);
	expecteq(stmt->ret->params[1]->params[0]->tok->type, TT_INT);
	expecteq(stmt->ret->params[1]->params[0]->tok->intv, 2);
	expecteq(stmt->ret->params[1]->params[1]->type, EX_REGULAR);
	expecteq(stmt->ret->params[1]->params[1]->tok - state->toks, 8);
	expecteq(stmt->ret->params[1]->params[1]->tok->type, TT_OPBSHIFTLEFT);
	expecteq(stmt->ret->params[1]->params[1]->params[0]->type, EX_PRIM);
	expecteq(stmt->ret->params[1]->params[1]->params[0]->tok - state->toks, 7);
	expecteq(stmt->ret->params[1]->params[1]->params[0]->tok->type, TT_INT);
	expecteq(stmt->ret->params[1]->params[1]->params[0]->tok->intv, 3);
	expecteq(stmt->ret->params[1]->params[1]->params[1]->type, EX_REGULAR);
	expecteq(stmt->ret->params[1]->params[1]->params[1]->tok - state->toks, 10);
	expecteq(stmt->ret->params[1]->params[1]->params[1]->tok->type, TT_OPBSHIFTRIGHT);
	expecteq(stmt->ret->params[1]->params[1]->params[1]->params[0]->type, EX_PRIM);
	expecteq(stmt->ret->params[1]->params[1]->params[1]->params[0]->tok - state->toks, 9);
	expecteq(stmt->ret->params[1]->params[1]->params[1]->params[0]->tok->type, TT_INT);
	expecteq(stmt->ret->params[1]->params[1]->params[1]->params[0]->tok->intv, 4);
	expecteq(state->ast[1].type, ST_EOF);
}

#include "tests_end.h"
