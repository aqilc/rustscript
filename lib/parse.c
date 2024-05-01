#include <stdlib.h>

#define VEC_H_STATIC_INLINE
#include <vec.h>
#include "tok.h"
#include "parse.h"
#include "error.h"

#define error(...) error_at(st->src, st->toks[st->ind + 1].place, st->file, __VA_ARGS__)


enum RS_OpClass {
	OC_FORBIDDEN = 0,
	OC_POSTFIX /* -- ++ ?. . */,
	OC_UNARY /* ++ -- - + ~ ! */, OC_POW /* ** */, OC_BIT /* | & ^ << >> */,
	OC_MUL /* * / % */, OC_ADD /* + - */,
	OC_TERTIARY /* ?: */,
	OC_ASSIGN /* = += -= *= /= %= &= |= ^= <<= >>= */,
	OC_COMMA /* , */,
	OC_PAREN /* () */
};

static inline RS_Expr* new_expr(RS_Expr* ex) {
	return memcpy(malloc(sizeof(RS_Expr)), ex, sizeof(RS_Expr));
}

static void parse_stmt(struct RS_ParserState*);
static RS_Expr* parse_expr(struct RS_ParserState* st, enum RS_OpClass highest);
static RS_Type* parse_type(struct RS_ParserState*);
static RS_FuncArg* parse_funcarg(struct RS_ParserState*);
static void parse_check(struct RS_ParserState* st, RS_Expr* ex);
static RS_Token* expect(struct RS_ParserState* st, enum RS_TokenType type);


struct RS_ParserState* parse(char* file, char* str) {
	RS_Token* toks = tokenize(str);

	if(vlast(toks)->type == TT_ERROR) {
		error_at(str, vlast(toks)->place, file, "%s", vlast(toks)->data);
		return NULL;
	}

	struct RS_ParserState* state = malloc(sizeof(struct RS_ParserState));
	*state = (struct RS_ParserState) {
		.ast = vnew(),
		.types = vnew(),

		.file = file,
		.src = str,
		.toks = toks,
		.ind = 0,
		.errors = 0,
		.warnings = 0,
	};

	while(state->toks[state->ind].type != TT_EOF) parse_stmt(state);
	vpush(state->ast, { .type = ST_EOF });

	// vfor(state->expressions, expr)
	// 	parse_check(state, expr);
	
	return state;
}

static void parse_stmt(struct RS_ParserState* st) {
	switch(st->toks[st->ind++].type) {
		case TT_PSEMICOLON: return;
		case TT_KRETURN:
			vpush(st->ast, { .type = ST_RETURN, .ret = parse_expr(st, 0) });
			return;
		case TT_KLET:
			
			return;
		default:
			st->ind--;
			vpush(st->ast, { .type = ST_EXPR, .expr = parse_expr(st, 0) });
			return;
	}
}

