
#include "stdlib.h"
#include "stdio.h"
#include "SPI_handler.h"
#include "UART_handler.h"
#include "IMU_handler.h"
#include "timer.h"
#include "xc.h"


int main(void) {
    
    ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = ANSELG = 0x0000;
    INTCON2bits.GIE = 1;
    
    timer_init();
    spi_init_pins();
    uart_init();
    imu_setup();
    imu_init();

    // switch to Sleep mode 
    imu_set_sleep(IMU_MAG);
    //wait 100 ms
    tmr_wait_ms(TIMER1,100);
    // switch to Active mode
    imu_set_active(IMU_MAG);
    //wait 100 ms
    tmr_wait_ms(TIMER1,100);

    // Acquire the x-axis of the magnetometer and send it to the 
    // UART at 10 Hz using the protocol $MAGX=xxx*, where xxx is the value.

    tmr_setup_period(TIMER2, 100);
     
    while(1)
    {
        // Reading magnetometer x axis
        int16_t X = imu_read_mag_x();

        //  ASCII conversion
        char msg[32];
        sprintf(msg, "$MAGX=%d*", X);

        // Sending via UART
        uart_send_string(msg);

        // Waiting 100 ms (10 Hz)
        tmr_wait_period(TIMER2);
    }

    return 0;
}

