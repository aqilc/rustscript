#include "tests.h"
#include <tok.h>
#define HASH_H_IMPLEMENTATION
#include <hash.h>
#define VEC_H_IMPLEMENTATION
#include <vec.h>

TEST("Tokenize Empty String") {
	char* str = "";
	RS_Token* tok = tokenize(str);
	expecteq(tok[0].type, TT_EOF);
	freetoks(tok);
}

TEST("Tokenize a single character: 'a'") {
  char* str = "a";
	RS_Token* tok = tokenize(str);
	expecteq(tok[0].type, TT_IDENT);
	expecteq(tok[0].len, 1);
	expecteq(tok[0].data[0], 'a');
  expecteq(tok[1].type, TT_EOF);
	freetoks(tok);
}

TEST("Tokenize integers: '1234567890 1234 =-1234'") {
  char* str = "1234567890 1234 =-1234";
	RS_Token* tok = tokenize(str);
	expecteq(tok[0].type, TT_INT);
	expecteq(tok[0].len, 10);
	expecteq(tok[0].intv, 1234567890);
  expecteq(tok[1].type, TT_INT);
	expecteq(tok[1].intv, 1234);
	expecteq(tok[2].type, TT_OPSET);
	expecteq(tok[3].type, TT_INT);
	expecteq(tok[3].intv, -1234);
	expecteq(tok[4].type, TT_EOF);
	freetoks(tok);
}

TEST("Tokenize a string: '\"Hello World\"'") {
  char* str = "\"Hello World\"";
	RS_Token* tok = tokenize(str);
	expecteq(tok[0].type, TT_STRING);
	expecteq(tok[0].len, 13);
  expectstreq(tok[0].data, "\"Hello World\"");
  expecteq(tok[1].type, TT_EOF);
	freetoks(tok);
}

TEST("Tokenize Operators: '+ - * / = += <<= => ++ == != a.b'") {
	char* str = "+ - * / = += <<= => ++ == != a.b";
	RS_Token* tok = tokenize(str);
	expecteq(tok[0].type, TT_OPADD);
	expecteq(tok[1].type, TT_OPSUB);
	expecteq(tok[2].type, TT_OPMUL);
	expecteq(tok[3].type, TT_OPDIV);
	expecteq(tok[4].type, TT_OPSET);
	expecteq(tok[5].type, TT_OPADDSET);
	expecteq(tok[6].type, TT_OPBSHIFTLEFTSET);
	expecteq(tok[7].type, TT_PARROW);
	expecteq(tok[8].type, TT_OPINCR);
	expecteq(tok[9].type, TT_CEQ);
	expecteq(tok[10].type, TT_CNOTEQ);
	expecteq(tok[11].type, TT_IDENT);
	expecteq(tok[12].type, TT_OPDOT);
	expecteq(tok[13].type, TT_IDENT);
	expecteq(tok[14].type, TT_EOF);
	freetoks(tok);
}

TEST("Tricky Situations: '=-=>=-'") {
	char* str = "=-=>=-";
	RS_Token* tok = tokenize(str);
	expecteq(tok[0].type, TT_OPSET);
	expecteq(tok[1].type, TT_OPSUBSET);
	expecteq(tok[2].type, TT_CGREATEQ);
	expecteq(tok[3].type, TT_OPSUB);
	expecteq(tok[4].type, TT_EOF);
	freetoks(tok);
}

TEST("Tokenize a main function: 'fn main() {}'") {
  char* str = "fn main() {}";
	RS_Token* tok = tokenize(str);
	expecteq(tok[0].type, TT_KFN);
	expecteq(tok[0].len, 2);
  expectstreq(tok[0].data, "fn");
	expecteq(tok[0].data[2], 0);
	expecteq(tok[1].type, TT_IDENT);
	expecteq(tok[1].len, 4);
	expectstreq(tok[1].data, "main");
  expecteq(tok[2].type, TT_POPENPAR);
  expecteq(tok[3].type, TT_PCLOSEPAR);
  expecteq(tok[4].type, TT_POPENCBR);
  expecteq(tok[5].type, TT_PCLOSECBR);
  expecteq(tok[6].type, TT_EOF);
  freetoks(tok);
}

#include "tests_end.h"
