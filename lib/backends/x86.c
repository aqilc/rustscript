#define VEC_H_STATIC_INLINE
#include <vec.h>
#include <hash.h>
#include "../parse.h"
#include "../asm/asm_x86.h"
#include "x86.h"

struct x86State {
	u32 ind;
	struct RS_ParserState* st;
	x64Ins* code;
};

static void parse_expr(struct x86State* st, RS_Expr* node);
static void parse_stmt(struct x86State* st);

RS_MachineResult x86_machine(struct RS_ParserState* st) {
	struct x86State state = { .st = st, .ind = 0, .code = vnew() };

	while(st->ast[state.ind].type != ST_EOF) parse_stmt(&state);

	u32 len;
	return (RS_MachineResult) { x64as(state.code, &len), len };
}

char* x86_asm(struct RS_ParserState* st) {
	struct x86State state = { .st = st, .code = vnew() };
	return x64stringify(state.code);
}

static void parse_stmt(struct x86State* st) {
	switch(st->st->ast[st->ind++].type) {
		case ST_RETURN:
			parse_expr(st, st->st->ast[st->ind - 1].ret);
			vpush(st->code, (x64Ins) {RET});
			return;
		case ST_EXPR:
			parse_expr(st, st->st->ast[st->ind - 1].expr);
			return;
		case ST_EOF:
			vpush(st->code, (x64Ins) {RET});
			return;
		default: return;
	}
}

static void parse_expr(struct x86State* st, RS_Expr* node) {
	switch(node->type) {
		case EX_PRIM:
			switch(node->tok->type) {
				case TT_INT:
					vpush(st->code, (x64Ins) {MOV, rax, imm(node->tok->intv)});
					return;
				default:
					return;
			}
			return;
		default:
			return;
	}
}
