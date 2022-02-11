//File name: hw2-helper.h
//Purpose: Storing the helper functions of the second part of hw2

#include <string.h>
typedef enum{false, true} bool;

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
    line[i] = '\0';

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
    int newlines = 0;
    while (c > 0) { 
        c = fgetc(file); 
        if (c == '\n') { newlines++; }
    }
    fclose(file);
    return newlines;
}


//deletes the trailing newline characters
void deleteNewlines(char * c) { 
    int len = strlen(c);
    for (int i = 0; i < len; i++) { 
        if (c[i] == '\n') { 
            c[i] = '\0';
            break;
        }
    }
}

//this function prints the formatted line for a given string
void printLine(bool left, bool right, char * s, bool isString, int space) {     
    if (left) printf("|");
    if (isString) {
        printf(" %*s ", space , s);
    }
    //change below
    else { 
        char * dashes = malloc(space * sizeof(char));
        memset(dashes, '-', space);
        printf(" %s ", dashes);
        free(dashes);
    }
    if (right) printf("|");
}
