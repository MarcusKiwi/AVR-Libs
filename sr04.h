#ifndef SR04_H_
#define SR04_H_

#include <avr/io.h>
#include <util/delay.h>

// Libraries required in project makefile:
// LIBS = sr04

/*******************************************************************
 * CONVERT TO CM: time in uS / 58
 ******************************************************************/

// The different prescalers you can use.
#define PRESCALE_1 (1<<CS00)
#define PRESCALE_8 (1<<CS01)
#define PRESCALE_64 ((1<<CS01)|(1<<CS00))
#define PRESCALE_256 (1<<CS02)
#define PRESCALE_1024 ((1<<CS02)|(1<<CS00))

// Create one of these and pass its address to sr04 functions.
struct sr04_conf {
	volatile uint8_t *pin;
	volatile uint8_t *port;
	uint8_t trig;
	uint8_t echo;
	uint8_t prescale;
};

// Init. Sets up ddr and timers.
void sr04_init(struct sr04_conf* conf, volatile uint8_t* ddr, volatile uint8_t* pin, volatile uint8_t* port, 
	uint8_t trig, uint8_t echo, uint8_t prescale);

// Reads distance. Returns 0 if timed out / too far.
uint8_t sr04_read(struct sr04_conf* conf);

#endif /* SR04_H_ */