#include <stdio.h>

/*
 * CAPSTONE: a tiny "exam scores" program that USES every pointer idea
 * from lessons 1=5. No new concepts -- just the ones you learned,
 * working together on a realistic task.
 * 
 * Concepts in play:
 *      L1/L2 a pointer holds an address; dereference to read/write the box
 *      L3    functions take addresses to modify the caller's data
 *      L4    swapping two values via pointers
 *      L5    array name decays to a pointer; a[i] == *(a+i); pointer walking
 *
*/

/* L3: writes results back through pointers (two "returns" via out-params). */
void analyze(int *scores, int n, int *outSum, int *outMax)
{
    int sum = 0;
    int max = scores[0];    // scores[0] == *(scores + 0)

    for (int *p = scores; p < scores + n; p++) { // walk by pointer
        sum += *p;  // read the box p points at
        if (*p > max)
            max = *p;
    }

    *outSum = sum;  // L1/L3: write through the pointer
    *outMax = max;
}

/* Swap two ints via their addresses. */
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* add 'bonus' to every score, modifying the caller's array in place. */
void curveUp(int *scores, int n, int bonus)
{
    for (int i = 0; i < n; i++)
        scores[i] += bonus;     // scores[i] == *(scores + i)
}

/* Simple bubble sort (descending) -- reuses swap() to show pointers passing
 * addresses of array elements. */
void sortDesc(int *scores, int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (scores[j] < scores[j + 1])
                swap(&scores[j], &scores[j + 1]); // &a[k] == (a + k)
}

void printScores(const char *label, int *scores, int n)
{
    printf("%s", label);
    for (int i = 0; i < n; i++)
        printf("%d ", scores[i]);
    printf("\n");
}

int main(void)
{
    int scores[6] = {55, 90, 72, 48, 88, 63};
    int n = 6;

    printScores("Original: ", scores, n);

    /* Give everyone a+5 curve (array modified in place via pointer). */
    curveUp(scores, n, 5);
    printScores("Curved+5 : ", scores, n);

    /* Sort highest-first (uses swap through element addresses). */
    sortDesc(scores, n);
    printScores("Sorted :", scores, n);

    /* Analyze: two results come back through out-pointers. */
    int sum = 0, max = 0;
    analyze(scores, n, &sum, &max);

    printf("\nTotal = %d\n", sum);
    printf("Average = %.1f\n", (double)sum / n);
    printf("Highest = %d\n", max);

    return 0;
}