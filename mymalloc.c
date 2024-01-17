/* This program is a custom implementation of the malloc and free functions in
 * C. it returness aligned adress with offsent to 32.
 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void *mymalloc(size_t size) {
  uintptr_t original_ptr = (uintptr_t)malloc(size + 4*sizeof(int));
  if (!original_ptr) {
    return NULL; // Allocation failed
  }

  char offset = (((original_ptr&0x1f) + 0x1f) & ~0x1f) - (original_ptr&0x1f);
  if (offset == 0) {
    offset = 32;
  }

  char *aligned_ptr = (char *)(original_ptr + offset);
  printf("offset set to %d\n", offset);

  ((char *)aligned_ptr)[-1] = offset;

  return (void *)aligned_ptr;
}

void myfree(void *ptr) {
  if (ptr != NULL) {
    char *aligned_ptr = (char *)ptr;
    char offset = aligned_ptr[-1];
    free((void *)aligned_ptr - offset);
  }
}

int main(void) {
  printf("Normal address allocation:\n");
  char *arr[10];
  for (int i = 0; i < 10; i++) {
    int size = rand() % 100 + 1;
    printf("Allocating %d bytes\n", size);
    arr[i] = (char *)malloc(size * sizeof(char));
    printf("arr[%d] address in hexadecimal: %p\n", i, (void *)arr[i]);
    printf("arr[%d] address in decimal mod 32: %ld\n\n", i, (uintptr_t)arr[i] % 32);
  }

  printf("\n===================\nAligned address allocation:\n");
  char *m_arr[10];
  for (int i = 0; i < 10; i++) {
    int size = rand() % 100 + 1;
    printf("Allocating %d bytes\n", size);
    m_arr[i] = (char *)mymalloc(size * sizeof(char));
    printf("arr[%d] address in hexadecimal: %p\n", i, (void *)m_arr[i]);
    printf("arr[%d] address in decimal mod 32: %ld\n\n", i, (uintptr_t)m_arr[i] % 32);
  }

  for (int i = 0; i < 10; i++) {
    myfree(m_arr[i]);
    free(arr[i]);
  }

  return 0;
}