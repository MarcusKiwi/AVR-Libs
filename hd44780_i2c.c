#include "hd44780_i2c.h"

#define HD44780_I2C_LED 3
#define HD44780_I2C_E   2
#define HD44780_I2C_RW  1
#define HD44780_I2C_RS  0

// Internal variables.
uint8_t hd44780_i2c_bus = 0b00001001;
uint8_t hd44780_i2c_addr;

void hd44780_i2c_init(uint8_t addr) {
	// store i2c addr
	hd44780_i2c_addr = addr;
	// command mode
	hd44780_i2c_bus &= ~(1<<HD44780_I2C_RS);
	//warmup period
	i2c_init();
	_delay_ms(17);
	// initiates reset
	hd44780_i2c_chr(0x33);
	_delay_ms(5);
	hd44780_i2c_chr(0x32);
	_delay_us(150);
	// init commands
	hd44780_i2c_chr(0x28); // function set (4 bit, 2 lines, english font)
	hd44780_i2c_chr(0x0C); // display on/off control (display on, no cursor char, no cursor flash)
	hd44780_i2c_chr(0x06); // entry mode (autoincrement right, cursor shift on)
	hd44780_i2c_chr(0x01); // cls
	_delay_ms(2); // cls is slow
	// data mode
	hd44780_i2c_bus |= (1<<HD44780_I2C_RS);
}

void hd44780_i2c_led(uint8_t led) {
	if(led==0) {
		hd44780_i2c_bus &= ~(1<<HD44780_I2C_LED);
	} else {
		hd44780_i2c_bus |= (1<<HD44780_I2C_LED);
	}
	i2c_start(hd44780_i2c_addr,I2C_W);
	i2c_write(hd44780_i2c_bus);
	i2c_stop();
}

void hd44780_i2c_cursor(uint8_t cursor) {
	// command mode
	hd44780_i2c_bus &= ~(1<<HD44780_I2C_RS);
	// cursor on/off command
	if(cursor==0) {
		hd44780_i2c_chr(0x0C);
	} else {
		hd44780_i2c_chr(0x0D);
	}
	// data mode
	hd44780_i2c_bus |= (1<<HD44780_I2C_RS);
}

void hd44780_i2c_cls() {
	// command mode
	hd44780_i2c_bus &= ~(1<<HD44780_I2C_RS);
	// clear command	
	hd44780_i2c_chr(0x01);
	// data mode
	hd44780_i2c_bus |= (1<<HD44780_I2C_RS);
	// slow command so additional delay
	_delay_ms(2);
}

void hd44780_i2c_pos(uint8_t x, uint8_t y) {
	// command mode
	hd44780_i2c_bus &= ~(1<<HD44780_I2C_RS);
	// set display memory location
	hd44780_i2c_chr(0x80 | ((y*0x40) + x));
	// data mode
	hd44780_i2c_bus |= (1<<HD44780_I2C_RS);
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
	i2c_start(hd44780_i2c_addr,I2C_W);

	outputs = (c & 0xF0) | hd44780_i2c_bus;
	i2c_write(outputs);
	outputs ^= (1<<HD44780_I2C_E);
	i2c_write(outputs);
	outputs ^= (1<<HD44780_I2C_E);
	i2c_write(outputs);
            
	outputs = (c<<4) | hd44780_i2c_bus;
	i2c_write(outputs);
	outputs ^= (1<<HD44780_I2C_E);
	i2c_write(outputs);
	outputs ^= (1<<HD44780_I2C_E);
	i2c_write(outputs);

	i2c_stop();
	//_delay_us(1000);
}