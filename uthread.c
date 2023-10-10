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

  /*
  TODO: 在这里初始化uthread结构体。可能包括设置rip,rsp等寄存器。入口地址需要是函数_uthread_entry.
        除此以外，还需要设置uthread上的一些状态，保存参数等等。
        
        你需要注意rsp寄存器在这里要8字节对齐，否则后面从context switch进入其他函数的时候会有rsp寄存器
        不对齐的情况（表现为在printf里面Segment Fault）
  */
  return uthread;
}


void schedule() {
  /*
  TODO: 在这里写调度子线程的机制。这里需要实现一个FIFO队列。这意味着你需要一个额外的队列来保存目前活跃
        的线程。一个基本的思路是，从队列中取出线程，然后使用resume恢复函数上下文。重复这一过程。
  */
}

long long uthread_yield() {
  /*
  TODO: 用户态线程让出控制权到调度器。由正在执行的用户态函数来调用。记得调整tcb状态。
  */
  return 0;
}

void uthread_resume(struct uthread *tcb) {
  /*
  TODO：调度器恢复到一个函数的上下文。
  */
}

void thread_destory(struct uthread *tcb) {
  free(tcb);
}

void _uthread_entry(struct uthread *tcb, void (*thread_func)(void *),
                    void *arg) {
  /*
  TODO: 这是所有用户态线程函数开始执行的入口。在这个函数中，你需要传参数给真正调用的函数，然后设置tcb的状态。
  */
}

void init_uthreads() {
  /*
  TODO: 初始化用户态线程。对于我们的参考实现，在这里我们初始化了一些全局的静态变量。
  */
}