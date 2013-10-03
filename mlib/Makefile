#!/usr/bin/env make

lib_name       = mlib
lib_version    = 0.0.1
comp_flags     = -I.. -g -Wall -Wextra -Werror -std=c99 \
                 -DPACKAGE_NAME=\""$(lib_name)"\" \
                 -DPACKAGE_VERSION=\""$(lib_version)"\" \
                 $(CPPFLAGS) $(CFLAGS)
link_flags     = $(LDFLAGS)
sources        = $(wildcard *.c)
headers        = $(wildcard *.h)
objects        = $(sources:.c=.o)

# In case someone runs `make -R` (no implicit variables)
CC ?= cc
RM ?= rm -f

# If V=1 is specified, print out all commands, otherwise, use
# pretty printing using echo.
ifeq ($(V),1)
	V_CC   =$(CC) -c -fPIC
	V_CCLD =$(CC)
else
	V_CC   =@echo "  [CC]   $@" && $(CC) -c -fPIC
	V_CCLD =@echo "  [CCLD] $@" && $(CC)
endif

# Default target
all: lib$(lib_name).so

# Compile the library itself
lib$(lib_name).so: $(objects)
	$(V_CCLD) -shared $(strip $(comp_flags)) -o $@ $^ $(strip $(link_flags))

# Compile each object file
%.o: %.c
	$(V_CC) $(strip $(comp_flags)) -o $@ $<

# Create the .build_tmp dir for caching Make file stuff
.build_tmp:
	@mkdir -p $@/

# Automatically compute the dependencies for the various files
.build_tmp/dependencies: .build_tmp
	@$(CC) -MM $(comp_flags) $(sources) > .build_tmp/dependencies
-include .build_tmp/dependencies

# Force re-compiling when compiler flags change
$(objects): .build_tmp/compiler_flags
.build_tmp/compiler_flags: .build_tmp
	@echo '$(comp_flags)' | cmp -s - $@ || echo '$(comp_flags)' > $@

# Force re-linking when linker flags change
lib$(lib_name).so: .build_tmp/linker_flags
.build_tmp/linker_flags: .build_tmp
	@echo '$(link_flags)' | cmp -s - $@ || echo '$(link_flags)' > $@

# Force re-compiling and re-linking when the Makefile changes
$(objects): Makefile
lib$(lib_name).so: Makefile

clean:
	$(RM) -r .build_tmp/
	$(RM) *.o *.so

.PHONY: all clean
