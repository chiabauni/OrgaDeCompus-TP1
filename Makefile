CFLAGS=-Wall -g

all: regressions
	:

regressions: regressions.c gcd.c gcd.S
	$(CC) $(CFLAGS) -o regressions regressions.c gcd.c gcd.S

test: regressions
	./regressions

clean:
	rm -f regressions
