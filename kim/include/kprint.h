/*
 * Author: Aurelio Colosimo, 2016
 *
 * This file is part of kim-os project: https://github.com/colosimo/kim-os
 * According to kim-os license, you can do whatever you want with it,
 * as long as you retain this notice.
 */

#ifndef _KPRINT_H_
#define _KPRINT_H_

extern int putchar(int c);

/* printf-like function */
void kprint(const char *fmt, ...) __attribute__((format(printf,1,2)));

/* sprintf-like function */
void k_sprintf(char * buf, const char *fmt, ...) \
    __attribute__((format(printf,2,3)));

#endif
