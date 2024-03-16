#include "tests.h"
#include "parse.h"

#define HASH_H_IMPLEMENTATION
#include <hash.h>

TEST("Parse a number?") {
	struct RS_ParserState* state = parse("test1.rc", "123");
	assert(state != NULL);
	asserteq(state->ast[0].type, ST_EXPR);
	asserteq(state->ast[0].expr->type, EX_PRIM);
	asserteq(state->ast[0].expr->tok, 0);
	asserteq(state->toks[state->ast[0].expr->tok].type, TT_INT);
	asserteq(state->toks[state->ast[0].expr->tok].intv, 123);
	asserteq(state->toks[state->ast[0].expr->tok].len, 3);
	asserteq(state->ast[1].type, ST_EOF);
}

TEST("Parse \"return 0;\"") {
	struct RS_ParserState* state = parse("test2.rc", "return 0;");
	assert(state != NULL);
	asserteq(state->ast[0].type, ST_RETURN);
	asserteq(state->ast[0].ret->type, EX_PRIM);
	asserteq(state->ast[0].ret->tok, 1);
	asserteq(state->toks[state->ast[0].ret->tok].type, TT_INT);
	asserteq(state->toks[state->ast[0].ret->tok].intv, 0);
	asserteq(state->toks[state->ast[0].ret->tok].len, 1);
	asserteq(state->ast[1].type, ST_EOF);
}

#include "tests_end.h"