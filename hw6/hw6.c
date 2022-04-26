//Filename: hw6.c
//Purpose: Implementation file of hw6, which is extending on hw5's compiler.

//Sample compilation: gcc -g -Wall -Wextra -Wvla hw6.c -o test.exe

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>




int main(int argc, char * argv[]) { 
    if (argc > 1) { 
        printf("%s\n", argv[1]);
    }
    return EXIT_SUCCESS;
}