#include "tests.h"
#include <tok.h>
#define HASH_H_IMPLEMENTATION
#include <hash.h>
#define VEC_H_IMPLEMENTATION
#include <vec.h>

TEST("Tokenize Empty String") {
	char* str = "";
	RS_Token* tok = tokenize(str);
	asserteq(tok[0].type, TT_EOF);
	freetoks(tok);
}

TEST("Tokenize a single character: 'a'") {
  char* str = "a";
	RS_Token* tok = tokenize(str);
	asserteq(tok[0].type, TT_IDENT);
	asserteq(tok[0].len, 1);
	asserteq(tok[0].data[0], 'a');
  asserteq(tok[1].type, TT_EOF);
	freetoks(tok);
}

TEST("Tokenize integers: '1234567890 1234'") {
    char* str = "1234567890 1234";
	RS_Token* tok = tokenize(str);
	asserteq(tok[0].type, TT_INT);
	asserteq(tok[0].len, 10);
	assertstreq(tok[0].data, "1234567890");
  asserteq(tok[1].type, TT_INT);
	assertstreq(tok[1].data, "1234");
  asserteq(tok[2].type, TT_EOF);
	freetoks(tok);
}

TEST("Tokenize a string: '\"Hello World\"'") {
  char* str = "\"Hello World\"";
	RS_Token* tok = tokenize(str);
	asserteq(tok[0].type, TT_STRING);
	asserteq(tok[0].len, 13);
  assertstreq(tok[0].data, "\"Hello World\"");
  asserteq(tok[1].type, TT_EOF);
	freetoks(tok);
}

TEST("Tokenize Operators: '+ - * / += <<= => == != a.b'") {
	char* str = "+ - * / += <<= => == != a.b";
	RS_Token* tok = tokenize(str);
	asserteq(tok[0].type, TT_OPADD);
	asserteq(tok[1].type, TT_OPSUB);
	asserteq(tok[2].type, TT_OPMUL);
	asserteq(tok[3].type, TT_OPDIV);
	asserteq(tok[4].type, TT_OPADDSET);
	asserteq(tok[5].type, TT_OPBSHIFTLEFTSET);
	asserteq(tok[6].type, TT_PARROW);
	asserteq(tok[7].type, TT_CEQ);
	asserteq(tok[8].type, TT_CNOTEQ);
	asserteq(tok[9].type, TT_IDENT);
	asserteq(tok[10].type, TT_OPDOT);
	asserteq(tok[11].type, TT_IDENT);
	asserteq(tok[12].type, TT_EOF);
	freetoks(tok);
}

TEST("Tokenize a main function: 'fn main() {}'") {
  char* str = "fn main() {}";
	RS_Token* tok = tokenize(str);
	asserteq(tok[0].type, TT_KFN);
	asserteq(tok[0].len, 2);
  assertstreq(tok[0].data, "fn");
	asserteq(tok[0].data[2], 0);
	asserteq(tok[1].type, TT_IDENT);
	asserteq(tok[1].len, 4);
	assertstreq(tok[1].data, "main");
  asserteq(tok[2].type, TT_POPENPAR);
  asserteq(tok[3].type, TT_PCLOSEPAR);
  asserteq(tok[4].type, TT_POPENCBR);
  asserteq(tok[5].type, TT_PCLOSECBR);
  asserteq(tok[6].type, TT_EOF);
  freetoks(tok);
}

#include "tests_end.h"
