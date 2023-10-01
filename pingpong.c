#include "uthread.h"
#include <stdint.h>
#include <stdio.h>


/**
should print:
thread 1: 0
thread 2: 0
thread 1: 1
thread 2: 1
thread 1: 2
thread 2: 2
thread 1: 3
thread 2: 3
thread 1: 4
thread 2: 4
*/
void test_func1(void* _arg){
    int arg = (intptr_t ) _arg;
    for(int i=0;i<5;i++){
        printf("thread %d: %d\n",arg,i);
        uthread_yield();
    }
}


int main(){
    init_uthreads();
    uthread_create(test_func1,(void*)1,NULL);
    uthread_create(test_func1,(void*)2,NULL);
    schedule();
    return 0;
}