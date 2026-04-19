#ifndef CONFIG_H
#define CONFIG_H

#include "xc.h"
#include "stdlib.h"
#include "stdio.h"


// UART1
#define UART1_RX_RPIN   75
#define UART1_TX_RPIN   64

// LED
#define LD1_LAT     LATAbits.LATA0
#define LD1_TRIS    TRISAbits.TRISA0

#define LD2_LAT     LATGbits.LATG9
#define LD2_TRIS    TRISGbits.TRISG9

// Buttons (INT1 e INT2)
#define BTN_T3_TRIS   TRISEbits.TRISE9
#define BTN_T3_RPIN   89

#define BTN_T2_TRIS   TRISEbits.TRISE8
#define BTN_T2_RPIN   88

#endif	


