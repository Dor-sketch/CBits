#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define sizeInBits(x) (sizeof(x) * 8)

/* all the combinations to set bits in 8-bit mask (represents 0-15 int) */
const uint8_t lookup[] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};

/* counting bits using a lookup table */
int count_bits_nibbles(int num) {
	unsigned int n = num; // for both positive and negative

	// count bits in group of 8
	int count = 0;
	for (int i = 0; i < 8; i++) {
		count += lookup[n & 0xf];
		n >>= 4;
	}
	return count;
}

/* counting bits using quick jumbs with n&(n-1)*/
int count_bits_jumps(int num) {
	unsigned int n = num; // for both positive and negative
	int count = 0;
	while (n) {
		n = n & (n - 1);
		count++;
	}
	return count;
}

/* count the number of bits (1's) in a number using iterative approach */
int count_bits_iterative(long int input) {
	int output = 0;
	unsigned long int unsigned_input = input;

	for (size_t i = 0; i < sizeof(unsigned_input) * 8; i++) {
		if (unsigned_input & 1)
			output++;
		unsigned_input >>= 1;
	}
	return output;
}

/* printRecursiveBits: print the bits in an int recursively */
void printRecursiveBits(int val, int counter) {
	if (counter > 0) {
		printRecursiveBits(
			val >> 1, counter - 1); // Recursive call with decremented counter
		printf("%u", val & 1);		// Print the least significant bit
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

void correctness_example(void) {
	// printing results for example
	for (int i = -10; i < 10; i++) {
		int num = rand() - RAND_MAX / 2;
		printBits(&num, sizeof(num));
		char buffer[50];
		sprintf(buffer, "count_bits_nibbles(%d)", num);
		printf("%-32s = %d\n", buffer, count_bits_nibbles(num));
		sprintf(buffer, "count_bits_jumps(%d)", num);
		printf("%-32s = %d\n", buffer, count_bits_jumps(num));
		sprintf(buffer, "count_bits_iterative(%d)", num);
		printf("%-32s = %d\n", buffer,
			   count_bits_iterative((unsigned int)num));
		printf("\n");
	}
}

void performance_example(void) {
	// test different approch performance
	time_t start, end;
	double cpu_time_used;

	char names[3][20] = {"count_bits_nibbles", "count_bits_jumps",
						 "count_bits_iterative"};
	int (*func_array[3])(int) = {count_bits_nibbles, count_bits_jumps,
								 count_bits_iterative};

	for (int i = 0; i < 3; i++) {
		int (*func)(int) = func_array[i];
		printf("Testing function %s\n", names[i]);
		start = clock();
		for (int j = -5000; j < 100000000; j++) {
			func(j);
		}
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("Time taken: %f\n", cpu_time_used);
	}
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
int scanbits(void) {
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
		printf("The number %ld has %d 1's.\n", read_num,
			   count_bits_iterative(read_num));
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

int main() {
	correctness_example();
	performance_example();
    printBits(&lookup, sizeof(lookup));
	return 0;
}