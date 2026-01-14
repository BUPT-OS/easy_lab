#include "uthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int stop_flag = 0;

void spinner(void *arg) {
    int id = (long)arg;
    // printf("Spinner %d started\n", id); 
    // Commented out printf to avoid I/O blocking/yielding implicitly
    while (!stop_flag) {
        // Spin
    }
    printf("Spinner %d exited\n", id);
}

void stopper(void *arg) {
    printf("Stopper running\n");
    stop_flag = 1;
}

int main() {
    init_uthreads();
    
    int num_spinners = 8; // > 4 workers
    for (int i = 0; i < num_spinners; i++) {
        uthread_create(spinner, (void*)(long)i, "spinner");
    }
    
    uthread_create(stopper, NULL, "stopper");
    
    printf("Starting schedule with %d spinners and 1 stopper...\n", num_spinners);
    schedule();
    
    printf("[PASS] Preemption Test (All threads finished)\n");
    return 0;
}
