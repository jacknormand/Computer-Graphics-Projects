CC= gcc
CFLAGS= -Wall
RM= rm -f

all: v3tester

v3tester: v3math.c v3test.c
	$(CC) $(CFLAGS) v3math.c v3test.c -o v3tester

clean:
	$(RM) v3tester *~