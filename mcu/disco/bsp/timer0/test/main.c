/*
 * test program for timer0 library
 * author 
 */
#include <bsplib.h>

void __interrupt(high_priority) isr_high (void)
{ 
    if( PIR0bits.TMR0IF )	{
        PIR0bits.TMR0IF = 0;
        timer0_reload(TIMER0_PERIOD);
        
        /* toggle led state */    
        #asm 
            btg LATA,4 
        #endasm
    }						
}


void __interrupt(low_priority) isr_low (void)
{
	/* low ISR processing */ 				
}


void main(void)
{
    /* system init */
    timer0_init(TIMER0_PERIOD);
    TRISAbits.TRISA4 = 0;
    LATAbits.LATA4 = 0;
    sys_interrupt_enable();
    
    while (1) {
        sleep();
    }   
}
