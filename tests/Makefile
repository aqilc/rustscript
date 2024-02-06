# https://devblogs.microsoft.com/cppblog/addresssanitizer-asan-for-windows-with-msvc/


MSVC := ${MSVC}

ifeq ($(MSVC), 1)
	# MSVC
	CC := cl
	CFLAGS := /std:c++17 /EHsc /MDd /Zi /D_CRT_SECURE_NO_WARNINGS
	TCFLAGS := /std:c++17 /EHsc /MDd /Zi /D_CRT_SECURE_NO_WARNINGS
	OBJEND := .obj
	OUTPUTFILENAME := /Fo
	EXENAME := /Fe
	COMPILEFLAG := /c
	LINK := /link /debug
else
	# GCC
	CC := gcc
	# CFLAGS := -O3 -I"../lib" -I"../deps/include"
	# CFLAGS := -g -Wall -Wextra -Wpedantic -I"../lib" -I"../deps/include"
	CFLAGS := -g -I"../lib" -I"../deps/include"
	# TCFLAGS := -O3 -I"../lib" -I"../deps/include"
	TCFLAGS := -g -I"../lib" -I"../deps/include"
	OBJEND := .o
	OUTPUTFILENAME := -o 
	EXENAME := -o 
	COMPILEFLAG := -c
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
	del *.o
	del *.obj
	del *.bin
	del *.exe
	del *.pdb

tok: tok.exe
	@echo Running '$^'
	@tok.exe
	@C:\Windows\system32\cmd.exe /C "echo."

asm: asm.exe
	@echo Running '$^'
	@asm.exe
	@C:\Windows\system32\cmd.exe /C "echo."

.PHONY: all tok clean



# ============== Test bins ==============
tok.exe: toktest$(OBJEND) tok$(OBJEND) error$(OBJEND) $(UTIL)
	@$(CC) $^ $(EXENAME)$@

asm.exe: asmtest$(OBJEND) asm$(OBJEND) error$(OBJEND) $(UTIL)
	@$(CC) $^ $(EXENAME)$@

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