struct {
	enum RS_OpClass prec[3];
	bool right_assoc;
} precedences[] = {
	[TT_OPADD]     = { { OC_FORBIDDEN, OC_ADD,       OC_FORBIDDEN } },
	[TT_OPSUB]     = { { OC_UNARY,     OC_ADD,       OC_FORBIDDEN } },
	[TT_OPMUL]     = { { OC_FORBIDDEN, OC_MUL,       OC_FORBIDDEN } },
	[TT_OPDIV]     = { { OC_FORBIDDEN, OC_MUL,       OC_FORBIDDEN } },
	[TT_OPMOD]     = { { OC_FORBIDDEN, OC_MUL,       OC_FORBIDDEN } },
	[TT_OPPOW]     = { { OC_FORBIDDEN, OC_POW,       OC_FORBIDDEN }, true },
	[TT_OPBXOR]    = { { OC_FORBIDDEN, OC_BIT,       OC_FORBIDDEN } },
	[TT_OPBOR]     = { { OC_FORBIDDEN, OC_BIT,       OC_FORBIDDEN } },
	[TT_OPBAND]    = { { OC_FORBIDDEN, OC_BIT,       OC_FORBIDDEN } },
	[TT_OPBSHR]    = { { OC_FORBIDDEN, OC_BIT,       OC_FORBIDDEN } },
	[TT_OPBSHL]    = { { OC_FORBIDDEN, OC_BIT,       OC_FORBIDDEN } },
	[TT_OPSET]     = { { OC_FORBIDDEN, OC_ASSIGN,    OC_FORBIDDEN } },
	[TT_OPADDSET]  = { { OC_FORBIDDEN, OC_ASSIGN,    OC_FORBIDDEN } },
	[TT_OPSUBSET]  = { { OC_FORBIDDEN, OC_ASSIGN,    OC_FORBIDDEN } },
	[TT_OPMULSET]  = { { OC_FORBIDDEN, OC_ASSIGN,    OC_FORBIDDEN } },
	[TT_OPDIVSET]  = { { OC_FORBIDDEN, OC_ASSIGN,    OC_FORBIDDEN } },
	[TT_OPMODSET]  = { { OC_FORBIDDEN, OC_ASSIGN,    OC_FORBIDDEN } },
	[TT_OPPOWSET]  = { { OC_FORBIDDEN, OC_ASSIGN,    OC_FORBIDDEN } },
	[TT_OPBXORSET] = { { OC_FORBIDDEN, OC_ASSIGN,    OC_FORBIDDEN } },
	[TT_OPBORSET]  = { { OC_FORBIDDEN, OC_ASSIGN,    OC_FORBIDDEN } },
	[TT_OPBANDSET] = { { OC_FORBIDDEN, OC_ASSIGN,    OC_FORBIDDEN } },
	[TT_OPBSHRSET] = { { OC_FORBIDDEN, OC_ASSIGN,    OC_FORBIDDEN } },
	[TT_OPBSHLSET] = { { OC_FORBIDDEN, OC_ASSIGN,    OC_FORBIDDEN } },
	[TT_OPDOT]     = { { OC_FORBIDDEN, OC_POSTFIX,   OC_FORBIDDEN } },
	[TT_OPQUESDOT] = { { OC_FORBIDDEN, OC_POSTFIX,   OC_FORBIDDEN } },
	[TT_OPQUES]    = { { OC_FORBIDDEN, OC_TERTIARY,  OC_FORBIDDEN } },
	[TT_OPINCR]    = { { OC_FORBIDDEN, OC_POSTFIX,   OC_FORBIDDEN } },
	[TT_OPDECR]    = { { OC_FORBIDDEN, OC_POSTFIX,   OC_FORBIDDEN } },

	[TT_POPENPAR]  = { { OC_PAREN,     OC_FORBIDDEN, OC_FORBIDDEN } },

	[TT_LNOT]      = { { OC_FORBIDDEN, OC_UNARY,     OC_FORBIDDEN } },
	[TT_LOR]       = { { OC_FORBIDDEN, OC_UNARY,     OC_FORBIDDEN } },
	[TT_LAND]      = { { OC_FORBIDDEN, OC_UNARY,     OC_FORBIDDEN } },
	// [TT_PCOLON] = { { OC_FORBIDDEN, OC_TERTIARY,  OC_FORBIDDEN } },
	[TT_ERROR]     = { { OC_FORBIDDEN, OC_FORBIDDEN, OC_FORBIDDEN } }, // Just to extend the array size to accomodate all tokens
};

/*
 * Parsing algorithm made using unrolled Recursive Descent Parsing
 * Example: 1 + 1
 *      EX_REG… --→  +
 *             ┌─────┴─────┐
 * EX_PRIM --→ 1           1
 *
 * Example: 1 + 1 * -2 * (3 + 4)
 *         +
 *     ┌───┴───┐
 *     1       *
 *         ┌───┴───┐
 *         *       +
 *       ┌─┴─┐   ┌─┴─┐
 *       1   -   3   4
 *           |
 *           2
 */
