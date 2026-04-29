#include "config.h"
#include "SPI_handler.h"

void spi_init_pins(void)
{
    // SDI1 = MISO
    TRISAbits.TRISA1 = 1;
    RPINR20bits.SDI1R = SPI1_MISO_RPIN;

    // SDO1 = MOSI
    TRISFbits.TRISF13 = 0;
    RPOR12bits.RP109R = 0b000101; // MOSI code function

    // SCK1
    TRISFbits.TRISF12 = 0;
    RPOR11bits.RP108R = 0b000110; // SCK1 output

    // Chip select
    ACC_CS_TRIS = 0; 
    GYR_CS_TRIS = 0; 
    MAG_CS_TRIS = 0; 

    ACC_CS_LAT = 1;
    GYR_CS_LAT = 1;
    MAG_CS_LAT = 1;

    SPI1STATbits.SPIEN = 0;   // disable SPI

    SPI1CON1bits.MSTEN = 1;   // master mode
    SPI1CON1bits.MODE16 = 0;  // 8-bit mode

    SPI1CON1bits.CKP = 0;     // clock idle low
    SPI1CON1bits.CKE = 1;     // data changes on rising edge
    SPI1CON1bits.SMP = 0;     // sample in middle

    SPI1CON1bits.SPRE = 0b110; // secondary prescaler 2:1
    SPI1CON1bits.PPRE = 0b11;  // primary prescaler 1:1

    SPI1STATbits.SPIROV = 0;  // clear overflow
    SPI1STATbits.SPIEN = 1;   // enable SPI
}

uint8_t spi_write(uint8_t data)
{
    while (SPI1STATbits.SPITBF == 1);
    SPI1BUF = data;
    while (SPI1STATbits.SPIRBF == 0);
    return SPI1BUF;
}

uint8_t spi_read_register(uint8_t addr)
{
    spi_write(addr | 0x80);
    return spi_write(0x00);
}

void spi_write_register(uint8_t addr, uint8_t value)
{
    spi_write(addr & 0x7F);
    spi_write(value);
}

/*
Se vuoi scrivere un registro con SPI, devi mandare due byte:
il byte dell’indirizzo seguito dal byte del valore
E per mandare un byte SPI, usi sempre la stessa funzione spi_write()
*/
// spi_write(0x4B);
// spi_write(0x01); // metto il magnetometro in sleep mode

// spi_write(0x4B);   // indirizzo del registro (MSB=0 → write)
// spi_write(0x00);   // active mode

 //SPI1BUF = 0x4B // non è necessario fare or con  0x00, visto che 0x4B è gia piu piccolo di 0x80 e non rischia di mettere a 1 il MSB;
 //SPI1BUF = 0x01 | 0x00;?

 /* esempio del prof
MAG_CS = 0; // change to the PORT connected to the chip select
read_addr = 0x40;
while (SPI1STATbits.SPITBF == 1);
SPI1BUF = read_addr | 0x80; // setting the MSB to 1    0x80 = 1000 0000 = MSB 1 = lettura
while (SPI1STATbits.SPIRBF == 0);
trash = SPI1BUF; // read to prevent buffer overrun. Not useful but has to be red because otherwise the next interaction would be an overflow
while (SPI1STATbits.SPITBF == 1);
SPI1BUF = 0x00; // clocking out zeros so that the other chip can send the value
while (SPI1STATbits.SPIRBF == 0);
value_from_chip = SPI1BUF; // get the value from the register
MAG_CS = 1;
 */
