#include <stdio.h>

int main(void)
{
    FILE *fp;   // Variable to represent open file

    fp = fopen("hello.txt", "r"); // Open file for reading

    int c = fgetc(fp);  // Read a single character
    printf("%c\n", c);  // Print char to stdout -> the first char read

    int d = fgetc(fp); // FILE* keeps track of the position -> will read the second char
    printf("%c\n", d);

    fclose(fp); // Close the file when done

    return 0;
}