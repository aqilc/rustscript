#include <vec.h>
#include <hash.h>
#include "../tok.h"
#include "../codegen.h"
#include "x86.h"

char* x86(RS_Token* toks, RS_CGOpts opts) {
	vstr ret = vnew();
	for(int i = 0; i < vlen(toks); i++) {
		RS_Token tok = toks[i];
		
	}
	return vtostr(ret);
}