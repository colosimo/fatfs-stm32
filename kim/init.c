/*
 * Author: Aurelio Colosimo, 2016
 * Originally modified from kim-os project:
 * https://github.com/colosimo/kim-os
 */

#include <linker.h>
#include <basic.h>
#include <log.h>
#include <gpio.h>
#include <stm32f411x.h>

#define STACK_TOP ((void*)(0x20004000))

#define CPU_FREQ      168000000
#define AHB_PRESCALER         4
#define HCLCK (CPU_FREQ / AHB_PRESCALER)
#define SYSTICKS_FREQ      1000

#define kprint(...) /* FIXME dummy */

static uint32_t ticks = 4294907296UL;

extern unsigned char _sdata_flash;
extern unsigned char _sdata;
extern unsigned char _edata;
extern unsigned char _sbss;
extern unsigned char _ebss;
extern void main(void);

void init(void);

void isr_reset(void)
{
	unsigned char *src, *dest;

	/* Load data to ram */
	src = &_sdata_flash;
	dest = &_sdata;
	while (dest != &_edata)
		*dest++ = *src++;

	/* Set bss section to 0 */
	dest = &_sbss;
	while (dest != &_ebss)
		*dest++ = 0;

	/* Skip to mach or board specific init */
	init();
}

static uint32_t attr_used ipsr(void)
{
  uint32_t res;
  __asm volatile ("mrs %0, ipsr" : "=r" (res));
  return res;
}


void attr_weak isr_none(void)
{
#if 0
	crt("Unhandled IPSR=%x ISPR=%x\n", (uint)ipsr(), (uint)rd32(R_NVIC_ISPR));
	while(1);
#endif
}

void attr_weak isr_nmi(void)
{
}

void attr_weak isr_hf(void)
{
}

void attr_weak isr_systick(void)
{
	ticks++;
}

static const void *attr_sect("isrv_sys") _isrv_sys[] = {
	/* Cortex-M0 system interrupts */
	STACK_TOP,	/* Stack top */
	isr_reset,	/* Reset */
	isr_nmi,	/* NMI */
	isr_hf,	/* Hard Fault */
	0,			/* Reserved */
	0,			/* Reserved */
	0,			/* Reserved */
	0,			/* Reserved */
	0,			/* Reserved */
	0,			/* Reserved */
	0,			/* Reserved */
	isr_none,	/* SVC */
	0,			/* Reserved */
	0,			/* Reserved */
	isr_none,	/* PendSV */
	isr_systick,	/* SysTick */
};

static const void *attr_sect("isrv_irq") _isrv_irq[] = {
	/* Peripheral interrupts */
	isr_none, /* WWDG */
	isr_none, /* EXTI16 / PVD */
	isr_none, /* EXTI21 / TAMP_STAMP */
	isr_none, /* EXTI22 / RTC_WKUP */
	isr_none, /* FLASH */
	isr_none, /* RCC */
	isr_none, /* EXTI0 */
	isr_none, /* EXTI1 */
	isr_none, /* EXTI2 */
	isr_none, /* EXTI3 */
	isr_none, /* EXTI4 */
	isr_none, /* DMA1_Stream0 */
	isr_none, /* DMA1_Stream1 */
	isr_none, /* DMA1_Stream2 */
	isr_none, /* DMA1_Stream3 */
	isr_none, /* DMA1_Stream4 */
	isr_none, /* DMA1_Stream5 */
	isr_none, /* DMA1_Stream6 */
	isr_none, /* ADC */
	0,		  /* Reserved */
	0,		  /* Reserved */
	0,		  /* Reserved */
	0,		  /* Reserved */
	isr_none, /* EXTI9_5 */
	isr_none, /* TIM1_BRK_TIM9 */
	isr_none, /* TIM1_UP_TIM10 */
	isr_none, /* TIM1_TRG_COM_TIM11 */
	isr_none, /* TIM1_CC */
	isr_none, /* TIM2 */
	isr_none, /* TIM3 */
	isr_none, /* TIM4 */
	isr_none, /* I2C1_EV */
	isr_none, /* I2C1_ER */
	isr_none, /* I2C2_EV */
	isr_none, /* I2C2_ER */
	isr_none, /* SPI1 */
	isr_none, /* SPI2 */
	isr_none, /* USART1 */
	isr_none, /* USART2 */
	0,		  /* Reserved */
	isr_none, /* EXTI15_10 */
	isr_none, /* EXTI17 / RTC_Alarm */
	isr_none, /* EXTI18 / OTG_FS WKUP */
	0,		  /* Reserved */
	0,		  /* Reserved */
	0,		  /* Reserved */
	0,		  /* Reserved */
	isr_none, /* DMA1_Stream7 */
	0,
	isr_none, /* SDIO */
	isr_none, /* TIM5 */
	isr_none, /* SPI3 */
	0,		  /* Reserved */
	0,		  /* Reserved */
	0,		  /* Reserved */
	0,		  /* Reserved */
	isr_none, /* DMA2_Stream0 */
	isr_none, /* DMA2_Stream1 */
	isr_none, /* DMA2_Stream2 */
	isr_none, /* DMA2_Stream3 */
	isr_none, /* DMA2_Stream4 */
	0,		  /* Reserved */
	0,		  /* Reserved */
	0,		  /* Reserved */
	0,		  /* Reserved */
	0,		  /* Reserved */
	0,		  /* Reserved */
	isr_none, /* OTG_FS */
	isr_none, /* DMA2_Stream5 */
	isr_none, /* DMA2_Stream6 */
	isr_none, /* DMA2_Stream7 */
	isr_none, /* USART6 */
	isr_none, /* I2C3_EV */
	isr_none, /* I2C3_ER */
	0,		  /* Reserved */
	0,		  /* Reserved */
	0,		  /* Reserved */
	0,		  /* Reserved */
	0,		  /* Reserved */
	0,		  /* Reserved */
	0,		  /* Reserved */
	isr_none, /* FPU */
	0,		  /* Reserved */
	0,		  /* Reserved */
	isr_none, /* SPI4 */
	isr_none, /* SPI5 */
};

