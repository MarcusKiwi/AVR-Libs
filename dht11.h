#ifndef DHT11_H
#define DHT11_H

#include <avr/io.h>
#include <util/delay.h>

// Libraries required in project makefile:
// LIBS = dht11

// Config
#include "config.h"

/* config.h example, create this in your project folder
#define DHT11_DDR 	DDRB
#define DHT11_PIN 	PINB
#define DHT11_PORT	PORTB
#define DHT11_DAT 	1
/**/

// Create one of these and pass its address to dht11 read.
struct dht11_data {
	uint8_t temp;
	uint8_t humid;
};

// Initializes and reads from sensor.
void dht11_read(struct dht11_data *retval);

#endif /* DHT11_H */
