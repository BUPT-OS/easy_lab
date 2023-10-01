#include "uthread.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


static volatile int x = 0;

/*
print:
thread 1: 0
thread 2: 1
thread 3: 2
thread 4: 3
thread 5: 4
thread 1: 5
thread 2: 6
thread 3: 7
thread 4: 8
thread 5: 9
thread 1: 10
thread 2: 11
thread 3: 12
thread 4: 13
thread 5: 14
thread 1: 15
thread 2: 16
thread 3: 17
thread 4: 18
thread 5: 19
thread 1: 20
thread 2: 21
thread 3: 22
thread 4: 23
thread 5: 24
*/
void test_func(void* _arg){
    int arg = (intptr_t ) _arg;
    for(int i=0;i<5;i++){
        printf("thread %d: %d\n",arg,x);
        x++;
        uthread_yield();
    }
}

int main(){
    init_uthreads();
    uthread_create(test_func,(void*)1,NULL);
    uthread_create(test_func,(void*)2,NULL);
    uthread_create(test_func,(void*)3,NULL);
    uthread_create(test_func,(void*)4,NULL);
    uthread_create(test_func,(void*)5,NULL);

    schedule();
    return 0;
}