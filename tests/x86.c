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
	assertbyteseq(res.code, { 0x48, 0xC7, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xC3 });
	assertstreq(str, "\tmov rax, 0\n\tret");
}

TEST("\"return 1 + 1;\"") {
	struct RS_ParserState* state = parse("test2.rc", "return 1 + 1;");
	assert(state != NULL);

	RS_MachineResult res = x86_machine(state);
	char* str = x86_asm(state);

	asserteq(res.len, 10);
	assertbyteseq(res.code, { 0x48, 0xC7, 0xC0, 0x02, 0x00, 0x00, 0x00, 0x04, 0x01, 0xC3 });
	assertstreq(str, "\tmov rax, 1\n\tadd ax, 1\n\tret");
}

#include "tests_end.h"