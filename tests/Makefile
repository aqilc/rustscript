# https://devblogs.microsoft.com/cppblog/addresssanitizer-asan-for-windows-with-msvc/


# MSVC
# CC := cl
# CFLAGS := /std:c++17 /EHsc /MDd /Zi /D_CRT_SECURE_NO_WARNINGS
# TCFLAGS := /std:c++17 /EHsc /MDd /Zi /D_CRT_SECURE_NO_WARNINGS
# OBJEND := .obj
# OUTPUTFILENAME := /Fo
# EXENAME := /Fe
# COMPILEFLAG := /c
# LINK := /link /debug
# GCC

OBJEND := .o
OUTPUTFILENAME := -o 
EXENAME := -o 
COMPILEFLAG := -c

ifeq ($(OS),Windows_NT)
	CC := clang-cl
	CFLAGS := /O2 /Z7 -I"../lib" -I"../deps/include"
	TCFLAGS := /Od /Z7 -I"../lib" -I"../deps/include"
	EXEEND := .exe
	FILEDELETE := del
	STUPIDUNIXSHIT := 
	LINK := /Z7
else
	CC := gcc
	CFLAGS := -O3 -g -I"../lib" -I"../deps/include"
	# CFLAGS := -g -Wall -Wextra -Wpedantic -I"../lib" -I"../deps/include"
	TCFLAGS := -O3 -g -I"../lib" -I"../deps/include"
	EXEEND := .bin
	FILEDELETE := rm
	STUPIDUNIXSHIT := ./
	LINK := 
endif


UTIL := hashfunc$(OBJEND)
TESTSUITE := tests.h tests_end.h


# if ($(OS),Windows_NT)
# 	define _del
# 		del $(1)
# 	endef
# else
# 	define _del
# 		rm $(1)
# 	endef
# endif



all: tok asm

clean:
	$(FILEDELETE) *.o
	$(FILEDELETE) *.bin
	$(FILEDELETE) *.exe
	$(FILEDELETE) *.pdb
	$(FILEDELETE) *.obj

tok: tok$(EXEEND)
	@echo Running '$^'
	@$(STUPIDUNIXSHIT)tok$(EXEEND)
# @C:\Windows\system32\cmd.exe /C "echo."

asm: asm$(EXEEND)
	@echo Running '$^'
	@$(STUPIDUNIXSHIT)asm$(EXEEND)
# @C:\Windows\system32\cmd.exe /C "echo."

.PHONY: all tok clean



# ============== Test bins ==============
tok$(EXEEND): toktest$(OBJEND) tok$(OBJEND) error$(OBJEND) $(UTIL)
	@$(CC) $^ $(EXENAME)$@ $(LINK)

asm$(EXEEND): asmtest$(OBJEND) asm$(OBJEND) error$(OBJEND) $(UTIL)
	@$(CC) $^ $(EXENAME)$@ $(LINK)

# ============= Test Builds =============
toktest$(OBJEND): tok.c ../lib/tok.c $(TESTSUITE)
	$(CC) $(TCFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

asmtest$(OBJEND): asm.c ../lib/asm/asm_x86.c $(TESTSUITE)
	$(CC) $(TCFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

# ----------- Base lib builds -----------
hashfunc$(OBJEND): ../deps/hashfunc.c
	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

codegen$(OBJEND): ../lib/codegen.c
	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
tok$(OBJEND): ../lib/tok.c
	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
error$(OBJEND): ../lib/error.c
	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
asm$(OBJEND): ../lib/asm/asm_x86.c
	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
# coderun$(OBJEND): ../lib/asm/coderun.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
# backend_load$(OBJEND): ../../backend_load.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

