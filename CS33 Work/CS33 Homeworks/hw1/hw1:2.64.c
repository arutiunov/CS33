// 2.64:

#include <stdio.h>
#include <limits.h>

int saturating_add(int x, int y)
{
    int sum = x + y;
    int placeholder;
    int amtBits = ((sizeof(int)<<3) -1);
    
    int xNeg = x >> amtBits;
    int yNeg = y >> amtBits;
    
    int overflow = __builtin_add_overflow(x, y, &placeholder);
    overflow = overflow >> amtBits;
    
    int posOverflow = ~xNeg & ~yNeg & overflow;
    int negOverflow = xNeg & yNeg & overflow;
    
    posOverflow = posOverflow >> amtBits;
    negOverflow = negOverflow >> amtBits;
    
    int notOverflow = ~overflow;
    int result = (posOverflow & INT_MAX) | (negOverflow & INT_MIN) | (notOverflow & sum);
    
    return result;
}

/*
 2.72:
 
 A) Since the sizeof operator returns the type size_t, the operator returns an unsigned value. Thus, when we perform the arithmetic operator maxbytes - sizeof(val), we are always going to yield a positive result, since an integer type minus an unsigned type always yields an unsigned type. Thus the expression if (maxbytes-sizeof(val) >= 0) always holds true.
 
 
 B) One way to rewrite the condition test in order to always make it work is to change it to the following: if (maxbytes >= sizeof(val)). Or maxbytes - (int)sizeof(val) >= 0.

 */
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

/*
 2.82:
 
 A) This does not always yield 1. If we had x be equal to INT_MIN, then the negation of INT_MIN would still be INT_MIN, because it has no positive counterpart. As a result, the right hand of the boolean equation is not true.
 
 B) This always yields 1. This is because shifting to the left by 4 means multiplying the sum of x and y by a constant of 16. By adding one more value of y and subtracting one value of x, we yield the same value every time as if we just did 17 * y + 15 * x.
 
 
 C) This always yields 1. This is because individually flipping the bits of x and y and then adding one yields the same exact result if you add the digits together first and then negate them. We rewrite ~x as -x-1 and ~y as -y-1, so the entire expression yields to
 (-x-y-1). When applying the tilde to the sum of x and y, we get the same result.
 
 
 D) This always yields 1. Since taking the different of two unsigned numbers will never overflow, we can have either a positive or a negative value on the left hand side. On the right hand side, casting the difference between y and x will yield a positive number, and assigning a negative value to it will yield the exact same number as the left hand side.
 
 
 E) This always yields 1. Shifting to the right arithmetically makes a number smaller, and shifting that smaller number is the same as multiplying it by 4. Even with negative numbers, we still get a smaller result than the right hand side, making the expression always true.

*/