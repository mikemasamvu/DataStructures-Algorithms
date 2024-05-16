CC = gcc
CFLAGS = -std=c17 -Wall -Werror -pedantic -g

HookBook: hookbook.c pirate.c pirate_list.c skills_list.c libhookbook.c pirate.h pirate_list.h skills_list.h libhookbook.h
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf HookBook *.o .dYSM

