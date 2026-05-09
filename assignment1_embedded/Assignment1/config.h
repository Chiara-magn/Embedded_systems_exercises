#ifndef CONFIG_H
#define CONFIG_H

#include "xc.h"
#include "stdlib.h"
#include "stdio.h"

// UART1 pin remapping
#define UART1_RX_RPIN   75   // UART1 RX mapped to RPI75 (RD11, input)
#define UART1_TX_RPIN   64   // UART1 TX mapped to RP64  (RD0,  output)

// SPI1 pin remapping
#define SPI1_MISO_RPIN   17   // MISO (SDI1) mapped to RPI17 (RA1,  input)
#define SPI1_MOSI_RPIN   109  // MOSI (SDO1) mapped to RP109 (RF13, output)
#define SPI1_SCK_RPIN    108  // SCK1        mapped to RP108 (RF12, output)

// Chip Select

#define ACC_CS_LAT     LATBbits.LATB3
#define ACC_CS_TRIS    TRISBbits.TRISB3 
#define ACC_CHIP_ID    0xFA   // letto 0xFD
 
#define GYR_CS_LAT     LATBbits.LATB4
#define GYR_CS_TRIS    TRISBbits.TRISB4 
#define GYR_CHIP_ID    0x0F   // letto 0x07

#define MAG_CS_LAT     LATDbits.LATD6 
#define MAG_CS_TRIS    TRISDbits.TRISD6 
#define MAG_CHIP_ID    0x32   // letto 0xFF

/* #define MAG_CS_LAT     LATBbits.LATB0 // possibile RB0 
#define MAG_CS_TRIS    TRISBbits.TRISB0
#define MAG_CHIP_ID    0x32   // letto 0xFF */

// LED
#define LD1_LAT     LATAbits.LATA0       // LD1 connected to RA0       
#define LD1_TRIS    TRISAbits.TRISA0

#define LD2_LAT     LATGbits.LATG9       // LD2 connected to RG9        
#define LD2_TRIS    TRISGbits.TRISG9

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