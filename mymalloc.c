/* This program is a custom implementation of the malloc and free functions in
 * C. it returness aligned adresses with a custom offset
 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ALIGNED_BYTES 255 // Must be less than 256 to fit in a byte

struct ThirtyTwoBytes {
	char data[ALIGNED_BYTES];
};

void *mymalloc(size_t size) {
	// get the original pointer + extra bytes for offset
	unsigned char *original_ptr = (unsigned char *)malloc(
		size + ALIGNED_BYTES); // Using char to move the pointer by bytes
	// also to store the offset in the byte before the aligned pointer

	if (!original_ptr) {
		return NULL; // Allocation failed
	}

	unsigned char offset =
		ALIGNED_BYTES - ((uintptr_t)(original_ptr) % ALIGNED_BYTES);

	unsigned char *aligned_ptr =
		original_ptr + offset; // increse by offset*sizeof(char)

	*(aligned_ptr - 1) =
		offset; // Store the offset in the byte before the aligned pointer

	// can also be done with
	aligned_ptr[-1] = offset;

	return (void *)aligned_ptr;
}

void myfree(void *ptr) {
	if (ptr != NULL) { // Check if the pointer is not NULL
		unsigned char *aligned_ptr =
			(unsigned char *)ptr; // Cast the void pointer to a char pointer
		unsigned char offset =
			aligned_ptr[-1]; // Retrieve the offset stored in the
							 // byte before the aligned pointer
		free((void *)((uintptr_t)aligned_ptr -
					  offset)); // Subtract the offset from the aligned pointer
								// to get the original pointer, cast it to
								// void*, and free it
	}
}

void test_mymalloc(void *(*alloc_func)(size_t), void (*free_func)(void *)) {

	char *arr[10];

	for (int i = 0; i < 10; i++) {
		int size = rand() % 1000 + 1;
		arr[i] = (char *)alloc_func(size * sizeof(char));
		for (int j = 0; j < size; j++) {
			arr[i][j] = 'a' + rand() % 26;
		}
		printf("| (void *)&arr[%d] = %p | alocating %3d bytes | arr[%d] = %p | "
			   "(uintptr_t)arr[%d] %% %d = %3lu |\n",
			   i, (void *)&arr[i], size, i, arr[i], i, ALIGNED_BYTES,
			   (uintptr_t)arr[i] % ALIGNED_BYTES);
	}

	for (int i = 0; i < 10; i++) {
		free_func(arr[i]);
	}
}

int main(void) {
	if (ALIGNED_BYTES > 0xFF) {
		printf("ALIGNED_BYTES cannot exceed %zu bytes\n", sizeof(char));
		return 1;
	}
	printf("Size of pointer is: %zu bytes\n", sizeof(void *));
	printf("Normal address allocation:\n");
	test_mymalloc(malloc, free);
	printf("\n\n");
	printf("Aligned address allocation:\n");
	test_mymalloc(mymalloc, myfree);
	return 0;
}
