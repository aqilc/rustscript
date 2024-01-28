#include "tests.h"
#include <tok.h>
#define HASH_H_IMPLEMENTATION
#include <hash.h>
#define VEC_H_IMPLEMENTATION
#include <vec.h>

TEST("Tokenize Empty String") {
	char* str = "";
	RS_Token* tok = tokenize(str);
	asserteq(tok->type, TT_EOF);
	freetoks(tok);
}

TEST("Tokenize a single character: 'a'") {
  char* str = "a";
	RS_Token* tok = tokenize(str);
	asserteq(tok->type, TT_IDENT);
	asserteq(tok->len, 1);
	asserteq(tok->data[0], 'a');
  asserteq(tok[1].type, TT_EOF);
	freetoks(tok);
}

TEST("Tokenize integers: '1234567890 1234'") {
    char* str = "1234567890 1234";
	RS_Token* tok = tokenize(str);
	asserteq(tok->type, TT_INT);
	asserteq(tok->len, 10);
	asserteq(tok->data[0], '1');
	asserteq(tok->data[9], '0');
  asserteq(tok[1].type, TT_INT);
  asserteq(tok[1].data[0], '1');
  asserteq(tok[1].data[3], '4');
  asserteq(tok[2].type, TT_EOF);
	freetoks(tok);
}

TEST("Tokenize a string: '\"Hello World\"'") {
  char* str = "\"Hello World\"";
	RS_Token* tok = tokenize(str);
	asserteq(tok->type, TT_STRING);
	asserteq(tok->len, 13);
	asserteq(tok->data[0], '"');
	asserteq(tok->data[13], '"');
  asserteq(tok[1].type, TT_EOF);
	freetoks(tok);
}


TEST("Tokenize a main function: 'fn main() {}'") {
  char* str = "fn main() {}";
	RS_Token* tok = tokenize(str);
	asserteq(tok->type, TT_KFN);
	asserteq(tok->len, 2);
  assertstrs(tok->data, "fn");
	asserteq(tok->data[2], 0);
	asserteq(tok[1].type, TT_IDENT);
	asserteq(tok[1].len, 4);
	assertstrs(tok[1].data, "main");
  asserteq(tok[2].type, TT_POPENPAR);
  asserteq(tok[3].type, TT_PCLOSEPAR);
  asserteq(tok[4].type, TT_POPENCBR);
  asserteq(tok[5].type, TT_PCLOSECBR);
  asserteq(tok[6].type, TT_EOF);
  freetoks(tok);
}

#include "tests_end.h"
