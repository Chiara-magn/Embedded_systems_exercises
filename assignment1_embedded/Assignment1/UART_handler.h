#ifndef UART_HANDLER_H
#define UART_HANDLER_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h> 

extern volatile int total_chars; 

void uart_init(void);

void uart_send_char(char c);
void uart_send_string(const char *s);

// Circular buffer 
#define UART_BUFFER_SIZE 64

int uart_available(void);
char uart_read_char(void);

// Assignment1 functions
#define UART_COMMAND_BUFFER_SZ 32
#define TX_BUFFER_SIZE   64 
bool uart_command_buffer(void);
bool uart_validate_command(void);
int uart_get_hz(void);

#endif
