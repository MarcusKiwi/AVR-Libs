#ifndef SERIAL_H
#define SERIAL_H

#include <avr/io.h>
#include <avr/pgmspace.h>

// Libraries required in project makefile:
// LIBS = serial

/*******************************************************************
 * BAUD RATE: Set with #define in makefile
 * PIN CONNECTIONS: Pins are labelled "RXD" and "TXD"
 * ATMEGA328P: RXD=2 TXD=3
 * ATTINY85: not compatible
 * Arduino-Uno: RXD=0 TXD=1
 * Arduino-Mega: RXD=0 TXD=1
 ******************************************************************/

// Initialize serial
void serial_init();

// Sends string from progrmem.
void serial_tx_mem(const char *c);

// Sends string.
void serial_tx_str(char* c);

// Sends char.
void serial_tx_chr(char c);

// Check for data to process.
uint8_t serial_rx_check();

// Wait for data to receive. 
void serial_rx_wait();

// Receive one byte.
char serial_rx_chr();

// Receive to string.
void serial_rx_str(char* str, uint8_t len);

#endif /* SERIAL_H */
