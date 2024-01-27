#include <stdarg.h>
#include <stdio.h>
#include "util.h"

// Every single piece of info about a line you'd ever want
static inline u32 line(char* str, u32* place, char** start, char** end) {
	
	// Calculates end of line
	char* e = str + *place;
	while(e && *e != '\n') e ++;
	*end = e;

	// Calculates start of line
	e = str + *place;
	while(e > str && *e != '\n') e--;
	*start = e;
	*place -= (e - str); // Normalizes `place` to the current line

	// Calculates line_count
	u32 line_count = 1;
	while (e > str) {
		if(*e == '\n') line_count++;
		e --;
	}
	return line_count;
}

// Counts the length of an integer
static inline u32 intlen(int i) {
	u32 j = 0;
	if(i < 0) i = -i, j++;
	while ((i /= 10) > 10) j++;
	return j;
}

#define ERRORSTRMAXWIDTH 200

/*
	Makes an error like
----------------------------------
L18@8: Unexpected identifier
18 | let br;h
   |        ^
----------------------------------
*/
void error_at(char* str, u32 place, char* fmt, ...) {
	char* start,* end;
	u32 linenum = line(str, &place, &start, &end);
	u32 linenumlen = intlen(linenum);
	u32 len = start - end - 1 + 3 + linenumlen;

	// The error
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "L%d@%d:", linenum, place);
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");

	// Prints out the line
	fprintf(stderr, "%d | %.*s\n", linenum, (u32) (start - end - 1), start);

	// Prints out the spaces and then the ^
	fprintf(stderr, "%*s|%*s\\033[31;1m^\\033[0m\n", linenumlen + 1, "", place - linenumlen - 2, "");
}

