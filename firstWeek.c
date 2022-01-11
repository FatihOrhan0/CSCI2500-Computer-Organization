#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

char *reverse(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

int fibonacci(int n) { 
    if (n < 2) { return 1; }
    else { return fibonacci(n - 1) + fibonacci(n - 2); }
}

int main() { 
    //creating a code to input a string from user, then printing the reversed 
    //version of the string.
    char input[32];
    printf("enter the input string: ");
    scanf("%s", input);
    reverse(input);
    printf("%s", input);
    int number;
    printf("\nEnter the number: ");
    scanf("%d", &number);
    printf("Calculated Fibonacci number is: %d\n", fibonacci(number));
{}