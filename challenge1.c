#include "uthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <fenv.h>
#include <assert.h>

void fpu_mode_worker(void *arg) {
    int mode = (long)arg;
    const char* mode_str = (mode == FE_UPWARD) ? "UPWARD" : "DOWNWARD";
    
    // Set rounding mode
    if (fesetround(mode) != 0) {
        printf("Failed to set rounding mode\n");
        exit(1);
    }
    
    for (int i = 0; i < 10000; i++) {
        uthread_yield();
        
        int current = fegetround();
        if (current != mode) {
            printf("[FAIL] Thread %s: Rounding mode corrupted! Expected %d, got %d\n", 
                   mode_str, mode, current);
            exit(1);
        }
    }
    // printf("Thread %s passed.\n", mode_str);
}

int main() {
    init_uthreads();
    
    int num_threads = 20;
    printf("Creating %d FPU mode threads...\n", num_threads);
    for (int i = 0; i < num_threads; i++) {
        int mode = (i % 2 == 0) ? FE_UPWARD : FE_DOWNWARD;
        uthread_create(fpu_mode_worker, (void*)(long)mode, "FPU");
    }
    
    schedule();
    
    printf("[PASS] FPU Mode Test Completed.\n");
    return 0;
}