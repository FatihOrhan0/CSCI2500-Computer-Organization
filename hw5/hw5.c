//Filename: hw5.c
//Purpose: Implementation file for the 5th homework. The aim is to create a 
//rudimentary compiler that can compile addition and subtraction into c code.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


//TODO: consider starting with register value.  


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
const char * tregs[10] = {"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9"};
const char * sregs[8] = {"s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7"};



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
    FILE * file = fopen(argv[1], "r");
    int s = 0, t = 0; 
    while (1) { 
        char * buffer = calloc(sizeof(char), 200);
        if (!fgets(buffer, 200, file)) { 
            free(buffer);
            break;
        }
        printf("# %s", buffer);
        char regDest = buffer[0];
        if (letters[buffer[0] - 'a'] == -1) {
            letters[buffer[0] - 'a'] = (s % 8); 
            s++;
        }
        int col = 4;
        int p = 0; 
        char prevWord[10] = "abc";
        while (buffer[col] != ';') {
            int col2 = 0;
            int opNum = (countSpaces(buffer) - 2) / 2; 
            while (buffer[col] != ' ' && buffer[col] != ';') { 
                word1[col2] = buffer[col];
                col2++;
                col++;
                p++;
            }
            word1[col2] = '\0';
            if (!isNum(word1) && letters[word1[0] - 'a'] == -1) { 
                letters[word1[0] - 'a'] = (s % 8); 
                s++;
                p--;
            }
            if (!isNum(word1) && opNum == 0) { 
                printf("addu $%s,$0,%s\n", sregs[letters[regDest - 'a']], sregs[letters[word1[0] - 'a']]);
            }
            else if (isNum(word1) && opNum == 0) { 
                printf("ori $%s,$0,%s\n", sregs[letters[regDest - 'a']], word1);
                p++;
            }
            else if (isNum(word1) && p == 2) { 
                printf("ori $%s,$0,%s\n", tregs[t % 10], word1);
                t++;   
            }
            else if (p <= opNum + 1) { 
                if (oprt == '+') { 
                    if (isNum(word1)) { 
                        printf("addi $%s,$%s,%s\n", tregs[t % 10], tregs[(t - 1) % 10], word1);
                        t++;
                    }
                    else { 
                        printf("add $%s,$%s,%s\n", tregs[t % 10], tregs[(t - 1) % 10],
                        sregs[letters[word1[0] - 'a']]);
                        t++;
                    }
                }
                else { 
                    if (isNum(word1)) { 
                        printf("addi $%s,$%s,-%s\n", tregs[t % 10], tregs[(t - 1) % 10], word1);
                        t++;
                    }
                    else { 
                        printf("sub $%s,$%s,%s\n", tregs[t % 10], tregs[(t - 1) % 10],
                        sregs[letters[word1[0] - 'a']]);
                        t++;
                    }
                }
            }
            else { 
                if (oprt == '+') { 
                    if (isNum(word1)) { 
                        printf("addi $%s,$%s,%s\n", sregs[letters[regDest - 'a']], tregs[t % 10], word1);
                    }
                    else { 
                        printf("add $%s,$%s,%s\n", sregs[letters[regDest - 'a']], tregs[t % 10],
                        sregs[letters[word1[0] - 'a']]);
                    }
                }
                else { 
                    if (isNum(word1)) { 
                        printf("addi $%s,$%s,-%s\n", sregs[letters[regDest - 'a']], tregs[(t - 1) % 10], word1);
                    }
                    else { 
                        printf("sub $%s,$%s,%s\n", sregs[letters[regDest - 'a']], tregs[(t - 1) % 10],
                        sregs[letters[word1[0] - 'a']]);
                    }
                }
            }

            if (buffer[col] == ';') break;
            col++; 
            oprt = buffer[col];
            col += 2; 
            col2 = 0; 
            //printf("%s %c %s\n", prevWord, oprt, word1);
            strcpy(prevWord, word1);
           // printf("%d %d\n", p, opNum);
        }
        free(buffer);
    }

    fclose(file);
    return EXIT_SUCCESS;
}