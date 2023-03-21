// eratosthenes.c
// Řešení IJC-DU1, příklad a), 14.03.2023
// Autor: Martin Slezák, FIT
// Přeloženo: gcc 10.2
// Implementace funkce Eratosthenes pro nalezení prvočísel

#include "eratosthenes.h"

void Eratosthenes(bitset_t arr)
{
    bitset_index_t lim = sqrt(bitset_size(arr));
    bitset_setbit(arr, 0L, 1);
    bitset_setbit(arr, 1L, 1);

    // Setting even numbers as not a prime number
    for (bitset_index_t i = 4; i <= bitset_size(arr); i += 2)
        bitset_setbit(arr, i, 1);

    // Looping through odd numbers
    for (bitset_index_t i = 3; i <= lim; i += 2)
    {
        if (bitset_getbit(arr, i))
            continue;

        // If number is prime, set all its multiples as not prime
        for (bitset_index_t j = i * i; j <= bitset_size(arr); j += i + i)
            bitset_setbit(arr, j, 1);
    }
}
