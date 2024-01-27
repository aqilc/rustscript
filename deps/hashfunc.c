#define XXH_STATIC_LINKING_ONLY
#define XXH_IMPLEMENTATION
#include <xxhash.h>

uint32_t hash(const char* data, uint32_t len) {
	// #if defined(__x86_64__) || defined(_M_X64)
	// 	return XXH3_64bits(data, len);
	// #else// defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
		return XXH32(data, len, 4184034893);
	// #endif
}
