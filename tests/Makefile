
mrt_cflags  = $(CPPFLAGS) $(CFLAGS) -g -I.. -std=c99 -Wall -Wextra -Werror
mrt_ldflags = $(LDFLAGS) -L../mlib -lmlib

all: run_tests

checks = check_memory.o check_strutils.o check_none.o check_boolean.o \
	check_integer.o check_real.o check_string.o check_pointer.o check_list.o

run_tests: CuTest.o main.o $(checks)
	$(CC) $(mrt_cflags) -o $@ $^ $(mrt_ldflags)

CuTest.o: CuTest.c CuTest.h
	$(CC) -c -fPIC $(mrt_cflags) -o $@ $<

main.o: main.c
	$(CC) -c -fPIC $(mrt_cflags) -o $@ $<

check_memory.o: check_memory.c
	$(CC) -c -fPIC $(mrt_cflags) -o $@ $<

check_strutils.o: check_strutils.c
	$(CC) -c -fPIC $(mrt_cflags) -o $@ $<

check_none.o: check_none.c
	$(CC) -c -fPIC $(mrt_cflags) -o $@ $<

check_boolean.o: check_boolean.c
	$(CC) -c -fPIC $(mrt_cflags) -o $@ $<

check_integer.o: check_integer.c
	$(CC) -c -fPIC $(mrt_cflags) -o $@ $<

check_real.o: check_real.c
	$(CC) -c -fPIC $(mrt_cflags) -o $@ $<

check_string.o: check_string.c
	$(CC) -c -fPIC $(mrt_cflags) -o $@ $<

check_pointer.o: check_pointer.c
	$(CC) -c -fPIC $(mrt_cflags) -o $@ $<

check_list.o: check_list.c
	$(CC) -c -fPIC $(mrt_cflags) -o $@ $<

clean:
	$(RM) *.o run_tests

.PHONY: all clean
