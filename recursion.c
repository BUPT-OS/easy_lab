#include "uthread.h"
#include <stdint.h>
#include <stdio.h>

long long factorial(int n)
{
    if(n == 0)
        return 1;
    else{
        uthread_yield();
        return n * factorial(n-1);
    }
}

void test_func(void* _arg){
    int arg = (intptr_t ) _arg;
    printf("%lld",factorial(arg));
}


int main(){
    init_uthreads();
    uthread_create(test_func,(void*)10,"a");
    uthread_create(test_func,(void*)11,"b");
    schedule();
    return 0;
}