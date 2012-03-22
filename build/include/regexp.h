/*
 * libregexp 1.0 - wrapper functions for regexp.h-functions
 *
 * Copyright 2012 by beroNet GmbH
 * Author: Florian Kraatz <fk@beronet.com>
 *
 * If you encounter problems with this software, please contact us
 * via mail:
 *
 *  support@beronet.com
 *
 */

#ifndef _LIB_REGEXP_H
#define _LIB_REGEXP_H 1

#include <regex.h>

char *re_ptr (const char *str, const char *pat, const unsigned int flags, unsigned int *start, unsigned int *end);
char *re_newstr (const char *str, const char *pat, const unsigned int flags);

#endif /* _LIB_REGEXP_H */
