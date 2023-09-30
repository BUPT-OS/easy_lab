all: simple pingpong recursion
.PHONY: clean dump
CFLAGS := -Wall -Werror -g -O0
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

dump:
	objdump -d test_simple > test_simple.S

clean:
	rm -f simple uthread.o switch.o test_simple.S pingpong recursion