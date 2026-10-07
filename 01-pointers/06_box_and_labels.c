#include <stdio.h>

/*
 * LESSON 1: A variable is a BOX. A pointer is a LABEL that says
 *           "the box over there".
 * 
 * Intuition:
 *  - int cash = 100;   -> a box named 'cash' with 100 inside.
 *  - &cash             -> the ADDRESS of that box (where it lives).
 *  - int *p = &cash;   -> 'p' is a lable pointing AT the box.
 *  - *p                -> "open the box p points to" (its contents).
 * 
 * Key idea: a pointer does NOT hold the value. It holds the LOCATION
 * of the value. Think street address vs the house itself.
 */

int main(void)
{
    int cash = 100;     // the box
    int *p = &cash;     // p = address of the box

    printf("cash (the value in the box)     : %d\n", cash);
    printf("&cash (where the box lives)     : %p\n", (void *)&cash);
    printf("p (what the label stores)       : %p\n", (void *)p);
    printf("*p (open the box p points to)   : %d\n", *p);

    printf("\nNotice: p and &cash are the SAME address.\n");
    printf("And *p and cash are the SAME value.\n");

    return 0;
}