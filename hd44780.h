#ifndef HD44780_H
#define HD44780_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

// Libraries required in project makefile:
// LIBS = hd44780

/*******************************************************************
 * PIN CONNECTIONS:
 * 1  VSS GND
 * 2  VDD 5V
 * 3  V0  2.5V (10K potentiometer for contrast)
 * 4  RS  Input1
 * 5  RW  GND
 * 6  E   Input2
 * 7  D0  No conx
 * 8  D1  No conx
 * 9  D2  No conx
 * 10 D3  No conx
 * 11 D4  Input3
 * 12 D5  Input4
 * 13 D6  Input5
 * 14 D7  Input6
 * 15 A   5V (display backlight)
 * 16 K   GND (display backlight)
 * NOTE: You can't display arbitrary, raw columns of text with this
 * display as you can with most others. Display has its own inbuilt
 * font in ROM. You can create a couple of custom characters for it
 * to display, but this isn't implemented by this library.
 * This library doesn't control the backight.
 * This library only works for 1602 displays, for now.
 ******************************************************************/

// Config
#include "config.h"

/* config.h example, create this in your project folder
#define HD44780_DDR 	DDRC
#define HD44780_PORT	PORTC
#define HD44780_RS  	0
#define HD44780_E   	1
#define HD44780_D4  	2
#define HD44780_D5  	3
#define HD44780_D6  	4
#define HD44780_D7  	5
*/

// Initializes display.
void hd44780_init();

// Show/hide flashing cursor.
void hd44780_cursor(uint8_t cursor);

// Clears all pixels on screen.
void hd44780_cls();

// Repositions cursor to given location.
void hd44780_pos(uint8_t x, uint8_t y);

// Writes string to screen from progmem.
void hd44780_mem(const char* c);

// Writes string to screen from sram.
void hd44780_str(char* c);

// Writes one character to screen.
void hd44780_chr(char c);

// Internal use only. Sends nibble of data to display.
void hd44780_nib(char c);

#endif /* HD44780_H */
