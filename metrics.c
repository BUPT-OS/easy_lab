#include "uthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// --- Helper for timing ---
long long current_timestamp_us() {
    struct timeval te; 
    gettimeofday(&te, NULL);
    return te.tv_sec*1000000LL + te.tv_usec;
}

// --- Test 1: Basic Yielding & Correctness ---
// Each thread increments a shared counter N times.
// Total expected = num_threads * N
int shared_counter = 0;
void worker_func(void *arg) {
    int n = (long)arg;
    for (int i = 0; i < n; i++) {
        shared_counter++;
        uthread_yield();
    }
}

// --- Test 2: Performance Benchmark ---
// Two threads yielding back and forth N times.
void yield_func(void *arg) {
    int n = (long)arg;
    for (int i = 0; i < n; i++) {
        uthread_yield();
    }
}

int main() {
    init_uthreads();

    printf("=== Test 1: Functional Correctness ===\n");
    int num_threads = 10;
    int increments = 1000;
    shared_counter = 0;
    
    printf("Creating %d threads, each incrementing %d times...\n", num_threads, increments);
    for (int i = 0; i < num_threads; i++) {
        char name[16];
        sprintf(name, "T%d", i);
        uthread_create(worker_func, (void *)(long)increments, strdup(name));
    }
    
    schedule();
    
    printf("Expected Counter: %d\n", num_threads * increments);
    printf("Actual Counter:   %d\n", shared_counter);
    
    if (shared_counter == num_threads * increments) {
        printf("[PASS] Functional Test\n");
    } else {
        printf("[FAIL] Functional Test\n");
        exit(1);
    }

    printf("\n=== Test 2: Performance Benchmark ===\n");
    int perf_iterations = 1000000;
    printf("Running %d yields between 2 threads...\n", perf_iterations);
    
    // Create 2 threads
    uthread_create(yield_func, (void *)(long)perf_iterations, "P1");
    uthread_create(yield_func, (void *)(long)perf_iterations, "P2");
    
    long long start = current_timestamp_us();
    schedule();
    long long end = current_timestamp_us();
    
    long long elapsed = end - start;
    // Total switches = 2 * iterations (each yields 'iterations' times)
    // Wait, simple scheduling: T1 yield -> Main -> T2 yield -> Main -> T1...
    // Total context switches = 2 (to/from main) * 2 (threads) * iterations?
    // Let's count user-perceived yields. 2 * perf_iterations.
    long long total_yields = 2LL * perf_iterations;
    
    printf("Elapsed time: %lld us\n", elapsed);
    printf("Total yields: %lld\n", total_yields);
    printf("Time per yield: %.3f us\n", (double)elapsed / total_yields);
    printf("Yields per second: %.2f\n", 1000000.0 * total_yields / elapsed);
    
    printf("\n[PASS] All Tests Completed.\n");
    
    return 0;
}
