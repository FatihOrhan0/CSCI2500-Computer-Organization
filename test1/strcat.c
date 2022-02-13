#include <stdio.h>
#include <stdlib.h>


char * strcat(char * s1, char * s2) { 
    char * temp = s1;
    int len1 = 0;
    while (temp && *temp != 0) { 
        len1++;
        temp++;
    }
    temp = s2;
    int len2 = 0; 
    while (temp && *temp != 0) { 
        len2++;
        temp++;
    }
    char * res = malloc((len1 + len2 + 1) * sizeof(char));
    for (int i = 0; i < len1; i++) { 
        *(res + i) = *(s1 + i);
    }
    for (int i = len1; i < len1 + len2; i++) { 
        *(res + i) = *(s2 + i - len1);
    }
    *(res + len1 + len2) = 0;
    s1 = res;
    return s1;
}

int main() {
    char * a = "abc";    
    char * b = NULL;    
    printf("%s\n", strcat(a, b));
}