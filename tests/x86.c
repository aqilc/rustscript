#include "tests.h"
#include "backends/x86.h"
#include "parse.h"

#define HASH_H_IMPLEMENTATION
#include <hash.h>

TEST("\"return 0;\"") {
	RS_MachineResult res = x86_machine(parse("test1.rc", "return 0;"));
	asserteq(res.len, 8);
	assertmemeq(res.code, { 0x48, 0xC7, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xC3 });
}

#include "tests_end.h"