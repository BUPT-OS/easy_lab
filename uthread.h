#ifndef UTHREAD_H
#define UTHREAD_H

#include <stddef.h>
#define STACK_SIZE 4096

/// @brief 线程的状态
enum thread_state {
  THREAD_INIT,
  THREAD_RUNNING,
  THREAD_STOP,
  THREAD_SUSPENDED,
};

/// @brief 线程的上下文。
/// 其中
struct context {
  long long rip, rsp, rbp, rbx, r12, r13, r14, r15;
  long long rdi, rsi, rdx;
};

struct uthread {
  char stack[STACK_SIZE];
  struct context context;
  enum thread_state state;
  const char *name;
};

void init_uthreads();
void schedule();
struct uthread *uthread_create(void (*func)(void *), void *arg,const char* thread_name);
void thread_resume(struct uthread *tcb);
long long thread_yield();
void thread_destory(struct uthread *tcb);

#endif