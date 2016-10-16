#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <avr/pgmspace.h>

// Libraries required in project makefile:
// LIBS = uart

/*******************************************************************
 * BAUD RATE: Set with #define in makefile
 * PIN CONNECTIONS: Pins are labelled "RXD" and "TXD"
 * ATMEGA328P: RXD=2 TXD=3
 * ATTINY85: not compatible
 * Arduino-Uno: RXD=0 TXD=1
 * Arduino-Mega: RXD=0 TXD=1
 ******************************************************************/

// Initialize uart
void uart_init();

// Sends string from progrmem.
void uart_tx_mem(const char *c);

// Sends string.
void uart_tx_str(char* c);

// Sends char.
void uart_tx_chr(char c);

// Check for data to process.
uint8_t uart_rx_check();

// Wait for data to receive. 
void uart_rx_wait();

// Receive one byte.
char uart_rx_chr();

// Receive to string.
void uart_rx_str(char* str, uint8_t len);

#endif /* UART_H */
