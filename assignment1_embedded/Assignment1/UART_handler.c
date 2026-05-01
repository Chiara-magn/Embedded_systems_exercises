#include "config.h"
#include "UART_handler.h"

volatile int total_chars = 0; 

// circular buffer global variables
volatile char uart_buffer[UART_BUFFER_SIZE];
volatile int uart_head = 0;
volatile int uart_tail = 0;

// Assigmnent1 variables
char command_buffer[UART_COMMAND_BUFFER_SZ];

// UART initialization function
void uart_init(void){
	
    TRISDbits.TRISD0 = 0;               // output
    TRISDbits.TRISD11 = 1;              // input
    
    RPINR18bits.U1RXR = UART1_RX_RPIN;  // metti UART1 in input sul pin fisico RD11 = RPI75
    RPOR0bits.RP64R = 1;                // metti in output sul pin RD0 = RP64 quello che ricevi da UART
    
    U1STA = 0x00;                       // reset control and status register
    U1MODE = 0x00;                      // reset mode register
    U1BRG = 468 ;                       //(72000000/16*9600)-1
    // Abilita UART1
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;
    
    U1STAbits.URXISEL = 0;              //Interrupt is set on every received character
    IFS0bits.U1RXIF = 0;
    IEC0bits.U1RXIE = 1;
	
}

// --- UART ISR ---   // chiamata ogni volta che arriva un carattere
void __attribute__((interrupt, no_auto_psv))
    _U1RXInterrupt(void) {

    IFS0bits.U1RXIF = 0;

    char c = U1RXREG;
    total_chars++;

    int next = (uart_head + 1) % UART_BUFFER_SIZE;   /// avanza head e torna a 0 se buffer finito
 
    if (next != uart_tail) {             // buffer pieno se next == tail
        uart_buffer[uart_head] = c;      // se c'è spazio salva il carattere
        uart_head = next;
    }
    // altrimenti, se pieno scarta carattere 
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
    return (uart_head != uart_tail); // C'è qualche carattere da leggere
}

char uart_read_char(void) {
    if (uart_head == uart_tail) // Se sono uguali non ho caratteri da leggere
        return 0; // buffer vuoto

    char c = uart_buffer[uart_tail];  // prendo il carattere piu vecchio
    uart_tail = (uart_tail + 1) % UART_BUFFER_SIZE;   // uart tail avanza di 1 se array finito torna a 0 
    return c;      // (uart_tail+1) = UART_BUFFER_SIZE se siamo alla fine del buffer. quindi uart_tail+1 % BUFFERSIZE == 0
}
//

// Assignment1 functions

char uart_command_buffer(void){ ////  meglio fare direttamente il parsing qua
    int i = 0; 
    bool string_ready = false
    while(uart_available()){
        char c = uart_read_char();

            if (c == 0) continue; // no trasmissione
            if (c == '$'){ // inizio un nuovo comando perche è arrivato $
                i = 0;
                command_buffer[i] = c;
                i++;
            }
            else if(c == '*'){
                command_buffer[i] = c;
                command_buffer[i+1] = "/0";
                string_ready = true
                return;
            } // devo terminare la stringa perche è arrivato *
            else{ // comandi normali che non sono $ o *
                if (cmd_index < UART_COMMAND_BUFFER_SZ - 1) { // serve per assicurarsi di non scrivere fuori dal buffer
                    command_buffer[i] = c;
                    i++;
                }
            }
    }
}

