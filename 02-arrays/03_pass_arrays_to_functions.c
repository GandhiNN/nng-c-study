#include <stdio.h>

void foo(int x[12])
{
    printf("%zu\n", sizeof(x)); // 8 -> size of the pointer
    printf("%zu\n", sizeof(int)); // 4 bytes is the size of an int

    printf("%zu\n", sizeof(x) / sizeof(int)); // 8/4 -> 2
}

int main(void)
{
    int f[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    
    foo(f);

    return 0;
}