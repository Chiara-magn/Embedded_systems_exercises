#include "config.h"
#include "UART_handler.h"

volatile int total_chars = 0; 

// circular buffer global variables
volatile char uart_buffer[UART_BUFFER_SIZE];
volatile int uart_head = 0;
volatile int uart_tail = 0;

// UART initialization function
void uart_init(void){
	
    TRISDbits.TRISD0 = 0;               // output
    TRISDbits.TRISD11 = 1;              // input
    
    RPINR18bits.U1RXR = UART1_RX_RPIN;  // metti UART1 in input sul pin fisico RD11 = RPI75
    RPOR0bits.RP64R = 1;                // metti in output sul pin RD0 = RP64 quello che ricevi da UART
    
    U1BRG = 468 ;                       //(72000000/16*9600)-1
    // Abilita UART1
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;
    
    U1STAbits.URXISEL = 0;              //Interrupt is set on every received character
    IFS0bits.U1RXIF = 0;
    IEC0bits.U1RXIE = 1;
	
}


// --- UART ISR ---
void __attribute__((interrupt, no_auto_psv))
    _U1RXInterrupt(void) {

    IFS0bits.U1RXIF = 0;

    char c = U1RXREG;
    total_chars++;

    int next = (uart_head + 1) % UART_BUFFER_SIZE;

    if (next != uart_tail) {
        uart_buffer[uart_head] = c;
        uart_head = next;
    }
    // se pieno scarta carattere 
}
// --- ---

void uart_send_char(char c) { 
    while (U1STAbits.UTXBF);   // aspetta che il buffer TX sia libero
    U1TXREG = c;               // invio carattere
}

void uart_send_string(const char *s) {  // serve per scorrere la stringa
    while (*s) {                        // finche s punta a caratteri, *s != 0, quando punta a \0, *s vale 0 ed esce dal while
		uart_send_char(*s);             // richiama l'invio per ogni carattere
		s++;
    }
}

// circular buffer read functions
int uart_available(void) {
    return (uart_head != uart_tail);
}

char uart_read_char(void) {
    if (uart_head == uart_tail)
        return 0; // buffer vuoto

    char c = uart_buffer[uart_tail];
    uart_tail = (uart_tail + 1) % UART_BUFFER_SIZE;
    return c;
}
//



