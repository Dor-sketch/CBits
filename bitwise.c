#include <stdio.h>

//////////////////////////
//  Bitwise Operators

//  AND – & – Sets each bit to 1 if both bits are 1
//  OR – | – Sets each bit to 1 if any of the bits is set to 1
//  XOR – ^ – Sets each bit to 1 if only one of the bits is set to 1
//  NOT – ~ – Inverts all the bits
//  << – Zero fill left shift
//  >> – Signed right shift
/////////////////////////

//  Shift Operators
//  << – Left Shift
//  >> – Right Shift
/////////////////////////

//  Bitwise Assignment Operators
//  |= – Bitwise OR assignment
//  &= – Bitwise AND assignment
//  ^= – Bitwise XOR assignment
//  <<= – Left shift assignment
//  >>= – Right shift assignment
//////////////////////////

/* bits union: represents a float as its parts according to the IEEE
 * floating-point standard */
union bits {
    float f; /* assumes sizeof(float) == sizeof(int) */
    unsigned int u;
    struct {
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
    } parts;
};

void print_float_parts(float number) {
    union bits num;
    num.f = number; // Store the float in the union

    // Extracting the parts
    unsigned int sign = num.parts.sign;
    unsigned int exponent = num.parts.exponent;
    unsigned int mantissa = num.parts.mantissa;

    // Print the parts
    printf("Float: %f\n", number);
    printf("Sign: %u (0 for positive, 1 for negative)\n", sign);
    printf("Exponent: %u (Stored Exponent)\n", exponent);
    printf("Mantissa: %u (Fraction part)\n", mantissa);
}



// 00001111
// &
// 00000111
//--------
// 00000111
////////////////////////////////////

// 00001111
// |
// 00000111
//--------
// 00001111
////////////////////////////////////

// 00001111
//^
// 00000111
//--------
// 00001000
////////////////////////////////////

/* xorSwap: swap *x and *y by XORing them */
void xorSwap(int *x, int *y) {
    if (x != y) {
        *x ^= *y; //<==> One = One ^ Two;
        *y ^= *x; //<==> Two = Two ^ One = Two ^ (One ^ Two) = One;
        *x ^= *y; //<==> One = One ^ Two = (One ^ Two) ^ One = Two;
    }
}

/* shift: demonstrates the left shift operator */
void shift() {
    unsigned int Value = 4; /*  4 = 0000 0100 */
    unsigned int Shift = 2;

    Value = Value << Shift; /* 16 = 0001 0000 */
    Value <<= Shift;        /* 64 = 0100 0000 */

    printf("%d\n", Value); /* Prints 64 */
}

/* mask and toggle: demonstrates the bitwise AND operator */
void mask_and_toggle() {
    unsigned int Value = 0x0F; /*  15 = 0000 1111 */
    unsigned int Mask = 0x06;  /*   6 = 0000 0110 */

    Value &= Mask;        /*   6 = 0000 0110 */

    printf("%d\n", Value); /* Prints 6 */
}

int main() {

    int x = 7;
    int y = 15;

    int z = x & y;
    printf("x&y=%d\n", z);
    z = x | y;
    printf("x|y=%d\n", z);
    z = x ^ y;
    printf("x^y=%d\n", z);

    printf("x&y=%d\n", z);
    float test_number = -123.456f;
    print_float_parts(test_number);

    mask_and_toggle();

    return 0;
}