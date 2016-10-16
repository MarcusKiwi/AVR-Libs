#include "dht11.h"

void dht11_read(struct dht11_data *retval) {
	// vars
	uint8_t crnt = 0;
	uint8_t last = 0;
	uint8_t len = 0;
	uint8_t sigcounts[40];
	uint8_t pos = 0;

	// dataput mode
	DHT11_DDR |= (1<<1);
	// default state high
	DHT11_PORT |= (1<<1);
	// send >18ms low signal
	DHT11_PORT &= ~(1<<1);
	_delay_ms(20);
	// input pullup
	DHT11_DDR &= ~(1<<1);
	DHT11_PORT |= (1<<1);
	// receive ~80us lo start signal, wait for it to finish
	_delay_us(20);
	while((DHT11_PIN & (1<<1))==0);
	// receive ~80us hi start signal, wait for it to finish
	while((DHT11_PIN & (1<<1))!=0);

	// receive 5x8 bits
	while(pos<40) {
		crnt = (DHT11_PIN & (1<<1));
		if(crnt==last) {
			// count
			if(len!=255) len++;
		} else {
			// log hi signals only
			if(last!=0) {
				sigcounts[pos]=len;
				pos++;
			}
			// next signal
			last = crnt;
			len = 1;
		}
	}

	// find the mid point of the signal lengths
	uint8_t lo = 255;
	uint8_t hi = 0;
	for(pos=0; pos<40; pos++) {
		if(sigcounts[pos]<lo) lo=sigcounts[pos];
		if(sigcounts[pos]>hi) hi=sigcounts[pos];
	}
	uint8_t mid = ((hi-lo) / 2) + lo;

	// find if signals are low or hi
	uint8_t data[5];
	uint8_t dbit = 0;
	uint8_t dbyte = 0;
	for(pos=0; pos<40; pos++) {
		if(sigcounts[pos]>mid) {
			data[dbyte] = ((data[dbyte]<<1) | 0x01);
		} else {
			data[dbyte] = ((data[dbyte]<<1));
		}
		dbit++;
		if(dbit==8) {
			dbit=0;
			dbyte++;
		}
	}

	// error checks
	if((((data[0]+data[2])!=data[4]))||(data[1]!=0)||(data[3]!=0)) {
		retval->temp = 0;
		retval->humid = 0;
	} else {
		retval->temp = data[2];
		retval->humid = data[0];
	}
}