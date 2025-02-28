#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

int result[NUM_THREADS];  // Array to store results

// Thread function that will update the result array
void* thread_function(void* arg) {
    int index = *(int*)arg;
    result[index] = index + 1;  // For example, store index + 1
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int sum = 0;

    // Create threads in a loop
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;  // Passing index to each thread
        if (pthread_create(&threads[i], NULL, thread_function, &thread_args[i]) != 0) {
            perror("Thread creation failed");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Sum the elements of the result array
    for (int i = 0; i < NUM_THREADS; i++) {
        sum += result[i];
    }

    // Print the sum
    printf("Sum of elements: %d\n", sum);

    return 0;
}
