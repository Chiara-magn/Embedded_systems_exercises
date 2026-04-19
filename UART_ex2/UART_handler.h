#ifndef UART_HANDLER_H
#define UART_HANDLER_H

#include <xc.h>
#include <stdint.h>

extern volatile int total_chars; 

void uart_init(void);

void uart_send_char(char c);
void uart_send_string(const char *s);
int uart_available(void);

// Circular buffer 
#define UART_BUFFER_SIZE 64

int uart_available(void);
char uart_read_char(void);

#endif
