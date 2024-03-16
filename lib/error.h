#pragma once
#include "util.h"

// void error_at(char* str, u32 place, char* fmt, ...);

#if defined __clang__ || defined __GNUC__
__attribute__((format(printf, 4, 5)))
#endif
void parser_message(char* str, u32 place, char* file, char* fmt, ...);

#define error_at(str, place, file, ...) parser_message(str, place, file, "error: " __VA_ARGS__)
