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
    // long fileSize = ftell(file);
    printf("%ld", fileSize);
    fclose(file);
    FILE *file2 = fopen(filename, "r");
    if (!file2)
    {
        perror("failed.");
        return EXIT_FAILURE;
    }
    unsigned long itemCount = fileSize / sizeof(unsigned long);
    unsigned long * data = calloc(itemCount, sizeof(unsigned long));
    fread(data, sizeof(unsigned long), itemCount, file2);
    for (unsigned int i = 0; i < itemCount; i++) { 
        printf("DATA POINT #%3d: <%lu>\n", i, data[i]);  
    }
    free(data);
    fclose(file2);
}