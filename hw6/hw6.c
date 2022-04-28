//Filename: hw6.c
//Purpose: Implementation file of hw6, which is extending on hw5's compiler.

//Sample compilation: gcc -g -Wall -Wextra -Wvla hw6.c -o test.exe

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

//TODO: Take care of multiplying by 0

//this function checks if there's multiplication in the file
int checkMult(char * filename) { 
    FILE * f = fopen(filename, "r"); 
    if (!f) { 
        return 0;
    }
    char c = 'a';
    do { 
        c = fgetc(f); 
        if (c == '*' || c == '/' || c == '%') { 
            fclose(f); 
            return 1; 
        }
    } while ((int) c > 0);
    fclose(f);
    return 0;
}

//fetches one word from given pos
char * getWord(char * s, int pos, int * isEnd, char * res) { 
    int i = 0;
    for (; i < 9 && i + pos < (int) strlen(s); i++) {
        if (s[i + pos] == ' ') break;
        else if (s[i + pos] == ';') { 
            *isEnd = 1;
            break;
        }
        res[i] = s[i + pos];
    }
    res[i] = '\0';
    return res;
}

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

//checks if ',' exists in buffer
int commaCheck(char * s) { 
    int i = 0;
    while (s[i] != '\0') { 
        if (s[i] == ',') return 1; 
        i++;
    }
    return 0;
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

//define the registers as strings
const char * tregs[10] = {"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9"};


int main(int argc, char * argv[]) { 
    if (argc != 2 && argc != 3) {
        fprintf(stderr, "ERROR: INCOMPATIBLE COMMAND LINE ARGUMENTS!\n");
        return EXIT_FAILURE;
    }

    int m = checkMult(argv[1]);
    
    //this array will be used to store the locations of integers
    int letters[26];
    //store the last used t register
    int t = 0;


    //initialize the letters array.
    for (int i = 0; i < 26; i++) { 
        letters[i] = -1;
    }

    //check pipelining
    short isPipe = 0; 
    if (argc == 3) {  
        if (strcmp("--pipelined", argv[2]) == 0) { 
            isPipe = 1;
        }
    }

    //open the file for read
    FILE * file = fopen(argv[1], "r");
    if (!file) { 
        fprintf(stderr, "ERROR: INVALID FILENAME!\n");
        return EXIT_FAILURE;
    }

    //store the integers in the stack
    char buffer[200];
    
    
    //we will need to store at most 2 words at once. We also need to store an int to imitate $sp
    char word1[10];
    char word2[10];
    int counter = 0;


    if (!m) {
        while (1) { 
            if (!fgets(buffer, 200, file)) break;
            t = 0;
            //integer assignments such as int x; int x, y;
            if (countSpaces(buffer) == 1 || commaCheck(buffer)) { 
                for (int i = 4; i < (int) strlen(buffer) - 1; i += 3) { 
                    letters[buffer[i] - 'a'] = counter * 4;
                    counter++;
                }
            }
            //direct assignments,
            else if (countSpaces(buffer) == 2) {
                printf("# %s", buffer);
                int i = 4; 
                for (; i < 13; i++) { 
                    if (!isdigit(buffer[i])) break;
                    word1[i - 4] = buffer[i];
                }
                word1[i - 4] = '\0';
                // x = y;
                if (strlen(word1) == 0) { 
                    printf("lw $t0,%d($a0)\n", letters[buffer[4] - 'a']);
                    printf("sw $t0,%d($a0)\n", letters[buffer[0] - 'a']);
                }
                //x = num;
                else {
                    printf("ori $t0,$0,%s\n", word1);
                    printf("sw $t0,%d($a0)\n", letters[buffer[0] - 'a']);
                }
            }
            //this will be else addition
            else { 
                printf("# %s", buffer);
                int i = 4; 
                for (; i < 13; i++) { 
                    if (buffer[i] == ' ') break;
                    word1[i - 4] = buffer[i];
                }
                word1[i - 4] = '\0';
                if (isNum(word1)) { 
                    printf("ori $t0,$0,%s\n", word1);
                    t++;
                }
                else { 
                    printf("lw $t0,%d($a0)\n", letters[word1[0] - 'a']);
                    t++;
                }
                int isEnd = 0;
                int pos = 7 + strlen(word1);
                while (!isEnd) { 
                    getWord(buffer, pos, &isEnd, word2);
                    char oprt = buffer[pos - 2];
                    if (oprt == '+') {
                        if (isNum(word2)) { 
                            printf("addi $%s,$%s,%s\n", tregs[(t % 10)], tregs[(t - 1) % 10], word2);
                            t++;
                        } 
                        else { 
                            printf("lw $%s,$%d($a0)\n", tregs[(t % 10)], letters[word2[0] - 'a']);
                            t++;
                            printf("add $%s,$%s,$%s\n", tregs[(t % 10)], tregs[(t - 1) % 10], tregs[(t - 2) % 10]);
                            t++;
                        }
                    }
                    else { 
                        if (isNum(word2)) { 
                            printf("addi $%s,$%s,%s\n", tregs[(t % 10)], tregs[(t - 1) % 10], word2);
                            t++;
                        }
                        else { 
                            printf("lw $%s,$%d($a0)\n", tregs[(t % 10)], letters[word2[0] - 'a']);
                            t++;
                            printf("sub $%s,$%s,$%s\n", tregs[(t % 10)], tregs[(t - 1) % 10], tregs[(t - 2) % 10]);
                            t++;
                        }
                    }
                    pos += strlen(word2) + 3;
                    if (isEnd) { 
                        printf("sw $%s,%d($a0)\n", tregs[(t - 1) % 10], letters[buffer[0] - 'a']);
                    }
                }
            }
        }
    }
    //parsing multiplications
    else { 
        while (1) { 
            if (!fgets(buffer, 200, file)) break;
            t = 0;
            //integer assignments such as int x; int x, y;
            if (countSpaces(buffer) == 1 || commaCheck(buffer)) { 
                for (int i = 4; i < (int) strlen(buffer) - 1; i += 3) { 
                    letters[buffer[i] - 'a'] = counter * 4;
                    counter++;
                }
            }
            //direct assignments,
            else if (countSpaces(buffer) == 2) {
                printf("# %s", buffer);
                int i = 4; 
                for (; i < 13; i++) { 
                    if (!isdigit(buffer[i])) break;
                    word1[i - 4] = buffer[i];
                }
                word1[i - 4] = '\0';
                // x = y;
                if (strlen(word1) == 0) { 
                    printf("lw $t0,%d($a0)\n", letters[buffer[4] - 'a']);
                    printf("sw $t0,%d($a0)\n", letters[buffer[0] - 'a']);
                }
                //x = num;
                else {
                    printf("ori $t0,$0,%s\n", word1);
                    printf("sw $t0,%d($a0)\n", letters[buffer[0] - 'a']);
                }
            }
            else { 
                printf("# %s", buffer);
                int i = 4; 
                int isEnd = 0;
                getWord(buffer, i, &isEnd, word1);
                i += strlen(word1) + 3;
                getWord(buffer, i, &isEnd, word2);
                if (isNum(word1)) { 
                    printf("ori $t0,$0,%s\n", word1);
                    t++;
                }
                else { 
                    printf("lw $t0,%d($a0)\n", letters[word1[0] - 'a']);
                    t++;
                }
                if (isNum(word2)) { 
                    printf("ori $t1,$0,%s\n", word1);
                    t++;
                }
                else { 
                    printf("lw $t1,%d($a0)\n", letters[word2[0] - 'a']);
                    t++;
                }
                if (buffer[i - 2] == '*') { 
                    printf("mult $t0,t1\nmflo $t2\n");
                    t++;
                }
                else if (buffer[i - 2] == '/') { 
                    printf("div $t0,t1\nmflo $t2\n");
                    t++;
                }
                else if (buffer[i - 2] == '%') { 
                    printf("div $t0,t1\nmfhi $t2\n");
                    t++;
                }
                if (isEnd) { 
                    printf("sw $t2,%d($a0)\n", letters[buffer[0] - 'a']);
                    break;
                }
                i += strlen(word2) + 3;
                while (!isEnd) { 
                    getWord(buffer, i, &isEnd, word2);
                    char oprt = buffer[i - 2];
                    if (isNum(word2)) { 
                        printf("ori $%s,$0,%s\n", tregs[t % 10], word2);
                    }
                    else { 
                        printf("lw $%s,%d($a0)\n", tregs[t % 10], letters[word2[0] - 'a']);
                    }
                    if (oprt == '*') { 
                        printf("mult $%s,$%s\n", tregs[t % 10], tregs[(t - 1) % 10]);
                        t++;
                        printf("mflo $%s\n", tregs[t % 10]);
                        t++;
                    }
                    else if (oprt == '/') { 
                        printf("div $%s,$%s\n", tregs[(t - 1) % 10], tregs[t % 10]);
                        t++;
                        printf("mflo $%s\n", tregs[t % 10]);
                        t++;
                    }
                    else if (oprt == '%') { 
                        printf("div $%s,$%s\n", tregs[(t - 1) % 10], tregs[t % 10]);
                        t++;
                        printf("mfhi $%s\n", tregs[t % 10]);
                        t++;
                    }
                    i += strlen(word2) + 3;
                    if (isEnd) { 
                        printf("sw $%s,%d($a0)\n", tregs[(t - 1) % 10], letters[buffer[0] - 'a']);
                    }
                }
            }
        }
    }



    //close the file and exit the program
    fclose(file);
    return EXIT_SUCCESS;
}