FILENAME = minimal

PREFIX 	= arm-none-eabi-
SERIAL  = /dev/tty.usbserial-AH013G1O
CPU 	= -mthumb -mcpu=cortex-m0plus -MD

LINK 	= $(FILENAME).ld

CFLAGS	+= -Os --specs=nano.specs -ffunction-sections -fdata-sections -fno-builtin

CC 		= ${PREFIX}gcc
LD 		= ${PREFIX}ld
OBJCOPY = ${PREFIX}objcopy
SIZE 	= ${PREFIX}size

# use these on the $(LD) line, as needed:
LIBM 	= ${shell ${CC} ${CFLAGS} --print-file-name=libm.a}
LIBC 	= ${shell ${CC} ${CFLAGS} --print-file-name=libc.a}
LIBGCC 	= ${shell ${CC} ${CFLAGS} --print-libgcc-file-name}

CFLAGS 	+= $(CPU) $(FPU)
LDFLAGS += --gc-sections

INC 	+= -Icmsis
CFLAGS 	+= $(INC) -D__USE_CMSIS

OBJS 	= gcc_startup_lpc8xx.o main.o

all: $(FILENAME).hex

$(FILENAME).axf: $(FILENAME).ld $(OBJS)
	@$(LD) -o $@ $(LDFLAGS) -T $(LINK) $(OBJS) $(LIBGCC)
	@$(SIZE) $(FILENAME).axf

clean:
	@rm -f *.o *.d
	@rm -f $(FILENAME).axf $(FILENAME).hex $(FILENAME).bin

%.hex: %.axf
	@$(OBJCOPY) --strip-unneeded -O ihex $(FILENAME).axf $(FILENAME).hex

install: ${FILENAME}.hex
	lpc21isp ${FILENAME}.hex ${SERIAL} 115200 12000