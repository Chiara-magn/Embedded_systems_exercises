/**
 * @file main.c
 * @author facci
 * @date 2026-04-30
 * @brief Main function
 */
/* 
1/ Simulate an algorithm that needs 7 ms for its execution and needs to work at 100 Hz.
This is to emulate a real-world scenario.
2/ Make LD2 blink at 1 Hz (500 on, 500 off).
3/ Read characters from UART1. If a string $BW,xx* is received, the xx dictates the bandwidth of the accelerometer
 filter. Valid data for xx are 8 to 15. Invalid values (e.g., -1, 3.2, 18) should be discarded and a message 
 $ERR,1* should be sent on the UART. The initial bandwidth is 1000 Hz (value 15, see page 58). If a string $HZ,yy*
is received, the yy dictates the frequency of the data sent over the UART. Valid data for xx are 0, 1, 2, 5, 10.
A value of 0 disables the message. Invalid values should be discarded and a message $ERR,1* should be sent on the
UART. The initial frequency is 10 Hz.
4/ Acquire the three accelerometer axes at 50 Hz.
5/ Compute the roll and pitch angles
6/ Send it to the UART at yy Hz using the protocol $ACC,x,y,z*.
7/ Send the computed angles at 5 Hz using the message $ANG,x,y*, where x is the roll angle in degrees 
and y is the pitch angle in degrees.
 */

#include <math.h>
#include "timer.h"
#include "UART_handler.h"
#include "led_handler.h"
#include "SPI_handler.h"
#include "IMU_handler.h"


#define RAD_TO_DEG (180.0f / M_PI)

/* void compute_pitch_roll(float ax, float ay, float az,
                        float *pitch_deg, float *roll_deg)
{
    float roll  = atan2f(ay, az);
    float pitch = atan2f(-ax, sqrtf(ay*ay + az*az));

    *roll_deg  = roll  * RAD_TO_DEG;
    *pitch_deg = pitch * RAD_TO_DEG;
}
 */
int main(){

    tmr_setup_period(TIMER1, 100);   // 100 Hz  periodo = 10 ms
    tmr_setup_period(TIMER3,100); // interrupt led 500 ms
    while (1) {

        //  Simulo la funzione che dura 7 ms
        tmr_wait_ms(TIMER2, 7);

        //  Blink del led (500 ms)
		if (blink_enabled) {	 
			if (num_int >= 5) {    // 5 per aspettare 5 interrupt da 100ms
				led_toggle_ld2();  
				num_int = 0;
			}
		}

		if (uart_command_buffer()) {
			uart_validate_command();
			}

			if (uart_get_hz() != 0) {
				// leggi IMU e invia dati
				accel_data_t accel;
				imu_read_acc(&accel);  // passa il puntatore alla struct
			
				char msg[64];
				sprintf(msg, "$ACC,%d,%d,%d*", accel.x, accel.y, accel.z);
				uart_send_string(msg);
/* 				float ax = accel.x;
				float ay = accel.y;
				float az = accel.z; */
			}

			tmr_wait_period(TIMER2);

        //  Aspetto la fine del periodo (10 ms totali)
        missed_deadlines += tmr_wait_period(TIMER1);
    }
    return 0;
}
