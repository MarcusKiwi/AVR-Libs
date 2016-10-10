#include "sr04.h"

void sr04_init(struct sr04_conf* conf, volatile uint8_t* ddr, volatile uint8_t* pin, volatile uint8_t* port, 
	uint8_t trig, uint8_t echo, uint8_t prescale) {
	// variables
	conf->pin = pin;
	conf->port = port;
	conf->trig = (1<<trig);
	conf->echo = (1<<echo);
	conf->prescale = prescale;
	// pin setup
	*ddr |= conf->trig;
	*(conf->port) &= ~(conf->trig|conf->echo);
	// timer setup
	TCCR0A = (1<<WGM01); //ctc mode
}

uint8_t sr04_read(struct sr04_conf* conf) {
	// clear timer
	TCNT0 = 0;

	// send ping
	*(conf->port) |= (conf->trig);
	_delay_us(10);
	*(conf->port) &= ~(conf->trig);

	// wait for signal to begin
	while(((*(conf->pin)) & (conf->echo))==0);

	// start timer
	TCCR0B = conf->prescale;

	// wait for pong
	while(((*(conf->pin)) & (conf->echo))!=0);

	// stop timer
	TCCR0B = 0;

	return TCNT0;
}
