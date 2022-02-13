#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct charTrio { 
    int spaces;
    int tabs;
    int newlines;
};

struct charTrio counter(char * filename) { 
    struct charTrio a;
    a.spaces = 0; a.tabs = 0; a.newlines = 0;
    FILE * file = fopen(filename, "r");
    if (!file) { 
        fprintf(stderr, "Cannot open the file");
        return a; 
    }
    char c = ' ';
    do { 
        c = fgetc(file);
        if (c < 0) break;
        else if (c == ' ') a.spaces++;
        else if (c == '\t') a.tabs++;
        else if (c == '\n') a.newlines++;
    } while (c >= 0);
    fclose(file);
    return a;
}

int main() { 
    struct charTrio a;
    a = counter("test.txt");
    printf("spaces: %d tabs: %d newlines: %d\n", a.spaces, a.tabs, a.newlines);
}