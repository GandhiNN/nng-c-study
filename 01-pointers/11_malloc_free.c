#include <stdio.h>
#include <stdlib.h> /* malloc, free live here */

/*
 * LESSON: malloc / free -- asking for memory AT RUNTIME.
 *
 * Until now every array had a size fixed in the SOURCE CODE:
 *  int a[10];  // 10 is baked in, forever
 * 
 * But what if you don't know the size until the program runs (e.g. the
 * user types how many numbers they have)? You ask the system for memory
 * with malloc, and you give it back with free.
 * 
 * KEY FACTS:
 *  - malloc(bytes) returns a pointer to a fresh block, or NULL if it failed.
 *  - You MUST check for NULL (ties directly to the previous lesson).
 *  - malloc gives you RAW bytes, so you ask for n * sizeof(type).
 *  - Every malloc needs exactly one matching free, or you "leak" memory.
 *  - After free, set the pointer to NULL so you can't use it by accident.    
*/
int main(void)
{
    int n = 5;  /* pretend this came from user input at runtime */

    /* Ask for enough bytes to hold n ints. sizeof keeps it portable. */
    int *arr = malloc(n * sizeof(int));

    /* ALWAYS check: malloc returns NULL if it could not get the memory. */
    if (arr == NULL) {
        printf("Out of memory!\n");
        return 1;
    }

    /* Use it EXACTLY like a normal array -- arr[i] works because of the
       array/pointer duality you already learned. */
    for (int i = 0; i < n; i++)
        arr[i] = (i + 1) * 10;

    printf("Dynamically allocated array of %d ints:\n ", n);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    /* Done with it: hand the memory back to the system. */
    free(arr);
    arr = NULL; /* defensive: now any accidental use is an obvious NULL */

    printf("Memory freed. arr is now NULL (%p).\n", (void *)arr);
    printf("\nUnlike 'int a[5]', the size here could be decided at runtime.\n");

    return 0;
}