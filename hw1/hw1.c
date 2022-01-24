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

void deallocate(int ** matrix, int row) { 
    for (int i = 0; i < row; i++) { 
        free(matrix[i]);
    }
    free(matrix);
}

bool errorCheck(char * argv[], int argc) { 
    for (int i = 1; i < argc; i++) { 
        if (atoi(argv[i]) < 0) { 
            return true;
        }
    }
    return false;
}

//this function finds the max digit number in a given matrix.
int findMaxDigits(int ** m, const int row, const int col){ 
    int max = 0;
    for (int i = 0; i < row; i++) { 
        for (int j = 0; j < col; j++) { 
            if (floor(log(m[i][j])) > max) { 
                max = floor(log(m[i][j]));
            }
        }
    }
    return max;
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

//a function to print a matrix1 multiplied by matrix 2.
void printMatrixes(int ** m1, int row1, int col1, int ** m2, int row2, int col2) { 
    int max1 = findMaxDigits(m1, row1, col1);
    int max2 = findMaxDigits(m2, row2, col2);

    //first print the first rows of the matrixes
    if (col1 == 1) { 
        printf("[%*d", -max1, m1[0][0]);
    }
    else { 
        printf("[");
        for (int i = 0; i < col1; i++) { 
            if (i < col1 - 1) { 
                printf("%*d  ", -max1, m1[0][i]);
            }
            else { 
                printf("%d", m1[0][i]);
            }
        }
    }
    printf("] multiplied by ");

    if (col2 == 1) { 
        printf("[%*d", -max2, m2[0][0]);
    }
    else { 
        printf("[");
        for (int i = 0; i < col2; i++) { 
            if (i < col2 - 1) { 
                printf("%*d  ", -max2, m2[0][i]);
            }
            else { 
                printf("%d", m2[0][i]);
            }
        }
    }
    printf("]");
    
    //at this point the first line is done. 
    printf("\n");

    //create two booleans to keep track of the rows of matrixes.
    bool first = true;
    bool second = true;
    int rowFirst = 1; 
    int rowSecond = 1;
    while (true) { 
        if (!first || !second) break;
        if (rowFirst == row1) { 
            first = false;
            continue;
        }
        if (rowSecond == row2) { 
            second = false;
            continue;
        }

        if (col1 == 1) { 
            printf("[%d]", m1[rowFirst][0]);
        }
        else { 
            printf("[");
            for (int i = 0; i < col1; i++) { 
                if (i < col1 - 1) { 
                    printf("%*d  ", -max1, m1[rowFirst][i]);
                }
                else { 
                    printf("%d", m1[rowFirst][i]);
                }
            }
        }
        printf("%-14c", ']');
        rowFirst++;
        rowSecond++;
    }

    /* for (int i = 0; i < row1; i++) { 
        for (int j = 0; j < col1; j++) { 
            printf("%d ", m1[i][j]);
        }
        printf("\n");
    } */
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


    multiplyMatrixes(matrix1, matrix2, resultant,
                     atoi(argv[1]), atoi(argv[4]), atoi(argv[2]));

    //printMultiplication(matrix1, matrix2, atoi(argv[1]), atoi(argv[2]),
    //atoi(argv[3]), atoi(argv[4]));

    deallocate(matrix1, atoi(argv[1]));
    deallocate(matrix2, atoi(argv[3]));
    deallocate(resultant, atoi(argv[1]));

    return EXIT_SUCCESS;
} 