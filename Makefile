CC:=clang
CFLAGS:=-g -Wall -Wextra -std=c11 -pedantic -fsanitize=address -O2
dir:=$(shell mkdir -p obj)

.PHONY: clean
.PHONY: run
.PHONY: default

default: primes primes-i steg-decode

run: primes primes-i
	ulimit -s 30000 ; ./primes
	ulimit -s 30000 ; ./primes-i

primes: obj/primes.o obj/eratosthenes.o obj/error.o
	$(CC) $(CFLAGS) -lm $^ -o $@

primes-i: obj/primes-i.o obj/eratosthenes-i.o obj/error.o
	$(CC) $(CFLAGS) -lm $^ -o $@

steg-decode: obj/steg-decode.o obj/ppm.o obj/error.o obj/eratosthenes.o
	$(CC) $(CFLAGS) -lm $^ -o $@

obj/primes.o: src/primes.c src/eratosthenes.h src/bitset.h src/error.h
obj/eratosthenes.o: src/eratosthenes.c src/eratosthenes.h src/bitset.h src/error.h
obj/error.o: src/error.c src/error.h
obj/steg-decode.o: src/steg-decode.c src/ppm.h src/error.h src/bitset.h src/eratosthenes.h
obj/ppm.o: src/ppm.c src/ppm.h src/error.h

obj/%-i.o: src/%.c src/eratosthenes.h src/bitset.h src/error.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c $< -o $@

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r obj
