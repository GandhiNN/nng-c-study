#include <stdio.h>

/*
 * WHY "array decays to pointer" MATTERS.
 * 
 * Two things to see:
 *  (1) Inside main, 'a' knows its full size via sizeof.
 *  (2) Once passed to a function, that size info is GONE --
 *      the function only received an address (a pointer).
 * 
 * This is exactly why C functions always take a separate length
 * parameter, and why you cannot find an array's length from a pointer.
*/

void takesArray(int *param) // it is a pointer
{
    /* 'param' is a pointer here, NOT the array. sizeof gives the size of a 
        pointer (usually 8 bytes), NOT the size of the whole array. */
    printf("inside function: sizeof(param) = %zu    (size of a POINTER)\n", 
            sizeof(param));
    printf("inside function: param thinks it has %zu ints\n\n",
            sizeof(param) / sizeof(int));   // WRONG answer -- info was lost
}

int main(void)
{
    int a[10] = {0};

    /* In main, the real array: sizeof knows the whole thing. */
    printf("in main: sizeof(a) = %zu (whole array: 10 ints x 4 bytes)\n",
            sizeof(a));
    printf("in main: array length = %zu\n\n", sizeof(a) / sizeof(a[0]));

    /* The moment we pass it, it decays to a pointer and the size is lost. */
    printf("passing 'a' to a function...\n");
    takesArray(a);

    printf("Lesson: the function got only an ADDRESS. That's why every\n");
    printf("array function needs a separate length argument like 'int n'.\n");

    return 0;
}