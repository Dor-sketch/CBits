#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int counter = 0;
pthread_mutex_t lock;

void *mythread(void *arg) {
  printf("%s: begin\n", (char *)arg);
  int i;
  for (i = 0; i < 1e7; i++) {
    pthread_mutex_lock(&lock); // Lock the mutex
    counter = counter + 1;
    pthread_mutex_unlock(&lock); // Unlock the mutex
  }
  printf("%s: done\n", (char *)arg);
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t p1, p2;

  // Initialize the mutex
  if (pthread_mutex_init(&lock, NULL) != 0) {
    printf("mutex init failed\n");
    return 1;
  }

  printf("main: begin (counter = %d)\n", counter);
  pthread_create(&p1, NULL, mythread, "A");
  pthread_create(&p2, NULL, mythread, "B");

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);

  printf("main: done with both (counter = %d)\n", counter);

  // Destroy the mutex
  pthread_mutex_destroy(&lock);

  return 0;
}
