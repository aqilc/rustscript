#include <vec.h>
#include <hash.h>
#include "util.h"
#include "error.h"
#include "tok.h"

struct { char* s; RS_TokenType t; } keyword_defs[] = {
	"let",    TT_KLET,
	"fn",     TT_KFN,
	"struct", TT_KSTRUCT,
	"if",     TT_KIF,
	"else",   TT_KELSE,
	"return", TT_KRETURN,

	"u32",    TT_TU32,
	"u16",    TT_TU16,
	"u8",     TT_TU8,
	"i32",    TT_TI32,
	"i16",    TT_TI16,
	"i8",     TT_TI8,
	"bool",   TT_TBOOL
};

ht(char*, RS_TokenType) keywords;

static inline u32 utf8(u8** str) {
	if(**str == 0) return 0;
	u32 code_point = 0;

	int len =
		**str > 0x80 ? // 10000000
			(**str & 0xE0) == 0xE0 ? 2 : // 0b11100000
				(**str & 0xC0) == 0xC0 ? 1 : 3 // 0b11000000
		: 0;

	if(len > 0) **str <<= len + 2, **str >>= len + 2;
	code_point += *(*str)++;
	while (len--) code_point = code_point << 6 | (*(*str)++ & 0x3F);
	return code_point;
}

static inline bool num   (u32 point) { return point >= '0' && point <= '9'; }
static inline bool alpha (u32 point) { return (point >= 'a' && point <='z') || (point >= 'A' && point <= 'Z'); }

Token* tokenize(char* str) {
	
	// Sets up keyword search
	if(!hgets(keywords, "if"))
		for(int i = 0; i < sizeof(keyword_defs) / sizeof(keyword_defs[0]); i ++)
			hsets(keywords, keyword_defs[i].s) = keyword_defs[i].t;

			
	char* start = str;
	Token* ret = vnew();

	#define op(t) vpush(ret, { .type = t, .len = 1, .data = NULL, .place = str - start })
	#define error(...) { vpush(ret, { .type = TT_ERROR, .len = 0, .data = NULL, .place = str - start }); error_at(start, str - start, __VA_ARGS__); return ret; }

	u32 point = 0;
	while ((point = utf8((u8**) &str))) {
		char* tokstart = str;
		
		// Floats not supported yet
		if(num(point)) {
			while (num((point = utf8((u8**) &str))));

			// str --;

			u32 len = str - tokstart;
			char* num = malloc(len + 1);
			num[len] = 0;
			memcpy(num, str - len - 1, len);
			
			vpush(ret, { .data = num, .type = TT_INT, .place = str - start, .len = len });\
			
			if(str[0] == '.') error("Floats are not available yet!");
		}

		if(alpha(point)) {
			while (alpha((point = utf8((u8**) &str))) || num(point));

			u32 len = str - tokstart;
			char* data;
			if(len == 0) {
				data = malloc(2);
				data[0] = str[- 1];
				data[1] = 0;
				len = 1;
			} else {
				data = malloc(len + 1);
				data[len] = 0;
				memcpy(data, str - len - 1, len);
			}
			// printf("\n%s, %s: %s, %d len", start, str, data, len);

			RS_TokenType* res = hgets(keywords, data);
			if(res) //printf("whoa got a keyword\n"),
				vpush(ret, { .type = *res, .data = data, .len = len, .place = str - start });
			else vpush(ret, { .type = TT_IDENT, .data = data, .len = len, .place = str - start });
		}

		switch (point) {
		case '(': op(TT_POPAR); break;
		case ')': op(TT_PCPAR); break;
		case '{': op(TT_POCBR); break;
		case '}': op(TT_PCCBR); break;
		case '[': op(TT_POSBR); break;
		case ']': op(TT_PCSBR); break;
		case '=': op(TT_OPSET); break;
		case '+': 
			if(str[0] == '=') op(TT_OPADDSET);
			else op(TT_OPADD);
			break;
		case '*': op(TT_OPMUL); break;
		}
	}

	#undef op
	#undef error

	vpush(ret, { .type = TT_EOF, .len = 0, .data = NULL, .place = str - start });

	return ret;
}


void freetoks(Token* tok) {
	for(int i = 0; i < vlen(tok); i ++)
		if(tok[i].data) free(tok[i].data);
	vfree(tok);
}
