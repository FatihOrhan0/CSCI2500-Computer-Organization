#include <stdio.h>
#include <stdlib.h>
#include <string.h>


short strend(char * s1, char * s2) { 
    if (!s2) return 1;
    if (!s1) return 0;
    if (strlen(s2) > strlen(s1)) { 
        return 0;
    }
    for (int i = 0; i < strlen(s2); i++) { 
        if (s2[i] != s1[strlen(s1) - strlen(s2) + i]) { 
            return 0;
        }
    }
    return 1;
}


int main() { 
    char * s1 = NULL;
    char * s2 = "ajksg";
    printf("%d\n", strend(s1, s2));
}