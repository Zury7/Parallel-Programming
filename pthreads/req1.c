#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 3

void *thread_function(void *arg) {
    int thread_num = *(int *)arg;
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    
    printf("Thread %d (ID: %ld) started at %ld.%ld seconds\n", thread_num, pthread_self(), ts.tv_sec, ts.tv_nsec);
    
    // Simulating rolling a dice
    srand(time(NULL) ^ pthread_self());
    int dice_roll = (rand() % 6) + 1;
    printf("Thread %d (ID: %ld) rolled a dice and got: %d\n", thread_num, pthread_self(), dice_roll);
    
    clock_gettime(CLOCK_REALTIME, &ts);
    printf("Thread %d (ID: %ld) finished at %ld.%ld seconds\n", thread_num, pthread_self(), ts.tv_sec, ts.tv_nsec);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_args[i]) != 0) {
            perror("pthread_create failed");
            return 1;
        }
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("All threads have completed.\n");
    return 0;
}
