#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) 
{
    int remainder;
    while (b != 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}
