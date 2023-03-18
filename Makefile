CC:=clang
OUT:=main
CFLAGS:=-g -Wall -std=c17 -lm -fsanitize=address
RFLAGS:=-std=c11 -lm -DNDEBUG -O2
CFILES:=$(wildcard src/*.c)
HFILES:=$(wildcard src/*.h)
OBJS:=$(patsubst src/%.c, obj/%.o, $(CFILES))

primes:
	clang $(CFLAGS) -o primes src/primes.c src/eratosthenes.c src/error.c

debug: $(OBJS)
	$(CC) $(CFLAGS) -o bin/debug/$(OUT) $(OBJS)

release: $(CFILES)
	$(CC) $(RFLAGS) -o bin/release/$(OUT) $(CFILES)

$(OBJS): $(CFILES)
	$(CC) $(CFLAGS) -c $(patsubst obj/%.o, src/%.c, $@) -o $@

clean:
	rm $(OBJS)
