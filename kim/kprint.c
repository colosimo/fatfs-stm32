/*
 * Author: Aurelio Colosimo, 2016
 *
 * This file is part of kim-os project: https://github.com/colosimo/kim-os
 * According to kim-os license, you can do whatever you want with it,
 * as long as you retain this notice.
 */

#include <stdarg.h>
#include <endiannes.h>
#include <basic.h>

extern int putchar(int c);

const char hex[] = "0123456789abcdef";

static void printhex(int x, int ndigits, int (*_putchar)(int))
{
	unsigned char *p;
	int i;
	int c;
	int started = 0;

	if (cpu_be)
		p = (unsigned char *)&x;
	else
		p = &((unsigned char *)&x)[3];

	for (i = 0; i < sizeof(x); i++) {

		if (*p != 0 || (ndigits && i >= sizeof(x) - ndigits / 2) ||
		    i == sizeof(x) - 1) {
			started = 1;
		}

		if (started) {
			c = hex[*p >> 4];
			_putchar(c);
			c = hex[*p & 0xf];
			_putchar(c);
		}

		if (cpu_be)
			p++;
		else
			p--;
	}
}

static void printint(int x, int sgnd, int (*_putchar)(int))
{
	int div = 1000000000;
	int started = 0;
	if (x == 0) {
		_putchar('0');
		return;
	}
	if (sgnd && x < 0) {
		_putchar('-');
		x = -x;
	}
	while (div > 0) {
		if (x / div || started) {
			started = 1;
			_putchar('0' + (x / div));
		}
		x = x % div;
		div /= 10;
	}
}

/* Minimal printf function. Supports strings, chars and hex numbers. */
void kprint(const char *fmt, ...)
{
	va_list args;
	char *s;
	va_start(args, fmt);
	int ndigits = 0;
	int fmt_prefix = 0;

	for (; *fmt; fmt++) {

		if (*fmt == '%' && !fmt_prefix) {
			fmt_prefix = 1;
			continue;
		}

		if (!fmt_prefix) {
			putchar(*fmt);
			continue;
		}

		fmt_prefix = 0;

		switch (*fmt) {
		case '%':
			putchar('%');
			break;
		case 'c':
			putchar(va_arg(args, int));
			break;
		case 's':
			while (ndigits--)
				putchar(' ');
			s = va_arg(args, char *);
			while (*s)
				putchar(*s++);
			ndigits = 0;
			break;

		case 'p':
			putchar('0');
			putchar('x');
			printhex(va_arg(args, int), ndigits, putchar);
			break;
		case 'u':
			printint(va_arg(args, unsigned int), 0, putchar);
			break;
		case 'd':
			printint(va_arg(args, int), 1, putchar);
			break;
		case 'x':
			printhex(va_arg(args, int), ndigits, putchar);
			ndigits = 0;
			break;

		default:
			if (isdigit(*fmt)) {
				fmt_prefix = 1;
				ndigits = ndigits * 10 + *fmt - '0';
			}
			break;
		}
	}

	va_end(args);
}


static char *tmpbuf;
static int cnt;

int buf_putchar(int c)
{
	tmpbuf[cnt++] = c;
	return 0;
}

#ifndef BOOTLOADER
/* Minimal sprintf function. Supports strings, chars and hex numbers. */
void k_sprintf(char *buf, const char *fmt, ...)
{
	va_list args;
	char *s;
	va_start(args, fmt);
	int ndigits = 0;
	int fmt_prefix = 0;

	cnt = 0;
	tmpbuf = buf;

	for (; *fmt; fmt++) {

		if (*fmt == '%' && !fmt_prefix) {
			fmt_prefix = 1;
			continue;
		}

		if (!fmt_prefix) {
			buf_putchar(*fmt);
			continue;
		}

		fmt_prefix = 0;

		switch (*fmt) {
		case '%':
			buf_putchar('%');
			break;
		case 'c':
			buf_putchar(va_arg(args, int));
			break;
		case 's':
			while (ndigits--)
				buf_putchar(' ');
			s = va_arg(args, char *);
			while (*s)
				buf_putchar(*s++);
			ndigits = 0;
			break;

		case 'p':
			buf_putchar('0');
			buf_putchar('x');
			printhex(va_arg(args, int), ndigits, buf_putchar);
			break;
		case 'u':
			printint(va_arg(args, unsigned int), 0, buf_putchar);
			break;
		case 'd':
			printint(va_arg(args, int), 1, buf_putchar);
			break;
		case 'x':
		case 'X':
			printhex(va_arg(args, int), ndigits, buf_putchar);
			ndigits = 0;
			break;

		default:
			if (isdigit(*fmt)) {
				fmt_prefix = 1;
				ndigits = ndigits * 10 + *fmt - '0';
			}
			break;
		}
	}

	va_end(args);

	buf_putchar('\0');
}

#endif
