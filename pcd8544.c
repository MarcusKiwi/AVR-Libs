#include "pcd8544.h"

void pcd8544_init() {
	// set ddr for output pins
	PCD8544_DDR |= (1<<PCD8544_RES) | (1<<PCD8544_DC) | (1<<PCD8544_DAT) | (1<<PCD8544_CLK);
	// reset display
	PCD8544_PORT &= ~(1<<PCD8544_RES);
	PCD8544_PORT |= (1<<PCD8544_RES);
	// enter command mode
	PCD8544_PORT &= ~(1<<PCD8544_DC);
	// extended init commands
	pcd8544_raw(0b00100001); // enter extended command mode
	pcd8544_raw(0b00001000|PCD8544_TEMP); // temperature
	pcd8544_raw(0b00010000|PCD8544_BIAS); // bias
	pcd8544_raw(0b10000000|PCD8544_VOP); // vop
	// basic init commands
	pcd8544_raw(0b00100000); // enter basic command mode
	pcd8544_raw(0b00001100); // address by column pixel mode
	// enter data mode
	PCD8544_PORT |= (1<<PCD8544_DC);
	// clear random noise from display
	pcd8544_cls();
}

void pcd8544_cls() {
	// send enough zeros to fill entire screen
	PCD8544_PORT &= ~(1<<PCD8544_DAT);
	for(uint16_t i=4032; i; i--) {
		PCD8544_PORT &= ~(1<<PCD8544_CLK);
		PCD8544_PORT |= (1<<PCD8544_CLK);
	}
	// force screen to update last byte
	pcd8544_nop();
}

void pcd8544_pos(uint8_t x, uint8_t y) {
	// enter command mode
	PCD8544_PORT &= ~(1<<PCD8544_DC);
	// set vertical address in ram
	pcd8544_raw(0b01000000+y);
	 // set horizontal address in ram
	pcd8544_raw(0b10000000+x);
	// enter data mode
	PCD8544_PORT |= (1<<PCD8544_DC);
}

void pcd8544_mem(const char* c) {
	for(; pgm_read_byte(c)!=0; c++) {
		pcd8544_chr(pgm_read_byte(c));
	}
}

void pcd8544_str(char* c) {
	for(; *c != 0; c++) {
		pcd8544_chr(*c);
	}
}

void pcd8544_chr(char c) {
	// for each column in font
	for(uint8_t i=0; i<5; i++) {
		// read column for character from progmem and display it
		pcd8544_raw(pgm_read_byte(&(font8x5[c-32][i])));
	}
	// space between characters
	pcd8544_raw(0x00);
}

void pcd8544_raw(uint8_t data) {
	// write a byte of data to screen with soft serial
	// bitwise comparison value
	uint8_t mask = 0b10000000;
	while(mask>0) {
		// figure out if bit is a 1 or 0
		if(data & mask) {
			PCD8544_PORT |= (1<<PCD8544_DAT);
		} else {
			PCD8544_PORT &= ~(1<<PCD8544_DAT);
		}
		// clock it in
		PCD8544_PORT &= ~(1<<PCD8544_CLK);
		PCD8544_PORT |= (1<<PCD8544_CLK);
		// increment comparison value
		mask = mask>>1;
	}
}

void pcd8544_nop() {
	// enter command mode
	PCD8544_PORT &= ~(1<<PCD8544_DC);
	// send no operation command
	pcd8544_raw(0);
	// enter data mode
	PCD8544_PORT |= (1<<PCD8544_DC);
}
