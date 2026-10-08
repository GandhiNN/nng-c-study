#include <stdio.h>

/*
 * LESSON: struct basics -- bundling related data into one type.
 *
 * So far every variable held ONE value (an int, a pointer, ...).
 * A struct lets you group several values into a single named type,
 * so related data travels together.
 * 
 * Access members with the DOT operator: point.x
*/

/* Define a new type called 'struct Point' with two int members. */
struct Point {
    int x;
    int y;
};

int main(void)
{
    /* Create a struct variable and initialize its members. */
    struct Point a = {3, 4};

    /* Read members with the dot operator. */
    printf("a = (%d, %d)\n", a.x, a.y);

    /* Write members the same way. */
    a.x = 10;
    a.y = 20;
    printf("after change: a = (%d, %d)\n", a.x, a.y);

    /* A struct is ONE value: you can copy the whole thing by assignment. */
    struct Point b = a; /* copies BOTH members at once */
    b.x = 99;           /* b is independent -- changing it won't touch a */

    printf("a = (%d, %d)    b = (%d, %d)    <- b is a separate copy\n",
            a.x, a.y, b.x, b.y);

    /* The whole struct lives at one address; members sit next to each other. */
    printf("\nsizeof(struct Point) = %zu bytes (two ints)\n",
            sizeof(struct Point));

    return 0;
}