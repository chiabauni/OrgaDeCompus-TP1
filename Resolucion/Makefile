CFLAGS=-Wall -g

all: main
	:

main: main.c max_divisor.c gcd.S
	$(CC) $(CFLAGS) -o main main.c max_divisor.c gcd.S

test: main
	./main -i tests/input_success.txt -o -
	./main -i tests/EOF_ultima_linea.txt -o -
	./main -i tests/linea_vacia.txt -o -

clean:
	rm -f main
