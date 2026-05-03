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
#include "config.h"
#include "timer.h"
#include "UART_handler.h"
#include "led_handler.h"
#include "SPI_handler.h"
#include "IMU_handler.h"

void setup() {
    ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = ANSELG = 0x0000;

	led_init();
    uart_init();
    spi_init_pins();
    imu_setup();
    imu_init();
    timer_init();
}


int main(void) {
    setup();

    accel_data_t accel = {0};
    angle_data_t angles = {0.0f, 0.0f};
    int count = 0;
    int missed_deadlines = 0;

    tmr_setup_period(TIMER1, 10);  // 100Hz

    while (1) {
        // 7 ms function
        tmr_wait_ms(TIMER2, 7);

        // led blink 500 ms
        if (count % 50 == 0) led_toggle_ld2();
        // meglio di num_int perche usa un timer in meno 
		// quindi meno interrupt inutili

        // 50 Hz read acc and compute angles
        if (count % 2 == 0) {
            imu_read_acc(&accel);
            imu_roll_pitch(&accel, &angles);
        }

        // Send $ACC at yy Hz
        int hz = uart_get_hz();
        if (hz > 0) {
            if (count % (100 / hz) == 0) {
                char msg[48];
                sprintf(msg, "$ACC,%d,%d,%d*\r\n", accel.x, accel.y, accel.z);
                uart_send_string(msg);
            }
        }

        // Send $ANG at 5 Hz  (20 count = 200 ms)
        if (count % 20 == 0) {
            char msg[48];
            sprintf(msg, "$ANG,%.2f,%.2f*\r\n", angles.roll, angles.pitch);
            uart_send_string(msg);
        }

        // Parsing  UART commands
        if (uart_command_buffer()) {
            uart_validate_command();
        }

        count++;
        missed_deadlines += tmr_wait_period(TIMER1);
    }
    return 0;
}

