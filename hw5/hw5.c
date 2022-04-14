//Filename: hw5.c
//Purpose: Implementation file for the 5th homework. The aim is to create a 
//rudimentary compiler that can compile addition and subtraction into c code.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//define the T registers in a string 
char * regs[18] = {"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9",
 "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7"};



int main(int argc, char * argv[]) { 
    if (argc != 2) { 
        fprintf(stderr, "ERROR: Incompatible Arguments!\n");
        return EXIT_FAILURE;
    }
    char * buffer = calloc(sizeof(char), 300);
    FILE * file = fopen(argv[1], "r");
    while ((buffer = fgets(buffer, 100, file))) { 
        for (unsigned int i = 0; i < sizeof(buffer); i++) { 
            printf("%c", buffer[i]);
        }
        printf("%s", buffer); 
    }
    return EXIT_SUCCESS;
}