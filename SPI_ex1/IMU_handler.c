#include "IMU_handler.h"
#include "SPI_handler.h"
#include "UART_handler.h"
#include "config.h"
#include "timer.h"

 void imu_init(){

    uart_send_string("IMU INIT START\r\n");

    ACC_CS_LAT = 1;
    GYR_CS_LAT = 1;
    MAG_CS_LAT = 1;

    // check magnetometer ID from datasheet -> 0x32
    uint8_t MAG_ID = imu_read_chip_id(IMU_MAG);
    if (MAG_ID != MAG_CHIP_ID){
        uart_send_string("Incorrect magnetometer Chip ID");
        return;
    }
    else{ uart_send_string("Correct  magnetometer Chip ID!");} 

    imu_set_active(IMU_ACC);
    imu_set_active(IMU_GYR);
    imu_set_active(IMU_MAG);

} 

static void imu_select(imu_device_t dev)
{
    // prima disattiva tutti
    ACC_CS_LAT = 1;
    GYR_CS_LAT = 1;
    MAG_CS_LAT = 1;

    // poi attiva solo uno
    switch(dev)
    {
        case IMU_ACC: ACC_CS_LAT = 0; break;
        case IMU_GYR: GYR_CS_LAT = 0; break;
        case IMU_MAG: MAG_CS_LAT = 0; break;
    }
}

void imu_setup(void){
    // Bosch BMX055 SPI protocol require idle LOW 

    SPI1STATbits.SPIEN = 0;     // disable SPI to change settings

    SPI1CON1bits.CKE = 1; // Output data changes on transition from active to idle
    SPI1CON1bits.CKP = 0; // Idle state for clock is a low level

    SPI1STATbits.SPIEN = 1;     // re-enable SPI

    tmr_wait_ms(TIMER1, 100);
}


void imu_write_register(imu_device_t dev, uint8_t reg, uint8_t value)
{
    imu_select(dev);

    spi_write(reg & 0x7F);   // write → MSB = 0
    spi_write(value);

    // deselect
    ACC_CS_LAT = 1;
    GYR_CS_LAT = 1;
    MAG_CS_LAT = 1;
}

uint8_t imu_read_register(imu_device_t dev, uint8_t reg)
{
    imu_select(dev);

    // invio indirizzo con MSB=1
    spi_write(reg | 0x80);

    // spi_write(0x00);   // scarto il valore ricevuto */

    uint8_t value = spi_write(0x00);

    // deselezione
    ACC_CS_LAT = 1;
    GYR_CS_LAT = 1;
    MAG_CS_LAT = 1;

    return value; 
}


uint8_t imu_read_chip_id(imu_device_t dev)
{
    //imu_select(dev);
    char msg[64];
    uint8_t id; 
    if (dev == IMU_MAG){
    id = imu_read_register(dev, 0x40);}
    else{
    id = imu_read_register(dev, 0x00);}
    sprintf(msg, "ID=0x%02X\r\n", id);
    uart_send_string(msg);
    return id;  
    //return imu_read_register(dev, 0x40);
}


void imu_set_sleep(imu_device_t dev)
{
    imu_write_register(dev, 0x4B, 0x01);
}

void imu_set_active(imu_device_t dev)
{
    imu_write_register(dev, 0x4C, 0x00);
}

// exercise 2
int16_t imu_read_mag_x(void)
{
    //Leggi i due registri del magnetometro
    uint8_t lsb = imu_read_register(IMU_MAG, 0x42);
    uint8_t msb = imu_read_register(IMU_MAG, 0x43);

    // Mask dei 3 bit inutili
    lsb &= 0xF8;

    // Ricostruzione 16 bit
    int16_t raw = ((int16_t)msb << 8) | lsb;

    // Scaling (shift aritmetico)
    return raw >> 3;
}



/*     // check accelerometer ID  from datasheet 1111 1010 -> 0xFA
    uint8_t ACC_ID = imu_read_chip_id(IMU_ACC);
    if (ACC_ID != ACC_CHIP_ID){
        uart_send_string("Incorrect accelerometer Chip ID");
        return;
    }
    else{ uart_send_string("Correct accelerometer Chip ID!");} 
     // check gyroscope ID from datasheet 0000 1111 -> 0x0F
    uint8_t GYR_ID = imu_read_chip_id(IMU_GYR);
    if (GYR_ID != GYR_CHIP_ID){
        uart_send_string("Incorrect gyroscope Chip ID");
        return;
    }
    else{ uart_send_string("Correct  gyroscope Chip ID!");} 
*/