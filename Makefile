# 2017, Aurelio Colosimo, <aurelio@aureliocolosimo.it>
# MIT License

BIGOBJ = ff-stm32f4-bigobj.o
LIB = ff_stm32f4.a
ELF = ff_demo.elf
BIN = ff_demo.bin

# Cross compiling configuration
CROSS_COMPILE = arm-none-eabi-
CC              = $(CROSS_COMPILE)gcc
AR              = $(CROSS_COMPILE)ar
LD              = $(CROSS_COMPILE)ld
OBJCOPY         = $(CROSS_COMPILE)objcopy
STRIP           = $(CROSS_COMPILE)strip

CFLAGS += -mthumb -Wall -Werror -Os -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 \
    -mfloat-abi=hard -ggdb

INCFLAGS = -Isource -Ikim/include
OBJS += source/ff.o
OBJS += source/ffunicode.o
OBJS += source/ffsystem.o
OBJS += source/diskio_stm32f4xx.o

DEMO_OBJS += kim/init.o
DEMO_OBJS += kim/kprint.o

DEMO_OBJS += main.o

all: $(BIN)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCFLAGS) -o $@ $<

$(BIGOBJ): $(OBJS)
	$(LD) $(OBJS) -r -o $(BIGOBJ)

$(LIB): $(BIGOBJ)
	$(AR) rs $(LIB) $(BIGOBJ)

$(ELF): $(LIB) $(DEMO_OBJS)
	$(LD) $(DEMO_OBJS) $(LIB) -Tkim/stm32f4xx.ld -o $(ELF)

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $(ELF) $(BIN)

clean:
	rm -f $(OBJS) $(DEMO_OBJS) $(BIGOBJ) $(LIB) $(ELF) $(BIN)

.PHONY: clean
