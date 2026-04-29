#ifndef IMU_HANDLER_H
#define IMU_HANDLER_H
#include <stdint.h> 


typedef enum {
    IMU_ACC,
    IMU_GYR,
    IMU_MAG
} imu_device_t;

void imu_init(void);

void imu_write_register(imu_device_t dev, uint8_t reg, uint8_t value);
uint8_t imu_read_register(imu_device_t dev, uint8_t reg);
uint8_t imu_read_chip_id(imu_device_t dev);
int16_t imu_read_mag_x(void);

void imu_set_sleep(imu_device_t dev);
void imu_set_active(imu_device_t dev);

#endif
