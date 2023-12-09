CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O2

all: bitwise count_bits

bitwise: bitwise.o
	$(CC) -o bitwise bitwise.o

bitwise.o: bitwise.c
	$(CC) $(CFLAGS) -c bitwise.c

count_bits: count_bits.o
	$(CC) -o count_bits count_bits.o

count_bits.o: count_bits.c
	$(CC) $(CFLAGS) -c count_bits.c

.PHONY: clean all
clean:
	rm -f *.o count_bits bitwise