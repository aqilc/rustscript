#include "tests.h"
#include "backends/x86.h"
#include "parse.h"

#define HASH_H_IMPLEMENTATION
#include <hash.h>

TEST("\"return 0;\"") {
	struct RS_ParserState* state = parse("test2.rc", "return 0;");
	assert(state != NULL);

	RS_MachineResult res = x86_machine(state);
	char* str = x86_asm(state);

	asserteq(res.len, 8);
	assertmemeq(res.code, { 0x48, 0xC7, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xC3 });
	assertstreq(str, "\tmov rax, 0\n\tret");
}

#include "tests_end.h"