# 2017, Aurelio Colosimo, <aurelio@aureliocolosimo.it>
# MIT License

LIB = ff_stm32f4xx.o

# Cross compiling configuration
CROSS_COMPILE = arm-none-eabi-
CC              = $(CROSS_COMPILE)gcc
AR              = $(CROSS_COMPILE)ar
LD              = $(CROSS_COMPILE)ld
OBJCOPY         = $(CROSS_COMPILE)objcopy
STRIP           = $(CROSS_COMPILE)strip

CFLAGS += -mthumb -Wall -Werror -Os -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 \
    -mfloat-abi=hard -ggdb

INCFLAGS = -Isource
OBJS += source/ff.o
OBJS += source/ffunicode.o
OBJS += source/ffsystem.o

all: $(LIB)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCFLAGS) -o $@ $<

$(LIB): $(OBJS)
	$(LD) $(OBJS) -r -o $(LIB)

clean:
	rm -f $(LIB)
	rm -f $(OBJS)

.PHONY: clean
