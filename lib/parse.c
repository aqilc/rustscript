#include <stdlib.h>

#define VEC_H_STATIC_INLINE
#include <vec.h>
#include "tok.h"
#include "parse.h"
#include "error.h"

#define error(...) error_at(st->src, st->toks[st->ind].place, st->file, __VA_ARGS__)

static void parse_stmt(struct RS_ParserState*);
static RS_Expr* parse_expr(struct RS_ParserState* st);
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

enum OP_CLASSES {
	FORBIDDEN = 0,
	POSTFIX = 1 /* -- ++ ?. . */,
	UNARY = 2 /* ++ -- - + ~ ! */, POW = 3 /* ** */, BIT = 4 /* | & ^ << >> */,
	MUL = 5 /* * / % */, ADD = 6 /* + - */,
	TERTIARY = 7 /* ?: */,
	ASSIGN = 8 /* = += -= *= /= %= &= |= ^= <<= >>= */,
	COMMA = 9 /* , */,
};

struct {
	char prec;
} precedences[] = {
	[TT_OPADD] = { ADD },
	[TT_OPSUB] = { ADD },
	[TT_OPMUL] = { MUL },
	[TT_OPDIV] = { MUL },
	[TT_OPMOD] = { MUL },
	[TT_OPPOW] = { BIT },
	[TT_OPBXOR] = { BIT },
	[TT_OPBOR] = { BIT },
	[TT_OPBAND] = { BIT },
	[TT_OPBSHIFTRIGHT] = { BIT },
	[TT_OPBSHIFTLEFT] = { BIT },
	[TT_OPSET] = { ASSIGN },
	[TT_OPADDSET] = { ASSIGN },
	[TT_OPSUBSET] = { ASSIGN },
	[TT_OPMULSET] = { ASSIGN },
	[TT_OPDIVSET] = { ASSIGN },
	[TT_OPMODSET] = { ASSIGN },
	[TT_OPPOWSET] = { ASSIGN },
	[TT_OPBXORSET] = { ASSIGN },
	[TT_OPBORSET] = { ASSIGN },
	[TT_OPBANDSET] = { ASSIGN },
	[TT_OPBSHIFTRIGHTSET] = { ASSIGN },
	[TT_OPBSHIFTLEFTSET] = { ASSIGN },
	[TT_OPDOT] = { POSTFIX },
	[TT_OPQUESDOT] = { POSTFIX },
	[TT_OPQUES] = { TERTIARY },
	[TT_OPINCR] = { POSTFIX },
	[TT_OPDECR] = { POSTFIX },

	[TT_LNOT] = { UNARY },
	[TT_LOR] = { UNARY },
	[TT_LAND] = { UNARY },
	// [TT_PCOLON] = { TERTIARY },
	[TT_ERROR] = { FORBIDDEN }, // Just to extend the array size to accomodate all tokens
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
static RS_Expr* parse_expr(struct RS_ParserState* st) {
	vpush(st->expressions, {});
	int parens = 0;
	RS_Expr** curexpr = vnew();
	RS_Expr* topexpr = vlast(st->expressions); // Always the highest order expression
	RS_Expr* prim = topexpr;


	#define RESET_PARENT() \
		if(vlen(curexpr)) {\
			if(curexpr[vlen(curexpr) - 1]->first)\
				curexpr[vlen(curexpr) - 1]->second = prim;\
			else curexpr[vlen(curexpr) - 1]->first = prim;\
		}

primary:
	prim->tok = st->toks + st->ind;
	switch(st->toks[st->ind++].type) {
	case TT_IDENT:
		prim->type = EX_VAR;
		RESET_PARENT()
		break;
	case TT_FLOAT:
	case TT_STRING:
	case TT_INT:
		prim->type = EX_PRIM;
		RESET_PARENT()
		break;
	case TT_OPBNOT:
	case TT_OPSUB:
	case TT_OPADD:
		vpush(curexpr, 0);
		curexpr[vlen(curexpr) - 1]->type = EX_REGULAR;
		curexpr[vlen(curexpr) - 1]->tok = st->toks + st->ind - 1;
		goto primary;
	case TT_POPENPAR:;
		parens ++;
		// Idea: Maintain a stack for parent expressions, with the top of the stack being the first `out`, and then preceeding stack entries being the "more current" sub-expression.
		// *parens++;
		// prim = parse_expr(st, parens);
		// if(st->toks[st->ind++].type != TT_PCLOSEPAR) vpop(st->expressions), error("Expected ')'");
		// *parens--;
		// RESET_PARENT()
		break;
	case TT_PSEMICOLON:
	case TT_EOF:
	case TT_PCLOSEPAR:
		error("Expected an expression here");
		// error("Expected an expression here (got %s)", toktype(st->toks[st->ind - 1].type));
		return NULL;
	default: error("Unexpected token"); return NULL;
	}

	RS_Token* op = st->toks + st->ind;

	if (op->type == TT_PSEMICOLON ||
			op->type == TT_EOF) {
		if(parens) {
			error("Statement ended in the middle of an expression.");
			return NULL;
		}
		vfree(curexpr);
		return topexpr;
	}

	if(precedences[op->type].prec) {
		st->ind++;
		
		vpusharr(st->expressions, {{}, {}});

		RS_Expr* opexpr = vlast(st->expressions) - 1;
		opexpr->type = EX_REGULAR;
		opexpr->tok = op;

		RS_Expr* tempprim = prim;
		prim = vlast(st->expressions);

		if(vlen(curexpr)) {

			// If the operator is of a higher order than the current top operator, make it the new top operator
			if(precedences[op->type].prec >= precedences[topexpr->tok->type].prec) {
				vempty(curexpr);
				vpush(curexpr, opexpr);
				opexpr->first = topexpr;
				topexpr = opexpr;
				goto primary;
			}


			u32 curexprind = vlen(curexpr) - 1;
			while(curexprind > 0 &&
						precedences[curexpr[curexprind]->tok->type].prec &&
						precedences[curexpr[curexprind]->tok->type].prec <= precedences[op->type].prec)
				curexprind --, vpop(curexpr);
			
			opexpr->first = curexpr[curexprind]->second;
			curexpr[curexprind]->second = opexpr;

			vpush(curexpr, opexpr);
			goto primary;
		}

		vpush(curexpr, opexpr);
		opexpr->first = tempprim;
		topexpr = opexpr;
		goto primary;
	}

	vfree(curexpr);
	return topexpr;
}

// Prints out the tree for the expression
void debug_expr(RS_Expr* ex) {
	if(!ex) return;
	if(ex->type == EX_REGULAR) {
		printf("(");
		debug_expr(ex->first);
		printf(" %s ", toktostr[ex->tok->type]);
		debug_expr(ex->second);
		printf(")");
	} else {
		printf("%lld", ex->tok->intv);
	}
}

// Checks types and assigns them to the expression.
static bool parse_check(RS_Expr* ex) {
	// if()
	return true;
}



static RS_Type* parse_type(struct RS_ParserState* st) {
	switch(st->toks[st->ind++].type) {
		default: error("Unexpected token"); return NULL;
	}
}

