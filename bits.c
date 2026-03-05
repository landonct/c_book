#include <stdio.h>
unsigned shiftbits(unsigned x, int p, int n, unsigned y);
unsigned invert(unsigned x, int p, int n);
unsigned rightrot(unsigned x, int n);
int wordlength();
void alphabet();
int lower(int c);

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

    printf("Starting Unit Tests for invert...\n\n");

    /* Test 1: Flipping all bits in a byte */
    // x = 0000 0000 (0), p = 7, n = 8
    // Expect: 1111 1111 (255)
    result = invert(0, 7, 8);
    printf("Test 1: %s (Expected 255, Got %u)\n", (result == 255) ? "PASS" : "FAIL", result);

    /* Test 2: Flipping middle bits */
    // x = 1010 1010 (170), p = 5, n = 4
    // Bits 5,4,3,2 are 1010 -> flip to 0101
    // Result: 1001 0110 (150)
    result = invert(170, 5, 4);
    printf("Test 2: %s (Expected 150, Got %u)\n", (result == 150) ? "PASS" : "FAIL", result);

    /* Test 3: Flip only the edges */
    // x = 0xFF (1111 1111), p = 7, n = 1, then p = 0, n = 1
    // Flipping bit 7 makes it 0111 1111 (127)
    result = invert(255, 7, 1);
    printf("Test 3a: %s (Expected 127, Got %u)\n", (result == 127) ? "PASS" : "FAIL", result);
    
    // Flipping bit 0 of 255 makes it 1111 1110 (254)
    result = invert(255, 0, 1);
    printf("Test 3b: %s (Expected 254, Got %u)\n", (result == 254) ? "PASS" : "FAIL", result);
    // /*Test 1: Invert middle */
    // // x = 15, p = 2, n = 2, return = 1001 (9)
    // result = invert(15, 2, 2);
    // printf("Test: %s, got %u\n", (result == 9) ? "PASS" : "FAIL", result);

    printf("Starting Unit Tests for rightrot (32-bit)...\n\n");

    /* Test 1: Rotate by 0 (Should change nothing) */
    result = rightrot(0x12345678, 0);
    printf("Test 1: %s (Expected 0x12345678, Got 0x%08x)\n", 
           (result == 0x12345678) ? "PASS" : "FAIL", result);

    /* Test 2: Simple wrap-around */
    // x = 1 (...0001). Rotate right by 1.
    // The 1 should jump to the MSB (2^31).
    // Expected: 0x80000000 (2147483648)
    result = rightrot(1, 1);
    printf("Test 2: %s (Expected 2147483648, Got %u)\n", 
           (result == 2147483648) ? "PASS" : "FAIL", result);

    /* Test 3: Multiple bit rotation */
    // x = 0x000000FF (...11111111). Rotate right by 4.
    // The last four 1s (0xF) should move to the very top.
    // Expected: 0xF000000F (which is 1111...0000...1111)
    // Actually, wait: bits 0,1,2,3 move to 31,30,29,28. 
    // Bits 4,5,6,7 move to 0,1,2,3.
    // Expected: 0xF000000F
    result = rightrot(0x000000FF, 4);
    printf("Test 3: %s (Expected 0xF000000F, Got 0x%08X)\n", 
           (result == 0xF000000F) ? "PASS" : "FAIL", result);

    /* Test 4: Full rotation */
    // Rotating by the word length (32) should return the original number
    result = rightrot(0xDEADBEEF, 32);
    printf("Test 4: %s (Expected 0xDEADBEEF, Got 0x%08X)\n", 
           (result == 0xDEADBEEF) ? "PASS" : "FAIL", result);

    alphabet();

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
    return (~(~0 << n) << (p + 1 - n)) ^ x;
}

/* Write a function rightrot(x, n) that returns the value of the integer x rotated to the right by n bit positions */
unsigned rightrot(unsigned x, int n)
{
    if(n > 32) 
        return x;
    
    int length = wordlength();
    unsigned xp1, xp2;

    xp1 = x >> n;
    xp2 = (x << (length - n));

    return xp1 | xp2;
}

int wordlength(void)
{
    unsigned iterated = (unsigned) ~0;
    int length;
    for(length = 1; (iterated = iterated >> 1) > 0; length++)
        ;
    return length;
}

void alphabet(void)
{
    int letter = 'A';
    while(letter <= 'z')
    {
        putchar(lower(letter));
        letter++;
    }
    printf("\n");
}

int lower(int c)
{
    return ('A' <= c && c <= 'Z') ? (c - 'A') + 'a' : c;
}
