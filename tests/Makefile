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

ifeq ($(OS),Windows_NT)
	EXEEND := .exe
	FILEDELETE := del
	STUPIDUNIXSHIT := 
	
	CC := clang-cl
	CFLAGS := /Od /Zi /I"../lib" /I"../deps/include"
	COMPILEFLAG := /c
	TCFLAGS := /Od /Zi /I"../lib" /I"../deps/include"
	EXENAME := /Fe
	OBJEND := .obj
	OUTPUTFILENAME := /Fo
	LINK := /link /DEBUG:FULL

	# CC := clang
	# COMPILEFLAG := -c 
	# CFLAGS := -O3 -g -I"../lib" -I"../deps/include"
	# TCFLAGS := -O3 -g -I"../lib" -I"../deps/include"
	# EXENAME := -o
	# OBJEND := .o 
	# OUTPUTFILENAME := -o 
	# LINK :=
else
	CC := gcc
	CFLAGS := -O3 -g -I"../lib" -I"../deps/include"
	COMPILEFLAG := -c
	# CFLAGS := -g -Wall -Wextra -Wpedantic -I"../lib" -I"../deps/include"
	TCFLAGS := -O3 -g -I"../lib" -I"../deps/include"
	EXEEND := .bin
	FILEDELETE := rm
	STUPIDUNIXSHIT := ./
	OBJEND := .o
	EXENAME := -o 
	OUTPUTFILENAME := -o 
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



all: tok asm parse x86 bf

clean:
	$(FILEDELETE) *.o
	$(FILEDELETE) *.exe
	$(FILEDELETE) *.bin
	$(FILEDELETE) *.pdb
	$(FILEDELETE) *.obj
	$(FILEDELETE) *.ilk
	$(FILEDELETE) *.raddbg*
	$(FILEDELETE) *.rdi
	$(FILEDELETE) *.idx
	$(FILEDELETE) gmon.out

tok: tok$(EXEEND)
	@echo Running '$^'
	@$(STUPIDUNIXSHIT)tok$(EXEEND)
# @C:\Windows\system32\cmd.exe /C "echo."

asm: asm$(EXEEND)
	@echo Running '$^'
	@$(STUPIDUNIXSHIT)asm$(EXEEND)
# @C:\Windows\system32\cmd.exe /C "echo."

parse: parse$(EXEEND)
	@echo Running '$^'
	@$(STUPIDUNIXSHIT)parse$(EXEEND)

x86: x86$(EXEEND)
	@echo Running '$^'
	@$(STUPIDUNIXSHIT)x86$(EXEEND)

bf: bf$(EXEEND)
	@echo Running '$^'
	@$(STUPIDUNIXSHIT)bf$(EXEEND)

.PHONY: all tok asm parse x86 clean



# ============== Test bins ==============
tok$(EXEEND): toktest$(OBJEND) tok$(OBJEND) hashfunc$(OBJEND)
	@$(CC) $^ $(EXENAME)$@ $(LINK)

asm$(EXEEND): asmtest$(OBJEND) asm_x64$(OBJEND)
	@$(CC) $^ $(EXENAME)$@ $(LINK)

parse$(EXEEND): parsetest$(OBJEND) parse$(OBJEND) tok$(OBJEND) error$(OBJEND) hashfunc$(OBJEND)
	@$(CC) $^ $(EXENAME)$@ $(LINK)

x86$(EXEEND): x86test$(OBJEND) x86$(OBJEND) coderun$(OBJEND) asm_x64$(OBJEND) tok$(OBJEND) parse$(OBJEND) error$(OBJEND) hashfunc$(OBJEND)
	@$(CC) $^ $(EXENAME)$@ $(LINK)

bf$(EXEEND): bftest$(OBJEND) asm_x64$(OBJEND)
	@$(CC) $^ $(EXENAME)$@ $(LINK)

# ============= Test Builds =============
toktest$(OBJEND): tok.c ../lib/tok.c $(TESTSUITE)
	$(CC) $(TCFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

asmtest$(OBJEND): asm.c ../lib/asm/asm_x64.c ../lib/asm/asm_x64.h $(TESTSUITE)
	$(CC) $(TCFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

parsetest$(OBJEND): parse.c ../lib/parse.c $(TESTSUITE)
	$(CC) $(TCFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

x86test$(OBJEND): x86.c ../lib/backends/x86.c ../lib/asm/coderun.c ../lib/asm/coderun.h ../lib/backends/x86.h ../lib/asm/asm_x64.c ../lib/asm/asm_x64.h ../lib/parse.c $(TESTSUITE)
	$(CC) $(TCFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

bftest$(OBJEND): bf.c ../lib/asm/asm_x64.c ../lib/asm/asm_x64.h $(TESTSUITE)
	$(CC) $(TCFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

# ----------- Base lib builds ------------

%$(OBJEND): ../deps/%.c
	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

%$(OBJEND): ../lib/%.c
	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

%$(OBJEND): ../lib/asm/%.c
	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

%$(OBJEND): ../lib/backends/%.c
	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

# hashfunc$(OBJEND): ../deps/hashfunc.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

# codegen$(OBJEND): ../lib/codegen.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
# tok$(OBJEND): ../lib/tok.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
# error$(OBJEND): ../lib/error.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
# asm$(OBJEND): ../lib/asm/asm_x64.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

# parse$(OBJEND): ../lib/parse.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
# coderun$(OBJEND): ../lib/asm/coderun.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
# backend_load$(OBJEND): ../../backend_load.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

