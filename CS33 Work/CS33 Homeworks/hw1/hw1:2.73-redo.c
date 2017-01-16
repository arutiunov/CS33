// 2.73 re-do

#include <stdio.h>
#include <limits.h>

int saturating_add(int x, int y)
{
    int sum = x + y;
    int placeholder;
    
    int amtBits = ((sizeof(int)<<3) - 1);
    
    int xNeg = x >> amtBits; // either 0 or 1
    
    int yNeg = y >> amtBits; // either 0 or 1
    
    int overflow = __builtin_add_overflow(x, y, &placeholder); // overflow have value of 0 or 1
    overflow = overflow >> amtBits; // arithmetic shift to the right
    
    int posOverflow = ~xNeg & ~yNeg & overflow;
    int negOverflow = xNeg & yNeg & overflow;
    
    posOverflow = posOverflow >> amtBits;
    negOverflow = negOverflow >> amtBits;
    
    int notOverflow = ~overflow;
    
    int result = (posOverflow & INT_MAX)|(negOverflow & INT_MIN) | (notOverflow & sum);
    
    return result;
}