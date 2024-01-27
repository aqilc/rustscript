#include "tests.h"
#include <tok.h>
#define HASH_H_IMPLEMENTATION
#include <hash.h>
#define VEC_H_IMPLEMENTATION
#include <vec.h>

TEST("Tokenize Empty String") {
	char* str = "";
	Token* tok = tokenize(str);
	asserteq(tok->type, TT_EOF);
	freetoks(tok);
}

TEST("Tokenize a single character: 'a'") {
  char* str = "a";
	Token* tok = tokenize(str);
	asserteq(tok->type, TT_IDENT);
	asserteq(tok->len, 1);
	asserteq(tok->data[0], 'a');
  asserteq(tok[1].type, TT_EOF);
	freetoks(tok);
}

TEST("Tokenize a main function: 'fn main() {}'") {
  char* str = "fn main() {}";
	Token* tok = tokenize(str);
	asserteq(tok->type, TT_KFN);
	asserteq(tok->len, 2);
	asserteq(tok->data[0], 'f');
	asserteq(tok->data[1], 'n');
	asserteq(tok->data[2], 0);
	asserteq(tok[1].type, TT_IDENT);
	asserteq(tok[1].len, 4);
	asserteq(tok[1].data[0],'m');
	asserteq(tok[1].data[1], 'a');
	asserteq(tok[1].data[2], 'i');
  asserteq(tok[1].data[3], 'n');
  asserteq(tok[2].type, TT_POPAR);
  asserteq(tok[3].type, TT_PCPAR);
  asserteq(tok[4].type, TT_POCBR);
  asserteq(tok[5].type, TT_PCCBR);
  asserteq(tok[6].type, TT_EOF);
  freetoks(tok);
}

#include "tests_end.h"
