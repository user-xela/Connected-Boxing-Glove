/*
 * uart2/src/uart2_init.c
 * uart2 configuration
 * author 
 */

#include <uart2/include/uart2.h>

//extern uInt8_t uart2_rx_ready;
extern circ_buffer_t uart2_rx;

void uart2_init(uInt32_t bdrate)
{
    uInt32_t    bdrate_calcul;
    uInt8_t     flush;
    
    /* pin select
     * TX2 init - datasheet 27.1.1.7 and 17.2 
     * RX2 init - datasheet  27.1.2.8,  17.1 and 15.5.18
     */
    RC1PPS = 0x0B;  // TX2 output connected to RC1 pin
    RX2PPS = 0x10;  // RX2 input connected to RC0 pin
    ANSELCbits.ANSELC0 = 0; // ST and TTL RC0 input buffer enable
  
    /* baudrate */
    BAUDCON2bits.BRG16=1;   // baud rate 16 bits mode   
    TXSTA2bits.BRGH  = 1;   // hight speed baud rate
    bdrate_calcul = (uInt32_t) (CPU_FREQ_HZ / ((uInt32_t) 4 * bdrate)) - 1 ; 
    SP2BRG   = (uInt8_t) bdrate_calcul;  // warning - SP1BRG before SP1BRGH init    
    SP2BRGH  = (uInt8_t) (bdrate_calcul >> 8);     
           
    /* receiver transmitter module */
    TXSTA2bits.SYNC  = 0;    // asynchronous mode
    TXSTA2bits.TX9   = 0;    // 8 bit transmission
    TXSTA2bits.TXEN  = 1;    // enable transmitter
    
    RCSTA2bits.RX9   = 0;    // 8 bit reception
    RCSTA2bits.CREN  = 1;    // enable receiver
    RCSTA2bits.SPEN  = 1;    // enable module
            
    /* rx interrupt */
    PIE3bits.TX2IE = 0;
    flush = RC2REG;     // flush reception fifo buffer
    flush = RC2REG;	 
    PIE3bits.RC2IE = 1;
    IPR3bits.RC2IP = 0;    

    /* software receiving buffer init */
    /* one byte buffer */
//    uart2_rx_ready = FALSE;
    
    /* circular buffer */
    uart2_rx.nb_elt = 0;
    uart2_rx.idx_write = 0;
    uart2_rx.idx_read = 0;  
}
