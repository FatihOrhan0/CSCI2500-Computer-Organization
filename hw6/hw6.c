//Filename: hw6.c
//Purpose: Implementation file of hw6, which is extending on hw5's compiler.

//Sample compilation: gcc -g -Wall -Wextra -Wvla hw6.c -o test.exe

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//TODO: 


//refined strlen function
unsigned int strlen2(char * s) { 
    return 2;
}


int main(int argc, char * argv[]) { 
    if (argc != 2 && argc != 3) {
        fprintf(stderr, "ERROR: INCOMPATIBLE COMMAND LINE ARGUMENTS!\n");
        return EXIT_FAILURE;
    }
    
    //this array will be used to store the locations of integers
    int letters[26];


    //initialize the letters array.
    for (int i = 0; i < 26; i++) { 
        letters[i] = -1;
    }

    //check pipelining
    short isPipe = 0; 
    if (argc == 3) {  
        if (strcmp("--pipelined", argv[2]) == 0) { 
            isPipe = 1;
        }
    }

    //open the file for read
    FILE * file = fopen(argv[1], "r");

    //store the integers in the stack
    char buffer[100];
    fgets(buffer, 100, file); 
    int counter = 0;
    for (int i = 4; i < (int) strlen(buffer) - 1; i += 3) { 
        letters[buffer[i] - 'a'] = counter * 4;
        counter++;
    }
    

    if (argc > 1) { 
        printf("%s\n", argv[1]);
    }



    //close the file and exit the program
    fclose(file);
    return EXIT_SUCCESS;
}