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
	CFLAGS := /O2 /Zi /I"../lib" /I"../deps/include"
	COMPILEFLAG := /c
	TCFLAGS := /O2 /Zi /I"../lib" /I"../deps/include"
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



all: tok asm parse

clean:
	$(FILEDELETE) *.o
	$(FILEDELETE) *.exe
	$(FILEDELETE) *.bin
	$(FILEDELETE) *.pdb
	$(FILEDELETE) *.obj
	$(FILEDELETE) *.ilk
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

.PHONY: all tok clean



# ============== Test bins ==============
tok$(EXEEND): toktest$(OBJEND) tok$(OBJEND) hashfunc$(OBJEND)
	@$(CC) $^ $(EXENAME)$@ $(LINK)

asm$(EXEEND): asmtest$(OBJEND) asm$(OBJEND)
	@$(CC) $^ $(EXENAME)$@ $(LINK)

parse$(EXEEND): parsetest$(OBJEND) parse$(OBJEND) hashfunc$(OBJEND)
	@$(CC) $^ $(EXENAME)$@ $(LINK)

# ============= Test Builds =============
toktest$(OBJEND): tok.c ../lib/tok.c $(TESTSUITE)
	$(CC) $(TCFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

asmtest$(OBJEND): asm.c ../lib/asm/asm_x86.c ../lib/asm/asm_x86.h $(TESTSUITE)
	$(CC) $(TCFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

parsetest$(OBJEND): parse.c ../lib/parse.c $(TESTSUITE)
	$(CC) $(TCFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

# ----------- Base lib builds ------------

%$(OBJEND): ../deps/%.c
	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

%$(OBJEND): ../lib/%.c
	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

# hashfunc$(OBJEND): ../deps/hashfunc.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

# codegen$(OBJEND): ../lib/codegen.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
# tok$(OBJEND): ../lib/tok.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
# error$(OBJEND): ../lib/error.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
# asm$(OBJEND): ../lib/asm/asm_x86.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

# parse$(OBJEND): ../lib/parse.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
# coderun$(OBJEND): ../lib/asm/coderun.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
# backend_load$(OBJEND): ../../backend_load.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

