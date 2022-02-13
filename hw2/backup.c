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
            break; 
        }
        if (c == '\n') { 
            line[i] = '\0';
            break; 
        }
        i++;
    } while (i < n);
    line[n] = '\0';

    //read the rest of the line
    while (c != '\n') { 
        c = fgetc(file1);
    }
}

//returns the number of lines the file has
int countLines(char * filename) { 
    FILE * file = fopen(filename, "r");
    if (!file) { 
        fprintf(stderr, "ERROR: Could Not Open: %s", filename);
        return EXIT_FAILURE;
    }
    char c = '1';
    int newlines = 1;
    while (c > 0) { 
        c = fgetc(file); 
        if (c == '\n') { newlines++; }
    }
    fclose(file);
    return newlines;
}

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
            data[i][j] = malloc(sizeof(char) * maxChars[i]);
        }
    }
    fseek(file2, 0, SEEK_SET);
    for (int i = 0; i < lineCount; i++) { 
        int column = i % col;
        int row = i / col;
        fgets(data[column][row], 40, file2);
    }
    int * numberCols = calloc(col, sizeof(int));
    /* for (int i = 0; i < col; i++) { 
        char buffer[17];
        strcpy(buffer, titles[i]);
        buffer[6] = '\0';
        if (strcmp("Number", buffer) == 0) { 
            numberCols[i] = 1;
            printf("%d", i);
        }
    } */
    
    return EXIT_SUCCESS;
}

//this function processes the first file
int processFirst(char * filename, char * line, int * cols, char * letter, char * filename2) { 
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
    printf("   === %s ===\n\n", line);
    processSecond(filename2, *cols, *letter, colData);
    fclose(file1);
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