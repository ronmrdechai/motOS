/*
 * A set of macros for quoting and concatenating.
 */
#ifndef _QUOTE_H
#define _QUOTE_H
#define _QUOTE(str) #str
#define  QUOTE(str) _QUOTE(str)
#define _CONCAT(str1, str2) str1##str2
#define  CONCAT(str1, str2) _CONCAT(str1, str2)
#endif /* ! defined(_QUOTE_H) */

