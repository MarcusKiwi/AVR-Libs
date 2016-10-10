#ifndef DS1307_H
#define DS1307_H

#include "i2c.h"

// Libraries required in project makefile:
// LIBS = ds1307 i2c

/*******************************************************************
 * PIN CONNECTIONS: See i2c.h
 * NOTE: Only time (hours, minutes, seconds) in only 24 hour mode
 * is implemented by this library.
 ******************************************************************/

// Create one of these and pass its address to ds1307 functions.
struct ds1307_time {
	uint8_t h;
	uint8_t m;
	uint8_t s;
};

// Initializes DS1307 and sets the time.
void ds1307_set(struct ds1307_time* time);

// Gets the time.
void ds1307_get(struct ds1307_time* time);

#endif /* DS1307_H */
