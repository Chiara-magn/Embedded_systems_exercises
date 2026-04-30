/**
 * @file main.c
 * @author facci
 * @date 2026-04-30
 * @brief Main function
 */

#include "timer.h"
#include "UART_handler.h"
#include "button_handler.h"
#include "led_handler.h"

int main(){

    // Add your code here and press Ctrl + Shift + B to build
    tmr_setup_period(TIMER1, 100);   // 100 Hz → periodo = 10 ms

    while (1) {

        // --- Simulo la funzione che dura 7 ms ---
        tmr_wait_ms(TIMER2, 7);

        // --- Aspetto la fine del periodo (10 ms totali) ---
        if (tmr_wait_period(TIMER1)) {
            deadline_miss_count++;   // Hai sforato i 10 ms
        }
    }
    return 0;
}
