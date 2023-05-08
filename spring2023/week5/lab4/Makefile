CC := gcc
CFLAGS := -g -Wall -std=c99
TARGETS := linkedlist-main

all: $(TARGETS)

linkedlist-main: linkedlist-main.c linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o $(TARGETS)
