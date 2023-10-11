#include "uthread.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
static struct uthread *current_thread = NULL;
static struct uthread *main_thread = NULL;

extern void thread_switch(struct context *from, struct context *to);

void bug(){
    printf("missing return address\n");
    exit(-1);
}

void test(){
    printf("hello,%d\n",1);
    thread_switch(&current_thread->context,&main_thread->context);
}

int main(){
    long long sp;
    main_thread = malloc(sizeof(struct uthread));
    memset(main_thread,0,sizeof(struct uthread));

    current_thread = malloc(sizeof(struct uthread));
    memset(current_thread,0,sizeof(struct uthread));

    current_thread->context.rip = (long long)test;
    sp = ((long long)&current_thread->stack + STACK_SIZE) & (~(long long)15);
    sp -= 8;
    *(long long*)sp = (long long)bug;
    current_thread->context.rsp = sp;

    thread_switch(&main_thread->context,&current_thread->context);
    printf("main\n");
    return 0;
}