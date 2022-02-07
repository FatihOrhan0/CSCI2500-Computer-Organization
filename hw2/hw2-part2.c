/* Fatih Orhan hw2-part2.c
   Sample compilation:  gcc -Wall -Werror -Wvla hw2-part2.c -o part2.out */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//TODO: Parse the left of the first file. 
//start working on the second file.

//this function processes the first file
int processFirst(char * filename, char * line, int * cols, char * letter) { 
    //open the file
    FILE * file1 = fopen(filename, "r");
    if (!file1) { 
        fprintf(stderr, "ERROR: cannot open %s.", filename);
        return EXIT_FAILURE;
    }
    fgets(line, 33, file1);
    //if there exists a trailing new line character, get rid of it.
    for (int i = 0; i < 33; i++) { 
        if (line[i] == '\n') { 
            line[i] = '\0';
            break;
        }
    }
    //read the number of columns in colNumber and parse to int
    char * charCols = malloc(4 * sizeof(char));
    fgets(charCols, 4, file1);
    *cols = atoi(charCols);
    free(charCols);
    if (*cols == 0) { 
        fprintf(stderr, "ERROR: Expected a Non-Zero Number on The Second Line.\n");
        return EXIT_FAILURE;
    }
    * letter = fgetc(file1);
    if (fgetc(file1) != '\n') { 
        fprintf(stderr, "ERROR: Invalid Character.");
        return EXIT_FAILURE;
    }
    if (!isprint(*letter)) { 
        fprintf(stderr, "ERROR: Invalid Character.");
        return EXIT_FAILURE;
    }
    printf("%c", *letter);
    return EXIT_SUCCESS;
}


int main (int argc, char * argv[]) { 
    if (argc != 3) { 
        fprintf(stderr, "ERROR: Wrong Use of Command Line Arguments.");
        return EXIT_FAILURE;
    }
    int * cols = malloc(sizeof(int));
    char line[32];
    char letter;
    processFirst(argv[1], line, cols, &letter);
    free(cols);
}