#include "ds1307.h"

void ds1307_set(struct ds1307_time* time) {

	// init
	i2c_init();
	uint8_t setup[8] = {0,0,0,0,0,0,0,0};
	uint8_t i = 0;

	// seconds
	if(time->s < 60) {
		setup[0] = (time->s % 10);
		i = (time->s - setup[0]);
		if(i!=0) i=(i/10);
		setup[0] = (i<<4) | setup[0];
	}

	// minutes
	if(time->m < 60) {
		setup[1] = (time->m % 10);
		i = (time->m - setup[1]);
		if(i!=0) i=(i/10);
		setup[1] = (i<<4) | setup[1];
	}

	// hours
	if(time->h < 24) {
		setup[2] = (time->h % 10);
		i = (time->h - setup[2]);
		if(i!=0) i=(i/10);
		setup[2] = (i<<4) | setup[2];
	}

	// write to ds1307
	i2c_start(0x68,I2C_W);
	i2c_write(0x00); // ds1307 mem start addr
	for(i=0; i<8; i++) {
		i2c_write(setup[i]);
	}
	i2c_stop();
}

void ds1307_get(struct ds1307_time* time) {
	// i2c read
	i2c_start(0x68,I2C_W);
	i2c_write(0x00); // ds1307 mem start addr
	i2c_start(0x68,I2C_R);
	time->s = i2c_read();
	time->m = i2c_read();
	time->h = i2c_readlast();
	i2c_stop();
	// covert to int
	time->s = (((time->s & 0xF0)>>4)*10) + (time->s & 0x0F);
	time->m = (((time->m & 0xF0)>>4)*10) + (time->m & 0x0F);
	time->h = (((time->h & 0x30)>>4)*10) + (time->h & 0x0F);
}