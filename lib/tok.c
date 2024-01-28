#include <vec.h>
#include <hash.h>
#include "util.h"
#include "error.h"
#include "tok.h"

ht(char*, RS_TokenType) keywords;

static inline u32 utf8(u8** str) {
	if(**str == 0) return 0;
	u32 code_point = 0;

	int len =
		**str > 0x80 ? // 0b10000000
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
		hinit(keywords, {
			{ "let",    TT_KLET    },
			{ "fn",     TT_KFN     },
			{ "struct", TT_KSTRUCT },
			{ "if",     TT_KIF     },
			{ "else",   TT_KELSE   },
			{ "return", TT_KRETURN },
			{ "trait",  TT_KTRAIT  },
			
			{ "u32",    TT_TU32    },
			{ "u16",    TT_TU16    },
			{ "u8",     TT_TU8     },
			{ "i32",    TT_TI32    },
			{ "i16",    TT_TI16    },
			{ "i8",     TT_TI8     },
			{ "bool",   TT_TBOOL   },
		});

			
	char* start = str;
	RS_Token* ret = vnew();

	#define op(t, l) vpush(ret, { .type = t, .len = l, .data = NULL, .place = str - start })//, printf("Op %s, %d\n", str, t)
	#define error(...) { vpush(ret, { .type = TT_ERROR, .len = 0, .data = NULL, .place = str - start }); error_at(start, str - start, __VA_ARGS__); return ret; }

	u32 point = 0;
	while ((point = utf8((u8**) &str))) {
		char* tokstart = str;
		
		// Floats not supported yet
		if(num(point)) {
			char* lasttok = str;
			while (num((point = utf8((u8**) &str)))) lasttok = str;

			u32 len = str - tokstart + !point; // Weird behavior at the end of strings
			char* num = malloc(len + 1);
			num[len] = 0;
			memcpy(num, str - len - !!point, len); // ^^^^^^^^^^^^
			
			vpush(ret, { .data = num, .type = TT_INT, .place = str - start, .len = len });\
			if(str[0] == '.') error("Floats are not available yet!");
			str = lasttok;
			continue;
		}

		if(alpha(point)) {
			char* lasttok = str;
			while (alpha((point = utf8((u8**) &str))) || num(point)) lasttok = str;

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
			str = lasttok;
			continue;
		}

		if(point == '"') {
			while ((point = utf8((u8**) &str)) && point != '"');
			if(point != '"') error("Unterminated string!");

			point = utf8((u8**) &str);

			u32 len = str - tokstart + !point; // Weird behavior at the end of strings
			char* data = malloc(len + 1);
			data[len] = 0;
			memcpy(data, str - len - !!point, len);
			// printf("\n%s, %s: %s, %d len", start, str, data, len);
			
			vpush(ret, { .type = TT_STRING, .data = data, .len = len, .place = str - start });
			continue;
		}

		switch (point) {
		case '(': op(TT_POPENPAR, 1); continue;
		case ')': op(TT_PCLOSEPAR, 1); continue;
		case '{': op(TT_POPENCBR, 1); continue;
		case '}': op(TT_PCLOSECBR, 1); continue;
		case '[': op(TT_POPENSQBR, 1); continue;
		case ']': op(TT_PCLOSESQBR, 1); continue;
		case ';': op(TT_PSEMICOLON, 1); continue;
		case ',': op(TT_PCOMMA, 1); continue;
		case ':': op(TT_OPCOLON, 1); continue;
		case '.': op(TT_OPDOT, 1); continue;
		}

		char* tokstart2 = str;
		u32 peek = utf8((u8**) &str);
		RS_TokenType t = 0;
		switch(point) {
		case '+': if (peek == '+') { op(TT_OPINCR, 2); continue; } else t = TT_OPADD; break;
		case '-': if (peek == '-') { op(TT_OPDECR, 2); continue; } else t = TT_OPSUB; break;
		case '*': if (peek == '*') { op(TT_OPPOW, 2); continue; } else t = TT_OPMUL; break;
		case '/': t = TT_OPDIV; break;
		case '%': t = TT_OPMOD; break;
		case '|': if (peek == '|') { op(TT_LOR, 2); continue; } else t = TT_OPBOR; break;
		case '&': if (peek == '&') { op(TT_LAND, 2); continue; } else t = TT_OPBAND; break;
		case '^': t = TT_OPBXOR; break;
		case '~': t = TT_OPBNOT; break;
		}

		if(t && peek == '=') { op(t + TT_OPADDSET - TT_OPADD, 2); continue; }
		else if(t) { op(t, 1); str = tokstart2; continue; }
		
		if(point == '!') {
			if (peek == '=') op(TT_CNOTEQ, 2);
			else { op(TT_LNOT, 1); str = tokstart2; }
			continue;
		} else if (point == '=') {
			if (peek == '>') op(TT_PARROW, 2);
			else if (peek == '=') op(TT_CEQ, 2);
			else { op(TT_OPSET, 1); str = tokstart2; }
			continue;
		}

		char* tokstart3 = str;
		u32 peek2 = utf8((u8**) &str);
		switch(point) {
		case '<':
			if (peek == '=') op(TT_CLESSEQ, 2);
			else if (peek == '<') {
				if (peek2 == '=') op(TT_OPBSHIFTLEFTSET, 3);
				else { op(TT_OPBSHIFTLEFT, 2); str = tokstart3; }
			}
			else { op(TT_CLESS, 1); str = tokstart2; }
			continue;
		case '>':
			if (peek == '=') op(TT_CGREATEQ, 2);
			else if (peek == '>') {
				if (peek2 == '=') op(TT_OPBSHIFTRIGHTSET, 3);
				else { op(TT_OPBSHIFTRIGHT, 2); str = tokstart3; }
			}
			else { op(TT_CGREATER, 1); str = tokstart2; }
			continue;
		}

		str = tokstart;
	}

	op(TT_EOF, 0);

	#undef op
	#undef error
	return ret;
}


void freetoks(RS_Token* tok) {
	for(u32 i = 0; i < vlen(tok); i ++)
		if(tok[i].data) free(tok[i].data);
	vfree(tok);
}
