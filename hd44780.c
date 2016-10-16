#include "hd44780.h"

void hd44780_init() {
	// set ddr for output pins
	HD44780_DDR |= (1<<HD44780_RS) | (1<<HD44780_E) | (1<<HD44780_D4) | (1<<HD44780_D5) | (1<<HD44780_D6) | (1<<HD44780_D7);
	// command mode
	HD44780_PORT &= ~(1<<HD44780_RS);
	//warmup period
	_delay_ms(17);
	// initiates reset
	hd44780_chr(0x33);
	_delay_ms(5);
	hd44780_chr(0x32);
	_delay_us(150);
	// init commands
	hd44780_chr(0x28); // function set (4 bit, 2 lines, english font)
	hd44780_chr(0x0C); // display on/off control (display on, no cursor char, no cursor flash)
	hd44780_chr(0x06); // entry mode (autoincrement right, cursor shift on)
	hd44780_chr(0x01); // cls
	_delay_ms(2); // cls is slow
	// data mode
	HD44780_PORT |= (1<<HD44780_RS);
}

void hd44780_cursor(uint8_t cursor) {
	// command mode
	HD44780_PORT &= ~(1<<HD44780_RS);
	// cursor on/off command
	if(cursor==0) {
		hd44780_chr(0x0C);
	} else {
		hd44780_chr(0x0D);
	}
	// data mode
	HD44780_PORT |= (1<<HD44780_RS);
}

void hd44780_cls() {
	// command mode
	HD44780_PORT &= ~(1<<HD44780_RS);
	// clear command	
	hd44780_chr(0x01);
	// data mode
	HD44780_PORT |= (1<<HD44780_RS);
	// slow command so additional delay
	_delay_ms(2);
}

void hd44780_pos(uint8_t x, uint8_t y) {
	// command mode
	HD44780_PORT &= ~(1<<HD44780_RS);
	// set display memory location
	hd44780_chr(0x80 | ((y*0x40) + x));
	// data mode
	HD44780_PORT |= (1<<HD44780_RS);
}

void hd44780_mem(const char* c) {
	for(; pgm_read_byte(c)!=0; c++) {
		hd44780_chr(pgm_read_byte(c));
	}
}

void hd44780_str(char* c) {
	for(; *c!=0; c++) {
		hd44780_chr(*c);
	}
}

void hd44780_chr(char c) {
	// send data to display
	hd44780_nib(c>>4);
	hd44780_nib(c);
	// allow display to react
	_delay_us(30);
}

void hd44780_nib(char c) {
	/* NOTE:
	there are faster ways of doing this of course
	but that doesn't really matter as we end up waiting
	for the display anyway.
	this only takes an extra 20 bytes of program mem
	and allows full pin remapping.
	*/
	// data pins
	if((c & 0b00000001)!=0) {
		HD44780_PORT |= (1<<HD44780_D4);
	} else {
		HD44780_PORT &= ~(1<<HD44780_D4);
	}
	if((c & 0b00000010)!=0) {
		HD44780_PORT |= (1<<HD44780_D5);
	} else {
		HD44780_PORT &= ~(1<<HD44780_D5);
	}
	if((c & 0b00000100)!=0) {
		HD44780_PORT |= (1<<HD44780_D6);
	} else {
		HD44780_PORT &= ~(1<<HD44780_D6);
	}
	if((c & 0b00001000)!=0) {
		HD44780_PORT |= (1<<HD44780_D7);
	} else {
		HD44780_PORT &= ~(1<<HD44780_D7);
	}
	// clock
	HD44780_PORT |= (1<<HD44780_E);
	HD44780_PORT &= ~(1<<HD44780_E);
}