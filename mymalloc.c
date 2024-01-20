/* This program is a custom implementation of the malloc and free functions in
 * C. it returness aligned adress with offsent to 32.
 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct ThirtyTwoBytes {
	char data[32];
};

void *mymalloc(size_t size) {
	// get the original pointer + 32 bytes.
	unsigned char *original_ptr = (unsigned char *)malloc(
		size + 32); // Using unsigned char to move the pointer by bytes

	if (!original_ptr) {
		return NULL; // Allocation failed
	}

	unsigned char i = 0;
	for (i = 0; i < 31; i++) {
		if (!((uintptr_t)(&original_ptr[i]) % 32)) {
			break;
		}
	}

	if (i == 0) {
		i = 32;
	}

	char *aligned_ptr = original_ptr + i;

	// printf("offset set to %d\n bytes", i);

	*(aligned_ptr - 1) =
		i; // Store the offset in the byte before the aligned pointer

	return (void *)aligned_ptr;
}

void myfree(void *ptr) {
	if (ptr != NULL) {
		unsigned char *aligned_ptr = (unsigned char *)ptr;
		unsigned char offset = aligned_ptr[-1];
		free((void *)aligned_ptr - offset);
	}
}

void test_mymalloc(void *(*alloc_func)(size_t), void (*free_func)(void *)) {

	char *arr[10];

	for (int i = 0; i < 10; i++) {
		int size = rand() % 100 + 1;
		arr[i] = (char *)alloc_func(size * sizeof(char));
		printf("| (void *)&arr[%d] = %p | alocating %d bytes | arr[%d] = %p | "
			   "(uintptr_t)arr[%d] %% 32 = %2lu |\n",
			   i, (void *)&arr[i], size, i, arr[i], i, (uintptr_t)arr[i] % 32);
	}

	for (int i = 0; i < 10; i++) {
		free_func(arr[i]);
	}
}

int main(void) {
	printf("Size of pointer is: %zu bytes\n", sizeof(void *));
	printf("Normal address allocation:\n");
	test_mymalloc(malloc, free);
  printf("\n\n");
  printf("Aligned address allocation:\n");
	test_mymalloc(mymalloc, myfree);
	return 0;
}