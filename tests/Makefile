
mrt_cflags  = $(CPPFLAGS) $(CFLAGS) -g -I.. -std=c99 -Wall -Wextra -Werror
mrt_ldflags = $(LDFLAGS) -L../mrt -lmrt

all: run_tests

run_tests: CuTest.o main.o check_memory.o
	$(CC) $(mrt_cflags) -o $@ $^ $(mrt_ldflags)

CuTest.o: CuTest.c CuTest.h
	$(CC) -c -fPIC $(mrt_cflags) -o $@ $<

main.o: main.c check_memory.c
	$(CC) -c -fPIC $(mrt_cflags) -o $@ $<

check_memory.o: check_memory.c ../mrt/memory.c ../mrt/memory.h
	$(CC) -c -fPIC $(mrt_cflags) -o $@ $<

clean:
	$(RM) *.o run_tests

.PHONY: all clean
