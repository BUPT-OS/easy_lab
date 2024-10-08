# Author: Yexuan Yang
# Date: 2024/10/08

CFLAGS := -Wall -g -O0
CC := gcc
OBJS := uthread.o switch.o
TARGETS := simple pingpong recursion demo

# 默认目标
all: $(TARGETS)

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

# 清理规则
clean:
	rm -f $(TARGETS) $(OBJS)
