/*
 * Author: Aurelio Colosimo, 2016
 *
 * This file is part of kim-os project: https://github.com/colosimo/kim-os
 * According to kim-os license, you can do whatever you want with it,
 * as long as you retain this notice.
 */

#ifndef _ENDIANNES_H_
#define _ENDIANNES_H_

/* Endiannes Configuration */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
static const int cpu_be = 1;
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
static const int cpu_be = 0;
#else
#error unsupported __BYTE_ORDER__
#endif

#endif /* _ENDIANNES_H_ */
