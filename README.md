# 🔢 Embedded C Concepts

This repository contains a diverse collection of C functions, focusing on bit manipulation, memory manipulation, and a special feature on inter-process communication (IPC) using UNIX pipes in the xv6 environment.

<p align="center">
  <img src="./images/bits_cover.png" width="400">
</p>

---

- [💾 Failed Interview Self-Study: Custom malloc \& free Implementation](#-failed-interview-self-study-custom-malloc--free-implementation)
  - [Overview](#overview)
  - [Key Takeaways](#key-takeaways)
- [🏓 PingPong Program](#-pingpong-program)
  - [Overview](#overview-1)
  - [Features](#features)
  - [How It Works](#how-it-works)
  - [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Compilation and Execution](#compilation-and-execution)
  - [Output](#output)
- [🔒 Multi-threaded Counter with POSIX Threads](#-multi-threaded-counter-with-posix-threads)
  - [Overview](#overview-2)
  - [Features](#features-1)
  - [How It Works](#how-it-works-1)
  - [Getting Started](#getting-started-1)
  - [Output](#output-1)
  - [Note](#note)
- [👾 Bitwise Example Program](#-bitwise-example-program)
- [🧮 Count Bits Program](#-count-bits-program)
  - [How to Use](#how-to-use)
  - [Examples](#examples)
- [License](#license)

---

## 💾 Failed Interview Self-Study: Custom malloc & free Implementation

### Overview

The [mymalloc.c](mymalloc.c) program is a result of my self-study following a failed interview question. It includes a custom implementation of the `malloc` and `free` functions in C, encapsulated within `mymalloc` and `myfree` wrapper functions. These functions are uniquely designed to allocate and free memory addresses aligned to specific hexadecimal increments (0x20, 0x40, 0x60, 0x80, 0xA0, 0xC0, 0xE0, 0x00).

The offset from the original to the aligned address is stored in the byte immediately preceding the address returned by `mymalloc`.

This project was an insightful journey into pointers and memory allocation in C, spurred by my experience in an interview setting.

![Alt text](image-1.png)

---

### Key Takeaways

1. **Pointer Arithmetic and Type Size Awareness:**

    - Adding 1 to a pointer increases the address by the size of the type it points to. For instance, adding 1 to a `char *` (1 byte) increments the address by 1 byte. Conversely, adding 1 to an `unsigned long long *` (8 bytes) increments it by 8 bytes. My initial attempts inadvertently added 32 * sizeof(unsigned long long) (256 bytes), instead of the intended 32 bytes for the custom alignment (0x20).

2. **Subtracting from Pointers:**

    - Similarly, subtracting 1 from a pointer decrements the address by the size of the type it points to. My initial approach subtracted 1 from larger types, like `unsigned long long *`, which decremented the address by 8 bytes, instead of the intended 1 byte. The correct approach is to use a `char *`, which decrements the address by 1 byte.

3. **Using the Modulus Operator with Pointers:**

    - The modulus operator `%` is applicable only to integer types. To use it with pointers, explicit casting to an appropriate integer type is necessary, as pointers are not inherently integer types. Possible solution is also using the `uintptr_t` type, which is an unsigned integer type capable of storing a pointer.

4. **Casting when Working with Pointers:**

    - When returning a pointer from `mymalloc`, it should be cast to `(void *)` to match the return type of the standard `malloc` function. This ensures compatibility and proper use in various contexts. Similarly, casting is required when calling `malloc`, as it returns a `(void *)` pointer, which must be cast to the appropriate type.

5. **Malloc Allignments:**

    - The `malloc` function returns a pointer to a memory address thats already aligned. The implementation is actually using a header `union` and inside it a `struct`.


![Alt text](image.png)

---

## 🏓 PingPong Program

### Overview

👨‍🏫 File [pingpong.c](pingpong.c) contains the PingPong program, a highlight of this repository, is an educational tool designed to demonstrate IPC using UNIX pipes in the xv6 environment. It allows two processes – a parent and a child – to communicate by "ping-ponging" a byte back and forth, providing a hands-on experience in process communication.

<p align="center">
  <img src="./images/cover.png" width="400">
</p>


### Features

- **IPC Demonstration**: Showcases pipes for process-to-process communication.
- **Performance Metrics**: Outputs the performance of IPC in terms of exchanges per second.
- **Educational Tool**: Perfect for teaching operating systems and process communication.

### How It Works

🔍 The program creates two processes using `fork()`. Each process:

1. Closes its standard input (STDIN) or standard output (STDOUT).

2. Redirects STDIN or STDOUT to the ends of the pipes.

3. Executes write and read operations to exchange a byte.

4. Toggles the byte value at each exchange using XOR.

### Getting Started

### Prerequisites

- xv6 Operating System environment.

- C compiler (like `gcc`) for xv6.

### Compilation and Execution

Compile the program by adding [pingpong.c](pingpong.c) to the xv6 source file, updating the Makefile, and then compiling xv6. Execute the program from userspace via the xv6 shell.

### Output

📈 The program outputs the total number of exchanges, total time in ticks, and exchanges per second.

![Alt text](./images/pingpong_output.png)

---

## 🔒 Multi-threaded Counter with POSIX Threads

### Overview

🔍 This section of the repository contains a multi-threaded counter program implemented in C using POSIX threads (`pthread`). The program demonstrates the basic use of threads to perform concurrent operations on a shared resource with proper synchronization using mutexes.

### Features

- **Multi-threaded Execution**: Utilizes two threads to perform concurrent increments on a shared counter.

- **Mutex Synchronization**: Demonstrates the use of `pthread_mutex_t` to ensure safe access to the shared counter and prevent race conditions.

- **Error Handling**: Includes basic error handling for mutex initialization.

### How It Works

🔍 Each thread in the program runs a loop of 10 million iterations, incrementing the shared counter in each iteration. A mutex lock is used to synchronize access to the counter, ensuring thread-safe modification.

### Getting Started

**Prerequisites:**

- A C compiler with support for POSIX threads (like `gcc`).

- POSIX-compliant operating system (Linux, UNIX, macOS).

**Compilation:**

To compile the program, navigate to the directory containing `counter.c` and run:

```bash
gcc -o counter counter.c -lpthread
```

Execution

Execute the compiled program using:

```bash
./counter
```

### Output

📈 The program will output the start and end values of the counter, demonstrating the correct and synchronized incrementation by both threads:

![Alt text](./images/counter_output.png)

### Note

This program is designed as an educational tool to understand the basics of multi-threading and synchronization in C. It's well-suited for learning purposes and can be modified for more advanced multi-threading concepts.

---

## 👾 Bitwise Example Program

![Alt text](./images/image.png)

File [bitwise.c](bitwise.c) includes simple bitwise operations in C:

- **Bits Union**: Represents a float in binary according to IEEE 754.

- **XORing**: Swaps numbers using XOR.

- **Bit Shifting**: Shifts a number left and right by 1 bit.

- **Bit Masking**: Applies a mask to a number.

- **Bit Toggling**: Toggles a specific bit in a number.

- **Bit Setting**: Sets a specific bit in a number.

---

## 🧮 Count Bits Program

<p align="center">
  <img src="./images/bits_cover.png" width="400">
</p>

File [count_bits.c](count_bits.c) offers functions for counting bits:

- **printRecursiveBits**: Recursively prints binary representation of an integer.

- **printIntBits**: Prints the bits of an int iteratively.

- **printBits**: Prints binary representation of any data type.

- **count_bits**: Counts the number of 1's in a number.

- **getSizeInBits**: Returns the size of a data type in bits.

- **count_odd_bits**: Counts the number of 1 bits in odd positions.

---

### How to Use

1. Clone the repository.

2. Navigate to the desired function's directory.

3. Compile using the included Makefile.

4. Run the executable and follow the prompts.

### Examples

[count_bits example](examples_count_bits.png)

![Alt text](./images/examples_count_bits.png)

[count_odd_bits example](examples_odd_bits.png)

![Alt text](./images/examples_odd_bits.png)

---

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
