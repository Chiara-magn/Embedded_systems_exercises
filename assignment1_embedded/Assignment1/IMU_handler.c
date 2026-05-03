#include "IMU_handler.h"
#include "SPI_handler.h"
#include "UART_handler.h"
#include "config.h"
#include "timer.h"

void imu_init(void) {

    uart_send_string("IMU INIT START\r\n");

    ACC_CS_LAT = 1;
    GYR_CS_LAT = 1;
    MAG_CS_LAT = 1;

    // check accelerometer ID from datasheet 1111 1010 -> 0xFA
    uint8_t ACC_ID = imu_read_chip_id(IMU_ACC);
    if (ACC_ID != ACC_CHIP_ID) {
        uart_send_string("Incorrect accelerometer Chip ID\r\n");
        return;
    }

    // check gyroscope ID from datasheet 0000 1111 -> 0x0F
    uint8_t GYR_ID = imu_read_chip_id(IMU_GYR);
    if (GYR_ID != GYR_CHIP_ID) {
        uart_send_string("Incorrect gyroscope Chip ID\r\n");
        return;
    }

    // check magnetometer ID from datasheet -> 0x32
    uint8_t MAG_ID = imu_read_chip_id(IMU_MAG);
    if (MAG_ID != MAG_CHIP_ID) {
        uart_send_string("Incorrect magnetometer Chip ID\r\n");
        return;
    }

    // Se sono tutti corretti, posso procedere
    uart_send_string("All Chip IDs are CORRECT!\r\n");

    imu_set_active(IMU_ACC);
    imu_set_active(IMU_GYR);
    imu_set_active(IMU_MAG);

    imu_set_bandwidth(15);  // 1000 Hz default
}

static void imu_select(imu_device_t dev)  // per essere sicuri che non siano mai attivi 2 insieme
{
    // prima disattiva tutti
    ACC_CS_LAT = 1;
    GYR_CS_LAT = 1;
    MAG_CS_LAT = 1;

    // poi attiva solo uno
    switch (dev) {
        case IMU_ACC: ACC_CS_LAT = 0; break;
        case IMU_GYR: GYR_CS_LAT = 0; break;
        case IMU_MAG: MAG_CS_LAT = 0; break;
    }
}

void imu_setup(void) {
    // Bosch BMX055 SPI protocol require idle LOW
    SPI1STATbits.SPIEN = 0;     // disable SPI to change settings
    SPI1CON1bits.CKE = 1;       // Output data changes on transition from active to idle
    SPI1CON1bits.CKP = 0;       // Idle state for clock is a low level
    SPI1STATbits.SPIEN = 1;     // re-enable SPI
    tmr_wait_ms(TIMER1, 100);
}

void imu_write_register(imu_device_t dev, uint8_t reg, uint8_t value)
{
    imu_select(dev);
    spi_write(reg & 0x7F);   // write -> MSB = 0
    spi_write(value);
    // deselect
    ACC_CS_LAT = 1;
    GYR_CS_LAT = 1;
    MAG_CS_LAT = 1;
}

uint8_t imu_read_register(imu_device_t dev, uint8_t reg)
{
    imu_select(dev);
    spi_write(reg | 0x80);   // MSB=1 -> lettura
    uint8_t value = spi_write(0x00);
    // deselect
    ACC_CS_LAT = 1;
    GYR_CS_LAT = 1;
    MAG_CS_LAT = 1;
    return value;
}

uint8_t imu_read_chip_id(imu_device_t dev)
{
    uint8_t id;
    if (dev == IMU_MAG)
        id = imu_read_register(dev, 0x40);
    else
        id = imu_read_register(dev, 0x00);
    return id;
}

void imu_set_sleep(imu_device_t dev)
{
    imu_write_register(dev, 0x4B, 0x01);
}

void imu_set_active(imu_device_t dev)
{
    imu_write_register(dev, 0x4C, 0x00);
}

// Exercise 2
int16_t imu_read_mag_x(void)
{
    uint8_t lsb = imu_read_register(IMU_MAG, 0x42);
    uint8_t msb = imu_read_register(IMU_MAG, 0x43);
    lsb &= 0xF8;  // mask dei 3 bit inutili
    int16_t raw = ((int16_t)msb << 8) | lsb;
    return raw >> 3;  // 13 bit utili -> shift di 3
}

// Assignment1 functions

void imu_read_acc(accel_data_t *data)
{
    uint8_t lsb, msb;

    // x axis
    lsb = imu_read_register(IMU_ACC, 0x02);
    msb = imu_read_register(IMU_ACC, 0x03);
    lsb &= 0xF0;  // mask per 12 bit
    data->x = ((int16_t)msb << 8 | lsb) >> 4;
    // shift di 4 perche accelerometro fornisce 12 bit (da datasheet)

    // y axis
    lsb = imu_read_register(IMU_ACC, 0x04);
    msb = imu_read_register(IMU_ACC, 0x05);
    lsb &= 0xF0;
    data->y = ((int16_t)msb << 8 | lsb) >> 4;

    // z axis
    lsb = imu_read_register(IMU_ACC, 0x06);
    msb = imu_read_register(IMU_ACC, 0x07);
    lsb &= 0xF0;
    data->z = ((int16_t)msb << 8 | lsb) >> 4;
}

void imu_set_bandwidth(uint8_t bandwidth_value)
{
    // Registro 0x10 = ACC_BW, datasheet pag.58
    // valori: 8=7.81Hz, 9=15.63Hz, 10=31.25Hz, 11=62.5Hz,
    //         12=125Hz, 13=250Hz, 14=500Hz, 15=1000Hz
    imu_write_register(IMU_ACC, 0x10, bandwidth_value);
}

// Conversione angoli roll e pitch
// NOTA: puntatori per evitare copie inutili in memoria
void imu_roll_pitch(const accel_data_t *acc, angle_data_t *angles)
{
    float ax = (float)acc->x;
    float ay = (float)acc->y;
    float az = (float)acc->z;

    angles->roll  = atan2f(ay, az) * RAD_TO_DEG;
    angles->pitch = atan2f(-ax, sqrtf(ay*ay + az*az)) * RAD_TO_DEG;
}




////////////////////////////////////////////






