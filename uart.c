#include "uart.h"

void uart_init() {
	// baud rate
	UBRR0H = ((F_CPU/16/BAUD)-1)>>8;
	UBRR0L = ((F_CPU/16/BAUD)-1);
	// 8 bit data frame
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	// 1 stop bit (default)
	// no parity (default)
	// enable TX and RX
	UCSR0B = (1<<TXEN0) | (1<<RXEN0);
}

void uart_tx_mem(const char *c) {
	for(; pgm_read_byte(c)!=0; c++) {
		// wait for USART-TX to be ready
		while((UCSR0A&(1<<UDRE0))==0);
		// send byte
		UDR0 = pgm_read_byte(c);
	}
}

void uart_tx_str(char* c) {
	for(; *c!=0; c++) {
		// wait for USART-TX to be ready
		while((UCSR0A&(1<<UDRE0))==0);
		// send byte
		UDR0 = *c;
	}
}

void uart_tx_chr(char c) {
	// wait for USART-TX to be ready
	while((UCSR0A&(1<<UDRE0))==0);
	// send byte
	UDR0 = c;
}

uint8_t uart_rx_check() {
	return(UCSR0A&(1<<RXC0));
}

void uart_rx_wait() {
	while((UCSR0A&(1<<RXC0))==0);
}

char uart_rx_chr() {
	return UDR0;
}

void uart_rx_str(char* str, uint8_t len) {
	// vars
	uint16_t timeout;
	uint8_t pos = 0;
	len = len - 1; // ensure room for delimiter
	while(1) {
		// wait for data or time out
		timeout = 0;
		while(((UCSR0A&(1<<RXC0))==0)&&(timeout<65535)) {
			timeout++;
		}
		// copy data to string
		if((UCSR0A&(1<<RXC0))!=0) {
			*str = UDR0;
			str++;
			pos++;
			// string full finished
			if(pos==len) {
				break;
			}
		// timed out finished
		} else {
			break;
		}
	}
	// add delimiter
	*str = 0;
}