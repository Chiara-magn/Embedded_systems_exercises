
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
		
		
		// Blink led 2
		if (blink_enabled) {	 
			if (num_int >= 2) {    
				led_toggle_ld2();  
				num_int = 0;
			}
		}
		
		// uart circular buffer
		while (uart_available()) {

			char c = uart_read_char();
			if (c == 0) continue;

			static char b0 = 0, b1 = 0, b2 = 0;

			b0 = b1;
			b1 = b2;
			b2 = c;

			if (b0 == 'L' && b1 == 'D' && b2 == '1') {
				led_toggle_ld1();
			}

			if (b0 == 'L' && b1 == 'D' && b2 == '2') {
				blink_enabled = !blink_enabled;
			}
		}

		// Button 2
		// Command C= T2 button	(UART chars)
		if (button_t2_pressed()) {
			char msg[8];
			sprintf(msg, "C=%d", total_chars);
			uart_send_string(msg); 
		}
		
		// Button 3
		// Command D= T3 button (missed deadlines)
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