/* hw1.c */
/* NAME: <Fatih Orhan> */
/* COMPILE: gcc -Wall -Werror -Wvla hw1.c -lm */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


//defining booleans for convenience
typedef enum {false, true} bool;

/* dynamically allocate memory for rows x cols matrix of integers */
int ** matrix_alloc(int rows, int cols) {
    int ** matrix = calloc(rows, sizeof(int*));
    for (int r = 0 ; r < rows ; r++) {
        matrix[r] = calloc(cols, sizeof(int));
    }
    return matrix;
}

//a function to print a matrix
void printMatrix(int ** m, int row, int col) { 
    for (int i = 0; i < row; i++) { 
        for (int j = 0; j < col; j++) { 
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char * argv[]) {
    /* Ensure we have the correct number of command-line arguments */
    if (argc != 5) {
        fprintf(stderr, "ERROR: Invalid inputs!\n");
        return EXIT_FAILURE;
    }
    //check if any of the values are negative
    bool neg = false;
    for (int i = 1; i < argc; i++) { 
        if (atoi(argv[i]) < 0) { 
            neg = true;
        }
    }
    if (neg) { 
        fprintf(stderr, "ERROR: Negative Numbers!");
        return EXIT_FAILURE;
    }

    if (atoi(argv[2]) != atoi(argv[3])) { 
        fprintf(stderr, "ERROR: Incompatible Sizes");
        return EXIT_FAILURE;
    }

    //at this point we're ready to allocate memory for the matrixes
    int ** matrix1 = matrix_alloc(atoi(argv[1]), atoi(argv[2]));
    int ** matrix2 = matrix_alloc(atoi(argv[3]), atoi(argv[4]));
    int ** resultant = matrix_alloc(atoi(argv[1]), atoi(argv[4]));

    printf("Please enter non-negative integer values for the first matrix (%dx%d):",
    atoi(argv[1]), atoi(argv[2]));
    for (int i = 0; i < atoi(argv[1]); i++) { 
        for (int j = 0; j < atoi(argv[2]); j++) { 
            int read;
            scanf("%d", &read);
            matrix1[i][j] = read;
        }
    }

    printf("Please enter non-negative integer values for the second matrix (%dx%d):",
    atoi(argv[3]), atoi(argv[4]));
    for (int i = 0; i < atoi(argv[3]); i++) { 
        for (int j = 0; j < atoi(argv[4]); j++) { 
            int read;
            scanf("%d", &read);
            matrix2[i][j] = read;
        }
    }


    return EXIT_SUCCESS;
} 