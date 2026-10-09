#include <stdio.h>
#include <string.h>

int my_strlen(char *s)
{
    int count = 0;
    while (s[count] != '\0') // single quotes for single char
        count++;

    return count;
}

int main(void)
{
    char *s = "Hello, world!";

    printf("The string is %zu bytes long.\n", strlen(s));
    printf("The string is %zu bytes long.\n", my_strlen(s));
    return 0;
}