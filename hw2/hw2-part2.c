/* Fatih Orhan hw2-part2.c
   Sample compilation:  gcc -Wall -Werror -Wvla hw2-part2.c -o part2.out */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "hw2-helper.h"

//TODO: Create a writeline function that takes left | right | string to print, 
//int/string as arguments
//clear out the wasted memory
//create a function to hard code the column titles
//create a function to print the dashes (by storing the entire line in a string)
//organize the files and functions
//consider using memset


//this function reads the second file and prints the expected output
int processSecond(char * filename, int col, char letter, char ** titles) { 
    int lineCount = countLines(filename); 
    FILE * file2 = fopen(filename, "r");
    if (!file2) { 
        fprintf(stderr, "ERROR: Could Not Open: %s", filename);
        return EXIT_FAILURE;
    }
    //store the max number of characters in an int array
    int * maxChars = calloc(col, sizeof(int));
    for (int i = 0; i < lineCount - 1 ; i++) { 
        char c = 'a';
        int temp = 0;
        do { 
            c = fgetc(file2);
            if (c == '\n') { break; }
            temp++;
        } while (c != '\n');
        if (temp - 1 > maxChars[i % col]) { 
            maxChars[i % col] = temp - 1;
        }
    }
    char *** data = malloc(sizeof(char**) * col);
    for (int i = 0; i < col; i++) { 
        data[i] = malloc(sizeof(char*) * lineCount / col);
    }
    for (int i = 0; i < col; i++) { 
        for (int j = 0; j < lineCount / col; j++) { 
            data[i][j] = malloc(sizeof(char) * maxChars[i] + 3);
        }
    }
    fseek(file2, 0, SEEK_SET);
    
    for (int i = 0; i < lineCount; i++) { 
        int column = i % col;
        int row = i / col;
        if (!fgets(data[column][row], maxChars[column] + 3, file2)) { 
            printf("%d %d %d\n", column, row, lineCount);
        }
        deleteNewlines(data[column][row]/* , maxChars[column] + 2 */);
    }
    
    for (int i = 0; i < col; i++) { 
        int len = strlen(titles[i]);
        if (len > maxChars[i]) { 
            maxChars[i] = len;
        }
        printf("%d %s \n", maxChars[i], titles[i]);
    }

    /* for (int i = 0; i < lineCount; i++) { 
        int column = i % col;
        int row = i / col;
        printf("%s\n", data[column][row]);
    } */

    for (int i = 0; i < lineCount; i++) { 
        int column = i % col;
        int row = i / col;
        // printf("%d %d %s", column, row, data[column][row]);
        if (column < col - 1) { 
            printf(" %*s |", maxChars[column] + 1, data[column][row]);
            // printLine(0, 1, data[column][row], 1, 20);
        }
        else { 
            printf(" %*s \n", maxChars[column] + 1, data[column][row]);
            // printLine(1, 0, data[column][row], 1, 20);
        }
    }
    printf("\n\n\n%s", data[0][0]);

    int * numberCols = calloc(col, sizeof(int));
    for (int i = 0; i < col; i++) { 
        char buffer[17];
        strcpy(buffer, titles[i]);
        buffer[6] = '\0';
        if (strcmp("Number", buffer) == 0) { 
            numberCols[i] = 1;
            printf("%d", i);
        }
    } 
    for (int j = 0; j < col; j++) { 
        for (int i = 0; i < lineCount / col; i++) { 
            free(data[j][i]);
        }
        free(data[j]);
    }
    free(numberCols);
    free(maxChars);
    free(data);
    return EXIT_SUCCESS;
}

//this function processes the first file
int processFirst(char * filename, char * line, int * cols, char * letter, char * secondFile) { 
    //open the file
    FILE * file1 = fopen(filename, "r");
    if (!file1) { 
        fprintf(stderr, "ERROR: cannot open %s.", filename);
        return EXIT_FAILURE;
    }
    //read the first 32 characters (if enough) to line
    readLine(line, file1, 32);

    //read the number of columns in colNumber and parse to int
    char * charCols = malloc(4 * sizeof(char));
    fgets(charCols, 4, file1);
    *cols = atoi(charCols);
    free(charCols);
    if (*cols == 0) { 
        fclose(file1);
        fprintf(stderr, "ERROR: Expected a Non-Zero Number on The Second Line.\n");
        return EXIT_FAILURE;
    }

    //get the printable character in the next line
    * letter = fgetc(file1);
    if (fgetc(file1) != '\n') { 
        fclose(file1);
        fprintf(stderr, "ERROR: Invalid Character.");
        return EXIT_FAILURE;
    }
    if (!isprint(*letter)) { 
        fclose(file1);
        fprintf(stderr, "ERROR: Invalid Character.");
        return EXIT_FAILURE;
    }
    
    //allocate memory to store the columns
    char ** colData = malloc((*cols) * sizeof(char*));
    for (int i = 0; i < (*cols); i++) { 
        colData[i] = malloc(17 * sizeof(char));
    }

    for (int i = 0; i < (*cols); i++) { 
        readLine(colData[i], file1, 16);
    }
    processSecond(secondFile, *cols, *letter, colData);
    fclose(file1);
    for (int i = 0; i < *cols; i++) { 
        free(colData[i]);
    }
    free(colData);
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
    processFirst(argv[1], line, cols, &letter, argv[2]);
    
    free(cols);
}