// 2.73:

#include <stdio.h>
#include <limits.h>

int saturating_add(int x, int y)

{
    int sum = x + y;
    
    // determine amount of bits in an integer type (shift by three because
    // result is yielded in bytes), gives us 31
    int amtBits = ((sizeof(int)<<3) - 1);
    
    int xNeg = x >> amtBits; // either 0 or 1
    
    int yNeg = y >> amtBits; // either 0 or 1
    
    int sumNeg = sum >> amtBits; // either 0 or 1
    
    int posOverflow =  ~xNeg & ~yNeg & sumNeg;
    // only yields all 1's when x is positive, y is positive, and sum is negative
    
    int negOverflow = xNeg & yNeg & ~sumNeg;
    // only yields all 1's when x is negaitve, y is negative, and sum is positive
    
    int notOverflow = ~(posOverflow | negOverflow);
    // yields 1 if either are 1, so we negate to yield 0
    
    int result = (posOverflow & INT_MAX)|(negOverflow & INT_MIN) | (notOverflow & sum);
    // result will take the value of one of these three, because only one variable between posOverflow, negOverflow,
    // or notOverflow will be all 1's, therefore taking on the value that it is & with
    
    return result;
}