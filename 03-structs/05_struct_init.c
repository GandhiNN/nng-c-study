#include <stdio.h>

struct car {
    char *name;
    float price;
    int speed;
};

int main(void)
{
    // initialize, same field order as in the struct declaration
    struct car saturn = {"Saturn SL/2", 16000.99, 175};

    printf("Name:   %s\n", saturn.name);
    printf("Price:  %f\n", saturn.price);
    printf("Top Speed: %d km\n", saturn.speed);

    return 0;
}