CC= gcc
CFLAGS= -Wall -lm
RM= rm -f

all: raycast

raycast: v3math.c ray.c
	$(CC) $(CFLAGS) v3math.c ray.c -o raycast

clean:
	$(RM) raycast *~