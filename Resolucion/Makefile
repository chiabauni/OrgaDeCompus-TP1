CFLAGS=-Wall -g

all: main
	:

main: main.c max_divisor.c gcd.S
	$(CC) $(CFLAGS) -o main main.c max_divisor.c gcd.S

test: main
	./main

clean:
	rm -f main
