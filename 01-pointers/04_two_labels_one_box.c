#include <stdio.h>

/*
 * LESSON 2: Many labels can point at the SAME box.
 *           Changing the box through ANY label changes it for ALL.
 * 
 * This is the "aha" that makes pointers click. There is only ONE
 * variable 'score'. Both p and q point at it. Writing through p
 * is literally writing to score.
 * 
 * Contrast with COPYING: 'copy = score' makes a brand-new box.
 * Changing 'copy' does nothing to 'score'.
*/

int main(void)
{
    int score = 50;
    int *p = &score;    // label 1 -> score
    int *q = &score;    // label 2 -> score (same box)

    printf("Start:  score=%d\n", score);

    *p = 70;    // write through label 1
    printf("After *p = 70: score=%d *q=%d\n", score, *q);
    // *q changed too, because q points at the same box!

    *q = 99;    // write through label 2
    printf("After *q = 99: score=%d *p=%d\n", score, *p);

    // Now compare with a COPY (not a pointer):
    int copy = score; // brand-new box, value copied in
    copy = 0; // only touches the copy
    printf("\nscore=%d copy=%d <- copy is independent\n", score, copy);

    return 0;
}