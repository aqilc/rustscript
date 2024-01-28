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
	"trait",  TT_KTRAIT,

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

RS_Token* tokenize(char* str) {
	
	// Sets up keyword search
	if(!hgets(keywords, "if"))
		for(u32 i = 0; i < sizeof(keyword_defs) / sizeof(keyword_defs[0]); i ++)
			hsets(keywords, keyword_defs[i].s) = keyword_defs[i].t;

			
	char* start = str;
	RS_Token* ret = vnew();

	#define op(t) vpush(ret, { .type = t, .len = 1, .data = NULL, .place = str - start })
	#define error(...) { vpush(ret, { .type = TT_ERROR, .len = 0, .data = NULL, .place = str - start }); error_at(start, str - start, __VA_ARGS__); return ret; }

	u32 point = 0;
	while ((point = utf8((u8**) &str))) {
		char* tokstart = str;
		
		// Floats not supported yet
		if(num(point)) {
			while (num((point = utf8((u8**) &str))));

			u32 len = str - tokstart + !point; // Weird behavior at the end of strings
			char* num = malloc(len + 1);
			num[len] = 0;
			memcpy(num, str - len - !!point, len); // ^^^^^^^^^^^^
			
			vpush(ret, { .data = num, .type = TT_INT, .place = str - start, .len = len });\
			if(str[0] == '.') error("Floats are not available yet!");
		}

		if(alpha(point)) {
			while (alpha((point = utf8((u8**) &str))) || num(point));

			u32 len = str - tokstart + !point; // Weird behavior at the end of strings
			char* data;
			data = malloc(len + 1);
			data[len] = 0;
			memcpy(data, str - len - !!point, len);
			
			// printf("\n%s, %s: %s, %d len", start, str, data, len);

			RS_TokenType* res = hgets(keywords, data);
			if(res) //printf("whoa got a keyword\n"),
				vpush(ret, { .type = *res, .data = data, .len = len, .place = str - start });
			else vpush(ret, { .type = TT_IDENT, .data = data, .len = len, .place = str - start });
		}

		if(point == '"') {
			while ((point = utf8((u8**) &str)) && point != '"');

			u32 len = str - tokstart + !point; // Weird behavior at the end of strings
			printf("\n%s, %s: %d len", start, str, len);
			char* data = malloc(len + 1);
			data[len] = 0;
			memcpy(data, str - len - !!point, len);
			printf("\n%s, %s: %s, %d len", start, str, data, len);

			if(point != '"') error("Unterminated string!");
			vpush(ret, { .type = TT_STRING, .data = data, .len = len, .place = str - start });
		}

		switch (point) {
		case '(': op(TT_POPENPAR); break;
		case ')': op(TT_PCLOSEPAR); break;
		case '{': op(TT_POPENCBR); break;
		case '}': op(TT_PCLOSECBR); break;
		case '[': op(TT_POPENSQBR); break;
		case ']': op(TT_PCLOSESQBR); break;
		case '=':
			if(str[0] == '=') op(TT_OPEQ);
			else if (str[0] == '>') op(TT_PARROW);
			else op(TT_OPSET);
			break;
		case '+': 
			if(str[0] == '=') op(TT_OPADDSET);
			else op(TT_OPADD);
			break;
		case '*':
			if(str[0] == '=') op(TT_OPMULSET);
			else op(TT_OPMUL);
			break;
		case '/':
			if(str[0] == '=') op(TT_OPDIVSET);
			else op(TT_OPDIV);
			break;
		case '%':
			if(str[0] == '=') op(TT_OPMODSET);
			else op(TT_OPMOD);
			break;
		case '|':
			if(str[0] == '=') op(TT_OPBORSET);
			else if(str[0] == '|') op(TT_LOR);
			else op(TT_OPBOR);
			break;
		case '&':
			if(str[0] == '=') op(TT_OPBANDSET);
			else if(str[0] == '&') op(TT_LAND);
			else op(TT_OPBAND);
			break;
		case '^':
			if(str[0] == '=') op(TT_OPBXORSET);
			else op(TT_OPBXOR);
			break;
		case '~':
			if(str[0] == '=') op(TT_OPBNOTSET);
			else op(TT_OPBNOT);
			break;
		case '!':
			if(str[0] == '=') op(TT_OPNOTEQ);
			else op(TT_LNOT);
			break;
		case '<':
			if(str[0] == '=') op(TT_OPLESSEQ);
			else if(str[0] == '<') {
				if(str[1] == '=') op(TT_OPBSHIFTLEFTSET);
				else op(TT_OPBSHIFTLEFT);
			}
			else op(TT_OPLESS);
			break;
		case '>':
			if(str[0] == '=') op(TT_OPGREATEQ);
			else if(str[0] == '>') {
				if(str[1] == '=') op(TT_OPBSHIFTRIGHTSET);
				else op(TT_OPBSHIFTRIGHT);
			}
			else op(TT_OPGREATER);
			break;
		case ':': op(TT_OPCOLON); break;
		}
	}

	#undef op
	#undef error

	vpush(ret, { .type = TT_EOF, .len = 0, .data = NULL, .place = str - start });

	return ret;
}


void freetoks(RS_Token* tok) {
	for(u32 i = 0; i < vlen(tok); i ++)
		if(tok[i].data) free(tok[i].data);
	vfree(tok);
}
