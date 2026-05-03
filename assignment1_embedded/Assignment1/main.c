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

// #include <math.h>
#include <stdio.h>
#include "timer.h"
#include "UART_handler.h"
#include "led_handler.h"
#include "SPI_handler.h"
#include "IMU_handler.h"


int main(){

	led_init();
    uart_init();
    spi_init_pins();
    imu_setup();
    imu_init();
    tmr_setup_period(TIMER1,10); // basta un timer per gestire tutto con il count
	// 10 ms -> 100Hz
	accel_data_t accel;
	angle_data_t angles;
	int count = 0;
	int missed_deadlines = 0;

    while (1) {

        //  7 ms function 
        tmr_wait_ms(TIMER2, 7);

        //  led blink (500 ms)
        if (count % 50 == 0) led_toggle_ld2();
		// meglio di num_int perche usa un timer in meno 
		// quindi meno interrupt inutili

		// ogni 2 count (50 Hz)
		if (count % 2 == 0) {
			imu_read_acc(&accel);
			imu_roll_pitch(&accel, &angles);  
		}


        // Invio $ACC a yy Hz
        int hz = uart_get_hz();
        if (hz > 0) {
            int period = 100 / hz;  // tick tra un invio e l'altro
            if (count % period == 0) {
                char msg[48];
                sprintf(msg, "$ACC,%d,%d,%d*\r\n", accel.x, accel.y, accel.z);
                uart_send_string(msg);
            }
        }

        // Invio $ANG a 5 Hz fissi (ogni 20 tick = 200 ms)
        if (count % 20 == 0) {
            char msg[48];
            sprintf(msg, "$ANG,%.2f,%.2f*\r\n", angles.roll, angles.pitch);
            uart_send_string(msg);
        }

        // Parsing comandi UART
        if (uart_command_buffer()) {
            uart_validate_command();
        }

        count++;
        missed_deadlines += tmr_wait_period(TIMER1);
    }
/* 
		if (uart_command_buffer()) {
			uart_validate_command();
		}



		// invio ANG a 5 Hz (100 / 20) = 5 Hz
		if (count % 20 == 0) {
			char msg[48];
			sprintf(msg, "$ANG,%.2f,%.2f*\r\n", angles.roll, angles.pitch);
			uart_send_string(msg);
		}

			if (uart_get_hz() != 0) {
				// leggi IMU e invia dati
				accel_data_t accel;
				imu_read_acc(&accel);  // passa il puntatore alla struct
			
				char msg[64];
				sprintf(msg, "$ACC,%d,%d,%d*", accel.x, accel.y, accel.z);
				uart_send_string(msg);
 				float ax = accel.x;
				float ay = accel.y;
				float az = accel.z; */
/* 			}

			tmr_wait_period(TIMER2);

        //  Aspetto la fine del periodo (10 ms totali)
        missed_deadlines += tmr_wait_period(TIMER1);  */
   // }
    return 0;
}
