#include <stdio.h>
unsigned shiftbits(unsigned x, int p, int n, unsigned y);

int main() 
{
    unsigned result;

    printf("Starting Unit Tests for setbits...\n\n");

    /* Test 1: Clearing bits using zeros from y */
    // x = 1111 1111 (255), p = 4, n = 3, y = 0000 0000 (0)
    // We expect bits 4,3,2 to become 0. Result: 1110 0011 (227)
    result = shiftbits(255, 4, 3, 0);
    printf("Test 1: %s (Expected 227, Got %u)\n", (result == 227) ? "PASS" : "FAIL", result);

    /* Test 2: Setting bits in a zeroed x */
    // x = 0, p = 3, n = 4, y = 15 (1111)
    // We expect bits 3,2,1,0 to become 1. Result: 0000 1111 (15)
    result = shiftbits(0, 3, 4, 15);
    printf("Test 2: %s (Expected 15, Got %u)\n", (result == 15) ? "PASS" : "FAIL", result);

    /* Test 3: Complex replacement */
    // x = 170 (1010 1010), p = 4, n = 3, y = 7 (0111)
    // Bits 4,3,2 of x are '010'. We want to replace them with '111' from y.
    // Result should be 1011 1110 (190)
    result = shiftbits(170, 4, 3, 7);
    printf("Test 3: %s (Expected 190, Got %u)\n", (result == 190) ? "PASS" : "FAIL", result);

    return 0;
}

/* Return x with the n bits that begin at position p set too the rightmost n bits of y leaving the other unchanged
x = 0110 1001, p = 2, n = 2, y = 1111 => 1100 */
unsigned shiftbits(unsigned x, int p, int n, unsigned y)
{
   return (x & ~(~(~0 << n) << (p + 1 - n))) | ((y & ~(~0 << n)) << (p + 1 - n));
}

/* Write invert(x, p, n) that returns x with the n bits that begin at position p inverted, leaving others unchanged 
x = 1111, p = 2, n = 2 => 1001 */
unsigned invert(unsigned x, int p, int n)
{
    
}
