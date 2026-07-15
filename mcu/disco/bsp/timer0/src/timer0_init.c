/*
 * timer0/src/timer0_init.c
 * timer0 configuration
 * author 
 */

#include <timer0/include/timer0.h>

void timer0_init(uInt16_t count)
{
    uInt16_t    preload;
    
    /* Fosc/4 (16MHz) source, 16 bits mode, asynchronous mode
     * prescale 1:16, postcale 1:1
     * reference counting period 1us (only for Fosc = HFINTOSC 64MHz)
     */ 
    T0CON0 = 0b00010000;
    T0CON1 = 0b01010100;

    preload = (uInt16_t) 65535 - count;
    TMR0H = (uInt8_t) (preload >> 8);     
    TMR0L = (uInt8_t) preload;  
    
    /* sleep mode */
    CPUDOZEbits.IDLEN = 1;
    
    /* interrupt */
    PIR0bits.TMR0IF = 0;
    PIE0bits.TMR0IE = 1;
    IPR0bits.TMR0IP = 1;
   
    timer0_start();
}
