#include "tests.h"
#include "parse.h"

#define HASH_H_IMPLEMENTATION
#include <hash.h>

TEST("Parse a number?") {
	struct RS_ParserState* state = parse("test1.rc", "123");
	assert(state != NULL);
	asserteq(state->ast[0].type, ST_EXPR);
	asserteq(state->ast[0].expr->type, EX_PRIM);
	assert(state->ast[0].expr->tok != NULL);
	asserteq(state->ast[0].expr->tok->type, TT_INT);
	asserteq(state->ast[0].expr->tok->intv, 123);
	asserteq(state->ast[0].expr->tok->len, 3);
	asserteq(state->ast[1].type, ST_EOF);
}

TEST("Parse \"return 0;\"") {
	struct RS_ParserState* state = parse("test2.rc", "return 0;");
	assert(state != NULL);
	asserteq(state->ast[0].type, ST_RETURN);
	asserteq(state->ast[0].ret->type, EX_PRIM);
	asserteq(state->ast[0].ret->tok - state->toks, 1);
	asserteq(state->ast[0].ret->tok->type, TT_INT);
	asserteq(state->ast[0].ret->tok->intv, 0);
	asserteq(state->ast[0].ret->tok->len, 1);
	asserteq(state->ast[1].type, ST_EOF);
}

TEST("Parse \"return 1 + 2;\"") {
	struct RS_ParserState* state = parse("test2.rc", "return 1 + 2;");
	assert(state != NULL);
	RS_Stmt* stmt = &state->ast[0];
	// printf("\ndebug: ");
	// debug_expr(stmt->ret);
	// puts("");
	asserteq(stmt->type, ST_RETURN);
	asserteq(stmt->ret->type, EX_REGULAR);
	asserteq(stmt->ret->tok - state->toks, 2);
	asserteq(stmt->ret->tok->type, TT_OPADD);
	asserteq(stmt->ret->first->type, EX_PRIM);
	asserteq(stmt->ret->first->tok - state->toks, 1);
	asserteq(stmt->ret->first->tok->type, TT_INT);
	asserteq(stmt->ret->first->tok->intv, 1);
	asserteq(stmt->ret->second->type, EX_PRIM);
	asserteq(stmt->ret->second->tok - state->toks, 3);
	asserteq(stmt->ret->second->tok->type, TT_INT);
	asserteq(stmt->ret->second->tok->intv, 2);
	asserteq(state->ast[1].type, ST_EOF);
	printf("\ndebug: ");
	debug_expr(stmt->ret);
}

TEST("Parse \"return 1 - 2 * 0;\"") {
	struct RS_ParserState* state = parse("test2.rc", "return 1 - 2 * 0;");
	assert(state != NULL);
	RS_Stmt* stmt = &state->ast[0];
	// printf("\ndebug: ");
	// debug_expr(stmt->ret);
	// puts("");
	asserteq(stmt->type, ST_RETURN);
	asserteq(stmt->ret->type, EX_REGULAR);
	asserteq(stmt->ret->tok - state->toks, 2);
	asserteq(stmt->ret->tok->type, TT_OPSUB);
	asserteq(stmt->ret->first->type, EX_PRIM);
	asserteq(stmt->ret->first->tok - state->toks, 1);
	asserteq(stmt->ret->first->tok->type, TT_INT);
	asserteq(stmt->ret->first->tok->intv, 1);
	asserteq(stmt->ret->second->type, EX_REGULAR);
	asserteq(stmt->ret->second->tok - state->toks, 4);
	asserteq(stmt->ret->second->tok->type, TT_OPMUL);
	asserteq(stmt->ret->second->first->type, EX_PRIM);
	asserteq(stmt->ret->second->first->tok - state->toks, 3);
	asserteq(stmt->ret->second->first->tok->type, TT_INT);
	asserteq(stmt->ret->second->first->tok->intv, 2);
	asserteq(stmt->ret->second->second->type, EX_PRIM);
	asserteq(stmt->ret->second->second->tok - state->toks, 5);
	asserteq(stmt->ret->second->second->tok->type, TT_INT);
	asserteq(stmt->ret->second->second->tok->intv, 0);
	asserteq(state->ast[1].type, ST_EOF);
}

TEST("Parse Problematic \"return 1 - 2 * 3 + 4 ^ 5 = 4\"") {
	struct RS_ParserState* state = parse("test2.rc", "return 1 - 2 * 3 + 4 ^ 5 = 4;");
	assert(state != NULL);
	RS_Stmt* stmt = &state->ast[0];
	// printf("\ndebug: ");
	// debug_expr(stmt->ret);
	// puts("");
	asserteq(stmt->type, ST_RETURN);
	asserteq(stmt->ret->type, EX_REGULAR);
	asserteq(stmt->ret->tok - state->toks, 10);
	asserteq(stmt->ret->tok->type, TT_OPSET);
	asserteq(stmt->ret->first->type, EX_REGULAR);
	asserteq(stmt->ret->first->tok - state->toks, 6);
	asserteq(stmt->ret->first->tok->type, TT_OPADD);
	asserteq(stmt->ret->first->first->type, EX_REGULAR);
	asserteq(stmt->ret->first->first->tok - state->toks, 2);
	asserteq(stmt->ret->first->first->tok->type, TT_OPSUB);
	asserteq(stmt->ret->first->first->first->type, EX_PRIM);
	asserteq(stmt->ret->first->first->first->tok - state->toks, 1);
	asserteq(stmt->ret->first->first->first->tok->type, TT_INT);
	asserteq(stmt->ret->first->first->first->tok->intv, 1);
	asserteq(stmt->ret->first->first->second->type, EX_REGULAR);
	asserteq(stmt->ret->first->first->second->tok - state->toks, 4);
	asserteq(stmt->ret->first->first->second->tok->type, TT_OPMUL);
	asserteq(stmt->ret->first->first->second->first->type, EX_PRIM);
	asserteq(stmt->ret->first->first->second->first->tok - state->toks, 3);
	asserteq(stmt->ret->first->first->second->first->tok->type, TT_INT);
	asserteq(stmt->ret->first->first->second->first->tok->intv, 2);
	asserteq(stmt->ret->first->first->second->second->type, EX_PRIM);
	asserteq(stmt->ret->first->first->second->second->tok - state->toks, 5);
	asserteq(stmt->ret->first->first->second->second->tok->type, TT_INT);
	asserteq(stmt->ret->first->first->second->second->tok->intv, 3);
	asserteq(stmt->ret->first->second->type, EX_REGULAR);
	asserteq(stmt->ret->first->second->tok - state->toks, 8);
	asserteq(stmt->ret->first->second->tok->type, TT_OPBXOR);
	asserteq(stmt->ret->first->second->first->type, EX_PRIM);
	asserteq(stmt->ret->first->second->first->tok - state->toks, 7);
	asserteq(stmt->ret->first->second->first->tok->type, TT_INT);
	asserteq(stmt->ret->first->second->first->tok->intv, 4);
	asserteq(stmt->ret->first->second->second->type, EX_PRIM);
	asserteq(stmt->ret->first->second->second->tok - state->toks, 9);
	asserteq(stmt->ret->first->second->second->tok->type, TT_INT);
	asserteq(stmt->ret->first->second->second->tok->intv, 5);
	asserteq(stmt->ret->second->type, EX_PRIM);
	asserteq(stmt->ret->second->tok - state->toks, 11);
	asserteq(stmt->ret->second->tok->type, TT_INT);
	asserteq(stmt->ret->second->tok->intv, 4);
	asserteq(state->ast[1].type, ST_EOF);
}

#include "tests_end.h"