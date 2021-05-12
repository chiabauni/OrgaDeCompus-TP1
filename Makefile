CFLAGS=-Wall -g

all: regressions
	:

regressions: regressions.c gcd.c gcd.S
	$(CC) $(CFLAGS) -o regressions main.c max_divisor.c regressions.c gcd.c 

test: regressions
	./regressions

clean:
	rm -f regressions
