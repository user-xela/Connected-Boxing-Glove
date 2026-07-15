/*
 * uart1/src/uart1_init.c
 * uart1 configuration
 * author 
 */

#include <uart1/include/uart1.h>

//extern uInt8_t uart1_rx_ready;
extern circ_buffer_t uart1_rx;

void uart1_init(uInt32_t bdrate)
{
    uInt32_t    bdrate_calcul;
    uInt8_t     flush;
    
    /* pin select
     * TX1 init - datasheet 27.1.1.7 and 17.2 
     * RX1 init - datasheet  27.1.2.8,  17.1 and 15.5.18
     */
    RC0PPS = 0x09;  // TX1 output connected to RC0 pin
    RX1PPS = 0x11;  // RX1 input connected to RC1 pin
    ANSELCbits.ANSELC1 = 0; // ST and TTL RC7 input buffer enable
  
    /* baudrate */
    BAUDCON1bits.BRG16 =1;   // baud rate 16 bits mode   
    TXSTA1bits.BRGH  = 1;   // hight speed baud rate
    bdrate_calcul = (uInt32_t) (CPU_FREQ_HZ / ((uInt32_t) 4 * bdrate)) - 1 ;
    SP1BRG   = (uInt8_t) bdrate_calcul;  // warning - SP1BRG before SP1BRGH init
    SP1BRGH  = (uInt8_t) (bdrate_calcul >> 8);             
    
    /* receiver transmitter module */
    TXSTA1bits.SYNC  = 0;    // asynchronous mode
    TXSTA1bits.TX9   = 0;    // 8 bit transmission
    TXSTA1bits.TXEN  = 1;    // enable transmitter
    
    RCSTA1bits.RX9   = 0;    // 8 bit reception
    RCSTA1bits.CREN  = 1;    // enable receiver
    RCSTA1bits.SPEN  = 1;    // enable module
            
    /* rx interrupt */
    PIE3bits.TX1IE = 0;
    flush = RC1REG;     // flush reception fifo buffer
    flush = RC1REG;	 
    PIE3bits.RC1IE = 1;
    IPR3bits.RC1IP = 0;    

    /* software receiving buffer init */
    /* one byte buffer */
    //uart1_rx_ready = FALSE;
    
    /* circular buffer */
    uart1_rx.nb_elt = 0;
    uart1_rx.idx_write = 0;
    uart1_rx.idx_read = 0;  
}
