#include <stdio.h>

/*
 * LESSON 5: Arrays and pointers are deeply related.
 * 
 * An array name "decays" into a pointer to its first element.
 * So for an array 'a':
 *      a       is the address of a[0]
 *      a[i]    is EXACTLY the same as *(a + i)
 *      &a[i]   is EXACTLY the same as  (a + i)
 * 
 * POINTER ARITHMETIC: adding 1 to an int* moves forward by one int
 * (4 bytes on most machines), NOT one byte. The type tells C the step size.
 */

int main(void)
{
    int a[5] = {10, 20, 30, 40, 50};
    int *p = a; // same as &a[0]; array name decays to a pointer

    printf("Indexing vs. pointer math (identical results):\n");
    for (int i = 0; i < 5; i++) {
        printf("a[%d]=%d  *(a+%d)=%d  p[%d]=%d  *(p+%d)=%d\n",
                i, a[i], i, *(a + i), i, p[i], i, *(p + i));
    }

    printf("\nAddresses step by sizeof(int)=%zu bytes each:\n", sizeof(int));
    for (int i = 0; i < 5; i++) {
        printf("&a[%d] = %p\n", i, (void *)(a + i));
    }

    printf("\nWalking the array by moving the pointer:\n");
    for (int *q = a; q < a + 5; q++) { // q++ advances one int
        printf("%d", *q);
    }
    printf("\n");

    return 0;
}