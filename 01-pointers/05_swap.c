#include <stdio.h>

/*
 * LESSON 4: The classic swap. The textbook proof that pointers matter.
 *
 * A swap MUST modify both the caller's variables, so it must
 * receive their addresses. The "broken" version below swaps copies
 * and accomplishes nothing. 
 */

void brokenSwap(int a, int b) // copies - useless
{
    int t = a;
    a = b;
    b = t;
    // a and b are local copies; swapping them changes nothing outside
}

void swap(int *a, int *b) // addresses - works
{
    int t = *a; // sae what a points to
    *a = *b;    // put b's value into a's box
    *b = t;     // put saved value into b's box
}

int main(void)
{
    int x = 10, y = 20;

    brokenSwap(x, y);
    printf("brokenSwap: x=%d y=%d   (nothing happened)\n", x, y);

    swap(&x, &y);
    printf("swap:   x=%d y=%d   (swapped!)\n", x, y);

    return 0;
}