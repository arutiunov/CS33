#include <stdio.h>
#include <limits.h>


// 2.64
int any_odd_one(unsigned x)
{
    return (x&0xAAAAAAAA) != 0;
}

// 2.72

void copy_int(int val, void *buf, int maxbytes) {
    if (maxbytes-sizeof(val) >= 0)
        memcpy(buf, (void *) &val, sizeof(val));
}

// A: Since the sizeof operator of type size_t, the operator returns an unsigned value. Thus, when we perform the arithmetic operator maxbytes - sizeof(val), we are always going to yield a positive result, since an integer type minus an unsigned type always yields an unsigned type. Thus the expression if (maxbytes-sizeof(val) >= 0) always holds true.
// B: One way to rewrite the condition test in order to always make it work is to change it to the following: if (maxbytes >= sizeof(val)). Or maxbytes - (int)sizeof(val) >= 0

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

// 2.72 Redone
//
//int redone_saturating_add(int x, int y)
//{
//    int sum = x + y;
//    int placeholder;
//    
//    int amtBits = ((sizeof(int)<<3) - 1);
//    
//    int overflow = __builtin_add_overflow(x, y, &placeholder); // overflow have valu eof 0 or 1
//    overflow = overflow >> amtBits; // arithmetic shift to the right
//    int notOverflow = ~overflow; // opposite value of overflow
//    notOverflow = notOverflow >> amtBits;
//    
//    int result = (overflow & INT_MAX)|(overflow & INT_MIN) | (notOverflow & sum);
//    
//    return result;
//}


// 2.82
// A: T; B: T; C: T; D: F; E: F

int main() {
////    unsigned int x = 0;
////    int result = any_odd_one(x);
////    printf("%d\n", result);
////    
////    int a = 0;
////    int b = ~a;
////    printf("%d\n", b);
//    
//    int x = 64;
//    int result = ~(x&INT_MIN);
//    printf("%d\n", result);
    int x = 69;
    int y = -3;
    
    int result = saturating_add(x, y);
    printf("%d\n", result);
}
