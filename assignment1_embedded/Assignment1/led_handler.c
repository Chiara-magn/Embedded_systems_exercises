#include "config.h"
#include "led_handler.h"

void led_init(void) {
	
	LD1_TRIS = 0;   // output led1
    LD1_LAT = 0;    // LED spento

    LD2_TRIS = 0;  //output led2
    LD2_LAT = 0;   // LED spento. vedi config.h per definizioni
	
}

void led_toggle_ld1(void) {
    LD1_LAT = !LD1_LAT;   // inverte lo stato led1
}

void led_toggle_ld2(void) {
    LD2_LAT = !LD2_LAT;  // inverte lo stato led2
}

void led_set_ld2(int state) {
    LD2_LAT = state;     // imposta nello stato richiesto
}

