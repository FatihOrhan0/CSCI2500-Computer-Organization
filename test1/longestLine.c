#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024


void printLongestLines(char * filename) { 
    FILE * file = fopen(filename, "r"); 
    if (!file) { 
        fprintf(stderr, "ERROR: Cannot Open File");
        return;
    }
    char * c = malloc(MAX_LINE * sizeof(char)); 
    int max = 0;
    int len;
    do { 
        if(!fgets(c, MAX_LINE, file)) break;
        len = strlen(c);
        if (len > max) { 
            max = len;
        }
    } while (c);
    fseek(file, 0, SEEK_SET);

    do {
        if(!fgets(c, MAX_LINE, file)) break;
        if (strlen(c) == max) { 
            printf("%s", c);
        }
    } while (c); 
    free(c);
    fclose(file);
}

int main() { 
    printLongestLines("test.txt");
}