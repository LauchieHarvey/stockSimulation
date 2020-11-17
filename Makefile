CC = gcc
CFLAGS = -Wall -pedantic -std=gnu99
LINKS = -lm
.PHONY = clean all
.DEFAULT_OPTION = all 

all: mcSim 

mcSim.o: mcSim.c mcSim.h
	$(CC) $(CFLAGS) mcSim.c -c

mcSim: mcSim.o
	$(CC) $(CFLAGS) mcSim.o -o runSim $(LINKS)

clean:
	rm runSim *.o 
