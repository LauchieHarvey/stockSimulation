CC = gcc
CFLAGS = -Wall -pedantic -std=gnu99
.PHONY = clean
.DEFAULT_OPTION = all 

all: mcSim 

mcSim.o: mcSim.c
	$(CC) $(CFLAGS) mcSim.c -c 

mcSim: mcSim.o
	$(CC) $(CFLAGS) mcSim.o -o runSim 

clean:
	rm runSim *.o
