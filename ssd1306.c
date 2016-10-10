#include "ssd1306.h"

#define SSD1306_CMD 0x00
#define SSD1306_DAT 0x40

const uint8_t ssd1306_init_seq[] PROGMEM = {
	0xAE,	// off
	0xD5,	// display clock div
	0x80,
	0xA8,	// multiplex
	0x3F,
	0xD3,	// offset
	0x00,
	0x40,	// start line 0
	0x8D,	// charge pump
	0x14,	// internal vcc
	0x20,	// memory mode
	0x00,
	0xDA,	// ???
	0x12,
	0x81,	// contrast
	0x9C,
	0xD9,	// precharge
	0xF1,
	0xDB,	// comdetect
	0x40,
	0xA4,	// allow resume
	0xA6,
	0xAF	// on
};

void ssd1306_init(uint8_t addr) {
	// needs time to warm up
	_delay_ms(500);
	// store address
	ssd1306_config_addr = addr;
	// i2c init
	i2c_init();
	// run startup commands
	i2c_start(ssd1306_config_addr,I2C_W);
	i2c_write(SSD1306_CMD); // command mode
	for(uint8_t i=0; i<23; i++) {
		i2c_write(pgm_read_byte(&(ssd1306_init_seq[i])));
	}
	i2c_stop();
	/// we set the display boundaries to not use the left and
	/// rightmost columns of display. need to do manual cls
	/// with the larger display boundaries first so that these
	/// extra unused columns aren't left with random noise on
	/// them.
	// cls
	i2c_start(ssd1306_config_addr,I2C_W);
	i2c_write(SSD1306_DAT); // data mode
	for(uint16_t i=0; i<8192; i++) {
		i2c_write(0x00);
	}
	i2c_stop();
	// same command sets display boundaries
	ssd1306_pos();
}

void ssd1306_cls() {
	i2c_start(ssd1306_config_addr,I2C_W);
	i2c_write(SSD1306_DAT); // data mode
	for(uint16_t i=0; i<8064; i++) {
		i2c_write(0x00);
	}
	i2c_stop();
}

void ssd1306_pos() {
	/// repositions screen memory addr to top left
	/// actually this sets the boundaries of the screen,
	/// repositions the mem addr as a side effect of this.
	/// this is the only way to reposition the mem addr.
	// page/row
	i2c_start(ssd1306_config_addr,I2C_W);
	i2c_write(SSD1306_CMD); // command mode
	i2c_write(0x22);
	i2c_write(0);
	i2c_write(7);
	// column
	i2c_write(0x21);
	/// lop 1px off left and right of screen
	/// this is so 8x6 byte fonts wrap properly
	/// otherwise you're stuck with 8x8 byte fonts
	i2c_write(1);
	i2c_write(126);
	i2c_stop();
}

void ssd1306_mem(const char* c) {
	i2c_start(ssd1306_config_addr,I2C_W);
	i2c_write(SSD1306_DAT); // data mode
	for(; pgm_read_byte(c)!=0; c++) {
		// send display the character, column by column for font
		for(uint8_t col=0; col<5; col++) {
			i2c_write(pgm_read_byte(&(font8x5[pgm_read_byte(c)-32][col])));
		}
	}
	// space between letters
	i2c_write(0x00);
	// stop
	i2c_stop();
}

void ssd1306_str(char* c) {
	i2c_start(ssd1306_config_addr,I2C_W);
	i2c_write(SSD1306_DAT); // data mode
	// while character is not 0
	for(; *c != 0; c++) {
		// send display the character, column by column for font
		for(uint8_t col=0; col<5; col++) {
			i2c_write(pgm_read_byte(&(font8x5[*c-32][col])));
		}
	}
	// space between letters
	i2c_write(0x00);
	// stop
	i2c_stop();
}

void ssd1306_chr(char c) {
	i2c_start(ssd1306_config_addr,I2C_W);
	i2c_write(SSD1306_DAT); // data mode
	// send display the character, column by column for font
	for(uint8_t col=0; col<5; col++) {
		i2c_write(pgm_read_byte(&(font8x5[c-32][col])));
	}
	// space between letters
	i2c_write(0x00);
	// stop
	i2c_stop();
}

void ssd1306_raw(uint8_t x) {
	i2c_start(ssd1306_config_addr,I2C_W);
	i2c_write(SSD1306_DAT); // data mode
	i2c_write(x);
	i2c_stop();
}
