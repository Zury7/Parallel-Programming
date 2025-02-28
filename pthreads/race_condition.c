#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int x = 0;

void *increment_x(void *arg) {
    for (int i = 0; i < 10; i++) {
        x++;
        printf("Increment Thread: x = %d\n", x);
        usleep(10000); // Small delay to increase race condition visibility
    }
    return NULL;
}

void *decrement_x(void *arg) {
    for (int i = 0; i < 10; i++) {
        x--;
        printf("Decrement Thread: x = %d\n", x);
        usleep(10000); // Small delay to increase race condition visibility
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, increment_x, NULL);
    pthread_create(&t2, NULL, decrement_x, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final value of x: %d\n", x);
    return 0;
}
