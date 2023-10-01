#include "uthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static struct uthread *current_thread = NULL;
static struct uthread *main_thread = NULL;

/// @brief 切换上下文
/// @param from 当前上下文
/// @param to 要切换到的上下文
extern void thread_switch(struct context *from, struct context *to);

/// @brief 线程的入口函数
/// @param tcb 线程的控制块
/// @param thread_func 线程的执行函数
/// @param arg 线程的参数
void _uthread_entry(struct uthread *tcb, void (*thread_func)(void *),
                    void *arg);

/// @brief 清空上下文结构体
/// @param context 上下文结构体指针
static inline void make_dummpy_context(struct context *context) {
  memset((struct context *)context, 0, sizeof(struct context));
}

struct uthread *uthread_create(void (*func)(void *), void *arg,const char* thread_name) {
  struct uthread *uthread = NULL;
  int ret;

  // 申请一块16字节对齐的内存
  ret = posix_memalign((void **)&uthread, 16, sizeof(struct uthread));
  if (0 != ret) {
    printf("error");
    exit(-1);
  }

  //         +------------------------+
  // low     |                        |
  //         |                        |
  //         |                        |
  //         |         stack          |
  //         |                        |
  //         |                        |
  //         |                        |
  //         +------------------------+
  //  high   |    fake return addr    |
  //         +------------------------+


  // TODO:
  return uthread;
}


void schedule() {
  //TODO:
}

long long uthread_yield() {
  // TODO:
  return 0;
}

void uthread_resume(struct uthread *tcb) {
  // TODO:
}

void thread_destory(struct uthread *tcb) {
  free(tcb);
}

void _uthread_entry(struct uthread *tcb, void (*thread_func)(void *),
                    void *arg) {
  // TODO:
}

void init_uthreads() {
  // TODO:
}