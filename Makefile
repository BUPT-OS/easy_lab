# Author: Yexuan Yang
# Date: 2024/10/08

CFLAGS := -Wall -g -O0
CC := gcc
OBJS := uthread.o switch.o
TARGETS := simple pingpong recursion demo

# 默认目标
all: $(TARGETS) tests

.PHONY: clean tests

# 目标编译规则
uthread.o: uthread.c
	$(CC) $(CFLAGS) -c $^ -o $@

switch.o: switch.S
	$(CC) $(CFLAGS) -c $^ -o $@

# 自动生成可执行文件的规则
$(TARGETS): % : %.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 测试规则
tests: simple pingpong recursion
	./simple
	./pingpong
	./recursion

metrics: metrics.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	./metrics

challenge1: challenge1.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm
	./challenge1

challenge2: challenge2.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	./challenge2

challenge3: challenge3.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm
	./challenge3

# 清理规则
clean:
	rm -f $(TARGETS) $(OBJS) metrics challenge1 challenge2 challenge3 
