// Threading library
// https://github.com/tinycthread/tinycthread
#include <codegen.h>
#include "lib/util.h"
// #include <tok.h>

#define VEC_H_IMPLEMENTATION
#include <vec.h>

#define HASH_H_IMPLEMENTATION
#include <hash.h>

int main() {
	char* hi = PROG(
		fn main() { return 0; }
	);

	RS_Token* tok = tokenize(hi);

	for(int i = 0; i < vlen(tok); i++) {
		RS_Token t = tok[i];
		printf("%d: %d %d %s\n", i, t.type, t.len, t.data);
	}

	// printf("%s", codegen(x86, tok));
	freetoks(tok);
	return 0;
}
