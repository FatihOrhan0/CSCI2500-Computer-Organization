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

//deallocates memory used by a matrix.
void deallocate(int ** matrix, int row) { 
    for (int i = 0; i < row; i++) { 
        free(matrix[i]);
    }
    free(matrix);
}

//finds the number of digits in num
int findDigits(int num) { 
    if (num == 0) { return 1; }
    int digit = 0; 
    while (num > 0) { 
        digit++;
        num /= 10;
    }
    return digit;
}

bool errorCheck(char * argv[], int argc) { 
    for (int i = 1; i < argc; i++) { 
        if (atoi(argv[i]) < 0) { 
            return true;
        }
    }
    return false;
}

//this function finds the max digit numbers of cols of a matrix.
int * findMaxCols(int ** m, const int row, const int col){ 
    int * colMax = calloc(col, sizeof(int));
    for (int j = 0; j < col; j++) { 
        int max = 0; 
        for (int i = 0; i < row; i++) {
            int digit = findDigits(m[i][j]); 
            if (digit > max) { 
                max = digit;
            }
        }
        colMax[j] = max;
    }
    return colMax;
}


//this function prints the target row in the specified format.
void printRow(int ** m, int colNumber, int targetRow, int * cols) { 
    printf("[");
    for (int i = 0; i < colNumber; i++) { 
        if (i != colNumber - 1)
            printf("%*d  ", cols[i], m[targetRow][i]);
        else 
            printf("%*d]", cols[i], m[targetRow][i]);
    }
} 

//this function prints the matrixes' multiplication
void printMultiplication(int ** m1, int row1, int col1,
                         int ** m2, int row2, int col2) {   
    int * cols1 = findMaxCols(m1, row1, col1);
    int * cols2 = findMaxCols(m2, row2, col2);
    
    for (int i = 0; i < col1; i++) { 
        printf("%d  ", cols1[i]);
    }
    printf(" second: \n");

    for (int i = 0; i < col2; i++) { 
        printf("%d  ", cols2[i]);
    }
    printf("\n");

    int row = 0;
    while (row < row1 && row < row2) { 
        printRow(m1, col1, row, cols1);
        if (row == 0) { 
            printf(" multiplied by ");
        }
        else { 
            printf("%15s", "");
        }
        printRow(m2, col2, row, cols2);
        printf("\n");
        row++;
    }
    //consider the remaining matrixes here.

    free(cols1);
    free(cols2);
}

void printResultant(int ** res, int row, int col) { 
    int * cols = findMaxCols(res, row, col);

    for (int i = 0; i < row; i++) { 
        if (i == 0) { 
            printf("equals ");
        }
        else { 
            printf("%7s", "");
        }
        printRow(res, col, i, cols);
        printf("\n");
    }

    free(cols);
}
//this function reads in the input and stores it in the matrix
bool readMatrix(int ** matrix, int row, int col) { 
    printf("Please enter non-negative integer values for the first matrix (%dx%d):",
    row, col);
    for (int i = 0; i < row; i++) { 
        for (int j = 0; j < col; j++) { 
            int read;
            scanf("%d", &read);
            if (read < 0) { 
                return false;
            }
            matrix[i][j] = read;
        }
    }
    return true;
}


//this function multiplies the m1 and m2 and stores the results
//in resultant
void multiplyMatrixes(int ** m1, int ** m2, int ** resultant,
                      int row1, int col2, int col1) { 
    for (int i = 0; i < row1; i++) { 
        for (int j = 0; j < col2; j++) { 
            int cell = 0; 
            for (int k = 0; k < col1; k++) { 
                cell += m1[i][k] * m2[k][j];
            }
            resultant[i][j] = cell;
        }
    }
}



int main(int argc, char * argv[]) {
    /* Ensure we have the correct number of command-line arguments */
    if (argc != 5) {
        fprintf(stderr, "ERROR: Invalid inputs!\n");
        return EXIT_FAILURE;
    }

    //check if any of the values are negative
    bool neg = errorCheck(argv, argc);

    if (neg) { 
        fprintf(stderr, "ERROR: Negative Numbers!");
        return EXIT_FAILURE;
    }

    //sizes must match for multiplication
    if (atoi(argv[2]) != atoi(argv[3])) { 
        fprintf(stderr, "ERROR: Incompatible Sizes");
        return EXIT_FAILURE;
    }

    //at this point we're ready to allocate memory for the matrixes
    int ** matrix1 = matrix_alloc(atoi(argv[1]), atoi(argv[2]));
    int ** matrix2 = matrix_alloc(atoi(argv[3]), atoi(argv[4]));
    int ** resultant = matrix_alloc(atoi(argv[1]), atoi(argv[4]));

    if (!readMatrix(matrix1, atoi(argv[1]), atoi(argv[2]))) { 
        fprintf(stderr, "ERROR: Negative Number(s) Found");
        deallocate(matrix1, atoi(argv[1]));
        deallocate(matrix2, atoi(argv[3]));
        deallocate(resultant, atoi(argv[1]));
        return EXIT_FAILURE;
    }

    if (!readMatrix(matrix2, atoi(argv[3]), atoi(argv[4]))) { 
        fprintf(stderr, "ERROR: Negative Number(s) Found");
        deallocate(matrix1, atoi(argv[1]));
        deallocate(matrix2, atoi(argv[3]));
        deallocate(resultant, atoi(argv[1]));
        return EXIT_FAILURE;
    }

    printMultiplication(matrix1, atoi(argv[1]), atoi(argv[2]), matrix2,
    atoi(argv[3]), atoi(argv[4]));

    multiplyMatrixes(matrix1, matrix2, resultant,
                     atoi(argv[1]), atoi(argv[4]), atoi(argv[2]));


    deallocate(matrix1, atoi(argv[1]));
    deallocate(matrix2, atoi(argv[3]));
    deallocate(resultant, atoi(argv[1]));
    // printf("%d", findDigits(312));

    return EXIT_SUCCESS;
} 