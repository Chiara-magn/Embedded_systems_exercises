
#include "config.h"

// ------------- 
#include "timer.h"
#include "UART_handler.h"
#include "button_handler.h"
#include "led_handler.h"
// -------------


void setup() {
    ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = ANSELG = 0x0000;

    uart_init();
    buttons_init();
    led_init();
    timer_init();
}
 
int missed_deadlines = 0; //ok nel main

int main() {

	setup(); 

    tmr_setup_period(TIMER1, 10);
    tmr_setup_period(TIMER3,200);
    
while(1) {
    
    // 7ms function
    tmr_wait_ms(TIMER2, 7);
    
	
// Blink led 2, nuova versione
	if (blink_enabled) {	//blink enabled è inizializzato in led_handler.c    
		if (num_int >= 2) {    
			led_toggle_ld2();  // funzione nel modulo LED
			num_int = 0;
		}
	}
	
// UART, nuova versione
    if (rx_ready) {
        rx_ready = 0;

        char b0 = rx_buffer[0];
        char b1 = rx_buffer[1];
        char b2 = rx_buffer[2];

        if (b0 == 'L' && b1 == 'D' && b2 == '1') {
			led_toggle_ld1(); 
        }
        if (b0 == 'L' && b1 == 'D' && b2 == '2') {
            blink_enabled = !blink_enabled;    
        }
    }
	
	// Button 2, nuova versione 
	// Comando C= (pulsante T2)	
	if (button_t2_pressed()) {
		char msg[8];
		sprintf(msg, "C=%d", total_chars);
		uart_send_string(msg); 
	}
	
	// Button 3, nuova versione
	// Comando D= (pulsante T3)
	if (button_t3_pressed()) {
		char msg[8];
		sprintf(msg, "D=%d", missed_deadlines);
		uart_send_string(msg);
	}
	
	missed_deadlines += tmr_wait_period(TIMER1);

	}
}


// TIMER1 viene usato in modalità polling per generare il ciclo a 100 Hz.
// NON dobbiamo abilitare l'interrupt di TIMER1, perché la sua ISR
// azzererebbe il flag T1IF prima che il main lo legga.
// Risultato: tmr_wait_period(TIMER1) rimarrebbe bloccato per sempre.
// Quindi TIMER1 deve funzionare SOLO in polling, senza interrupt abilitato.