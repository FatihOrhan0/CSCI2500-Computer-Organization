/* Fatih Orhan hw2-part1.c
   Sample compilation:  gcc -Wall -Werror -Wvla hw2-part1.c -o part1.out */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main (int argc, char * argv[]) { 
    if (argc > 2) { 
        fprintf(stderr, "ERROR: Too many command line arguments.");
    }
    //a practical use of boolean with short
    short histogram = 0;
    if (argc == 2) { 
        if (!strcmp(argv[1], "-b")) { 
            histogram = 1;
        }
        else { 
            fprintf(stderr, "ERROR: Unknown flag");
        }
    } 

    //initialize the array
    int * chars = calloc(95, sizeof(int));

    //process the input stream
    char c;
    do {
        c = fgetc(stdin);
        if (c == '\0' || c == '\n') { 
            break;
        }
        if (isprint((int) c)) {
            chars[(int) c - 32]++;
        }
    } while (c);

    if (!histogram) { 
        for (int i = 0; i < 95; i++) { 
            if (chars[i] != 0) { 
                printf("%c: %d\n", (char) (i + 32), chars[i]);
            }
        }
    }
    else { 
        for (int i = 0; i < 95; i++) { 
            if (chars[i] != 0) { 
                printf("%c: ", (char) (i + 32));
                char * pounds = malloc(chars[i] + 1);
                memset(pounds, '#', chars[i]);
                pounds[chars[i]] = '\0';
                printf("%s", pounds);
                printf("\n");
                free(pounds);
            }
        }
    }
    free(chars);
}
