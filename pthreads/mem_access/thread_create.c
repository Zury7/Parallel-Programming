#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int x = 0;
pthread_mutex_t lock;

void *increment_x(void *arg) {
    pthread_mutex_lock(&lock);
    x++;
    printf("Thread 1: Incremented x to %d\n", x);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *print_x(void *arg) {
    pthread_mutex_lock(&lock);
    printf("Thread 2: x = %d\n", x);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, increment_x, NULL);
    pthread_join(t1, NULL);

    pthread_create(&t2, NULL, print_x, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}
