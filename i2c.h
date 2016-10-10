#ifndef I2C_H
#define I2C_H

#include <util/twi.h>

// Libraries required in project makefile:
// LIBS = i2c

/*******************************************************************
 * PIN CONNECTIONS: Pins are labelled "SCL" and "SDA"
 * ATmega328p: SDA=27 SCL=28
 * ATtiny85: not compatible, uses USI instead of TWI
 * Arduino-Uno: SDA=A4 SCL=A5
 * Arduino-Mega: SDA=A4/20 SCL=A5/21
 ******************************************************************/

#define I2C_R 1
#define I2C_W 0

// Initializes I2C
void i2c_init();

// Initializes packet or changes mode.
void i2c_start(uint8_t addr, uint8_t rw);

// Writes one byte to I2C.
void i2c_write(uint8_t data);

// Read one byte from I2C, prep the next.
char i2c_read();

// Reads one byte from I2C, no more.
char i2c_readlast();

// End I2C packet.
void i2c_stop();

#endif /* I2C_H */
