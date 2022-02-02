#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char * createStars(int n) { 
    char * c = (char*) malloc(sizeof(char) * (n + 1));
    for (int i = 0; i < n; i++) { 
        c[i] = '*';
    }
    c[n] = '\0';
    return c;
}

void printDiamond(int n) {
    for (int i = 1; i < n + 1; i += 2) { 
        for (int j = 0; j < (n - i) / 2; j++) { 
            printf(" ");
        }
        printf("%s\n", createStars(i));
    }
    int count = 1;
    for (int i = n - 2; i > 0; i -= 2) { 
        for (int j = 0; j < count; j++) { 
            printf(" ");
        }
        count++;
        printf("%s\n", createStars(i));
    }

}

void playDiamond() { 
    int input;
    do {
    printf("Enter n (or -1 to exit): ");
    scanf("%d", &input);
    if (input == -1) { exit(1); }
    if (input % 2 == 1) { 
       printDiamond(input);
    }
    else { 
        printf("ERROR: invalid input; please try again\n");
    }
    } while (input != -1); 

}

int main() { 
    playDiamond();
    exit(1);
}