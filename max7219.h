#ifndef MAX7219_H
#define MAX7219_H

#include <avr/io.h>

// Libraries required in project makefile:
// LIBS = max7219

// Create one of these and pass its address to max7219 functions.
struct max7219_conf {
	volatile uint8_t *port;
	uint8_t din;
	uint8_t load;
	uint8_t clk;
};

// Initializes pins and max7219 chip.
void max7219_init(struct max7219_conf* conf, volatile uint8_t* ddr, 
	volatile uint8_t* port, uint8_t din, uint8_t load, uint8_t clk);

// Update one column of display.
void max7219_col(struct max7219_conf* conf, uint8_t addr, uint8_t data);

// For internal use.
void max7219_byte(struct max7219_conf* conf, uint8_t data);

#endif /* MAX7219_H */
