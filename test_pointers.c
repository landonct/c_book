#include <stdio.h>

int main()
{
    int x = 10;
    int *ref = &x;
    *ref = 5;
    printf("x is: %d\n", x);
}