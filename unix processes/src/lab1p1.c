#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// Take the inputs 
int main(int argc, char *argv[]){
    if (argc <2){
        fprintf(stderr,"Invalid Input Format");
    }

    char *arguments[100][8];
    char *variable[8];
    int pos = 0;
    int arg_count = 0;

    // Correctly map and store each process in the arguments array
    for ( int i= 1; i < argc ; i++){

        if (strcmp(argv[i],"+") == 0){
            arg_count ++;
            pos = 0;
        }
        else{
            arguments[arg_count][pos] = argv[i];
            pos++;
        }
    }

    // Create a child process one at a time and execute the process
    for (int j=0; j<arg_count+1; j++) {

        int pid = fork();

        if (pid == -1){
            return 1;
        }
        else if (pid == 0){
            execve(arguments[j][0], arguments[j], NULL);
            exit(1);
        }
        else{
            wait(NULL);
        }
    }

     return 0;
}
