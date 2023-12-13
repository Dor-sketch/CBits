#include "types.h"
#include "user.h"

void pingpong(int max_count) {
  ushort bit = '0';
  int count = 0;

  while (count < max_count) {
    write(1, &bit, 1); // Write to STDOUT
    read(0, &bit, 1);  // Read from STDIN
    bit ^= 1;          // Toggle the bit
    count++;
  }
}

int main(void) {
  int p1[2], p2[2];
  int max_count = 10000;

  if (pipe(p1) < 0 || pipe(p2) < 0) {
    printf(2, "Pipe creation failed\n");
    exit();
  }

  int pid = fork();
  if (pid < 0) {
    printf(2, "Fork failed\n");
    exit();
  }

  if (pid == 0) { // Child process
    close(0);     // Close STDIN
    dup(p1[0]);   // Duplicate read end of pipe p1 to STDIN
    close(1);     // Close STDOUT
    dup(p2[1]);   // Duplicate write end of pipe p2 to STDOUT
    close(p1[0]);
    close(p2[1]);
    close(p1[1]);
    close(p2[0]);
    pingpong(max_count);
    exit();
  } else {                     // Parent process
    close(0);                  // Close STDIN
    dup(p2[0]);                // Duplicate read end of pipe p2 to STDIN
    int saved_stdout = dup(1); // save the original STDOUT
    close(1);                  // Close STDOUT
    dup(p1[1]);                // Duplicate write end of pipe p1 to STDOUT
    close(p1[0]);
    close(p2[1]);
    close(p1[1]);
    close(p2[0]);
    int start_time = uptime();
    pingpong(max_count);
    int total_time = uptime() - start_time;

    close(1);
    dup(saved_stdout); // resotore STDOUT
    printf(1, "Total exchanges: %d\n", max_count);
    printf(1, "Total time: %d ticks\n", total_time);
    if (total_time > 0) {
      printf(1, "Exchanges per second: %d\n", max_count / total_time);
    } else {
      printf(1, "Total time too short for accurate measurement\n");
    }
    close(saved_stdout); // Close the saved file descriptor

    wait();
    exit();
  }
}
