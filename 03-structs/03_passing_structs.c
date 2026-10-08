#include <stdio.h>

/*
 * LESSON: passing structs BY VALUE vs BY POINTER.
 *
 * Unlike raw arrays (which decay to a pointer), a struct passed to a
 * function is COPIED in full, every member. That has two consequences:
 * 
 *  1. The function works on a COPY, so it cannot change the caller's
 *     struct, unless you pass a POINTER (&s) instead.
 *  2. Copying a big struct costs time/memory (recall the earlier
 *     copy-vs-pointer benchmark, same idea applies to structs).
 * 
 * Rule of thumb: pass small structs by value if you want a copy; pass by
 * pointer when the struct is large OR you need to modify the original.
*/

struct Point {
    int x;
    int y;
};

/* BY VALUE: receives a COPY. Changes here do NOT affect the caller. */
void tryMoveByValue(struct Point p, int dx, int dy)
{
    p.x += dx;  /* modifies the local copy only */
    p.y += dy;
}

/* BY POINTER: receives the address. Changes DO affect the caller. */
void moveByPointer(struct Point *p, int dx, int dy)
{
    p->x += dx; /* reaches through the pointer to the real struct */
    p->y += dy;
}

int main(void)
{
    struct Point a = {3, 4};

    /* By value: no effect on 'a' (the function changed a copy). */
    tryMoveByValue(a, 100, 100);
    printf("after tryMoveByValue: a = (%d, %d)  <- unchanged (copy)\n",
            a.x, a.y);

    /* By pointer: 'a' really changes. */
    moveByPointer(&a, 10, 20);
    printf("after moveByPointer: a = (%d, %d)   <- changed (via pointer)\n",
            a.x, a.y);

    /* Returning a struct also copies it out, fine for small structs. */
    printf("\nA struct can be returned by value too (whole thing copied back).\n");

    return 0;
}