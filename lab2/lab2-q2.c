#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *filename = "lab2-data-little.dat";
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("failed.");
        return EXIT_FAILURE;
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    //printf("%ld", fileSize);
    fclose(file);
    FILE *file2 = fopen(filename, "r");
    if (!file2)
    {
        perror("failed.");
        return EXIT_FAILURE;
    }
    unsigned int itemCount = fileSize / sizeof(unsigned int);
    unsigned int * data = calloc(itemCount, sizeof(unsigned int));
    fread(data, sizeof(unsigned int), itemCount, file2);
    for (unsigned int i = 0; i < itemCount; i++) { 
        printf("DATA POINT #%3d: <%8x>\n", i, data[i]);  
    }
    free(data);
    fclose(file2);
}