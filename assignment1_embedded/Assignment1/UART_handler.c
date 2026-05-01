#include "config.h"
#include "UART_handler.h"

volatile int total_chars = 0; 

// circular buffer global variables
static volatile char uart_buffer[UART_BUFFER_SIZE];
static volatile int uart_head = 0;
static volatile int uart_tail = 0;

// Assigmnent1 variables
static char command_buffer[UART_COMMAND_BUFFER_SZ];
static uint8_t i = 0; // counter parsing
static int current_hz = 10; // default 10 Hz
// stati per parsing
typedef enum {
    STATE_WAIT_START,   // Aspetto '$'
    STATE_CMD_TYPE,     // Aspetto B o H
    STATE_B,            // Aspetto 'B' 
    STATE_H,            // Aspetto 'H'
    STATE_COMMA,        // Aspetto ','
    STATE_DATA1,        // Prima cifra
    STATE_DATA2,        // Seconda cifra
    STATE_END           // Aspetto '*'
} parser_state_t;
static parser_state_t state = STATE_WAIT_START;
// nota: devo dividere i due casi per evitare di ottenere BZ o HW


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

bool uart_command_buffer(void){  // correttezza stringhe
    bool string_ready = false;

    while(uart_available()){
        char c = uart_read_char();

        switch (state){

            case STATE_WAIT_START:
                if (c == '$'){
                    state = STATE_CMD_TYPE;
                    i = 0;
                    command_buffer[i] = c;
                    i++;
                }    
            break;
            
            case STATE_CMD_TYPE:
                if (c == 'B'){
                    state = STATE_B;
                    command_buffer[i] = c;
                    i++;
                } 
                else if (c == 'H'){
                    state = STATE_H;
                    command_buffer[i] = c;
                    i++;
                } 
                else {
                    state = STATE_WAIT_START;
                }
            break;

            case STATE_B:
                if (c == 'W') {
                    command_buffer[i] = c;
                    i++;
                    state = STATE_COMMA;
                } 
                else {
                    state = STATE_WAIT_START;
                }
            break;

            case STATE_H:
                if (c == 'Z') {
                    command_buffer[i] = c;
                    i++;
                    state = STATE_COMMA;
                } 
                else {
                    state = STATE_WAIT_START;
                }
            break;

            case STATE_COMMA: 
                if (c == ',') {
                    command_buffer[i] = c;
                    i++;
                    state = STATE_DATA1;
                } 
                else {
                    state = STATE_WAIT_START;
                }
            break;

            case STATE_DATA1: // controllo che siano cifre
                if (c >= '0' && c <= '9') {
                    command_buffer[i] = c;
                    i++;
                    state = STATE_DATA2;
                } 
                else {
                    state = STATE_WAIT_START;
                }
            break;

            case STATE_DATA2:
                if (c >= '0' && c <= '9') {
                    command_buffer[i] = c;
                    i++;
                    state = STATE_END;
                } 
                else {
                    state = STATE_WAIT_START;
                }
            break;

            case STATE_END:
                if (c == '*') {
                    command_buffer[i] = c;
                    i++;
                    command_buffer[i] = '\0';
                    string_ready = true;
                }
                state = STATE_WAIT_START;
            break;
        }

        // Protezione overflow
        if (i >= UART_COMMAND_BUFFER_SZ - 1) {
            i = 0;
            state = STATE_WAIT_START;
        }

        if (string_ready) break; 
    }

    return string_ready;
}

bool uart_validate_command(void) { // controllo range dati

    int tens  = command_buffer[4] - '0'; // -'0' serve per convertire facilmente in ASCII 
    int units = command_buffer[5] - '0'; // perche '0' vale 48 e 1 49 ecc, 49-48 = 1;

    int data = tens * 10 + units; 

    if (command_buffer[1] == 'B'){ // se B allora controllo bandwith
        if (data <8 || data > 15){
            uart_send_string("$ERR,1*");
            return false;}
    }
    if (command_buffer[1] == 'H'){ // se H controllo HZ
        if (data != 0 && data != 1 && data != 2 && data != 5 && data != 10){
            uart_send_string("$ERR,2*");
            return false;}
            current_hz = data;
    }
    return true;
}

// Serve per sapere gli hz correnti senza avere una globale 
int uart_get_hz(void) {
    return current_hz;
}

