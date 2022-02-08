/* Fatih Orhan hw2-part2.c
   Sample compilation:  gcc -Wall -Werror -Wvla hw2-part2.c -o part2.out */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//TODO: Parse the left of the first file. 
//start working on the second file.

//this function reads the first n characters and stores them in line
void readLine(char * line, FILE * file1, int n) { 
    int i = 0;
    char c;
    do { 
        c = fgetc(file1);
        if (isprint(c)) { 
            line[i] = c;
        }
        else { 
            line[i] = '\0';
            break; }
        if (c == '\n') { 
            line[i] = '\0';
            break; }
        i++;
    } while (i < n);
    line[n] = '\0';

    //read the rest of the line
    while (c != '\n') { 
        c = fgetc(file1);
    }
}

//this function processes the first file
int processFirst(char * filename, char * line, int * cols, char * letter) { 
    //open the file
    FILE * file1 = fopen(filename, "r");
    if (!file1) { 
        fprintf(stderr, "ERROR: cannot open %s.", filename);
        return EXIT_FAILURE;
    }
    //read the first 32 characters (if enough) to line
    readLine(line, file1, 32);

    printf("%s", line);
    //read the number of columns in colNumber and parse to int
    char * charCols = malloc(4 * sizeof(char));
    fgets(charCols, 4, file1);
    *cols = atoi(charCols);
    free(charCols);
    if (*cols == 0) { 
        fprintf(stderr, "ERROR: Expected a Non-Zero Number on The Second Line.\n");
        return EXIT_FAILURE;
    }

    //get the printable character in the next line
    * letter = fgetc(file1);
    if (fgetc(file1) != '\n') { 
        fprintf(stderr, "ERROR: Invalid Character.");
        return EXIT_FAILURE;
    }
    if (!isprint(*letter)) { 
        fprintf(stderr, "ERROR: Invalid Character.");
        return EXIT_FAILURE;
    }
    printf("%c %d\n", *letter, *cols);
    
    //allocate memory to store the columns
    char ** colData = malloc((*cols) * sizeof(char*));
    for (int i = 0; i < (*cols); i++) { 
        colData[i] = malloc(17 * sizeof(char));
    }

    for (int i = 0; i < (*cols); i++) { 
        readLine(colData[i], file1, 16);
    }
    for (int i = 0; i < (*cols); i++) { 
        printf("%s\n", colData[i]);
    } 
    return EXIT_SUCCESS;
}


int main (int argc, char * argv[]) { 
    if (argc != 3) { 
        fprintf(stderr, "ERROR: Wrong Use of Command Line Arguments.");
        return EXIT_FAILURE;
    }
    int * cols = malloc(sizeof(int));
    char line[33];
    char letter;
    processFirst(argv[1], line, cols, &letter);
    free(cols);
}