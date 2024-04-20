#include <util.h>
#include <string.h>
#include <stdio.h>

// Aligns to the next multiple of a, where a is a power of 2
static inline u32 align(u32 n, u32 a) { return (n + a - 1) & ~(a - 1); }

#if defined _WIN32 | defined __CYGWIN__
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
static SYSTEM_INFO sysinfo;

void (*run(void* mem, u32 size))(void) {
	DWORD pagesize = sysinfo.dwPageSize;
	if(pagesize == 0) {
		GetSystemInfo(&sysinfo);
		pagesize = sysinfo.dwPageSize;
	}

	// printf("Page size: %ld\n", pagesize);

	u32 alignedsize = align(size, pagesize);

	// printf("Original size: %d, new size: %d\n", size, alignedsize);

	void* buf = VirtualAlloc(NULL, alignedsize, MEM_COMMIT, PAGE_READWRITE);
	memcpy(buf, mem, size);

	DWORD old;
	VirtualProtect(buf, size, PAGE_EXECUTE_READ, &old);

	return buf;
}

#else
#include <sys/mman.h>
#include <unistd.h>

void (*run(void* mem, u32 size))(void) {
	u32 pagesize = sysconf(_SC_PAGESIZE);
	u32 alignedsize = align(size, pagesize);

	printf("Page size: %d\n", pagesize);
	printf("Original size: %d, new size: %d\n", size, alignedsize);

	void* buf = mmap(NULL, alignedsize, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON, -1, 0);
	memcpy(buf, mem, size);

	mprotect(buf, size, PROT_READ | PROT_EXEC);

	return buf;
}

#endif
