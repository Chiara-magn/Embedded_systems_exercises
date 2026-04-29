#ifndef CONFIG_H
#define CONFIG_H

#include "xc.h"
#include "stdlib.h"
#include "stdio.h"

// UART1
#define UART1_RX_RPIN   75
#define UART1_TX_RPIN   64

// SPI1 pin remapping
#define SPI1_MISO_RPIN   17     // RA1 = RPI17  
#define SPI1_MOSI_RPIN   109    // RF13 = RP109
#define SPI1_SCK_RPIN    108    // RF12 = RP108

// Chip Select
// Tutto l’IMU nello slot 1 → CS = RB3 prova

#define ACC_CS_LAT     LATBbits.LATB3
#define ACC_CS_TRIS    TRISBbits.TRISB3
#define ACC_CHIP_ID    0xFA   // letto 0xFD

#define GYR_CS_LAT     LATBbits.LATB4
#define GYR_CS_TRIS    TRISBbits.TRISB4
#define GYR_CHIP_ID    0x0F   // letto 0x07

#define MAG_CS_LAT     LATBbits.LATB0 // possibile RB0 
#define MAG_CS_TRIS    TRISBbits.TRISB0
#define MAG_CHIP_ID    0x32   // letto 0xFF

/* #define MAG_CS_LAT     LATDbits.LATD6 // possibile RB0 
#define MAG_CS_TRIS    TRISDbits.TRISD6
#define MAG_CHIP_ID    0x32   // letto 0xFF
 */
/* 

// accelerometer
#define ACC_CS_LAT     LATBbits.LATB3
#define ACC_CS_TRIS    TRISBbits.TRISB3
#define ACC_CHIP_ID    0xFA  
// gyroscope
#define GYR_CS_LAT     LATBbits.LATB4
#define GYR_CS_TRIS    TRISBbits.TRISB4
#define GYR_CHIP_ID    0x0F
// magnetometer
#define MAG_CS_LAT     LATDbits.LATD6
#define MAG_CS_TRIS    TRISDbits.TRISD6
#define  MAG_CHIP_ID   0x32 */

#endif

// nota per ricordare: 
// Fisicamente nella scheda ho i collegamenti segnati e vedo nella SPI1
// SCK/RF12  -> rimappable pin corrispondente = RP108 
// MISO/RA1  -> RPI17 -> 
// MOSI/RF13 -> RP109 
// SDA/RD9   -> RPI74
// SCL/RD10  -> RPI73


// Nella SPI2
// MISO/RG7 -> RPI119
// MOSI/RG8 -> RP120
// SCK/RG6  -> RP118
// SCL/RD10 -> RPI74
// SDA/RD9  -> RPI73