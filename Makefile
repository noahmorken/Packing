CC=gcc
CFLAGS=-O3 -std=c99 -Wall -Wshadow -Wvla -pedantic
DEPS=packing.h
OBJ=pa3.o packing.o

%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

pa3: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core
