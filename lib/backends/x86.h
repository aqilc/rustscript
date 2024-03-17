#include "parse.h"
#include "util.h"

typedef struct RS_MachineResult RS_MachineResult;

struct RS_MachineResult {
	char* code;
	u32 len;
};

RS_MachineResult x86_machine(struct RS_ParserState* st);
char* x86_asm(struct RS_ParserState* st);