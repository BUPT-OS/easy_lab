#include "uthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static struct uthread *current_thread = NULL;
static struct uthread *main_thread = NULL;

extern void thread_switch(struct context *from, struct context *to);
void _uthread_entry(struct uthread *tcb, void (*thread_func)(void *),
                    void *arg);

static inline void make_dummpy_context(struct context *context) {
  memset((struct context *)context, 0, sizeof(struct context));
}

struct uthread *uthread_create(void (*func)(void *), void *arg,const char* thread_name) {
  struct uthread *uthread = NULL;
  int ret;
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

long long thread_yield() {
  // TODO:
  return 0;
}

void thread_resume(struct uthread *tcb) {
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