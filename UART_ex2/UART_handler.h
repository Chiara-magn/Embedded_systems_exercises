#ifndef UART_HANDLER_H
#define UART_HANDLER_H

#include <xc.h>
#include <stdint.h>

extern volatile char rx_buffer[3];
extern volatile int rx_ready; 
extern volatile int total_chars; 

void uart_init(void);

void uart_send_char(char c);
void uart_send_string(const char *s);
int uart_available(void);

#endif
