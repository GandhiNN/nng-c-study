#include <stdio.h>

/*
 * POINTER ARITHMETIC, made visible.
 *
 * The claim: arr[i] is just sugar for *(arr + i), and 'arr + i' is
 * real address math scaled by sizeof(the element type)
 * 
 * This program prints the addresses so you can SEE that:
 *  &arr[i] == arr + i
 * and that each step moves forward by sizeof(int) bytes.
*/

int main(void)
{
    int arr[5] = {10, 20, 30, 40, 50};
    int *p = arr;   /* decays to &arr[0] */

    printf("sizeof(int) = %zu bytes, so each +1 should move that far.\n\n",
            sizeof(int));

    for (int i = 0; i < 5; i++) {
        printf("i=%d | arr[i]=%d | &arr[i]=%p | p+i=%p | *(p+i)=%d\n",
                i,
                arr[i],             /* the value, via indexing */
                (void *)&arr[i],    /* address, via &arr[i] */
                (void *)(p + i),    /* address, via pointer arithmetic */
                *(p + i)            /* the value, via pointer arithmetic */
            );
    }

    /* Pointer MINUS pointer = how many elements apart (not bytes). */
    int *first = &arr[0];
    int *last = &arr[4];
    printf("\nlast - first = %td elements apart\n", last - first); /* 4 */

    /* Advancing with ++ moves by one element each time. */
    printf("\nWalking with p++:\n");
    for (int *q = arr; q < arr + 5; q++)
        printf("address %p holds %d\n", (void *)q, *q);

    return 0;
}