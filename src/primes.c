// primes.c
// Řešení IJC-DU1, příklad a), 14.03.2023
// Autor: Martin Slezák, FIT
// Přeloženo: clang 14.0.0-1ubuntu1
// Vypsání posledních 10 prvočísel z 230 milionů

#include <stdio.h>
#include <time.h>
#include "eratosthenes.h"
#include "error.h"
#include "bitset.h"

/// @brief gets 230mil prime numbers and print last 100
void get_primes();

int main()
{
    clock_t start = clock();
    get_primes();
    fprintf(stderr, "Time=%.3g\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    return 0;
}

void get_primes()
{
    bitset_alloc(primes, 230000000);
    Eratosthenes(primes);

    bitset_index_t k = bitset_size(primes);
    for (int i = 0; i < 10 && k >= 0; --k)
        if (!bitset_getbit(primes, k))
            ++i;

    for (bitset_index_t i = k; i < bitset_size(primes); ++i)
        if (!bitset_getbit(primes, i))
            printf("%lu\n", i);
            
    bitset_free(primes);
}
