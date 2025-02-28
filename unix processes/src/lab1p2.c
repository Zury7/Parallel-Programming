#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

// Take the first command line argument 
int main(int argc, char *argv[]){
    char *arguments[argc];
    int percent_count = 0;
    int argument_count = 0;

    for (int i=0;i<argc;i++){       // Nullify the array
        arguments[i]=NULL;
    }

    for (int i=1;i<argc;i++) {      // Count the number of % marks and args 
        if (strcmp("%", argv[i])==0){
            percent_count++;
        }
        else {
            arguments[i-1] = argv[i];
            argument_count++;
        }
    }

    // Take the each input argument one by one to process in a while loop
    char inputLine[100];
    char *array[100];
    while (fgets(inputLine, sizeof(inputLine), stdin) != NULL){

        for (int i=0;i<100;i++){     // Nullify the array
            array[i]=NULL;
        }

        inputLine[strcspn(inputLine, "\n")] = '\0';

        char *token = strtok(inputLine, " ");   
        int count = 0;

        while (token != NULL){      // Eliminate the free spaces 
            array[count] = token;
            count++;
            token = strtok(NULL, " ");
        }

        // Create a final arguments array in a manner of [ <command>, arg1,arg2,....]
        char *final_arguments[argument_count+count+1];

        int final_argument_count = 0;

        for (int i=0;i<argument_count;i++){
            final_arguments[i] = arguments[i];
            final_argument_count++;
        }

        for (int i=0;i<count;i++){
            final_arguments[final_argument_count] = array[i];
            final_argument_count++;
        }

        final_arguments[final_argument_count] = NULL;

        // Create a child process and execute the command by replacing execvp()'s arguments by 
        // iterating the final arguments array

        int pid = fork();

        if (pid == 0){
            execvp(final_arguments[0], final_arguments);
            exit(1);
        }
        else {
            int status;
            waitpid(pid, &status, 0);
        }       
    }
    return 0;    
}