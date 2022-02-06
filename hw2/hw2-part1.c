/* Fatih Orhan hw2-part1.c
   Sample compilation:  gcc -Wall -Werror -Wvla hw2-part1.c -o part1.out */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>




int main (int argc, char * argv[]) { 
    //initialize the array
    int * chars = calloc(95, sizeof(int));
    
    do {
        char c = fgetc(stdin);
        if (c == '\0' || c == '\n') { 
            break;
        }
        if (isprint((int) c)) {
            chars[(int) c - 32]++;
        }
    } while (1);
    printf("%d", chars[0]);
    for (int i = 0; i < 95; i++) { 
        if (chars[i] != 0) { 
            printf("%c: %d\n", (char) chars[i] + 32, chars[i]);
        }
    }
    free(chars);
}
