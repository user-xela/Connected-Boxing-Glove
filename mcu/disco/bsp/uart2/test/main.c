/*
 * test program for uart2 library
 * author 
 */

#include <bsplib.h>

#define APP_BUFFER_SIZE 77

void __interrupt(high_priority) isr_high (void)
{ 
    /* high ISR processing */					
}


void __interrupt(low_priority) isr_low (void)
{
    uart2_isr_process ();    				
}

void main(void)
{
    uInt8_t tmp, str_tmp[APP_BUFFER_SIZE];
    
    /* system init*/
    uart2_init(UART2_BAUD_RATE);
    sys_interrupt_enable();
    
    /* test application */
    uart2_puts("\r\nHello World Bro's\n\r");
    
    while (1) {
        /* test for caracter receiving */
//        if(uart2_getc(&tmp, UART2_ECHO)){
//          uart2_putc('\n');
//          uart2_putc('\r');        
//        }

        /* test for string receiving */
        if (uart2_gets(str_tmp, APP_BUFFER_SIZE, UART2_ECHO_OFF)) {
            uart2_puts(str_tmp); 
            uart2_puts("\r\n"); 
        }
    }      
}
