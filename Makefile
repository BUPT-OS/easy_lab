all: demo tests
.PHONY: clean dump tests
CFLAGS := -Wall -g -O0
CC := gcc

uthread.o: uthread.c 
	$(CC) $(CFLAGS) -c $^ -o $@ 
switch.o: switch.S
	$(CC) $(CFLAGS) -c $^ -o $@

simple : simple.c uthread.o switch.o
	$(CC) $(CFLAGS) -o $@ $^

pingpong : pingpong.c uthread.o switch.o
	$(CC) $(CFLAGS) -o $@ $^
	
recursion : recursion.c uthread.o switch.o
	$(CC) $(CFLAGS) -o $@ $^
demo : demo.c switch.o
	$(CC) $(CFLAGS) -o $@ $^
tests: simple pingpong recursion
	./simple
	./pingpong
	./recursion

clean:
	rm -f simple uthread.o switch.o test_simple.S pingpong recursion