/* lab2-q1.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    /* The 0x prefix below indicates a hexadecimal number */
    int secret = 0x44434241;
    long secret2 = 0x4847464544434241;
    long secret3[31/sizeof(long) + 1];
    secret3[0] = 0x20746f6e20796857;
    secret3[1] = 0x742065676e616863;
    secret3[2] = 0x646c726f77206568;
    secret3[3] = 0x6f6c6c65480A3f;
    // printf("%ld\n", sizeof(long));
    for (int i = 0; i < 4; i++) { 
        char * cptr3 = (char*)&secret3[i];
        printf("%c", *cptr3++);
        printf("%c", *cptr3++);
        printf("%c", *cptr3++);
        printf("%c", *cptr3++);
        printf("%c", *cptr3++);
        printf("%c", *cptr3++);
        printf("%c", *cptr3++);
        printf("%c", *cptr3++);
    }
    printf("\n");
    char *cptr = (char *)&secret;
    char * cptr2 = (char *)&secret2;
    printf("%c", *cptr++);
    printf("%c", *cptr++);
    printf("%c", *cptr++);
    printf("%c\n", *cptr++);
     
    printf("%c", *cptr2++);
    printf("%c", *cptr2++);
    printf("%c", *cptr2++);
    printf("%c", *cptr2++);
    printf("%c", *cptr2++);
    printf("%c", *cptr2++);
    printf("%c", *cptr2++);
    printf("%c\n", *cptr2++);
    return EXIT_SUCCESS;
}