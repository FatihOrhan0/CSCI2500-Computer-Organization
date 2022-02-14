#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

void storeFile(int n, FILE * file, short tail) {
    char * temp = calloc(MAX_LINE, sizeof(char)); 
    int lineCount = 0;
    while (fgets(temp, MAX_LINE, file)) { 
        lineCount++;
    }

    fseek(file, 0, SEEK_SET);

    char ** res = malloc(lineCount * sizeof(char*));
    for (int i = 0; i < lineCount; i++) { 
        res[i] = malloc(1024 * sizeof(char));
    }
    for (int i = 0; i < lineCount; i++) { 
        fgets(res[i], MAX_LINE, file);
    }
    if (n > lineCount) { 
        return;
    }
    if (tail) { 
        for (int i = 0; i < n; i++) { 
            if (n == 0) { 
                printf("%s\n", res[lineCount - 1]);
            }
            else { 
                printf("%s", res[lineCount - 1 - i]);
            }
        }
    }
    else { 
        for (int i = 0; i < n; i++) { 
            printf("%s", res[i]);
        }
    }
    for (int i = 0; i < lineCount; i++) { 
        free(res[i]);
    }
    free(res);
}

int main(int argc, char * argv[]) { 
    if (argc != 4) { 
        fprintf(stderr, "ERROR");
    }
    FILE * file = fopen(argv[3], "r");
    if (!file) { 
        fprintf(stderr, "ERROR");
        return EXIT_FAILURE;
    }
    short tail = 0;
    if (strcmp(argv[1], "tail")) tail = 1;
    storeFile(-atoi(argv[2]), file, tail);
}