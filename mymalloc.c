/* This program is a custom implementation of the malloc and free functions in
 * C. it returness aligned adress with offsent to 32.
 */

#include <stdio.h>
#include <stdlib.h>

void *mymalloc(unsigned int size) {
  // Allocate extra memory for alignment and storing the offset
  char *p = (char *)malloc(size + 2); // Allocate extra space for alignment

  if (p == NULL) {
    return NULL;
  }

  // Calculate the offset
  unsigned int offset = (32 - ((unsigned long)p % 32)) % 32;

  char *ret = p + offset;

  // Store the offset just before the aligned address
  ret[-1] = offset;

  return (void *)(ret);
}

void myfree(void *ptr) {
  // Retrieve the offset and calculate the original pointer
  unsigned char *aligned = (unsigned char *)ptr;
  unsigned char offset = *(aligned - 1);
  free(*(aligned - offset));
}

int main(void) {
  int **ptr = (int **)mymalloc(sizeof(int *) * 5);
  for (int i = 0; i < 5; i++) {
    ptr[i] = (char *)mymalloc(sizeof(char));
    printf("ptr[%d]: %p\n", i, ptr[i]);
    myfree(ptr[i]);
  }
  printf("ptr: %p\n", ptr);

  return 0;
}