static RS_Expr* parse_expr(struct RS_ParserState* st, enum RS_OpClass highest) {
	int parens = 0;
	int depth = 0;
	static RS_Expr* curexpr[1000] = {};

primary:
	curexpr[depth] = new_expr(&(RS_Expr) {});
	curexpr[depth]->tok = st->toks + st->ind;
	if(depth) curexpr[depth - 1]->params[curexpr[depth - 1]->paramnum] = curexpr[depth];
	switch(st->toks[st->ind++].type) {
	case TT_IDENT:
	case TT_FLOAT:
	case TT_STRING:
	case TT_INT:
		curexpr[depth]->type = EX_PRIM;
		break;
	case TT_POPENPAR:
		parens ++;
	case TT_OPBNOT:
	case TT_OPSUB:
	case TT_OPADD:
		curexpr[depth]->type = EX_REGULAR;
		depth ++;
		curexpr[depth] = new_expr(&(RS_Expr) {});
		curexpr[depth - 1]->params[0] = curexpr[depth];
		goto primary;
	case TT_PSEMICOLON:
	case TT_EOF:
	case TT_PCLOSEPAR:
		error("Expected an expression here (got %s) (debug: resolving %s)", toktostr[st->toks[st->ind - 1].type], toktostr[curexpr[depth - 1]->tok->type]);
		return NULL;
	default: error("Unexpected token(got %s)", toktostr[st->toks[st->ind - 1].type]); return NULL;
	}

	RS_Token* op = st->toks + st->ind;

detectparens:
	if (op->type == TT_PSEMICOLON ||
			op->type == TT_EOF) {
		
		if(parens) {
			error("Statement ended in the middle of an expression.");
			return NULL;
		}

		return curexpr[0];
	} else if (op->type == TT_PCLOSEPAR) {
		if(parens) {

			while(depth > 1 && curexpr[depth - 1]->tok->type != TT_POPENPAR) depth --;
			depth --;
			parens --;
			op = st->toks + ++st->ind;
			
			if(depth > 0)
				curexpr[depth - 1]->params[curexpr[depth - 1]->paramnum] = curexpr[depth]->params[0];
			
			goto detectparens;
		}
		
		error("Unexpected closing parenthesis");
		return NULL;
	}

	// if(highest && precedences[op->type].prec[1] > highest) {
	// 	st->ind--;
	// 	return curexpr[0];
	// }

	// Go up the operator hierarchy chain, and swap the operator that has the higher precedence with the one that has lower precedence
	if(precedences[op->type].prec[1]) {
		st->ind++;

		RS_Expr* opexpr = new_expr(&(RS_Expr) {
			.type = EX_REGULAR,
			.tok = op,
			.paramnum = 1,
		});


		// If the operator is of a higher order than the current top operator, make it the new top operator
		if(!depth || (!parens && precedences[curexpr[0]->tok->type].prec[curexpr[0]->paramnum] <= precedences[op->type].prec[curexpr[0]->paramnum])) {
			opexpr->params[0] = curexpr[0];
			depth = 1;
			curexpr[0] = opexpr;
			goto primary;
		}

		// Already checked curexpr[0]
		while(depth > 1 &&
					precedences[curexpr[depth - 1]->tok->type].prec[curexpr[depth - 1]->paramnum] &&
					precedences[curexpr[depth - 1]->tok->type].prec[curexpr[depth - 1]->paramnum] <= precedences[op->type].prec[curexpr[depth - 1]->paramnum])
			depth --;
		
		opexpr->params[0] = curexpr[depth - 1]->params[curexpr[depth - 1]->paramnum];
		curexpr[depth - 1]->params[curexpr[depth - 1]->paramnum] = opexpr;

		curexpr[depth++] = opexpr;
		goto primary;
	}

	return curexpr[0];
}

// Prints out the tree for the expression.
void debug_expr(RS_Expr* ex) {
	if(!ex) return;
	if(ex->type == EX_REGULAR) {
		if(!ex->params[1]) {
			printf("(%s ", toktostr[ex->tok->type]);
			debug_expr(ex->params[0]);
			printf(")");
			return;
		}
		printf("(");
		debug_expr(ex->params[0]);
		printf(" %s ", toktostr[ex->tok->type]);
		debug_expr(ex->params[1]);
		printf(")");
	} else {
		printf("%lld", ex->tok->intv);
	}
}

// Checks types and assigns them to the expression.
static void parse_check(struct RS_ParserState* st, RS_Expr* ex) {
}



static RS_Type* parse_type(struct RS_ParserState* st) {
	switch(st->toks[st->ind++].type) {
		default: error("Unexpected token"); return NULL;
	}
}


static RS_Token* expect(struct RS_ParserState* st, enum RS_TokenType type) {
	if(st->toks[st->ind].type != type) {
		error("Expected %s, got %s", toktostr[type], toktostr[st->toks[st->ind].type]);
		return NULL;
	}
	return st->toks + st->ind++;
}

static RS_FuncArg* parse_funcarg(struct RS_ParserState* st) {
	switch(st->toks[st->ind++].type) {
		default: error("Unexpected token"); return NULL;
	}
}