uint32_t systicks_freq(void)
{
	return SYSTICKS_FREQ;
}

u32 systicks(void)
{
	return ticks;
}

inline void sleep()
{
	asm("wfi");
}

u32 k_ticks() attr_weak attr_alias("systicks");
u32 k_ticks_freq(void) attr_alias("systicks_freq");

void init_clock(void)
{
	/* Enable HSE (8MHz external oscillator) */
	or32(RCC_CR, BIT16);
	while (!(rd32(RCC_CR) & BIT17));

	/* PLLM=8 PLLN=336, PLLP=00 (2), PLLQ=7; f_PLL=168MHz, f_USB=48MHz */
	and32(RCC_PLLCFGR, ~0x0f037fff);
	or32(RCC_PLLCFGR, BIT22 | (7 << 24) | (336 << 6) | 8);
	or32(RCC_CR, BIT24);
	while (!(rd32(RCC_CR) & BIT25));

	/* Configure flash */
	wr32(R_FLASH_ACR, BIT10 | BIT9 | BIT8 | 1);

	/* Use PLL as system clock, with AHB prescaler set to 4 */
	wr32(RCC_CFGR, (0x9 << 4) | 0x2);
	while (((rd32(RCC_CFGR) >> 2) & 0x3) != 0x2);

	/* Enable clock on AHB and APB peripherals */
	wr32(RCC_AHB1ENR, BIT7 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0); /* GPIO */
	wr32(RCC_APB1ENR, BIT1 | BIT2 | BIT17); /* TIM3, TIM4 and USART2 */
	wr32(RCC_APB2ENR, BIT0 | BIT4 | BIT8 | BIT18); /* TIM1/11, ADC1, USART1 */
}

void init_systick(void)
{
	ticks = 0;
	wr32(R_SYST_RVR, HCLCK / SYSTICKS_FREQ);
	wr32(R_SYST_CVR, 0);
	wr32(R_SYST_CSR, BIT0 | BIT1 | BIT2);
}

int putchar(int c)
{
	if (c == '\n')
		putchar('\r');
	wr32(R_USART2_DR, c);
	while (!(rd32(R_USART2_SR) & BIT6));
	return c;
}

void init_uart(void)
{
	/* USART2 on PA9/PA10 */
	gpio_func(IO(PORTD, 5), 7);
	gpio_func(IO(PORTD, 6), 7);
	gpio_mode(IO(PORTD, 5), PULL_NO);
	gpio_mode(IO(PORTD, 6), PULL_NO);
	/* fPCLK=42MHz, br=115.2KBps, USARTDIV=22.8125, see table 80 pag. 519 */
	wr32(R_USART2_BRR, (22 << 4) | 13);
	or32(R_USART2_CR1, BIT13 | BIT5 | BIT3 | BIT2);
	or32(R_NVIC_ISER(1), BIT6); /* USART2 is irq 38 */
}

void init(void)
{
	init_clock();
	init_systick();
	init_uart();
	main();
}
