#include <stdio.h>
#include <string.h>

/*
 * LESSON: string literals -> array copy vs read-only pointer.
 *
 * A string literal like "Hello" is stored by the compiler as a sequence of chars ending in a hidden '\0'
 * HOW you bind it to a variable changes everything:
 * 
 *  char s[] = "Hello";     -> COPIES the literal into YOUR array (writable)
 *  char *p = "Hello";      -> points AT the literal in READ-ONLY memory
 * 
 * Writing through the pointer version is undefined behavior (often a crash).
 * Writing to the array version is fine -- it's our own copy.
*/

int main(void)
{
    /* (1) ARRAY: a writable copy we own. */
    char s[] = "Hello";
    printf("array s = \"%s\" (length %zu, array size %zu incl. '\\0')\n",
            s, strlen(s), sizeof(s));

    s[0] = 'J'; /* SAFE: s is our own copy */
    printf("after s[0]='J': \"%s\"\n\n", s);

    /* (2) POINTER to a literal: read-only. Reading is fine. */
    const char *p = "World"; /* 'const' documents + enforces read-only */
    printf("pointer p = \"%s\" (length %zu)\n", p, strlen(p));
    printf("p[0] = '%c' (reading is fine)\n", p[0]);
    /* p[0] = 'X'; <-- would be UNDEFINED BEHAVIOR: literal is read-only.
       Left commented so the program stays safe to run. The 'const' above
       makes the compiler reject it, which is exactly the protection we want. */

    /* The hidden terminator: walk until '\0' instead of hardcoding a length. */
    printf("\nwalking s until '\\0': ");
    for (int i = 0; s[i] != '\0'; i++)
        printf("%c", s[i]);
    printf("\n");

    /* Proof of the '\0': the char right after the text has value 0. */
    printf("s has %zu visible chars; s[%zu] = %d (the '\\0')\n",
            strlen(s), strlen(s), s[strlen(s)]);

    return 0;
}