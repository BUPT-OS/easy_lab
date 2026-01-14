#include "uthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int shared_counter = 0;
int atomic_counter = 0;

void worker(void *arg) {
    long id = (long)arg;
    for (int i = 0; i < 1000; i++) {
        // Race condition generator
        int temp = shared_counter;
        // spin a bit
        for (volatile int j = 0; j < 100; j++);
        shared_counter = temp + 1;
        
        // Correct atomic
        __sync_fetch_and_add(&atomic_counter, 1);
        
        if (i % 200 == 0) uthread_yield();
    }
    
    printf("Thread %ld finished on pthread %lu\n", id, pthread_self());
}

int main() {
    init_uthreads();
    
    int num_threads = 20;
    printf("Creating %d threads on M:N scheduler...\n", num_threads);
    for (int i = 0; i < num_threads; i++) {
        uthread_create(worker, (void*)(long)i, "mn");
    }
    
    schedule(); 
    
    printf("Final Atomic Counter: %d (Expected %d)\n", atomic_counter, num_threads * 1000);
    printf("Final Shared Counter: %d (Expected < %d due to race)\n", shared_counter, num_threads * 1000);
    
    if (atomic_counter == num_threads * 1000) {
        printf("[PASS] M:N Scheduling Test (Atomic Correctness)\n");
    } else {
        printf("[FAIL] Atomic Counter mismatch\n");
        exit(1);
    }
    
    // Check if shared counter is corrupted (likely yes with 4 threads)
    // If it's equal, we might be lucky or running on 1 thread effectively.
    if (shared_counter < num_threads * 1000) {
        printf("[INFO] Race condition confirmed (Parallel execution verified)\n");
    } else {
        printf("[WARN] No race condition detected. Are we running sequentially?\n");
    }

    return 0;
}
