#ifndef SOFTSERIAL_H_
#define SOFTSERIAL_H_

#include <avr/io.h>
#include <avr/pgmspace.h>

// Libraries required in project makefile:
// LIBS = softserial

// Create one of these and pass its address to softserial functions.
struct softserial_conf {
	volatile uint8_t *port;
	uint8_t dat;
	uint8_t clk;
};

// Init. Sets up ddr and struct vars.
void softserial_init(struct softserial_conf* conf, volatile uint8_t* ddr, volatile uint8_t* port, uint8_t dat, uint8_t clk);

// Send data via software serial.
void softserial(struct softserial_conf* conf, char data);

#endif /* SOFTSERIAL_H_ */