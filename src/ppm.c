// ppm.c
// Řešení IJC-DU1, příklad b), 14.03.2023
// Autor: Martin Slezák, FIT
// Přeloženo: gcc 10.2
// ...

#include "ppm.h"

struct ppm* ppm_read(const char* filename)
{
    FILE *f = fopen(filename, "rb");
    if (!f)
        error_exit("ppm_read: file doesn't exist or can't be accessed");
    
    char type[3];
    fscanf(f, "%2s", type);
    type[2] = '\0';

    if (strcmp(type, "P6"))
        error_exit("ppm_read: file is not P6 type");

    int width, height, max;
    fscanf(f, "%d %d %d", &width, &height, &max);

    if (max <= 0 || max >= 65536)
        error_exit("ppm_read: invalid maximum color value in given file");

    struct ppm* p = malloc(sizeof(unsigned) * 2 + 3 * width * height);
    if (!p)
        error_exit("ppm_read: error allocating memory");

    p->xsize = width;
    p->ysize = height;

    fseek(f, 1, SEEK_CUR);

    char c = '\0';
    for (int i = 0; i < 3 * width * height && fscanf(f, "%c", &c) != 0; ++i)
        p->data[i] = c;

    fclose(f);
    return p;
}

void ppm_free(struct ppm* p)
{
    free(p);
    p = NULL;
}
