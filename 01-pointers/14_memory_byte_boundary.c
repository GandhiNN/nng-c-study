#include <stdio.h>
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy, memset, strlen */

/*
 * LESSON: the ELEMENT vs BYTE boundary.
 *
 * Rule you already know:
 *      - INDEXING / pointer arithmetic -> think in ELEMENTS (compiler scales).
 *      - MEMORY / SIZE functions       -> think in BYTES (you multiply by sizeof).
 * 
 * This file shows both sides side by side, plus the classic bugs that
 * happen when you mix them up. Each section prints what it did.
 *
*/

static void printInts(const char *label, const int *a, int n)
{
    printf("%s", label);
    for (int i = 0; i < n; i++) 
        printf("%d ", a[i]);
    printf("\n");
}

int main(void)
{
    int n = 5;

    /* --- 1. malloc: BYTES. You ask for n * sizeof(int) --- */
    int *a = malloc(n * sizeof(int)); /* BYTE math: 5 * 4 = 20 bytes */
    if (a == NULL) {
        printf("out of memory\n");
        return 1;
    }

    /* --- 2. filling it: ELEMENTS. Index normally, no sizeof --- */
    for (int i = 0; i < n; i++)
        a[i] = (i + 1) * 10; /* ELEMENT thinking */
    printInts("1) malloc'd then filled : ", a, n);

    /* --- 3. memcpy: BYTES. Copy the whole block. --- */
    int *b = malloc(n * sizeof(int));
    if (b == NULL) {
        free(a);
        return 1;
    }
    memcpy(b, a, n * sizeof(int)); /* BYTE math again: 20 bytes */
    printInts("2) memcpy'd copy : ", b, n);

    /* --- 4. THE CLASSIC BUG: forgetting sizeof in memcpy --- 
        memcpy(b, a, n) would copy only 5 BYTES = just over 1 int,
        leaving the rest of b as garbage. We do it on purpose into 
        a scratch buffer to SEE the damage, without corrupting b.
    */
   int *bug = malloc(n * sizeof(int));
   if (bug == NULL) {
        free(a);
        free(b);
        return 1;
   }
   memset(bug, 0, n * sizeof(int)); /* zero it first so garbage is visible */
   memcpy(bug, a, n);               /* BUG: 'n' bytes, not n*sizeof(int) */
   printInts("3) BUGGY memcpy(.., n)    : ", bug, n);
   printf("^ only the first int (partially) copied; rest stayed: 0.\n");

   /* --- 5. sizeof on the pointer vs the element --- 
      sizeof(a) here is the POINTER size (8), NOT the array size.
      sizeof(*a) or sizeof(int) is one ELEMENT (4). This is why the
      byte count must be n * sizeof(*a), computed by YOU.
   */
  printf("\nsizeof(a)   = %zu   (a POINTER - size info is NOT here)\n", sizeof(a));
  printf("sizeof(*a)    = %zu   (one ELEMENT - what you multiply by n)\n", sizeof(*a));
  printf("so bytes needed = n * sizeof(*a)  = %zu * %zu = %zu\n",
        (size_t)n, sizeof(*a), n * sizeof(*a));

    /* --- 6. strings: element indexing is normal, but length has the
        hidden '\0'. The ARRAY is strlen+1 bytes. --- */
    char *s = malloc(6);    /* 6 BYTES for "hello" + '\0' */
    if (s == NULL) {
        free(a);
        free(b);
        free(bug);
        return 1;
    }
    strcpy(s, "hello");
    printf("\nstring \"%s\": strlen=%zu (elements of text), "
           "but array uses %zu bytes (incl. '\\0')\n",
           s, strlen(s), strlen(s) + 1);
    printf("s[0]=%c s[4]=%c s[5]=%d <- s[5] is the '\\0' terminator (value 0)\n",
            s[0], s[4], s[5]);

    /* --- 7. cleanup: one free per malloc --- */
    free(a);
    free(b);
    free(bug);
    free(s);

    printf("\nTakeaway: index in ELEMENTS; malloc/memcpy/memset in BYTES "
           "(always n * sizeof(element)).\n");
    return 0;
}