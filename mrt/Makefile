#!/usr/bin/env make

mrt_sources = $(wildcard *.c)
mrt_headers = $(wildcard *.h)
mrt_objects = $(mrt_sources:.c=.o)
mrt_cflags  = $(CPPFLAGS) $(CFLAGS) -g -I.. -std=c99 -Wall -Wextra -Werror
mrt_ldflags = $(LDFLAGS)

all: libmrt.so

libmrt.so: $(mrt_objects)
	$(CC) -shared $(mrt_cflags) -o $@ $^ $(mrt_ldflags)

%.o: %.c $(mrt_headers)
	$(CC) -c -fPIC $(mrt_cflags) -o $@ $<

clean:
	$(RM) *.o *.so
