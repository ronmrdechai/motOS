#ifndef _PRINTF_H
#define _PRINTF_H

/* Define a __printf macro depending on the compiler */
#if defined(__GNUC__)
# define __printf __attribute__ ((format (printf, 1, 2)))
#elif defined(__clang__)
# define __printf __attribute__ ((__format__ (__printf__, 1, 2)))
#else
# define __printf
#endif

/* A subset of prinf for printing to the terminal.
 * Most of the basic formats are implemented, except for stuff dealing with
 * doubles and floats. Extra specifiers are also unimplemented.
 *
 * Stuff that works
 * - %d: a signed integer
 * - %i: a signed integer
 * - %u: an unsigned integer
 * - %x: a hexadecimal number, in lowercase
 * - %X: a hexadecimal number, in uppercase
 * - %c: a character
 * - %s: a string
 * - %n: nothing, the corresponding argument is set to the number of characters
 *       written so far.
 * - %%: the '%' character
 */
unsigned int kprintf(const char *fmt, ...) __printf;

#endif /* ! defined(_PRINTF_H) */
