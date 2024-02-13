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



TEST("Assemble push instructions (1 argument, 1-3 bytes with optional REX)") {
	char buf[3] = {0};

	substart("push rax");
	asserteq(x64emit(&(x64Ins) { PUSH, rax }, buf), 1);
	asserteq(buf[0], 0x50);
	subend(1);

	substart("push rdx");
	asserteq(x64emit(&(x64Ins) { PUSH, rdx }, buf), 1);
	asserteq(buf[0], 0x52);
	subend(1);
}

TEST("Assemble mov instructions (2 arguments, 2-4 bytes with optional REX and Immediates)") {
	char buf[10] = {0};
	
	substart("mov al, 3");
	asserteq(x64emit(&(x64Ins) { MOV, { al, im8(3) }}, buf), 2);
	assertmemeq(buf, { 0xB0, 0x03 });
	subend(1);

	substart("mov rax, rdx");
	asserteq(x64emit(&(x64Ins) { MOV, { rax, rdx }}, buf), 3);
	assertmemeq(buf, { 0x48, 0x89, 0xD0 });
	subend(1);

	substart("mov rax, r8");
	asserteq(x64emit(&(x64Ins) { MOV, { rax, r8 }}, buf), 4);
	assertmemeq(buf, { 0x4C, 0x89, 0xC0 });
	subend(1);
}

#include "tests_end.h"
