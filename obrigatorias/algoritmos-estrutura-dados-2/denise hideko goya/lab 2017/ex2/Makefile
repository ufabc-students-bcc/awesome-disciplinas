CC=gcc
CFLAGS=-O3 -Wall

test: testBTree
	./testBTree

testBTree: bTree.o testBTree.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) testBTree *.o
