#include <stdio.h>
#include <time.h>

/*
 * EXPERIMENT: copying an array by value vs. passing a pointer.
 * 
 * You CANNOT pass a raw C array by value -- it decays to a pointer.
 * The only way to force a full copy is to wrap it in a struct, because
 * structs ARE passed by value (the whole thing is copied).
 * 
 * So we compare:
 *  byValue(Big b)      -> copies ALL the ints every call (expensive)
 *  byPointer(int *)    -> copies only an 8-byte address (cheap)
 * 
 * Both just sum the array so the compiler can't optimize the work away.
*/

#define N 100000        /* array size: 100k ints ~ 400 KB per copy */
#define CALLS 20000     /* how many times we call each function */

typedef struct {
    int data[N];
} Big;

/* Pass by value: the ENTIRE Big struct (all N ints) is copied in. */
long byValue(Big b)
{
    long sum = 0;
    for (int i = 0; i < N; i++)
        sum += b.data[i];
    return sum;
}

/* Pass by pointer: only an address is copied in (8 bytes). */
long byPointer(const int *p, int n)
{
    long sum = 0;
    for (int i = 0; i < n; i++)
        sum += p[i];
    return sum;
}

int main(void)
{
    static Big big;     /* static: too large for the stack */
    for (int i = 0; i < N; i++)
        big.data[i] = i % 7;

    volatile long sink = 0; /* volatile stops the compiler eliding calls */
    clock_t t0, t1;

    /* --- Time the by-value version (copies the whole array each call) --- */
    t0 = clock();
    for (int c = 0; c < CALLS; c++)
        sink += byValue(big);
    t1 = clock();
    double valueSecs = (double)(t1 - t0) / CLOCKS_PER_SEC;

    /* --- Time the by-pointer version (copies only an address) --- */
    t0 = clock();
    for (int c = 0; c < CALLS; c++)
        sink += byPointer(big.data, N);
    t1 = clock();
    double ptrSecs = (double)(t1 - t0) / CLOCKS_PER_SEC;

    printf("Array size per call     : %zu bytes\n", sizeof(Big));
    printf("Calls each              : %d\n\n", CALLS);
    printf("by value (full copy)    : %.3f sec\n", valueSecs);
    printf("by pointer (address)    : %.3f sec\n", ptrSecs);
    if (ptrSecs > 0)
        printf("\nby-value was %.1fx slower\n", valueSecs / ptrSecs);

    return (int)(sink & 1); /* use sink so nothing is optimized away */
}