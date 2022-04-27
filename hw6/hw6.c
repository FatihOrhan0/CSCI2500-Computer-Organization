//Filename: hw6.c
//Purpose: Implementation file of hw6, which is extending on hw5's compiler.

//Sample compilation: gcc -g -Wall -Wextra -Wvla hw6.c -o test.exe

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//TODO: 


//a function to check if a string is an integer
int isNum(char * s) { 
    int j = 0; 
    while (s[j] != '\0') { 
        if (s[j] > 47 && s[j] < 58) { 
            j++; continue; 
        }
        return 0;
    }
    return 1;
}


//count the number of spaces to determine the operator count
int countSpaces(char * s) { 
    int i = 0, spaces = 0; 
    while (s[i] != '\0') { 
        if (s[i] == ' ') spaces++;
        i++; 
    }
    return spaces;  
}

//define the registers as strings
const char * tregs[10] = {"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9"};
const char * sregs[8] = {"s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7"};


int main(int argc, char * argv[]) { 
    if (argc != 2 && argc != 3) {
        fprintf(stderr, "ERROR: INCOMPATIBLE COMMAND LINE ARGUMENTS!\n");
        return EXIT_FAILURE;
    }
    
    //this array will be used to store the locations of integers
    int letters[26];
    //store the last used t register
    int t = 0;


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