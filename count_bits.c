#include <stdint.h>
#include <stdio.h>
#define sizeInBits(x) (sizeof(x) * 8)

/* printRecursiveBits: print the bits in an int recursively */
void printRecursiveBits(int val, int counter) {
    if (counter > 0) {
        printRecursiveBits(
            val >> 1, counter - 1); // Recursive call with decremented counter
        printf("%u", val & 1);      // Print the least significant bit
        if (counter % 8 == 0) {
            printf(" "); // Print a space after every 8 bits
        }
    }
}

/* printIntBits: print the bits in an int */
void printIntBits(int k) {
    size_t i;
    for (i = 0; i < sizeof(k) * 8; i++) {
        printf("%d", (k >> (sizeof(k) * 8 - i - 1)) & 1);
    }
    putchar('\n');
}

/* printBits: print the bits in any data type */
void printBits(void *ptr, size_t size) {
    unsigned char *bytes = (unsigned char *)ptr;
    for (size_t i = size - 1; i != SIZE_MAX; i--) {
        for (int j = 7; j >= 0; j--) {
            printf("%d", (bytes[i] >> j) & 1);
        }
        putchar(' '); // print a space after each byte
    }
    putchar('\n');
}

/*count the number of bits (1's) in a number*/
int count_bits(long int input) {
    int output = 0;
    unsigned long int unsigned_input = input;

    for (size_t i = 0; i < sizeof(unsigned_input) * 8; i++) {
        if (unsigned_input & 1)
            output++;
        unsigned_input >>= 1;
    }
    return output;
}

/* getSizeInBits: return the size of a data type in bits */
int getSizeInBits(unsigned short int input) { return sizeof(input) * 8; }

/* count the number of bits (1's) in a number in odd places*/
int count_odd_bits(unsigned short int input) {
    int output = 0;
    for (int i = 1; i < getSizeInBits(input); i += 2) {
        if (input & 1)
            output++;
        input >>= 2;
    }
    return output;
}

/* ask the user for a number and print the number of bits (1's) in it */
int main() {
    long int read_num;
    printf("This program counts the number of bits (1's) in a number, and "
           "prints the result. Please insert a number:\n");

    while (1) {
        if (scanf("%ld", &read_num) != 1) {
            printf("Invalid input. Please insert a number:\n");
            while (getchar() != '\n')
                ; // Clearing the input buffer
            continue;
        }
        printBits(&read_num, sizeof(read_num));
        printRecursiveBits(read_num, sizeInBits(read_num));
        printf("\n");
        printf("The number %ld has %d 1's.\n", read_num, count_bits(read_num));
        printf("The number %hu has %d 1's in odd places.\n",
               (unsigned short int)read_num,
               count_odd_bits((unsigned short int)read_num));
        printf("Do you want to continue? (y/n)\n");
        while (getchar() != '\n')
            ; // Clearing the input buffer

        if (getchar() != 'y')
            break;

        printf("Please insert a number:\n");
    }

    return 0;
}