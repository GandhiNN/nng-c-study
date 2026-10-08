#include <stdio.h>

/*
 * LESSON: pointers to structs and the ARROW operator (->).
 *
 * When you have a POINTER to a struct, you could write:
 *      (*p).x -- dereference p, then take member x
 * but that's clumsy, so C gives you a shortcut that means the SAME thing:
 *      p->x  -- "the x member of the struct p points to"
 * 
 * So:  p->x IS EXACTLY (*p).x
 * 
 * This matters because, just like arrays, passing a struct by pointer
 * avoids copying the whole thing and lets a function modify the original.
*/

struct Point {
    int x;
    int y;
};

/* Takes a POINTER, so it can modify the caller's struct (no copy made). */
void moveBy(struct Point *p, int dx, int dy)
{
    p->x += dx;     /* same as (*p).x += dx */
    p->y += dy;
}

int main(void)
{
    struct Point a = {3, 4};
    struct Point *p = &a;   /* p points at a */

    /* Two equivalent ways to reach a member through a pointer: */
    printf("p->x    = %d\n", p->x);
    printf("(*p).x  = %d    <- identical to p->x\n", (*p).x);

    /* Because moveBy got a pointer, it changes the REAL 'a'. */
    moveBy(&a, 10, 20);
    printf("\nafter moveBy: a = (%d, %d) <- original modified\n", a.x, a.y);

    return 0;
}