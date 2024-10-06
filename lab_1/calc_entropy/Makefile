CC=gcc
CFLAGS=

.PHONY: all clean

all: calc_entropy

calc_entropy: main.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f calc_entropy