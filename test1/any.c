#include <stdio.h>


char * any(char * s1, char * s2) { 
    char * ptr1 = s1;
    char * ptr2 = s2;
    if (!ptr1 || !ptr2) { return NULL; }
    int len = 0;
    while (*ptr1 != '\0') { 
        len++;
        ptr1++;
    }
    ptr1 = s1;
    for (int i = 0; i < len; i++) { 
        while (*ptr2 != '\0') { 
            if (*ptr2 == *ptr1) { return ptr1; }
            ptr2++;
        }
        ptr2 = s2;
        ptr1++;
    }
    return NULL;
}

int main() { 
    char * c1 = "";
    char * c2 = "zxcvabcd";
    char * c3 = any(c1, c2);
    printf("%s", c3);
}