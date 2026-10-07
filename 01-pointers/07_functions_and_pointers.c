#include <stdio.h>

/*
 * LESSON 3: Functions get COPIES. Pointers let them reach the original.
 *
 * In C, arguments are passed BY VALUE: the function receives a copy.
 * So a function that takes an 'int' cannot change the caller's int.
 * To change the caller's variable, you hand it the ADDRESS instead.
 * 
 * This is exactly why scanf needs &x: scanf("%d", &x);
 * scanf must write into YOUR variable, so you give it the address.
*/

void tryToChange(int x) // receives a COPY
{
    x = 999;            // only changes the local copy; caller unaffected
}

void reallyChange(int *x)   // receives the ADDRESS of the caller's int
{
    *x = 999;   // writes through the pointer -> changes original
}

int main(void)
{
    int a = 1;
    tryToChange(a);
    printf("After tryToChange:  a = %d  (unchanged - it got a copy)\n", a);

    int b = 1;
    reallyChange(&b);   // hand over the address
    printf("After reallyChange: b = %d (changed - it had the address)\n", b);

    return 0;
}