CC = gcc
CFLAGS = -DNDEBUG -O3 -Wall

.PHONY: all clean

all: test6

preem: test6.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f test6
