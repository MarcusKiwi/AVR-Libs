#include "softserial.h"

void softserial_init(struct softserial_conf* conf, volatile uint8_t* ddr, volatile uint8_t* port, uint8_t dat, uint8_t clk) {
	// setup struct
	conf->port = port;
	conf->dat = (1<<dat);
	conf->clk = (1<<clk);
	// set ddr
	*ddr |= conf->dat | conf->clk;
}

void softserial(struct softserial_conf* conf, char data) {
	uint8_t mask = 0b10000000;
	while(mask>0) {
		// figure out if bit is a 1 or 0
		if(data & mask) {
			*(conf->port) |= (conf->dat);
		} else {
			*(conf->port) &= ~(conf->dat);
		}
		// clock it in
		*(conf->port) &= ~(conf->clk);
		*(conf->port) |= (conf->clk);
		// increment comparison value
		mask = mask>>1;
	}
}
