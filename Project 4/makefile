CC = gcc
CFLAGS = -std=c17 -Wall -Werror -pedantic -g

Blotto: blotto.c entry.c libblotto.c gmap.c gmap.h libblotto.h entry.h
	$(CC) $(CFLAGS) -o $@ $^

GmapUnit: gmap_unit.c entry.c gmap.c gmap_test_functions.c string_key.c entry.h gmap_test_functions.h gmap.h string_key.h
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf Blotto *.o .dYSM