// BECAUSE FUCKING MWINDOW.H WANTS TO FUCKING TYPEDEF INT FOR SOME STUPID REASON AND THEN NOT EVEN FUCKING USE IT MORE THAN ONCE FUCK WINDOWS RAHHHHHHHHHHHHHHHHHHHHHHHHHH
#define VOID void
#define _MINWINDEF_
#define CHAR char
#define INT int
#define FLOAT float
typedef short SHORT;
#define LONG __LONG32
#define CONST const
#define far
typedef float* PFLOAT;
typedef unsigned short WORD;
typedef unsigned short* PWORD;
typedef unsigned short* LPWORD;
typedef unsigned char BYTE;
typedef unsigned char* PBYTE;
typedef unsigned char* LPBYTE;
typedef unsigned long DWORD;
typedef unsigned long* PDWORD;
typedef unsigned long* LPDWORD;
typedef unsigned long ULONG;
typedef unsigned char UCHAR;
typedef unsigned char* PUCHAR;
typedef unsigned short USHORT;
typedef unsigned short* PUSHORT;
typedef unsigned int* LPINT;
typedef void* LPVOID;
typedef const void* LPCVOID;
typedef void* PVOID;
typedef unsigned long* PULONG;
typedef long* LPLONG;
typedef _Bool WINBOOL;
typedef WINBOOL BOOL;
typedef _Bool* PBOOL;
typedef _Bool* LPBOOL;
typedef unsigned long WPARAM;
typedef long long LPARAM;
typedef long long LRESULT;
typedef unsigned int UINT;
typedef unsigned int* PUINT;
typedef long long INT_PTR;
#if defined(_ARM_)
#define WINAPI
#define CALLBACK
#define APIPRIVATE
#define PASCAL
#else
#define WINAPI __stdcall
#define CALLBACK __stdcall
#define APIPRIVATE __stdcall
#define PASCAL __stdcall
#endif
#define WINAPI_INLINE WINAPI
#define WINAPIV __cdecl
#define APIENTRY WINAPI
#define MAX_PATH 260
typedef WORD ATOM;
typedef void* *SPHANDLE;
typedef void* *LPHANDLE;
typedef void* HGLOBAL;
typedef void* HLOCAL;
typedef void* GLOBALHANDLE;
typedef void* LOCALHANDLE;
#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
typedef int HFILE;
DECLARE_HANDLE (HINSTANCE);
DECLARE_HANDLE (HKEY);
typedef HKEY *PHKEY;
DECLARE_HANDLE (HKL);
DECLARE_HANDLE (HLSURF);
DECLARE_HANDLE (HMETAFILE);
typedef HINSTANCE HMODULE;
DECLARE_HANDLE (HRGN);
DECLARE_HANDLE (HRSRC);
DECLARE_HANDLE (HSPRITE);
DECLARE_HANDLE (HSTR);
DECLARE_HANDLE (HTASK);
DECLARE_HANDLE (HWINSTA);
#undef DECLARE_HANDLE
#ifdef _WIN64
  typedef INT_PTR (WINAPI *FARPROC) ();
  typedef INT_PTR (WINAPI *NEARPROC) ();
  typedef INT_PTR (WINAPI *PROC) ();
#else
  typedef int (WINAPI *FARPROC) ();
  typedef int (WINAPI *NEARPROC) ();
  typedef int (WINAPI *PROC) ();
#endif
#include "tests.h"
#undef FAR
#undef IN
#undef INT
#undef OUT
#define VEC_H_IMPLEMENTATION
#include <vec.h>
#include <asm/asm_x86.h>


#define INSTEST(bytes, ...) substart(#__VA_ARGS__ " => " #bytes);\
	asserteq(x64emit(&(x64Ins) { __VA_ARGS__ }, buf), sizeof(#bytes) / 5);
#define INSTESTMEMEQ(...) assertmemeq(buf, { __VA_ARGS__ }); subend(1);

TEST("Assemble push instructions (1 argument, 1-3 bytes with optional REX)") {
	char buf[3] = {0};

	INSTEST(0x50, PUSH, rax);
	INSTESTMEMEQ(0x50);

	INSTEST(0x52, PUSH, rdx);
	INSTESTMEMEQ(0x52);

	INSTEST(0x66 0x53, PUSH, bx);
	INSTESTMEMEQ(0x66, 0x53);

	INSTEST(0x41 0x50, PUSH, r8);
	INSTESTMEMEQ(0x41, 0x50);
}

TEST("Assemble call instructions (1 argument, 5-7 bytes with optional REX and Immediates)") {
	char buf[7] = {0};

	INSTEST(0xE8 0x00 0x00 0x00 0x00, CALL, im64(0));
	INSTESTMEMEQ(0xE8, 0x00, 0x00, 0x00, 0x00);

	INSTEST(0xFF 0xD0, CALL, rax);
	INSTESTMEMEQ(0xFF, 0xD0);

	INSTEST(0x41 0xFF 0xD0, CALL, r8);
	INSTESTMEMEQ(0x41, 0xFF, 0xD0);

}

TEST("Assemble mov instructions (2 arguments, 2-4 bytes with optional REX and Immediates)") {
	char buf[10] = {0};
	
	INSTEST(0xB0 0x03, MOV, al, im8(3));
	INSTESTMEMEQ(0xB0, 0x03);

	INSTEST(0x48 0x89 0xD0, MOV, rax, rdx);
	INSTESTMEMEQ(0x48, 0x89, 0xD0);

	INSTEST(0x48 0x89 0xC0, MOV, rax, r8);
	INSTESTMEMEQ(0x48, 0x89, 0xC0);

	INSTEST(0x67 0x8A 0x4B 0x03, MOV, cl, m8(3, $ebx));
	INSTESTMEMEQ(0x67, 0x8A, 0x4B, 0x03);
}

TEST("Assemble lea instructions (2 arguments, 3-5 bytes with optional REX and Immediates)") {
	char buf[10] = {0};

	INSTEST(0x48 0x8D 0x4C 0x24 0x08, LEA, rcx, mem(8, $rsp));
	INSTESTMEMEQ(0x48, 0x8D, 0x4C, 0x24, 0x08);

	INSTEST(0x8D 0x4C 0x24 0x08, LEA, ecx, mem(8, $rsp));
	INSTESTMEMEQ(0x8D, 0x4C, 0x24, 0x08);
}

#include "tests_end.h"
