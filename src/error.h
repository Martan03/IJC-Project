// error.h
// Řešení IJC-DU1, příklad b), 14.03.2023
// Autor: Martin Slezák, FIT
// Přeloženo: clang 14.0.0-1ubuntu1
// Deklarace funkcí warning a error

#ifndef ERROR_INCLUDED
#define ERROR_INCLUDED

#include <stdio.h>
#include <stdarg.h>

/// @brief Prints warning message (params like printf)
/// @param fmt message string
/// @param variables to be inserted to string
void warning(const char *fmt, ...);

/// @brief Prints error message (params like printf) and exits program
/// @param fmt message string
/// @param variables to be inserted to string
void error_exit(const char *fmt, ...);

#endif
