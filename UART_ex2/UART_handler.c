#include "config.h"
#include "UART_handler.h"

volatile char rx_buffer[3] = {0};
volatile int rx_ready = 0;
volatile int total_chars = 0; 

void uart_init(void){
	
    TRISDbits.TRISD0 = 0;               // output
    TRISDbits.TRISD11 = 1;              // input
    
    RPINR18bits.U1RXR = UART1_RX_RPIN;  // metti UART1 in input sul pin fisico RD11 = RPI75
    RPOR0bits.RP64R = 1;                // metti in output sul pin RD0 = RP64 quello che ricevi da UART
    
    U1BRG = 468 ;                       //(72000000/16*9600)-1
    // Abilita UART1
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;
    
    // interrupts per UART!!!!
    U1STAbits.URXISEL = 0;              //Interrupt is set on every received character
    IFS0bits.U1RXIF = 0;
    IEC0bits.U1RXIE = 1;
	
}


// --- ISR ---
void __attribute__((interrupt, no_auto_psv)) // psv = program space visibility 
    _U1RXInterrupt(void) {
    IFS0bits.U1RXIF = 0;
    
    char c = U1RXREG;
    total_chars++; 

    // shift buffer
    rx_buffer[0] = rx_buffer[1];
    rx_buffer[1] = rx_buffer[2];
    rx_buffer[2] = c;
    
    rx_ready =1;   
	}
// --- ---

void uart_send_char(char c) { 
    while (!U1STAbits.TRMT);            // trasmettitore pronto modificare con flag
    U1TXREG = c; // invio carattere
} 

void uart_send_string(const char *s) {  // serve per scorrere la stringa
    while (*s) {                        // finche s punta a caratteri, *s != 0, quando punta a \0, *s vale 0 ed esce dal while
		uart_send_char(*s);             // richiama l'invio per ogni carattere
		s++;
    }
}

int uart_available(void) {
    return rx_ready;
}


