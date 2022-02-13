/* Fatih Orhan hw2-part2.c
   Sample compilation:  gcc -Wall -Werror -Wvla hw2-part2.c -o part2.out */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "hw2-helper.h"


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
    for (int i = 0; i < lineCount; i++) { 
        char c = 'a';
        int temp = 0;
        do { 
            c = fgetc(file2);
            if (c == '\n') { break; }
            temp++;
        } while (c != '\n');
        if (temp > maxChars[i % col]) { 
            maxChars[i % col] = temp;
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
        readLine(data[column][row], file2, maxChars[column] + 3);
    }
    
    for (int i = 0; i < col; i++) { 
        int len = strlen(titles[i]);
        if (len > maxChars[i]) { 
            maxChars[i] = len;
        }
    }

   int * numberCols = calloc(col, sizeof(int));
    for (int i = 0; i < col; i++) { 
        char buffer[17];
        strcpy(buffer, titles[i]);
        buffer[6] = '\0';
        if (strcmp("Number", buffer) == 0) { 
            numberCols[i] = 1;
        }
    } 

    for (int i = 0; i < col; i++) { 
        if (numberCols[i]) { 
            int max = maxChars[i];
            for (int j = 0; j < lineCount / col; j++) { 
                if (atoi(data[i][j]) > max) { max = atoi(data[i][j]); }
            }
            maxChars[i] = max;
        }
    }
    // printf("%d %d\n", maxChars[0], lineCount);
    for (int i = 0; i < col; i++) { 
        if (!numberCols[i]) { 
            if (col == 1) { 
                printf(" %*s\n", maxChars[i], titles[i]);
            }
            else if (i != col - 1) { 
            printf(" %*s |", maxChars[i], titles[i]);
            }
            else { 
                printf(" %*s\n", maxChars[i], titles[i]);
            }
        }
        else { 
            if (col == 1) { 
                printf("%-*s\n", maxChars[i], titles[i]);
            }
            if (i != col - 1) { 
                printf(" %-*s |", maxChars[i], titles[i]);
            }
            else { 
                printf(" %s\n", titles[i]);
            }
        }
    }
    for (int i = 0; i < col; i++) { 
        char * letters = malloc(sizeof(char) * (maxChars[i] + 1));
        memset(letters, '-', maxChars[i]);
        letters[maxChars[i]] = 0;
        printf("-%s-", letters);
        if (col == 1) { 
            printf("\n");
         }
        else if (i != col - 1) { 
            printf("|");
        }
        else { 
            printf("\n");
        }
        free(letters);
    }

    for (int i = 0; i < lineCount; i++) { 
        int column = i % col;
        int row = i / col;
        if (!numberCols[column]) { 
            if (col == 1) { 
                printf(" %*s\n", maxChars[column], data[column][row]);
            }
            else if (column < col - 1) { 
                printf(" %*s |", maxChars[column], data[column][row]);
            }
            else { 
                printf(" %*s\n", maxChars[column], data[column][row]);
            }
        }
        else { 
            if (column < col - 1 || col == 1) { 
                if (atoi(data[column][row]) == 0) { printf("\n"); }
                char * letters = malloc(sizeof(char) * (atoi(data[column][row]) + 1));
                memset(letters, letter, atoi(data[column][row]));
                letters[atoi(data[column][row])] = 0;
                printf(" %-*s |", maxChars[column], letters);
                free(letters);
            }
            else { 
                if (atoi(data[column][row]) == 0) { printf("\n"); }
                char * letters = malloc(sizeof(char) * (atoi(data[column][row]) + 1));
                memset(letters, letter, atoi(data[column][row]));
                letters[atoi(data[column][row])] = 0;
                printf(" %s\n", letters);
                free(letters);
            }
        }
    }
    for (int i = 0; i < col; i++) { 
        char * letters = malloc(sizeof(char) * (maxChars[i] + 1));
        memset(letters, '-', maxChars[i]);
        letters[maxChars[i]] = 0;
        printf("-%s-", letters);
        if (col == 1) { 
            
        }
        else if (i != col - 1) { 
            printf("|");
        }
        else { 
            printf("\n");
        }
        free(letters);
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
    fclose(file2);
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
    for (int i = 0; i < (int) strlen(line); i++) { 
        line[i] = toupper(line[i]);
    }
    printf("   === %s ===\n\n", line);

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