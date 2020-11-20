CC = gcc
CFLAGS = -Wall -pedantic -std=gnu99
LINKS = -lm
.PHONY = clean all
.DEFAULT_OPTION = all 

all: main

main.o: main.c main.h
	$(CC) $(CFLAGS) main.c -c

account.o: account.c
	$(CC) $(CFLAGS) account.c -c


main: main.o account.o
	$(CC) $(CFLAGS) main.o account.o -o runSim $(LINKS)

clean:
	rm runSim *.o 
