#include <stdio.h>

/*
 * LESSON: operating on a SUB-RANGE of an array.
 *
 * A function that takes (int *start, int count) doesn't care whether
 * 'start' is the real beginning of an array or somewhere in the MIDDLE.
 * A pointer just says "here"; the count says "how many from here".
 * 
 * This is how C works on slices without copying: you pass
 *      &arr[i]     (same as arr + i) as the start
 *      some count                    as the length
 * and the function sees a normal little array that begins at element i.
 * 
 * KEY IDENTITIES (from pointer arithmetic):
 *      &arr[i] == arr + i
 *      inside the function, p[0] is the caller's arr[i]
*/

/* Works on 'count' elements starting wherever 'p' points. */
long sumRange(const int *p, int count)
{
    long sum = 0;
    for (int i = 0; i < count; i++)
        sum += p[i];    /* p[0] is the START element, not arr[0] */
    return sum;
}

/* Fills 'count' elements starting at p with a value -- modifies the
   caller's array in place, only within the chosen sub-range. */
void fillRange(int *p, int count, int value)
{
    for (int i = 0; i < count; i++)
        p[i] = value;
}

static void printArray(const char *label, const int *a, int n)
{
    printf("%s", label);
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main(void)
{
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    /* Sum the WHOLE array: start at the front, count = 10. */
    printf("sum all 10      : %ld\n", sumRange(arr, 10));

    /* Sum only arr[5..9]: start in the MIDDLE via &arr[5]. */
    printf("sum arr[5..9]   : %ld\n", sumRange(&arr[5], 5));

    /* Same thing written with pointer arithmetic -- identical. */
    printf("sum arr[5..9]   : %ld (via arr + 5)\n", sumRange(arr + 5, 5));

    /* Sum a middle chunk arr[3..6]: start at index 3, take 4 elements. */
    printf("sum arr[3..6]   : %ld\n", sumRange(&arr[3], 4));

    /* Modify just a sub-range: set arr[2..5] to 99, rest untouched. */
    fillRange(&arr[2], 4, 99);
    printArray("after fillRange(&arr[2], 4, 99): ", arr, 10);

    printf("\nThe function never knew it was working on part of a bigger array.\n");
    return 0;
}