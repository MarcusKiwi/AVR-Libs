#include "i2c.h"

void i2c_init() {
	TWSR = 0;
	TWBR = 2; // 32=100khz@8mhz 2=400khz@8mhz 2=50khz@1mhz
}

void i2c_start(uint8_t addr, uint8_t rw) {
	// start cond
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);
	// wait for complete
	while(!(TWCR & (1<<TWINT)));
	// send slave address + r/w mode
	TWDR = (addr<<1) | rw;
	// send over bus
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for ACK
	while(!(TWCR & (1<<TWINT)));
}

void i2c_write(uint8_t data) {
	// put data in register
	TWDR = data;
	// send over bus
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for ACK
	while(!(TWCR & (1<<TWINT)));
}

char i2c_read() {
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}

char i2c_readlast() {
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}

void i2c_stop() {
	// stop cond
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	// wait for ACK
	while(TWCR & (1<<TWSTO));
}
