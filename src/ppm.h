// ppm.h
// Řešení IJC-DU1, příklad b), 14.03.2023
// Autor: Martin Slezák, FIT
// Přeloženo: gcc 10.2
// ...

#ifndef PPM_INCLUDED
#define PPM_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "error.h"
/*
Implement only binary variant of PPM P6
Colors 0..255 and without comments
*/

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bytes, 3 * xsize * ysize in total
};

/// @brief Reads date from given PPM file to the PPM struct
/// @param filename name of the PPM file
/// @return PPM struct with read data
struct ppm* ppm_read(const char* filename);

/// @brief Frees given PPM struct
/// @param p PPM struct
void ppm_free(struct ppm* p);

#endif
