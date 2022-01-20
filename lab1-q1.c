#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char * createDashes(int n) { 
    char * c = (char*) malloc(sizeof(char) * (n + 1));
    for (int i = 0; i < n; i++) { 
        c[i] = '-';
    }
    c[n] = '\0';
    return c;
}

int main() { 
    char * eight;
    eight = createDashes(8);
    char * fifteen;
    fifteen = createDashes(15);
    
    printf("%7s%16s %16s", "i", "sqrt(i)", "cbrt(i)\n");
    printf("%s %s %s\n", eight, fifteen, fifteen);
    for (int i = 1; i < 31; i++) { 
        printf("%7d%16.9f%16.9f\n", i, pow(i, 0.5), pow(i, ((double) 1 / 3)));
    }
    printf("%s %s %s\n", eight, fifteen, fifteen);
    free(fifteen);
    free(eight);
}