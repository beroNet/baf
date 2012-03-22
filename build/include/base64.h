/*
 * libbase64 1.0 - encode or decode text to or from base64
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

#ifndef _LIB_BASE64_H
#define _LIB_BASE64_H 1

char *b64_encode (const char *str, const size_t str_len, size_t *ret_len);
char *b64_decode (const char *str, const size_t str_len, size_t *ret_len);

#endif /* _LIB_BASE64_H */
