# Reference: https://stackoverflow.com/a/30602701/10013227

CC := gcc
LINKER := gcc
OUTPUTFILENAMEOPT := -o 
CFLAGS := -O2 -g -m64 -Ideps/include -Ilib
# BUILDDIR := bin

# CC := clang-cl
# LINKER := lld-link
# OUTPUTFILENAMEOPT := /OUT:
# CFLAGS := /Od /MD /Zi /EHsc -m64 -Ideps/include -Ilib -c /D_CRT_SECURE_NO_WARNINGS
# LINKFLAGS := /DEBUG:FULL
#/NODEFAULTLIB:libcmt.lib /SUBSYSTEM:CONSOLE	#/LIBPATH:deps/lib
# LIBS := msvcrt.lib
#shell32.lib gdi32.lib user32.lib
BUILDDIR := bin

# https://stackoverflow.com/a/51156408/10013227
define c2o
$(patsubst %.c,$(BUILDDIR)/%.o,$(notdir $(1)))
endef

# Defines platform specific stuff for dlls
ifeq ($(OS),Windows_NT)
	DLLENDING := .dll
	DLLFLAGS  := -Wl,--subsystem,windows
	EXEENDING := .exe
	STUPIDUNIXSHIT :=
	CLEAN := rmdir /s /q
else
	DLLENDING := .a
	DLLFLAGS  := 
	EXEENDING := .bin
	STUPIDUNIXSHIT := ./
	CLEAN := rm -rf
	ifeq (,$(shell command -v mold 2> /dev/null))
		LINKER := gcc -fuse-ld=ld
	else
		LINKER := gcc -fuse-ld=mold
	endif
endif
define c2dll
$(patsubst %.c,%$(DLLENDING),$(notdir $(1)))
endef

# Get the O file names from the C files
SRCS := $(wildcard *.c deps/*.c lib/*.c lib/asm/*.c)
OBJS := $(call c2o,$(SRCS))

# A lot of backend specific stuff
# BACKDEPS := bin/vec.o
# BACKSRCS := $(wildcard backends/*.c)
# BACKOBJS := $(call c2o,$(BACKSRCS))
# BACKDLLS := $(call c2dll,$(BACKSRCS))

# Require the build folder to be done first, DK if this is the right way but it works for now
all: $(BUILDDIR) | main$(EXEENDING) # $(BACKDLLS)
	@$(STUPIDUNIXSHIT)main$(EXEENDING)
# @C:\Windows\system32\cmd$(EXEENDING) /C "echo."

# back: $(BUILDDIR) | $(BACKDLLS)

main$(EXEENDING): $(OBJS)
	$(LINKER) $(LIBS) $^ $(OUTPUTFILENAMEOPT)$@ $(LINKFLAGS)
# $(CC) $^ -o $@

# %$(DLLENDING): $(BUILDDIR)/%.o $(BACKDEPS)
# 	gcc -o $@ $(BACKDEPS) -s -shared $< $(DLLFLAGS)

# Create build dir
$(BUILDDIR):
	mkdir $@

$(BUILDDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
$(BUILDDIR)/%.o: lib/%.c
	$(CC) $(CFLAGS) -c $^ -o $@
$(BUILDDIR)/%.o: deps/%.c
	$(CC) $(CFLAGS) -c $^ -o $@
$(BUILDDIR)/%.o: lib/asm/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	$(CLEAN) $(BUILDDIR)
	del main$(EXEENDING)
	del *.dll

.PHONY: all clean