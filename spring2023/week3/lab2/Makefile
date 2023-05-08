# variables to make changes easier
CC=gcc
CFLAGS=-g -Wall -std=c99
TARGETS=ex-factorial catalan

all: $(TARGETS)

ex-factorial: ex-factorial.c
	$(CC) $(CFLAGS) -o ex-factorial ex-factorial.c

catalan: catalan.c
	$(CC) $(CFLAGS) -o catalan catalan.c

clean:
	rm -rf *.o *~ $(TARGETS) a.out

sub:
	@zip "$${PWD##*/}" *.c *.h Makefile
