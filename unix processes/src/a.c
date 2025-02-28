#include <stdio.h>
extern int f1();
extern int f2();

int main()
{
 
    // This prints hello world
    printf("Hello World from Main!\n");

    f1();   // Calling the function from b.c
    f2();   // Calling the function from c.c
 
    return 0;
}