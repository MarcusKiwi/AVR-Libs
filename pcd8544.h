#ifndef PCD8544_H
#define PCD8544_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "font8x5.h"

// Libraries required in project makefile:
// LIBS = pcd8544 font8x5

/*******************************************************************
 * NOTE ON BUG: When you send a byte of display data to the 
 * controller, it won't show it right away. It'll only show it when
 * it starts recieving the next byte of data. Issue on the display
 * controllers end.
 * 
 * This isn't normally much of an issue as you're typically 
 * sending it characters where the last byte is always blank,
 * on an already cleared display.
 * 
 * However when sending raw display data for images and such it 
 * can be an annoying issue. Sending one bit would knock the
 * alignment off for future display data and commands. Sending a
 * byte would knock off the alignment for characters and make a
 * column that mysteriously fills itself when more display data
 * is sent through.
 * 
 * Use the nop function to send it a byte of data that will force
 * it to update.
 * 
 * This command isn't in the datasheet as it's not a valid command
 * so it doesn't do anything. However since it is a new byte of
 * data it'll force the display to actually use the previous byte.
 ******************************************************************/

// Config
#include "config.h"

/* config.h example, create this in your project folder
#define PCD8544_DDR		DDRC
#define PCD8544_PORT	PORTC
#define PCD8544_RES 	3
#define PCD8544_DC  	2
#define PCD8544_DAT 	1
#define PCD8544_CLK 	0
/**/

// Contrast controls, shouldn't need to be changed
#define PCD8544_TEMP 1	// 0-3, temperature, minor effect
#define PCD8544_BIAS 3	// 0-7, bias, major effect
#define PCD8544_VOP	63	// 0-127 vop, major effect

// Initializes display.
void pcd8544_init();

// Clears all pixels on screen.
void pcd8544_cls();

// Repositions cursor to given location.
// Multiply x*6 to keep things aligned for characters.
void pcd8544_pos(uint8_t x, uint8_t y);

// Writes string to screen from progmem.
void pcd8544_mem(const char* c);

// Writes string to screen from sram.
void pcd8544_str(char* c);

// Writes one character to screen.
void pcd8544_chr(char c);

// Writes one column of data to screen.
void pcd8544_raw(uint8_t x);

// No operation command for forcing display to update.
void pcd8544_nop();

#endif /* PCD8544_H */
