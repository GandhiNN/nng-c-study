#include <stdio.h>

/*
 * LESSON: NULL -- a pointer that points at NOTHING.
 *
 * Sometimes a pointer has no valid thing to point at yet.
 * For that, C has NULL: a special pointer value meaning "points nowhere".
 * 
 * TWO rules that will save you from crashes:
 *  (1) A fresh/invalid pointer should be set to NULL so you can TEST it.
 *  (2) NEVER dereference a NULL pointer. *p when p == NULL = crash
 *      (on most systems: "segmentation fault").
 * 
 * The pattern below -- check before you dereference -- is everywhere
 * in real C code.
*/

/* Returns a pointer to the first element equal to 'target', or NULL if
   none is found. Returning NULL is how C functions say "nothing here". */
int *findFirst(int *arr, int n, int target)
{
    for (int i = 0; i < n; i++) {
        if (arr[i] == target)
            return &arr[i];     // hand back the ADDRESS of the match
    }
    return NULL;                // not found -> point nowhere
}

int main(void)
{
    int data[5] = {4, 8, 15, 16, 23};

    /* Case 1: the value exists. */
    int *hit = findFirst(data, 5, 15);
    if (hit != NULL) {  // ALWAYS check before dereferencing
        printf("Found 15 at address %p, value = %d\n", (void *)hit, *hit);
    } else {
        printf("15 not found\n");
    }

    /* Case 2: the value does NOT exist -> function returns NULL. */
    int *miss = findFirst(data, 5, 99);
    if (miss != NULL) {
        printf("Found 99, value = %d\n", *miss);
    } else {
        printf("99 not found (findFirst returned NULL)\n");
    }

    /* This is what you must NEVER do -- shown as a comment on purpose:
     *
     *      int *bad = NULL;
     *      *bad = 10;  // CRASH: dereferencing NULL
     * 
     * Uncomment it and run to see the segfault for yourself (optional).
    */

    printf("\nRule: test 'p != NULL' BEFORE you ever write '*p'.\n");
    return 0;
}