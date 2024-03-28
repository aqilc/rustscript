#include <stdarg.h>
#include <stdio.h>
#include "util.h"

// Every single piece of info about a line you'd ever want
static inline u32 line(char* str, u32 place, u32* start, u32* end) {

	if(end) {
		u32 cur = place;
		while(str[cur] && str[cur] != '\n') cur ++;
		*end = cur;
	}

	u32 cur = place;
	while(cur > 0 && str[cur] != '\n') cur --;
	if(start) *start = cur;
	
	u32 line_count = 1;
	for(; cur > 0; cur --) if(str[cur] == '\n') line_count ++;
	return line_count;
}

// Counts the length of an integer
static inline int count_digits(uint32_t n) {
#ifndef __has_builtin
#  define __has_builtin(x) 0
#endif
#if __has_builtin(__builtin_clz)
  // This increments the upper 32 bits (log10(T) - 1) when >= T is added.
  #  define K(T) (((sizeof(#T) - 1ull) << 32) - T)
  static const uint64_t table[] = {
      K(0),          K(0),          K(0),           // 8
      K(10),         K(10),         K(10),          // 64
      K(100),        K(100),        K(100),         // 512
      K(1000),       K(1000),       K(1000),        // 4096
      K(10000),      K(10000),      K(10000),       // 32k
      K(100000),     K(100000),     K(100000),      // 256k
      K(1000000),    K(1000000),    K(1000000),     // 2048k
      K(10000000),   K(10000000),   K(10000000),    // 16M
      K(100000000),  K(100000000),  K(100000000),   // 128M
      K(1000000000), K(1000000000), K(1000000000),  // 1024M
      K(1000000000), K(1000000000)                  // 4B
  };
  return (n + table[__builtin_clz(n | 1) ^ 31]) >> 32u;
#else
  int count = 1;
  for (;;) {
    if (n < 10) return count;
    if (n < 100) return count + 1;
    if (n < 1000) return count + 2;
    if (n < 10000) return count + 3;
    n /= 10000u;
    count += 4;
  }
  return count;
#endif
}

#define ERRORSTRMAXWIDTH 200

/*
	Makes an error like
----------------------------------
test.c@18:8: Unexpected identifier
18 | let br;h
   |        ^
----------------------------------
*/
void parser_message(char* str, u32 place, char* file, char* fmt, ...) {
	u32 start, end;
	u32 linenum = line(str, place, &start, &end);
	u32 linenumlen = count_digits(linenum);
	// u32 len = start - end - 1 + 3 + linenumlen;

	// The error
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "%s@%d:%d: ", file, linenum, place - start);
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");

	// Prints out the line
	fprintf(stderr, "%d | %.*s\n", linenum, (u32) (start - end - 1), str + start);

	// Prints out the spaces and then the ^
	fprintf(stderr, "%*s|%*s\033[31;1m^\033[0m\n", linenumlen + 1, "", place - linenumlen - 2 - start, "");
}