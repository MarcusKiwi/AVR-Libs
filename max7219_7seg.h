#ifndef MAX7219_7SEG_H
#define MAX7219_7SEG_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <max7219.h>

// Libraries required in project makefile:
// LIBS = max7219 max7219_7seg

/*******************************************************************
 * This extends the max7219 library to provide 8x 7 segment 
 * display functions. Has many more characters than the max7219s
 * internal BCD font.
 ******************************************************************/

// Writes string to screen from progmem.
void max7219_mem(struct max7219_conf* conf, const char* c);

// Writes string to screen from sram.
void max7219_str(struct max7219_conf* conf, char* c);

// Writes one character to screen.
void max7219_chr(struct max7219_conf* conf, uint8_t col, char c);

// font used internally
const uint8_t max7219_font[95] PROGMEM;

#endif /* MAX7219_7SEG_H */