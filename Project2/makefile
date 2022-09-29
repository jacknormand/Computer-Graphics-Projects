CC=gcc
CFLAGS=-Wall
RM=rm -f

all: v3tester

v3tester: v3test.c v3math.o
	$(CC) $(CFLAGS) v3test.c v3math.o -o v3tester

v3math.o: v3math.c v3math.h
	$(CC) $(CFLAGS) v3math.c

clean:
	$(RM) v3tester *~