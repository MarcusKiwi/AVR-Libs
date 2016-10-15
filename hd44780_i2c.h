#ifndef HD44780_I2C_H
#define HD44780_I2C_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <i2c.h>

// Libraries required in project makefile:
// LIBS = hd44780_i2c i2c

/*******************************************************************
 * PIN CONNECTIONS: See i2c.h
 * NOTE: You can't display arbitrary, raw columns of text with this
 * display as you can with most others. Display has its own inbuilt
 * font in ROM. You can create a couple of custom characters for it
 * to display, but this isn't implemented by this library.
 ******************************************************************/

// Initializes display.
void hd44780_i2c_init();

// Clears all pixels on screen.
void hd44780_i2c_cls();

// Repositions cursor to given location.
// Multiply x*6 to keep things aligned for characters.
void hd44780_i2c_pos(uint8_t x, uint8_t y);

// Writes string to screen from progmem.
void hd44780_i2c_mem(const char* c);

// Writes string to screen.
void hd44780_i2c_str(char* c);

// Writes one character to screen.
void hd44780_i2c_chr(char c);

#endif /* HD44780_I2C_H */
