// steg-decode.c
// Řešení IJC-DU1, příklad b), 14.03.2023
// Autor: Martin Slezák, FIT
// Přeloženo: gcc 10.2
// ...

#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"
#include "bitset.h"
#include "eratosthenes.h"
#include "error.h"

#define START_PRIME 101

typedef struct
{
    unsigned char *str;
    int len, actLen;
} msg_t;

unsigned char *utf8_check(unsigned char *s)
{
  while (*s) {
    if (*s < 0x80)
      /* 0xxxxxxx */
      s++;
    else if ((s[0] & 0xe0) == 0xc0) {
      /* 110XXXXx 10xxxxxx */
      if ((s[1] & 0xc0) != 0x80 ||
	  (s[0] & 0xfe) == 0xc0)                        /* overlong? */
	return s;
      else
	s += 2;
    } else if ((s[0] & 0xf0) == 0xe0) {
      /* 1110XXXX 10Xxxxxx 10xxxxxx */
      if ((s[1] & 0xc0) != 0x80 ||
	  (s[2] & 0xc0) != 0x80 ||
	  (s[0] == 0xe0 && (s[1] & 0xe0) == 0x80) ||    /* overlong? */
	  (s[0] == 0xed && (s[1] & 0xe0) == 0xa0) ||    /* surrogate? */
	  (s[0] == 0xef && s[1] == 0xbf &&
	   (s[2] & 0xfe) == 0xbe))                      /* U+FFFE or U+FFFF? */
	return s;
      else
	s += 3;
    } else if ((s[0] & 0xf8) == 0xf0) {
      /* 11110XXX 10XXxxxx 10xxxxxx 10xxxxxx */
      if ((s[1] & 0xc0) != 0x80 ||
	  (s[2] & 0xc0) != 0x80 ||
	  (s[3] & 0xc0) != 0x80 ||
	  (s[0] == 0xf0 && (s[1] & 0xf0) == 0x80) ||    /* overlong? */
	  (s[0] == 0xf4 && s[1] > 0x8f) || s[0] > 0xf4) /* > U+10FFFF? */
	return s;
      else
	s += 4;
    } else
      return s;
  }

  return NULL;
}

/// @brief Adds character to message, reallocates if string too small
/// @param msg msg_t struct
/// @param c character to be added
void add_char(msg_t *msg, char c);

int main(int argc, char **argv)
{
    if (argc != 2)
        error_exit("steg-decode: invalid usage");

    struct ppm* p = ppm_read(argv[1]);

    bitset_alloc(primes, 3 * p->xsize * p->ysize);
    Eratosthenes(primes);

    unsigned char c = 0;
    unsigned bcount = 0;
    msg_t msg = { .len = 0, .actLen = 16, .str = malloc(16) };
    if (!msg.str)
    {
        bitset_free(primes);
        ppm_free(p);
        error_exit("steg-decode: error allocating memory");
    }

    for (bitset_index_t i = START_PRIME; i < 3 * p->xsize * p->ysize; ++i)
    {
        if (bitset_getbit(primes, i))
            continue;

        c |= (p->data[i] & 1) << (bcount++ % 8);

        if (bcount % 8)
            continue;

        if (c == '\0')
            break;

        add_char(&msg, c);
        c = 0;
    }
    add_char(&msg, '\0');

    bitset_free(primes);
    ppm_free(p);

    if (utf8_check(msg.str))
    {
        free(msg.str);
        error_exit("steg-decode: message is not in UTF-8 format\n");
    }
    printf("%s\n", msg.str);
    
    return 0;
}

void add_char(msg_t *msg, char c)
{
    if (msg->len + 1 >= msg->actLen)
    {
        msg->actLen *= 2;
        msg->str = realloc(msg->str, msg->actLen);

        if (msg->str == NULL)
        {
            free(msg->str);
            error_exit("steg-decode: allocating memory\n");
        }
    }

    msg->str[msg->len++] = c;
}
