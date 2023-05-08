TARGETS=pi happy
CC=gcc
CFLAGS=-Wall -g

all : $(TARGETS)

$(TARGETS): %: %.c

clean: 
	@rm -f $(TARGETS) a.out *.o

sub:
	@zip $${PWD##*/}.zip $(SRCS) Makefile
