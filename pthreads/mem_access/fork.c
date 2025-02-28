#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void increment_x() {
    int x = 0;  // x is now local to this function and not shared
    x++;
    printf("Child Process: Incremented x to %d\n", x);
}

void print_x() {
    int x = 0;  // Each process gets its own copy
    printf("Parent Process: x = %d\n", x);
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process: Increment x
        increment_x();
    } else {
        // Parent process: Wait for child, then print x
        wait(NULL);
        print_x();
    }

    return 0;
}