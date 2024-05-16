CC = gcc
CFLAGS = -std=c17 -Wall -Werror -pedantic -g

HookBook: hookbook.c pirate.c pirate_list.c pirate_list.h pirate.h
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf HookBook *.o .dYSM

