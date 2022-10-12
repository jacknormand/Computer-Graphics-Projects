CC= gcc
CFLAGS= -Wall -lm
RM= rm -f

all: raycaster

raycaster: ray.c
	$(CC) $(CFLAGS) ray.c -o raycaster

clean:
	$(RM) raycaster *~