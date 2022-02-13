#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int atoh(char * c) { 
    int total = 0;
    char * ptr = &c[0];
    if (!ptr) { return -1; }
    short neg = 0;
    if (*ptr == '-') { 
        neg = 1;
    }
    if (*ptr == '0') { 
        ptr++;
        if (!ptr) { return 0; }
        if (*ptr == 'x' || *ptr == 'X') { 
            ptr++;
        }
    }
    
    while (*ptr != '\0') { 
        if (*ptr <= '9' && *ptr >= '0') { 
            total += (int) (*ptr - '0');
        }
        else if (*ptr == 'a' || *ptr == 'A') { total += 10; } 
        else if (*ptr == 'b' || *ptr == 'B') { total += 11; } 
        else if (*ptr == 'c' || *ptr == 'C') { total += 12; } 
        else if (*ptr == 'd' || *ptr == 'D') { total += 13; } 
        else if (*ptr == 'e' || *ptr == 'E') { total += 14; } 
        else if (*ptr == 'f' || *ptr == 'F') { total += 15; } 
        else { return -1; }
        total *= 16;
        ptr++;
    }
    total /= 16;
    if (neg) total *= -1;
    return total;
}

int main() { 
    printf("%d %d %d %d %d \n", atoh("0x"), atoh("10"), atoh("0xaa"), atoh("0xb"), atoh("ab"));
}