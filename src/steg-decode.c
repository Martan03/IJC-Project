// steg-decode.c
// Řešení IJC-DU1, příklad b), 14.03.2023
// Autor: Martin Slezák, FIT
// Přeloženo: gcc 10.2
// ...

#include <stdio.h>
#include "ppm.h"
#include "bitset.h"
#include "eratosthenes.h"
#include "error.h"

#define START_PRIME 101

int main(int argc, char **argv)
{
    if (argc != 2)
        error_exit("steg-decode: invalid usage");

    struct ppm* p = ppm_read(argv[1]);

    bitset_alloc(primes, 3 * p->xsize * p->ysize);
    Eratosthenes(primes);

    unsigned char c = 0;
    unsigned val, bcount = 0;

    for (bitset_index_t i = START_PRIME; i < 3 * p->xsize * p->ysize; ++i)
    {
        if (bitset_getbit(primes, i))
            continue;

        val = p->data[i] & 1;
        if (val)
            c |= 1 << (bcount++ % 8);
        else
            c &= ~(1 << (bcount++ % 8));

        if (bcount % 8)
            continue;

        if (c == '\0')
            break;

        printf("%c", c);
        c = 0;
    }
    printf("\n");

    bitset_free(primes);
    ppm_free(p);
    
    return 0;
}