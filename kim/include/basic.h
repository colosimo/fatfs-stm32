/*
 * Author: Aurelio Colosimo, 2016
 *
 * This file is part of kim-os project: https://github.com/colosimo/kim-os
 * According to kim-os license, you can do whatever you want with it,
 * as long as you retain this notice.
 */

#ifndef _BASIC_H_
#define _BASIC_H_

#include <intdefs.h>

/* Some useful macros */
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max3(a, b, c) max(max((a), (b)), (c))
#define min3(a, b, c) min(min((a), (b)), (c))
#define msb(x) (((x) >> 8) & 0xff)
#define lsb(x) ((x) & 0xff)

#define array_size(x) (sizeof((x)) / sizeof((x)[0]))

static inline u32 abs(i32 a)
{
	if (a >= 0)
		return a;
	else
		return -a;
}

/* Memory handling functions */
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *dest, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

/* String handling functions */
size_t strlen(const char *s1);
int strcmp(const char *s1, const char *s2);
int strncmp(char *s1, const char *s2, size_t n);
char *strcpy(char *s1, const char *s2);
char *strncpy(char *s1, const char *s2, size_t n);
int atoi(const char *p);
int atoi_hex(const char *p);

/* char check functions */
int isspace(int c);
int isdigit(int c);
int ishexdigit(int c);
int isalpha(int c);
int isalnum(int c);

/* Useful BITx definition, for bitmask computation */
#define BIT0 (1 << 0)
#define BIT1 (1 << 1)
#define BIT2 (1 << 2)
#define BIT3 (1 << 3)
#define BIT4 (1 << 4)
#define BIT5 (1 << 5)
#define BIT6 (1 << 6)
#define BIT7 (1 << 7)
#define BIT8 (1 << 8)
#define BIT9 (1 << 9)
#define BIT10 (1 << 10)
#define BIT11 (1 << 11)
#define BIT12 (1 << 12)
#define BIT13 (1 << 13)
#define BIT14 (1 << 14)
#define BIT15 ((u16)(1 << 15))
#define BIT16 (1 << 16)
#define BIT17 (1 << 17)
#define BIT18 (1 << 18)
#define BIT19 (1 << 19)
#define BIT20 (1 << 20)
#define BIT21 (1 << 21)
#define BIT22 (1 << 22)
#define BIT23 (1 << 23)
#define BIT24 (1 << 24)
#define BIT25 (1 << 25)
#define BIT26 (1 << 26)
#define BIT27 (1 << 27)
#define BIT28 (1 << 28)
#define BIT29 (1 << 29)
#define BIT30 (1 << 30)
#define BIT31 ((u32)(1 << 31))

/* Useful constants */
#define _K 1024
#define _M (1024 * 1024)

/* Hardware registers definition and manipulation */
#define reg8(x)  ((volatile uint8_t*)(x))
#define reg16(x) ((volatile uint16_t*)(x))
#define reg32(x) ((volatile uint32_t*)(x))

/* 32 bits registers */
static inline void wr32(volatile u32 *reg, u32 val) {*reg = val;}
static inline u32 rd32(volatile u32 *reg) {return *reg;}
static inline void or32(volatile u32 *reg, u32 val) {*reg |= val;}
static inline void and32(volatile u32 *reg, u32 val) {*reg &= val;}
static inline void clr32(volatile u32 *r, int nbit) {and32(r, ~(1 << nbit));}
static inline void set32(volatile u32 *reg, int nbit) {or32(reg, 1 << nbit);}

/* 16 bits registers */
static inline void wr16(volatile u16 *reg, u16 val) {*reg = val;}
static inline u16 rd16(volatile u16 *reg) {return *reg;}
static inline void or16(volatile u16 *reg, u16 val) {*reg |= val;}
static inline void and16(volatile u16 *reg, u16 val) {*reg &= val;}
static inline void clr16(volatile u16 *reg, int nbit) {and16(reg, ~(1 << nbit));}
static inline void set16(volatile u16 *reg, int nbit) {or16(reg, 1 << nbit);}

/* 8 bits registers */
static inline void wr8(volatile u8 *reg, u8 val) {*reg = val;}
static inline u8 rd8(volatile u8 *reg) {return *reg;}
static inline void or8(volatile u8 *reg, u8 val) {*reg |= val;}
static inline void and8(volatile u8 *reg, u8 val) {*reg &= val;}
static inline void clr8(volatile u8 *reg, int nbit) {and8(reg, ~(1 << nbit));}
static inline void set8(volatile u8 *reg, int nbit) {or8(reg, 1 << nbit);}

/* Circular buffer */
struct c_buf_t {
	u32 iwr;
	u32 ird;
	u8 buf[];
};

typedef struct c_buf_t c_buf_t;

static inline int cbuf_wr(c_buf_t *b, u8 data, int size)
{
	/* FIXME handle overrun */
	b->buf[b->iwr] = data;
	b->iwr = (b->iwr + 1) % size;
	return 1;
}

static inline int cbuf_rd(c_buf_t *b, u8 *data, int size)
{
	if (b->ird == b->iwr)
		return 0;
	*data = b->buf[b->ird];
	b->ird = (b->ird + 1) % size;
	return 1;
}

#endif /* _BASIC_H_ */
