//Filename: hw5.c
//Purpose: Implementation file for the 5th homework. The aim is to create a 
//rudimentary compiler that can compile addition and subtraction into c code.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


//a function to check if a string is an integer
int isNum(char * s) { 
    int j = 0; 
    while (s[j] != '\0') { 
        if (s[j] > 47 && s[j] < 58) { 
            j++; continue; 
        }
        return 0;
    }
    return 1;
}


//count the number of spaces to determine the operator count
int countSpaces(char * s) { 
    int i = 0, spaces = 0; 
    while (s[i] != '\0') { 
        if (s[i] == ' ') spaces++;
        i++; 
    }
    return spaces;  
}

int letters[26];

//define the T registers in a string 
const char * regs[18] = {"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9",
 "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7"};



int main(int argc, char * argv[]) { 
    if (argc != 2) { 
        fprintf(stderr, "ERROR: Incompatible Arguments!\n");
        return EXIT_FAILURE;
    }
    //initialize the letters array
    for (int i = 0; i < 26; i++) { 
        letters[i] = -1; 
    }
    //we assume no number will be longer than 9 digits. 
    char word1[10];
    char oprt = '!';
    char * buffer = calloc(sizeof(char), 300);
    FILE * file = fopen(argv[1], "r");
    int s = 0, t = 0; 
    while ((buffer = fgets(buffer, 100, file))) { 
        printf("# %s", buffer);
        char regDest = buffer[0];
        if (letters[buffer[0] - 'a'] == -1) {
            letters[buffer[0] - 'a'] = 10 + (s % 8); 
            s++;
        }
        int col = 4;
        char prevWord[10] = "abc";
        while (buffer[col] != ';') {
            int col2 = 0;
            int p = 0; 
            int opNum = (countSpaces(buffer) - 2) / 2; 
            while (buffer[col] != ' ' && buffer[col] != ';') { 
                word1[col2] = buffer[col];
                col2++;
                col++;
            }
            word1[col2] = '\0';
            if (!isNum(word1) && opNum == 0) { 
                printf("addu %s,$0,%s\n", regs[letters[regDest - 'a']], regs[letters[word1[0] - 'a']]);
            }
            else if (isNum(word1) && opNum == 0) { 
                printf("ori %s,$0,%s\n", regs[letters[regDest - 'a']], word1);
                p++;
            }
            else if (isNum(word1)) { 
                printf("ori $t%d,$0,%s\n", t % 10, word1);
                t++; 
                p++;
            } 
            else if (p < opNum) { 
                if (oprt == '+') { 
                    if (isNum(word1)) { 
                        printf("addi $t%d,$t%d,%s\n", t % 10, t % 10 - 1, word1);
                        t++;
                    }
                    else { 
                        printf("add $t%d,$t%d,%s\n", t % 10, t % 10 - 1, regs[letters[word1[0] - 'a']]);
                        t++;
                    }
                }
            }
            //printf("%s %c %s\n", prevWord, oprt, word1);

            if (buffer[col] == ';') break;
            col++; 
            oprt = buffer[col];
            col += 2; 
            col2 = 0; 
            //printf("%s %c %s\n", prevWord, oprt, word1);
            strcpy(prevWord, word1);
        }
    }
    free(buffer);
    return EXIT_SUCCESS;
}