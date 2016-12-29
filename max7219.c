#include "max7219.h"

void max7219_init(struct max7219_conf* conf, volatile uint8_t* ddr, volatile uint8_t* port, uint8_t din, uint8_t load, uint8_t clk) {
	conf->port = port;
	conf->din = (1<<din);
	conf->load = (1<<load);
	conf->clk = (1<<clk);
	*ddr |= conf->din | conf->load | conf->clk;
	// initial setup
	max7219_col(conf,0x0C,0x01); // normal mode (0x00 is shutdown)
	max7219_col(conf,0x0A,0x0F); // intensity max
	max7219_col(conf,0x0B,0x07); // 8 row mode
	// blank rows 1-8 (addr 1-8) and set BCD decode mode (addr 9) to none
	for(uint8_t i=1; i<10; i++) {
		max7219_col(conf,i,0);
	}
}

void max7219_col(struct max7219_conf* conf, uint8_t addr, uint8_t data) {
	// open comms
	*(conf->port) &= ~(conf->load);
	max7219_byte(conf,addr);
	max7219_byte(conf,data);
	// end comms
	*(conf->port) |= (conf->load);
}

void max7219_byte(struct max7219_conf* conf, uint8_t data) {
	// send addr
	uint8_t mask = 0b10000000;
	while(mask>0) {
		if(data & mask) {
			*(conf->port) |= (conf->din);
		} else {
			*(conf->port) &= ~(conf->din);
		}
		*(conf->port) &= ~(conf->clk);
		*(conf->port) |= (conf->clk);
		// increment comparison value
		mask = mask>>1;
	}
}
