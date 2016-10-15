#ifndef SSD1306_H
#define SSD1306_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "i2c.h"
#include "font8x5.h"

// Libraries required in project makefile:
// LIBS = ssd1306 font8x5 i2c

/*******************************************************************
 * PIN CONNECTIONS: See i2c.h
 ******************************************************************/

// Initializes display and I2C bus. Addr is usually 0x3C.
void ssd1306_init(uint8_t addr);

// Clears pixels from screen.
void ssd1306_cls();

// Repositions cursor to top left of display.
// Display doesn't support moving to a specific addr.
void ssd1306_pos();

// Writes string to screen from progmem.
void ssd1306_mem(const char* c);

// Writes string to screen.
void ssd1306_str(char* c);

// Writes one character to screen.
void ssd1306_chr(char c);

// Writes one column of data to screen.
void ssd1306_raw(uint8_t x);

#endif /* SSD1306_H */
