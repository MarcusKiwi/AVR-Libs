#include "hd44780_i2c.h"

// Internal variable.
uint8_t hd44780_i2c_bus;

void hd44780_i2c_init() {
	// command mode
	hd44780_i2c_bus = 0b00001000;
	//warmup period
	i2c_init();
	_delay_ms(17);
	// initiates reset
	hd44780_i2c_chr(0x33);
	_delay_ms(5);
	hd44780_i2c_chr(0x32);
	_delay_us(150);
	// init commands
	hd44780_i2c_chr(0x28);
	hd44780_i2c_chr(0x0C);
	hd44780_i2c_chr(0x06);
	hd44780_i2c_chr(0x01);
	// data mode
	hd44780_i2c_bus = 0b00001001;
	_delay_ms(2);
}

void hd44780_i2c_cls() {
	// command mode
	hd44780_i2c_bus = 0b00001000;
	// clear command	
	hd44780_i2c_chr(0x01);
	// data mode
	hd44780_i2c_bus = 0b00001001;
	// slow command so additional delay
	_delay_ms(2);
}

void hd44780_i2c_pos(uint8_t x, uint8_t y) {
	// command mode
	hd44780_i2c_bus = 0b00001000;
	// set display memory location
	hd44780_i2c_chr(0x80 | ((y*0x40) + x));
	// data mode
	hd44780_i2c_bus = 0b00001001;
}

void hd44780_i2c_mem(const char* c) {
	for(; pgm_read_byte(c)!=0; c++) {
		hd44780_i2c_chr(pgm_read_byte(c));
	}
}

void hd44780_i2c_str(char* c) {
	for(; *c!=0; c++) {
		hd44780_i2c_chr(*c);
	}
}

void hd44780_i2c_chr(char c) {
	// each byte is broken into two to be sent
	// byte 1:
	//   nibble 1: data (first nibble)
	//   nibble 2: LED, E, RW, RS - the bus control pins
	// byte 2
	//   nibble 1: data (second nibble)
	//   nibble 2: LED, E, RW, RS - the bus control pins

	uint8_t outputs;
	i2c_start(0x27,I2C_W);

	outputs = (c & 0xF0) | hd44780_i2c_bus;
	i2c_write(outputs);
	outputs ^= (1<<2);
	i2c_write(outputs);
	outputs ^= (1<<2);
	i2c_write(outputs);
            
	outputs = (c<<4) | hd44780_i2c_bus;
	i2c_write(outputs);
	outputs ^= (1<<2);
	i2c_write(outputs);
	outputs ^= (1<<2);
	i2c_write(outputs);

	i2c_stop();
	//_delay_us(1000);
}