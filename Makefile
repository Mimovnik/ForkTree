CC=gcc
CFLAGS=-Wall -g

all:
	mkdir -p build
	$(CC) $(CFLAGS) -o build/main main.c

clean:
	rm build/main

run:
	./build/main

