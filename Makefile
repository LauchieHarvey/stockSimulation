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

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) stack.c -c


main: main.o account.o stack.o
	$(CC) $(CFLAGS) main.o account.o stack.o -o runSim $(LINKS)

clean:
	rm runSim *.o 
