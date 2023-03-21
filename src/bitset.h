// bitset.h
// Řešení IJC-DU1, příklad a), 14.03.2023
// Autor: Martin Slezák, FIT
// Přeloženo: clang 14.0.0-1ubuntu1
// Definování zadaných funkcí a maker pro práci s bitovým polem

#ifndef BITSET_INCLUDED
#define BITSET_INCLUDED

#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdlib.h>

#include "error.h"

typedef unsigned long* bitset_t;
typedef unsigned long bitset_index_t;

/// @brief returns size of bitset_index_t in bits
#define BITSET_SIZE (CHAR_BIT * sizeof(bitset_index_t))

/// @brief Defines and zeroes out given array
/// @param name name of the array to be defined
/// @param size size of the array
#define bitset_create(name, size) \
    bitset_index_t name[size / BITSET_SIZE + 2] = {size, 0}

/// @brief Dynamically allocates array with given name
/// @param name name of the array to be allocated
/// @param size size of the array
#define bitset_alloc(name, size) \
    bitset_index_t len = size / BITSET_SIZE + 2; \
    bitset_t name = calloc(len, sizeof(bitset_index_t)); \
    if (name == NULL) error_exit("bitset_alloc: Error while allocating\n"); \
    name[0] = size; \

/// @brief Frees given array
/// @param arr array to be freed
static inline void bitset_free(bitset_t arr)
{
    free(arr);
}

/// @brief Returns size of given array
/// @param arr array to find out it's size
/// @return size of given array
static inline bitset_index_t bitset_size(bitset_t arr)
{
    return arr[0];
}

/// @brief Sets bit on given index to given expression
/// @param arr array to set the bit in
/// @param index index of the bit to be set
/// @param exp expression to set the bit to (0 == 0 bit, else 1 bit)
static inline void bitset_setbit(bitset_t arr, bitset_index_t index, int exp)
{
    if (bitset_size(arr) < index || index < 0)
        error_exit(
            "bitset_setbit: Index %lu mimo rozsah 0..%lu\n",
            index, bitset_size(arr)
        );
    if (exp)
    {
        arr[index / BITSET_SIZE + 1] |= 1L << (index % BITSET_SIZE);
        return;
    }
    arr[index / BITSET_SIZE + 1] &= ~(1L << (index % BITSET_SIZE));
}

/// @brief Gets value of the bit on given index
/// @param arr array to get bit value from
/// @param index index of the bit to get the value
/// @return value of the bit (true/false)
static inline _Bool bitset_getbit(bitset_t arr, bitset_index_t index)
{
    if (bitset_size(arr) < index || index < 0)
        error_exit(
            "bitset_getbit: Index %lu mimo rozsah 0..%lu\n",
            index, bitset_size(arr)
        );
    bitset_index_t k = index % BITSET_SIZE;
    return (arr[index / BITSET_SIZE + 1] & (1L << k));
}

#ifndef USE_INLINE

/// @brief Frees given array
/// @param arr array to be freed
#define bitset_free(arr) free(arr)

/// @brief Returns size of given array
/// @param arr array to find out it's size
/// @return size of given array
#define bitset_size(arr) arr[0]

/// @brief Sets bit on given index to given expression
/// @param arr array to set the bit in
/// @param index index of the bit to be set
/// @param exp expression to set the bit to (0 == 0 bit, else 1 bit)
#define bitset_setbit(arr, index, exp) do {\
    bitset_t barr = (arr); \
    bitset_index_t ind = (index); \
    if (bitset_size(barr) < ind || ind < 0) \
        error_exit( \
            "bitset_setbit: index %lu mimo rozsah 0..%lu\n", \
            ind, bitset_size(barr) \
        ); \
    if (exp) \
        barr[ind / BITSET_SIZE + 1] |= 1L << (ind % BITSET_SIZE); \
    else \
        barr[ind / BITSET_SIZE + 1] &= ~(1L << (ind % BITSET_SIZE)); \
} while (0);

/// @brief Gets value of the bit on given index
/// @param arr array to get bit value from
/// @param index index of the bit to get the value
/// @return value of the bit (true/false)
#define bitset_getbit(arr, index) bitset_getbit(arr, index)

#endif // USE_INLINE
#endif // BITSET_INCLUDED
