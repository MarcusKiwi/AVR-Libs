###############-------------------------------------------------------------###############
###############                           Example                           ###############
###############-------------------------------------------------------------###############

# Copy this into your project directory as your makefile
# Uncomment and customise settings to suit

#MCU   = atmega328p
#LIBS  = 
#F_CPU = 8000000
#BAUD  = 9600
#include ~/Code/AVR-Libs/makefile

###############-------------------------------------------------------------###############
###############                       Global Settings                       ###############
###############-------------------------------------------------------------###############

# Customise this to suit

PROG_TYPE = usbasp
PROG_ARGS = -V

CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -ffunction-sections -fdata-sections

###############-------------------------------------------------------------###############
###############                          Variables                          ###############
###############-------------------------------------------------------------###############

# Do not alter this

CFLAGS += -Os -std=gnu99 -mmcu=$(MCU) -DF_CPU=$(F_CPU)UL -DBAUD=$(BAUD)UL

LIBDIR = $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
VPATH = $(LIBDIR)
PRJ = $(lastword $(subst /, ,$(CURDIR)))

SRC = $(wildcard *.c) $(LIBS:=.c)
OBJ = $(SRC:.c=.o)
HED = $(wildcard *.h) $(LIBS:=.h)

###############-------------------------------------------------------------###############
###############                           Targets                           ###############
###############-------------------------------------------------------------###############

# Do not alter this

.PHONY: clean

all: $(PRJ).hex

install: $(PRJ).hex
	avrdude $(PROG_ARGS) -c $(PROG_TYPE) -p $(MCU) -U flash:w:$<
	@echo  

clean:
	rm -f *.o *.elf *.hex

###############-------------------------------------------------------------###############
###############                            Rules                            ###############
###############-------------------------------------------------------------###############

# Do not alter this

%.o: %.c $(HED)
	@echo "avr-gcc $(subst $(LIBDIR),"libs",$<)"
	@avr-gcc $< -o $@ $(CFLAGS) -c -I. -I$(LIBDIR)

$(PRJ).elf: $(OBJ)
	@echo "linking"
	@avr-gcc $^ -o $(PRJ).elf -mmcu=$(MCU)
	@rm *.o

$(PRJ).hex: $(PRJ).elf
	@echo "objcopy"
	@avr-objcopy -j .text -j .data -O ihex $(PRJ).elf $(PRJ).hex
	@echo  
	@echo "Device:     $(MCU) $(F_CPU)" | sed -e 's/000000UL/mhz/g'
	@avr-size -C --mcu=$(MCU) $(PRJ).elf | grep 'Program\|Data'
	@echo  
	@rm *.elf
