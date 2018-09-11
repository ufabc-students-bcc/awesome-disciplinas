CC=gcc
CFLAGS=-O3 -Wall

test: hash
	./hash

hash: hash.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) hash *.o
