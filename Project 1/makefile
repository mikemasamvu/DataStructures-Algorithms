CC = gcc
CFLAGS = -std=c17 -Wall -Werror -pedantic -g

all: Life

Life: main.o life.o helpers.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c life.h helpers.h
	$(CC) $(CFLAGS) -c $@ $<

life.o: life.c life.h
	$(CC) $(CFLAGS) -c $@ $<

helpers.o: helpers.c helpers.h
	$(CC) $(CFLAGS) -c $@ $<

clean:
	rm -rf Life *.o .dYSM
