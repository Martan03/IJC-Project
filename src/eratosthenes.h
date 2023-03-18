// eratosthenes.h
// Řešení IJC-DU1, příklad a), 14.03.2023
// Autor: Martin Slezák, FIT
// Přeloženo: gcc 10.2
// Deklarace funkce Eratosthenes pro nalezení prvočísel

#ifndef ERA_INCLUDED
#define ERA_INCLUDED

#include "bitset.h"
#include <math.h>

/// @brief Finds out first n prime numbers (n == arr size in bites - 8)
/// @param arr bitarray where index == number (0 == prime)
void Eratosthenes(bitset_t arr);

#endif
