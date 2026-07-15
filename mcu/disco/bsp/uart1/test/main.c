/*
 * test program for uart1 library
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
    uart1_isr_process ();  
}

void main(void)
{
    uInt8_t tmp, str_tmp[APP_BUFFER_SIZE];
    
    /* system init*/
    uart1_init(UART1_BAUD_RATE);
    sys_interrupt_enable();
    
    /* test application */
    //uart1_puts("\r\nHello World Bro's\n\r");
   
    while (1) {
        uart1_puts("DUB");
        
        /* test for caracter receiving */
//        if(uart1_getc(&tmp, UART1_ECHO)){
//          uart1_putc('\n');
//          uart1_putc('\r');        
//        }

//        /* test for string receiving */
//        if (uart1_gets(str_tmp, APP_BUFFER_SIZE, UART1_ECHO_OFF)) {
//            uart1_puts(str_tmp); 
//            uart1_puts("\r\n"); 
//        }
    }      
}
